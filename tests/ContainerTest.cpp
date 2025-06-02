#include <gtest/gtest.h>
#include "board.h"
#include "Container.h"
#include "PointHandle.h"


TEST(ContainerTest, InitializesWithAllCellsDead) {
    Container c(3, 3);
    for (int x = 0; x < c.getWidth(); ++x)
        for (int y = 0; y < c.getHeight(); ++y)
            EXPECT_FALSE(c.getCellState(x, y));
}

TEST(ContainerTest, SetCellStateChangesState) {
    Container c(3, 3);
    c.setCellState(1, 1, true);
    EXPECT_TRUE(c.getCellState(1, 1));
}

TEST(ContainerTest, SetCellStateOutOfBoundsDoesNothing) {
    Container c(3, 3);
    c.setCellState(-1, -1, true);
    c.setCellState(5, 5, true);
    // brak crasha = test passed
}

TEST(ContainerTest, ResetContainerClearsCells) {
    Container c(2, 2);
    c.setCellState(0, 0, true);
    c.resetContainer();
    EXPECT_FALSE(c.getCellState(0, 0));
}

TEST(ContainerTest, GetWidthReturnsCorrect) {
    Container c(4, 5);
    EXPECT_EQ(c.getWidth(), 4);
}

TEST(ContainerTest, GetHeightReturnsCorrect) {
    Container c(4, 5);
    EXPECT_EQ(c.getHeight(), 5);
}

TEST(ContainerTest, FindMinMaxXReturnsCorrectRange) {
    Container c(5, 5);
    c.setCellState(2, 2, true);
    auto range = c.findMinMaxX();
    EXPECT_LE(range.first, 2);
    EXPECT_GE(range.second, 3);
}

TEST(ContainerTest, FindMinMaxYReturnsCorrectRange) {
    Container c(5, 5);
    c.setCellState(1, 4, true);
    auto range = c.findMinMaxY();
    EXPECT_LE(range.first, 4);
    EXPECT_GE(range.second, 5);
}

TEST(ContainerTest, AllCellsDeadAfterInit) {
    Container c(3, 3);
    int liveCount = 0;
    for (int x = 0; x < c.getWidth(); ++x)
        for (int y = 0; y < c.getHeight(); ++y)
            if (c.getCellState(x, y)) ++liveCount;
    EXPECT_EQ(liveCount, 0);
}

TEST(ContainerTest, AllCellsDeadAfterReset) {
    Container c(3, 3);
    c.setCellState(0, 0, true);
    c.resetContainer();
    EXPECT_FALSE(c.getCellState(0, 0));
}