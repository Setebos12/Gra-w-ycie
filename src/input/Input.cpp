#pragma once

#include "Input.h"
#include <iostream>

void MVC::Input::pollEvents(sf::RenderWindow& window) {
   ParseKeyBoard parser; // parser

   std::optional<sf::Event> eventOpt;
   while ((eventOpt = window.pollEvent())) {
       const sf::Event& event = *eventOpt;

       if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
           InputToken token = parser.parseKey(static_cast<int>(keyPressed->scancode));
           addToken(token);
       }

       if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>()) {
           sf::Vector2i mousePos = sf::Mouse::getPosition(window); 
           std::cout << mousePos.x << std::endl;
           for (auto& btn : buttons) {
               const auto& pos = btn->position_;
               const auto& size = btn->size_;
               std::cout << btn->label_ << std::endl;
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
}