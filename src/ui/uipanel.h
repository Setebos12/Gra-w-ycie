// Filename: uipanel.h
//
// Description:
//     Declares the Uipanel class, a UI component that manages input buttons,
//     HUD display, and interactions with game logic and board within the MVC framework.
//
// Authors: Krzysztof Rutkowski, Piotr Pyrak


#pragma once

#include "../input/InputButton.h"
#include "../logic/board.h"
#include "../logic/logic.h"
#include "../core/gameobject.h"
#include "hud.h"

#include <vector>
#include <memory>
#include <functional>

class Uipanel : public MVC::GameObject {
public:
    Uipanel(std::shared_ptr<Util::Event<const std::string&, Util::Level>> logEvent,
        const sf::Vector2u& windowSize,
        int uiPanelWidth,
        int margin,
        int boardWidth,
        int boardHeight,
        const std::weak_ptr<MVC::Logic>& logic,
        const std::weak_ptr<Board>& board,
        Util::Event<> && simEndEvent,
        Util::Event<>&& saveEvent,
        Util::Event<>&& loadEvent);

    void draw(Render::Drawer& drawer) override;
    void update() override;
    bool input(InputToken& events) override;

    std::string printString() const override;
    void readString(const std::string& read) override;

private:
    std::vector<std::unique_ptr<InputButton>> inputbuttons;
    std::unique_ptr<Hud> hud;
};