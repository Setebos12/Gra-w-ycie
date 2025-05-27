#include "uipanel.h"
#include <memory>
#include "../logic/Board.h"


Uipanel::Uipanel(std::shared_ptr<Util::Event<const std::string&, Util::Level>> logEvent, const sf::Vector2u& windowSize, int uiPanelWidth, int margin, int boardWidth, int boardHeight)
{
    // Create the board
    board = std::make_shared<Board>("Game of Life Board", boardWidth, boardHeight, logEvent);

    float buttonX = static_cast<float>(windowSize.x - uiPanelWidth + margin);
    float buttonWidth = 180.f;
    float buttonHeight = 60.f;
    float buttonY = 500.f;

    // SPEED UP above START
    inputbuttons.emplace_back(std::make_shared<InputButton>(
        "SpeedUpButton",
        sf::Vector2f{ buttonX, buttonY - 140.f },
        sf::Vector2f{ buttonWidth, buttonHeight }, "SPEED UP"));

    // SPEED DOWN above START
    inputbuttons.emplace_back(std::make_shared<InputButton>(
        "SpeedDownButton",
        sf::Vector2f{ buttonX, buttonY - 70.f },
        sf::Vector2f{ buttonWidth, buttonHeight }, "SPEED DOWN"));

    // START
    inputbuttons.emplace_back(std::make_shared<InputButton>(
        "StartButton", sf::Vector2f{ buttonX, buttonY },
        sf::Vector2f{ buttonWidth, buttonHeight }, "START"));

    // STOP
    inputbuttons.emplace_back(std::make_shared<InputButton>(
        "StopButton", sf::Vector2f{ buttonX, buttonY + 100.f },
        sf::Vector2f{ buttonWidth, buttonHeight }, "STOP"));

    // END
    inputbuttons.emplace_back(std::make_shared<InputButton>(
        "EndButton", sf::Vector2f{ buttonX, buttonY + 200.f },
        sf::Vector2f{ buttonWidth, buttonHeight }, "END"));

    // TOGGLE DRAW
    inputbuttons.emplace_back(std::make_shared<InputButton>(
        "ToggleDrawButton", sf::Vector2f{ buttonX, buttonY + 300.f },
        sf::Vector2f{ buttonWidth, buttonHeight }, "TOGGLE DRAW"));

    // HUD
    hud = std::make_shared<Hud>("Hud", sf::Vector2f{ buttonX, buttonY + 400.f });
}


std::vector<std::shared_ptr<MVC::GameObject>> Uipanel::getGameObjects() {
    std::vector<std::shared_ptr<MVC::GameObject>> objects;
    if (board) objects.push_back(board);
    for (auto& btn : inputbuttons) {
        if (btn) objects.push_back(btn);
    }
    if (hud) objects.push_back(hud);
    return objects;
}