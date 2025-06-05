//Filename: board.h
//
// Class that represents board of the game, maintains
// its state and takes input. Ihnerits from gameobject and implements
// override methods
//
//Author: Bartosz Paszkiewicz

#pragma once

#include "gameobject.h"
#include "container.h"
#include "pointhandle.h"
#include <memory>

class Board : public MVC::GameObject {
public:
    Board(const std::string& name,
          int width, int height,
          const std::shared_ptr<Util::Event<const std::string&, Util::Level>>& logEvent);

    void draw(Render::Drawer& drawer) override;
    void update() override;

    void toggleCellState(int x, int y);
    bool input(const InputPoll::InputToken& token) override;

    void resetBoard();
    int getGenerationCount() const;

    std::string printString() const override;
    void readString(const std::string& read) override;

    void enableInput() { inputEnabled_ = true; }
    void disableInput() { inputEnabled_ = false; }
    auto getInputEnabled() const { return inputEnabled_; }

    template<typename T>
    std::string static toString(const T& value) {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }

    auto& getUpdateGenEvent() { return updateGenEvent_; }
private:
    std::unique_ptr<Container> container_;
    std::unique_ptr<PointHandle> pointHandle_;
    int generationCount_;

    bool inputEnabled_ = false;

    bool erasing_ = false;

    void incrementGeneration();

    Util::Event<int> updateGenEvent_;
};
