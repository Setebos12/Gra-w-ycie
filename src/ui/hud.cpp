#include "hud.h"




void Hud::draw(Render::Drawer& drawer) {
    std::ostringstream ss;
    ss << "Generation: " << generation_;

    drawer.drawText(ss.str(), position_, 24, sf::Color::Red);
}

void Hud::update() {
    generation_ += 1;
}

void Hud::reset()
{
    generation_ = 0;
}
