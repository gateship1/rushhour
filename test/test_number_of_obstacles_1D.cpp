#include "UnitTest.hpp"

#include "heuristics.hpp"


TEST_F(UnitTest, number_of_obstacles_1D) {

    initialize_sample_board3();
    ASSERT_EQ( number_of_obstacles_1D(game_board), 1 );

    initialize_sample_board1();
    ASSERT_EQ( number_of_obstacles_1D(game_board), 2 );

}
