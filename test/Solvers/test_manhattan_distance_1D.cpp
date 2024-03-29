#include "heuristics.hpp"
#include "SolverTests.hpp"


TEST_F(SolverTests, manhattan_distance_1D) {

    initialize_sample_board3();
    ASSERT_EQ( manhattan_distance_1D(game_board), 1 );

    initialize_sample_board1();
    ASSERT_EQ( manhattan_distance_1D(game_board), 4 );

    initialize_default_board();
    ASSERT_EQ( manhattan_distance_1D(game_board), 4 );

}
