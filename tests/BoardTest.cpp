#include <gtest/gtest.h>
#include "board.h"
#include "Container.h"
#include "PointHandle.h"

std::shared_ptr<Util::Event<const std::string&, Util::Level>> nullEvent =
    std::make_shared<Util::Event<const std::string&, Util::Level>>();

TEST(BoardTest, ConstructorInitializesEmptyBoard) {
    Board board("Test", 5, 5, nullEvent);
    EXPECT_EQ(board.getGenerationCount(), 0);
    EXPECT_FALSE(board.getInputEnabled());
}

TEST(BoardTest, ToggleCellStateTurnsCellOn) {
    Board board("Test", 3, 3, nullEvent);
    board.toggleCellState(1, 1);
    std::string s = board.printString();
    EXPECT_NE(s.find("1"), std::string::npos);
}

TEST(BoardTest, ToggleCellStateTwiceTurnsCellOff) {
    Board board("Test", 3, 3, nullEvent);
    board.toggleCellState(1, 1);
    board.toggleCellState(1, 1);
    std::string s = board.printString();
    EXPECT_EQ(s.find("1"), std::string::npos);
}

TEST(BoardTest, ResetBoardClearsAllCells) {
    Board board("Test", 3, 3, nullEvent);
    board.toggleCellState(1, 1);
    board.resetBoard();
    EXPECT_EQ(board.printString().find("1"), std::string::npos);
}

TEST(BoardTest, EnableAndDisableInputWorksCorrectly) {
    Board board("Test", 2, 2, nullEvent);
    board.enableInput();
    EXPECT_TRUE(board.getInputEnabled());
    board.disableInput();
    EXPECT_FALSE(board.getInputEnabled());
}

TEST(BoardTest, GenerationCountIncrementsAfterUpdate) {
    Board board("Test", 3, 3, nullEvent);
    int before = board.getGenerationCount();
    board.update();
    EXPECT_EQ(board.getGenerationCount(), before + 1);
}

TEST(BoardTest, PrintStringReturnsValidFormat) {
    Board board("Test", 2, 2, nullEvent);
    std::string out = board.printString();
    EXPECT_EQ(out.substr(0, 8), "2 2 0 0 ");
}

TEST(BoardTest, ReadStringReconstructsBoard) {
    Board board("Test", 2, 2, nullEvent);
    board.readString("2 2 3 2 1100");
    EXPECT_EQ(board.getGenerationCount(), 3);
    EXPECT_EQ(board.printString(), "2 2 3 2 1100");
}

TEST(BoardTest, ReadStringTooShortDataIsHandled) {
    Board board("Test", 2, 2, nullEvent);
    EXPECT_NO_THROW(board.readString("2 2 0 1 1"));
}

TEST(BoardTest, AllCellsDeadAfterReset) {
    Board board("Test", 2, 2, nullEvent);
    board.toggleCellState(0, 0);
    board.resetBoard();
    EXPECT_EQ(board.printString().substr(8), "0000");
}

TEST(BoardTest, UpdateKillsLonelyCell) {
    Board board("Test", 3, 3, nullEvent);
    board.toggleCellState(1, 1);
    board.update();
    EXPECT_EQ(board.printString().substr(8).find("1"), std::string::npos);
}

TEST(BoardTest, StillLifeDoesNotChangeAfterUpdate) {
    Board board("Test", 4, 4, nullEvent);
    board.toggleCellState(1, 1);
    board.toggleCellState(1, 2);
    board.toggleCellState(2, 1);
    board.toggleCellState(2, 2);
    std::string before = board.printString().substr(8);
    board.update();
    EXPECT_EQ(board.printString().substr(8), before);
}

TEST(BoardTest, CellBornWithThreeNeighbors) {
    Board board("Test", 3, 3, nullEvent);
    board.toggleCellState(0, 1);
    board.toggleCellState(1, 1);
    board.toggleCellState(2, 1);
    board.update();
    EXPECT_NE(board.printString().find("1"), std::string::npos);
}

TEST(BoardTest, CellWithOneNeighborDies) {
    Board board("Test", 3, 3, nullEvent);
    board.toggleCellState(1, 1);
    board.toggleCellState(2, 1);
    board.update();
    board.update();
    EXPECT_EQ(board.printString().find("1"), std::string::npos);
}

TEST(BoardTest, UpdateOnEmptyBoardDoesNothingVisible) {
    Board board("Test", 4, 4, nullEvent);
    std::string before = board.printString();
    board.update();
    EXPECT_EQ(board.printString().substr(10), before.substr(10));
}

TEST(BoardTest, OutOfBoundsToggleDoesNothing) {
    Board board("Test", 3, 3, nullEvent);
    board.toggleCellState(-5, 100);
    EXPECT_EQ(board.printString().find("1"), std::string::npos);
}

TEST(BoardTest, TogglingSeveralCellsWorks) {
    Board board("Test", 3, 3, nullEvent);
    board.toggleCellState(0, 0);
    board.toggleCellState(1, 1);
    board.toggleCellState(2, 2);
    std::string state = board.printString();
    int ones = std::count(state.begin(), state.end(), '1');
    EXPECT_EQ(ones, 3);
}

TEST(BoardTest, ReadStringWithZeroAliveCellsWorks) {
    Board board("Test", 2, 2, nullEvent);
    board.readString("2 2 1 0 0000");
    EXPECT_EQ(board.getGenerationCount(), 1);
}

TEST(BoardTest, GenerationCountRemainsConsistent) {
    Board board("Test", 2, 2, nullEvent);
    board.update();
    board.update();
    EXPECT_EQ(board.getGenerationCount(), 2);
}

TEST(example, example)
{
    EXPECT_EQ(1, 1);
}
