#include "UnitTest.hpp"

#include "defines.hpp"


TEST_F(UnitTest, get_board_state) {

    initialize_default_board();
    initialize_sample_board1();
    initialize_sample_board3();

}


TEST_F(UnitTest, get_state_of_vehicle) {

    initialize_sample_board3();

    ASSERT_EQ(game_board->get_state_of_vehicle(PLAYER_VEHICLE_ID), 0b0000'0000'0000'0000'0000'0000'0000'1100'0000'0000'0000'0000'0000'0000'0000'0000 );

}


TEST_F(UnitTest, get_board_state_wout_vehicle) {

    initialize_sample_board3();

    ASSERT_EQ(game_board->get_state_wout_vehicle('q'), 0b1111'1111'1111'1111'1101'1111'1111'1110'1011'0001'1001'0001'1110'0001'1111'1111 );

}
