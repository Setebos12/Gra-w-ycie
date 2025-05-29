#pragma once
#include "../input/InputButton.h"
#include "../logic/board.h"
#include <vector>
#include "hud.h"

class Uipanel /* : public MVC::GameObject */{
public:
    Uipanel(std::shared_ptr<Util::Event<const std::string&, Util::Level>> logEvent, const sf::Vector2u& windowSize, int uiPanelWidth, int margin, int boardWidth, int boardHeight);

    std::vector<std::shared_ptr<MVC::GameObject>> getGameObjects();


public:
    std::shared_ptr<Board> board;
    std::vector<std::shared_ptr<InputButton>> inputbuttons;
    std::shared_ptr<Hud> hud;
};