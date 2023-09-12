#include "GameEngineTests.hpp"

#include <memory>

#include "Board.hpp"


TEST_F(GameEngineTests, is_solution_state) {

    initialize_solution_board();
    ASSERT_TRUE( game_board->is_solution_state() );

    initialize_default_board();
    ASSERT_FALSE( game_board->is_solution_state() );

}
