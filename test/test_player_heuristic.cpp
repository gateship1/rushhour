#include "UnitTest.hpp"

#include "heuristics.hpp"


TEST_F(UnitTest, player_heuristic_1D) {

    initialize_sample_board3();
    ASSERT_EQ( player_heuristic_1D(game_board), 2 );

    initialize_sample_board1();
    ASSERT_EQ( player_heuristic_1D(game_board), 6 );

    initialize_default_board();
    ASSERT_EQ( player_heuristic_1D(game_board), 5 );

}
