#include "Input.h"
#include "Input.h"
#include "Input.h"
#pragma once

#include <iostream>

void MVC::Input::pollEvents(sf::RenderWindow& window, int mode) {
   ParseKeyBoard parser; // parser

   std::optional<sf::Event> eventOpt;
   while ((eventOpt = window.pollEvent())) {
       const sf::Event& event = *eventOpt;



       if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
           InputToken token = parser.parseKey(static_cast<int>(keyPressed->scancode));
           addToken(token);
       }

       if (this->mode != 0) {
           if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>()) {
               sf::Vector2i mousePos = sf::Mouse::getPosition(window);
               if (auto pos = readBoard(mousePos)) {
                   boardClicks.push(*pos);
               }
           }

           if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
               sf::Vector2i mousePos = sf::Mouse::getPosition(window);
               if (auto pos = readBoard(mousePos)) {
                   boardClicks.push(*pos);
               }
           }
       }

       if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>()) {
           sf::Vector2i mousePos = sf::Mouse::getPosition(window); 
           for (auto& btn : buttons) {
               const auto& pos = btn->position_;
               const auto& size = btn->size_;
               if (mousePos.x >= pos.x && mousePos.x <= pos.x + size.x &&
                   mousePos.y >= pos.y && mousePos.y <= pos.y + size.y) {
                   btn->setPressed(true);
                   // Dodaj token w zale¿noœci od nazwy przycisku
                   if (btn->label_ == "START") addToken(InputToken::Start);
                   else if (btn->label_ == "STOP") addToken(InputToken::Stop);
                   else if (btn->label_ == "END") addToken(InputToken::End);
                   else if (btn->label_ == "TOGGLE DRAW") addToken(InputToken::ToggleDraw);
               }
               else {
                   btn->setPressed(false);
               }
           }
       }



       if (const auto* closed = event.getIf<sf::Event::Closed>()) {
           window.close();
       }
   }
}

std::optional<sf::Vector2i> MVC::Input::readBoard(sf::Vector2i& mousePos) {
    float cellSize = 10.f;
    int boardWidth = 100;   // Set this to your actual board width
    int boardHeight = 100;  // Set this to your actual board height

    int cellX = static_cast<int>(mousePos.x / cellSize);
    int cellY = static_cast<int>(mousePos.y / cellSize);

    if (cellX >= 0 && cellX < boardWidth && cellY >= 0 && cellY < boardHeight) {
        return sf::Vector2i(cellX, cellY);
    }
    return std::nullopt;
}

//void Board::draw(Render::Drawer& drawer) {
//    if (!container) return;
//
//    float cellSize = 10.0f;
//
//    for (int x = 0; x < container->getWidth(); ++x) {
//        for (int y = 0; y < container->getHeight(); ++y) {
//            bool alive = container->getCellState(x, y);
//
//            sf::Vector2f position(x * cellSize, y * cellSize);
//            sf::Vector2f size(cellSize, cellSize);
//            sf::Color color = alive ? sf::Color::Green : sf::Color::Black;
//
//            drawer.drawRect(position, size, color);
//        }
//    }
//}


void MVC::Input::addToken(const InputToken token) {
   Tokens.push(token);
}

InputToken MVC::Input::nextToken() {
   if (Tokens.empty())
       return InputToken::Unknown;
   InputToken token = Tokens.front();
   Tokens.pop();
   return token;
}

void MVC::Input::clear() {
   while (!Tokens.empty()) {
       Tokens.pop();
   }

   while (!boardClicks.empty()) {
       boardClicks.pop();
   }
}


sf::Vector2i MVC::Input::NextPos() {
    if (boardClicks.empty())
        return sf::Vector2i(-1, -1);
    sf::Vector2i pos = boardClicks.front();
    boardClicks.pop();
    return pos;
}