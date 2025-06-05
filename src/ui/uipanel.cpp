// Filename: uipanel.cpp
//
// Description:
//     Implements the Uipanel class, managing UI components such as input buttons and HUD,
//     handling drawing, updates, and input forwarding within the MVC architecture.
//
// Authors: Krzysztof Rutkowski, Piotr Pyrak


#include "uipanel.h"
#include <memory>
#include "../logic/board.h"

using namespace UI;

Uipanel::Uipanel(std::shared_ptr<Util::Event<const std::string&, Util::Level>>& logEvent,
    const sf::Vector2u& windowSize, int uiPanelWidth, int margin, int boardWidth,
    int boardHeight,
    const std::weak_ptr<MVC::Logic>& logic,
    const std::weak_ptr<Board>& board,
    Util::Event<> && simEndEvent,
    Util::Event<>&& saveEvent,
    Util::Event<>&& loadEvent,
    Util::Event<int>& updateGenEvent)
    : MVC::GameObject("Uipanel", logEvent) {
    float buttonX = static_cast<float>(windowSize.x - uiPanelWidth + margin);
    float buttonWidth = 180.f;
    float buttonHeight = 60.f;
    float buttonY = 500.f;

    using sf::Vector2f;
    hud = std::make_shared<Hud>("Hud", Vector2f{ buttonX, buttonY + 400.f });
    updateGenEvent.subscribe<Hud>(std::weak_ptr<Hud>(hud), &Hud::updateGeneration);

    Util::Event<> resetBoard;
    resetBoard.subscribe(std::weak_ptr<Board>(board), &Board::resetBoard);
    resetBoard.subscribe(std::weak_ptr<MVC::Logic>(logic), &MVC::Logic::pause);
    resetBoard.subscribe(std::weak_ptr<Hud>(hud), &Hud::reset);

    inputbuttons.emplace_back(std::make_unique<UI::InputButton>(
        "ResetButton",
        Vector2f{ buttonX, 20.f },
        Vector2f{ buttonWidth, buttonHeight },
        "RESET",
        std::move(resetBoard),
        logEvent
    ));

    Util::Event<> increaseSpeed, decreaseSpeed;
    increaseSpeed.subscribe(std::weak_ptr<MVC::Logic>(logic), &MVC::Logic::increaseSpeed);
    decreaseSpeed.subscribe(std::weak_ptr<MVC::Logic>(logic), &MVC::Logic::decreaseSpeed);

    inputbuttons.emplace_back(std::make_unique<UI::InputButton>(
        "SpeedUpButton",
        Vector2f{ buttonX, buttonY - 140.f },
        Vector2f{ buttonWidth, buttonHeight },
        "SPEED UP",
        std::move(increaseSpeed),
        logEvent
    ));

    inputbuttons.emplace_back(std::make_unique<UI::InputButton>(
        "SpeedDownButton",
        Vector2f{ buttonX, buttonY - 70.f },
        Vector2f{ buttonWidth, buttonHeight },
        "SPEED DOWN",
        std::move(decreaseSpeed),
        logEvent
    ));

    Util::Event<> start, stop;
    start.subscribe(std::weak_ptr<MVC::Logic>(logic), &MVC::Logic::start);
    start.subscribe(std::weak_ptr<Board>(board), &Board::disableInput);
    stop.subscribe(std::weak_ptr<MVC::Logic>(logic), &MVC::Logic::pause);

    inputbuttons.emplace_back(std::make_unique<UI::InputButton>(
        "StartButton",
        Vector2f{ buttonX, buttonY },
        Vector2f{ buttonWidth, buttonHeight },
        "START",
        std::move(start),
        logEvent
    ));

    inputbuttons.emplace_back(std::make_unique<UI::InputButton>(
        "StopButton",
        Vector2f{ buttonX, buttonY + 100.f },
        Vector2f{ buttonWidth, buttonHeight },
        "STOP",
        std::move(stop),
        logEvent
    ));

    inputbuttons.emplace_back(std::make_unique<UI::InputButton>(
        "EndButton",
        Vector2f{ buttonX, buttonY + 200.f },
        Vector2f{ buttonWidth, buttonHeight },
        "END",
        std::move(simEndEvent),
        logEvent
    ));

    Util::Event<> toggleDraw;
    toggleDraw.subscribe(std::weak_ptr<MVC::Logic>(logic), &MVC::Logic::pause);
    toggleDraw.subscribe(std::weak_ptr<Board>(board), &Board::enableInput);
    inputbuttons.emplace_back(std::make_unique<UI::InputButton>(
        "ToggleDrawButton",
        Vector2f{ buttonX, buttonY + 300.f },
        Vector2f{ buttonWidth, buttonHeight },
        "ENABLE DRAW",
        std::move(toggleDraw),
        logEvent
    ));

    inputbuttons.emplace_back(std::make_unique<UI::InputButton>(
        "SaveButton",
        Vector2f{ buttonX, buttonY - 210.f },
        Vector2f{ buttonWidth, buttonHeight },
        "SAVE",
        std::move(saveEvent),
        logEvent
    ));

    inputbuttons.emplace_back(std::make_unique<UI::InputButton>(
        "LoadButton",
        Vector2f{ buttonX, buttonY - 280.f },
        Vector2f{ buttonWidth, buttonHeight },
        "LOAD",
        std::move(loadEvent),
        logEvent

    ));
    logEvent_.value()->invoke("Uipanel initialized\n", Util::Level::INFO);
}


void Uipanel::draw(Render::Drawer& drawer) {
    if (hud) hud->draw(drawer);
    for (auto& btn : inputbuttons) {
        if (btn) btn->draw(drawer);
    }
}

void Uipanel::update() {
    if (hud) hud->update();
    for (auto& btn : inputbuttons) {
        if (btn) btn->update();
    }
}

bool Uipanel::input(InputToken& token) {
    if (hud) hud->input(token);
    for (auto& btn : inputbuttons) {
        if (btn) btn->input(token);
    }
    return false;
}

std::string Uipanel::printString() const {
    std::string result;
    if (hud) result += hud->printString();
    for (const auto& btn : inputbuttons) {
        if (btn) result += btn->printString();
    }
    return result;
}

void Uipanel::readString(const std::string& read) {
    if (hud) hud->readString(read);
    for (auto& btn : inputbuttons) {
        if (btn) btn->readString(read);
    }
}