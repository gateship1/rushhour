#pragma once

#include <cstdint>
#include <memory>

#include "Board.hpp"
//#include "HorizontalVehicle.hpp"
#include "make.hpp"
//#include "PlayerVehicle.hpp"
#include "Vehicle.hpp"
//#include "VerticalVehicle.hpp"

#include "gtest/gtest.h"


class RushHourTests : public ::testing::Test {

protected:

    std::unique_ptr<Board> game_board;

    void check_board_state(const std::unique_ptr<Board>& board, const uint64_t& initial_board_state);

    void initialize_default_board();
    void initialize_empty_board();
    void initialize_no_solution_board();
    void initialize_sample_board1();
    void initialize_sample_board3();
    void initialize_solution_board();


public:

    virtual void SetUp() { }

    virtual void TearDown() { }

};
