#pragma once

#include "../input/InputButton.h"
#include "../logic/Board.h"
#include "../logic/Logic.h"
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
        std::weak_ptr<MVC::Logic> logic,
        std::weak_ptr<Board> board,
        Util::Event<> && simEndEvent);

    void draw(Render::Drawer& drawer) override;
    void update() override;
    bool input(InputToken& events) override;

    std::string printString() const override;
    void readString(const std::string& read) override;

private:
    std::vector<std::unique_ptr<InputButton>> inputbuttons;
    std::unique_ptr<Hud> hud;
};