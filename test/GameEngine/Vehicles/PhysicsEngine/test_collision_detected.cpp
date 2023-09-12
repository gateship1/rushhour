#include "PhysicsEngineTests.hpp"

#include "collision_detected.hpp"


TEST_F(PhysicsEngineTests, collision_detected) {

    uint64_t border_bit_board { 0b1111'1111'1000'0001'1000'0001'1000'0000'1000'0001'1000'0001'1000'0001'1111'1111 };
    uint64_t border_collision_left_bit_board { 0b0000'0000'0000'0000'1100'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000 };
    uint64_t border_collision_right_bit_board { 0b0000'0000'0000'0000'0000'0011'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000 };
    uint64_t border_collision_up_bit_board { 0b0000'1000'0000'1000'0000'1000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000 }; 
    uint64_t border_collision_down_bit_board { 0b0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0001'0000'0001'0000 };

    ASSERT_TRUE( collision_detected(border_bit_board, border_collision_left_bit_board) );
    ASSERT_TRUE( collision_detected(border_bit_board, border_collision_right_bit_board) );
    ASSERT_TRUE( collision_detected(border_bit_board, border_collision_up_bit_board) );
    ASSERT_TRUE( collision_detected(border_bit_board, border_collision_down_bit_board) );

    uint64_t exit_row_move_right_bit_board { 0b0000'0000'0000'0000'0000'0000'0000'0011'0000'0000'0000'0000'0000'0000'0000'0000 };
    ASSERT_FALSE( collision_detected(border_bit_board, exit_row_move_right_bit_board) );

    uint64_t vehicle_bit_board { 0b1111'1111'1001'1101'1111'0101'1000'0110'1111'0111'1101'0111'1101'0111'1111'1111 };
    uint64_t player_vehicle_move_right_bit_board { 0b0000'0000'0000'0000'0000'0000'0000'1100'0000'0000'0000'0000'0000'0000'0000'0000 };
    ASSERT_TRUE( collision_detected(vehicle_bit_board, player_vehicle_move_right_bit_board) );

    player_vehicle_move_right_bit_board = 0b0000'0000'0000'0000'0000'0000'0001'1000'0000'0000'0000'0000'0000'0000'0000'0000;
    ASSERT_FALSE( collision_detected(vehicle_bit_board, player_vehicle_move_right_bit_board) );

}
