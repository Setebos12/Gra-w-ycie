// Filename: gameobject.h
//
// All objects that need to interact with the game loop will inherit this class,
// requires implementation of draw and update functions.
//
// Author: Piotr Pyrak

#pragma once

#include "irenderobj.h"
#include "event.h"
#include "logger.h"
#include <istream>
#include <optional>
#include <ostream>
#include <string>
#include "inputtoken.h"


namespace MVC {
class GameObject : public Render::IRenderObject {
public:
    GameObject(const std::string& name,
               std::optional<std::shared_ptr<Util::Event<const std::string&, Util::Level>>> logEvent = std::nullopt,
               bool saveState = false)
        : name_(name), logEvent_(std::move(logEvent)), saveState_(saveState) {
        if (logEvent_.has_value()) {
            logEvent_.value()->invoke("Created gameobject named: " + name, Util::Level::DEBUG);
        }
    }
    virtual ~GameObject() = default;

    // recivers renderer object where it will be able to call drawing methods
    virtual void draw(Render::Drawer& drawer) override = 0;
    virtual void update() = 0;
    virtual bool input(const InputPoll::InputToken& events) { return false; }

    const auto& getName() const { return name_; }
    void setName(const std::string& name) { name_ = name; }

    virtual std::string printString() const = 0;
    virtual void readString(const std::string& read) = 0;

    auto getSaveState() const { return saveState_; }
protected:
    friend std::ostream& operator<<(std::ostream& write,
                                    const GameObject& gameObj);
    friend std::istream& operator>>(std::istream& read, GameObject& gameObj);

    std::optional<std::shared_ptr<Util::Event<const std::string&, Util::Level>>>
        logEvent_;
private:
    std::string name_;
    bool saveState_;
};
} // namespace MVC
