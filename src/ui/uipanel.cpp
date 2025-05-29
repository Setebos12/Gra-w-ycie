#include "uipanel.h"
#include <memory>
#include "../logic/Board.h"

Uipanel::Uipanel(std::shared_ptr<Util::Event<const std::string&, Util::Level>> logEvent,
    const sf::Vector2u& windowSize, int uiPanelWidth, int margin, int boardWidth,
    int boardHeight, std::unique_ptr<MVC::Logic>& logic, std::function<void()> endCallback)
    : MVC::GameObject("Uipanel", logEvent)
{
    board = std::make_unique<Board>("Game of Life Board", boardWidth, boardHeight, logEvent);

    float buttonX = static_cast<float>(windowSize.x - uiPanelWidth + margin);
    float buttonWidth = 180.f;
    float buttonHeight = 60.f;
    float buttonY = 500.f;

    using sf::Vector2f;
    hud = std::make_unique<Hud>("Hud", Vector2f{ buttonX, buttonY + 400.f });


    inputbuttons.emplace_back(std::make_unique<InputButton>(
        "ResetButton",
        Vector2f{ buttonX, 20.f },
        Vector2f{ buttonWidth, buttonHeight },
        "RESET",
        [this, &logic]() { this->board->resetBoard();
    this->hud->reset();
    logic->pause(); }
    ));

    inputbuttons.emplace_back(std::make_unique<InputButton>(
        "SpeedUpButton",
        Vector2f{ buttonX, buttonY - 140.f },
        Vector2f{ buttonWidth, buttonHeight },
        "SPEED UP",
        [&logic]() { logic->increaseSpeed(); }
    ));

    inputbuttons.emplace_back(std::make_unique<InputButton>(
        "SpeedDownButton",
        Vector2f{ buttonX, buttonY - 70.f },
        Vector2f{ buttonWidth, buttonHeight },
        "SPEED DOWN",
        [&logic]() { logic->decreaseSpeed(); }
    ));

    inputbuttons.emplace_back(std::make_unique<InputButton>(
        "StartButton",
        Vector2f{ buttonX, buttonY },
        Vector2f{ buttonWidth, buttonHeight },
        "START",
        [&logic, this]() { logic->start();
    this->board->drawEnabled = false; }
    ));

    inputbuttons.emplace_back(std::make_unique<InputButton>(
        "StopButton",
        Vector2f{ buttonX, buttonY + 100.f },
        Vector2f{ buttonWidth, buttonHeight },
        "STOP",
        [&logic]() { logic->pause(); }
    ));

    inputbuttons.emplace_back(std::make_unique<InputButton>(
        "EndButton",
        Vector2f{ buttonX, buttonY + 200.f },
        Vector2f{ buttonWidth, buttonHeight },
        "END",
        endCallback
    ));

    inputbuttons.emplace_back(std::make_unique<InputButton>(
        "ToggleDrawButton",
        Vector2f{ buttonX, buttonY + 300.f },
        Vector2f{ buttonWidth, buttonHeight },
        "TOGGLE DRAW",
        [&logic, this]() { logic->pause(); this->board->drawEnabled = true; }
    ));

}


void Uipanel::draw(Render::Drawer& drawer) {
    if (hud) hud->draw(drawer);
    for (auto& btn : inputbuttons) {
        if (btn) btn->draw(drawer);
    }
    if (board) board->draw(drawer);
}

void Uipanel::update() {
    if (hud) hud->update();
    for (auto& btn : inputbuttons) {
        if (btn) btn->update();
    }
    if (board) board->update();
}

void Uipanel::input(InputEvent& events) {
    if (hud) hud->input(events);
    for (auto& btn : inputbuttons) {
        if (btn) btn->input(events);
    }
    if (board) board->input(events);
}

std::string Uipanel::printString() const {
    std::string result;
    if (hud) result += hud->printString();
    for (const auto& btn : inputbuttons) {
        if (btn) result += btn->printString();
    }
    if (board) result += board->printString();
    return result;
}

void Uipanel::readString(const std::string& read) {
    if (hud) hud->readString(read);
    for (auto& btn : inputbuttons) {
        if (btn) btn->readString(read);
    }
    if (board) board->readString(read);
}