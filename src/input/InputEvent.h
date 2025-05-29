#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <functional>

class InputEvent {
public:
    InputEvent(std::shared_ptr<sf::RenderWindow> window) : window_(std::move(window)) {}

    using ClickCallback = std::function<void()>;

    void watchClickRect(const sf::Vector2f& position, const sf::Vector2f& size, ClickCallback callback) {
        clickRegions_.emplace_back(sf::FloatRect(position, size), std::move(callback));
    }

    void watchSingleClickRect(const sf::Vector2f& position, const sf::Vector2f& size, ClickCallback callback) {
        singleClickRegions_.emplace_back(sf::FloatRect(position, size), std::move(callback));
    }

    void processClicks() {
        if (!window_ || !window_->hasFocus()) return;

        sf::Vector2i mousePos = sf::Mouse::getPosition(*window_);
        sf::Vector2f mouseF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        bool mousePressedNow = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

        if (mousePressedNow) {
            for (const auto& [rect, callback] : clickRegions_) {
                if (rect.contains(mouseF)) {
                    if (callback) callback();
                }
            }
        }

        if (mousePressedNow && !mousePressedPrev_) {
            pressedInsideRect_ = false;
            for (const auto& [rect, callback] : singleClickRegions_) {
                if (rect.contains(mouseF)) {
                    pressedInsideRect_ = true;
                    break;
                }
            }
        }
        else if (!mousePressedNow && mousePressedPrev_) {
            if (pressedInsideRect_) {
                for (const auto& [rect, callback] : singleClickRegions_) {
                    if (rect.contains(mouseF)) {
                        if (callback) callback();
                    }
                }
            }
            pressedInsideRect_ = false; // reset after release
        }

        mousePressedPrev_ = mousePressedNow;

        clickRegions_.clear();
        singleClickRegions_.clear(); 
    }

    std::shared_ptr<sf::RenderWindow> getWindow() const {
        return window_;
    }

private:
    std::shared_ptr<sf::RenderWindow> window_;

    std::vector<std::pair<sf::FloatRect, ClickCallback>> clickRegions_;
    std::vector<std::pair<sf::FloatRect, ClickCallback>> singleClickRegions_;

    bool mousePressedPrev_ = false;
    bool pressedInsideRect_ = false;
};
