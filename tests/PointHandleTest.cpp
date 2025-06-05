#include <gtest/gtest.h>
#include "board.h"
#include "Container.h"
#include "PointHandle.h"

TEST(PointHandleTest, CellDiesWithZeroNeighbors) {
    Container c(3, 3);
    c.setCellState(1, 1, true);
    PointHandle ph(c);
    EXPECT_FALSE(ph.shouldCellLive(1, 1));
}

TEST(PointHandleTest, CellSurvivesWithTwoNeighbors) {
    Container c(3, 3);
    c.setCellState(1, 1, true);
    c.setCellState(0, 1, true);
    c.setCellState(2, 1, true);
    PointHandle ph(c);
    EXPECT_TRUE(ph.shouldCellLive(1, 1));
}

TEST(PointHandleTest, CellSurvivesWithThreeNeighbors) {
    Container c(3, 3);
    c.setCellState(1, 1, true);
    c.setCellState(0, 1, true);
    c.setCellState(2, 1, true);
    c.setCellState(1, 0, true);
    PointHandle ph(c);
    EXPECT_TRUE(ph.shouldCellLive(1, 1));
}

TEST(PointHandleTest, CellDiesWithFourNeighbors) {
    Container c(3, 3);
    c.setCellState(1, 1, true);
    c.setCellState(0, 1, true);
    c.setCellState(2, 1, true);
    c.setCellState(1, 0, true);
    c.setCellState(1, 2, true);
    PointHandle ph(c);
    EXPECT_FALSE(ph.shouldCellLive(1, 1));
}

TEST(PointHandleTest, DeadCellComesAliveWithThreeNeighbors) {
    Container c(3, 3);
    c.setCellState(0, 1, true);
    c.setCellState(1, 0, true);
    c.setCellState(2, 1, true);
    PointHandle ph(c);
    EXPECT_TRUE(ph.shouldCellLive(1, 1));
}

TEST(PointHandleTest, DeadCellStaysDeadWithTwoNeighbors) {
    Container c(3, 3);
    c.setCellState(0, 1, true);
    c.setCellState(2, 1, true);
    PointHandle ph(c);
    EXPECT_FALSE(ph.shouldCellLive(1, 1));
}

TEST(PointHandleTest, CountLiveNeighborsReturnsZero) {
    Container c(3, 3);
    PointHandle ph(c);
    EXPECT_FALSE(ph.shouldCellLive(1, 1));
}

TEST(PointHandleTest, CellOnEdgeDoesNotCrash) {
    Container c(3, 3);
    PointHandle ph(c);
    EXPECT_FALSE(ph.shouldCellLive(0, 0));
}

TEST(PointHandleTest, CellInCornerStaysDeadIfNoNeighbors) {
    Container c(3, 3);
    PointHandle ph(c);
    EXPECT_FALSE(ph.shouldCellLive(0, 0));
}

TEST(PointHandleTest, AliveCellWithExactlyThreeNeighborsSurvives) {
    Container c(3, 3);
    c.setCellState(1, 1, true);
    c.setCellState(0, 0, true);
    c.setCellState(0, 1, true);
    c.setCellState(0, 2, true);
    PointHandle ph(c);
    EXPECT_TRUE(ph.shouldCellLive(1, 1));
}