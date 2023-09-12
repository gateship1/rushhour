#include "VehiclesTests.hpp"

#include <memory>

#include "HorizontalVehicle.hpp"
#include "PlayerVehicle.hpp"
#include "VerticalVehicle.hpp"


TEST_F(VehiclesTests, horizontal_movement) {

    auto horizontal_vehicle {
        std::make_unique<HorizontalVehicle>(0b0000'0000'0000'0000'0000'0000'0011'0000'0000'0000'0000'0000'0000'0000'0000'0000, 'o')
    }; 

    uint64_t horizontal_vehicle_move_right { 0b0000'0000'0000'0000'0000'0000'0001'1000'0000'0000'0000'0000'0000'0000'0000'0000 };
    uint64_t horizontal_vehicle_move_left { 0b0000'0000'0000'0000'0000'0000'0110'0000'0000'0000'0000'0000'0000'0000'0000'0000 };

    ASSERT_EQ( horizontal_vehicle->move_right()->bitboard, horizontal_vehicle_move_right );
    ASSERT_EQ( horizontal_vehicle->move_left()->bitboard, horizontal_vehicle_move_left );

}


TEST_F(VehiclesTests, vertical_movement) {

    auto vertical_vehicle {
        std::make_unique<VerticalVehicle>(0b0000'0000'0000'0000'0000'0000'0000'0000'0100'0000'0100'0000'0000'0000'0000'0000, 'd')
    }; 

    uint64_t vertical_vehicle_move_down { 0b0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0100'0000'0100'0000'0000'0000 };
    uint64_t vertical_vehicle_move_up { 0b0000'0000'0000'0000'0000'0000'0100'0000'0100'0000'0000'0000'0000'0000'0000'0000 };

    ASSERT_EQ( vertical_vehicle->move_down()->bitboard, vertical_vehicle_move_down );
    ASSERT_EQ( vertical_vehicle->move_up()->bitboard, vertical_vehicle_move_up );

}


TEST_F(VehiclesTests, next_moves_vertical) {

    auto vertical_vehicle1 {
        std::make_unique<VerticalVehicle>(0b0000'0000'0000'0000'0000'0000'0001'0000'0001'0000'0000'0000'0000'0000'0000'0000, 'a')
    }; 
    uint64_t vertical_vehicle1_move_down_expected { 0b0000'0000'0000'0000'0000'0000'0000'0000'0001'0000'0001'0000'0000'0000'0000'0000 };
    uint64_t vertical_vehicle1_move_up_expected { 0b0000'0000'0000'0000'0001'0000'0001'0000'0000'0000'0000'0000'0000'0000'0000'0000 };

    auto vertical_vehicle1_moves { vertical_vehicle1->next_moves() };

    ASSERT_EQ( vertical_vehicle1_moves.at(0)->bitboard, vertical_vehicle1_move_down_expected );
    ASSERT_EQ( vertical_vehicle1_moves.at(1)->bitboard, vertical_vehicle1_move_up_expected );

    auto vertical_vehicle2 {
        std::make_unique<VerticalVehicle>(0b0000'0000'0001'0000'0001'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000, 'b')
    }; 
    uint64_t vertical_vehicle2_move_down_expected { 0b0000'0000'0000'0000'0001'0000'0001'0000'0000'0000'0000'0000'0000'0000'0000'0000 };
    uint64_t vertical_vehicle2_move_up_expected { 0b0001'0000'0001'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000 };

    auto vertical_vehicle2_moves { vertical_vehicle2->next_moves() };

    ASSERT_EQ( vertical_vehicle2_moves.at(0)->bitboard, vertical_vehicle2_move_down_expected );
    ASSERT_EQ( vertical_vehicle2_moves.at(1)->bitboard, vertical_vehicle2_move_up_expected );

    auto vertical_vehicle3 {
        std::make_unique<VerticalVehicle>(0b0000'0000'0000'0000'0000'0000'0000'0000'0000'0010'0000'0010'0000'0010'0000'0000, 'c')
    }; 
    uint64_t vertical_vehicle3_move_down_expected { 0b0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0010'0000'0010'0000'0010 };
    uint64_t vertical_vehicle3_move_up_expected { 0b0000'0000'0000'0000'0000'0000'0000'0010'0000'0010'0000'0010'0000'0000'0000'0000 };

    auto vertical_vehicle3_moves { vertical_vehicle3->next_moves() };

    ASSERT_EQ( vertical_vehicle3_moves.at(0)->bitboard, vertical_vehicle3_move_down_expected );
    ASSERT_EQ( vertical_vehicle3_moves.at(1)->bitboard, vertical_vehicle3_move_up_expected );
}


TEST_F(VehiclesTests, next_moves_horizontal) {

    auto horizontal_vehicle1 {
        std::make_unique<HorizontalVehicle>(0b0000'0000'0000'0000'0001'1100'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000, 'a')
    }; 
    uint64_t horizontal_vehicle1_move_left_expected { 0b0000'0000'0000'0000'0011'1000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000 };
    uint64_t horizontal_vehicle1_move_right_expected { 0b0000'0000'0000'0000'0000'1110'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000 };

    auto horizontal_vehicle1_moves { horizontal_vehicle1->next_moves() };

    ASSERT_EQ( horizontal_vehicle1_moves.at(0)->bitboard, horizontal_vehicle1_move_left_expected );
    ASSERT_EQ( horizontal_vehicle1_moves.at(1)->bitboard, horizontal_vehicle1_move_right_expected );

    auto horizontal_vehicle2 {
        std::make_unique<HorizontalVehicle>(0b0000'0000'0000'0000'0000'0000'0000'0000'0111'0000'0000'0000'0000'0000'0000'0000, 'b')
    }; 
    uint64_t horizontal_vehicle2_move_left_expected { 0b0000'0000'0000'0000'0000'0000'0000'0000'1110'0000'0000'0000'0000'0000'0000'0000 };
    uint64_t horizontal_vehicle2_move_right_expected { 0b0000'0000'0000'0000'0000'0000'0000'0000'0011'1000'0000'0000'0000'0000'0000'0000 };

    auto horizontal_vehicle2_moves { horizontal_vehicle2->next_moves() };

    ASSERT_EQ( horizontal_vehicle2_moves.at(0)->bitboard, horizontal_vehicle2_move_left_expected );
    ASSERT_EQ( horizontal_vehicle2_moves.at(1)->bitboard, horizontal_vehicle2_move_right_expected );

    auto horizontal_vehicle3 {
        std::make_unique<HorizontalVehicle>(0b0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'1110'0000'0000, 'c')
    }; 
    uint64_t horizontal_vehicle3_move_left_expected { 0b0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0001'1100'0000'0000 };
    uint64_t horizontal_vehicle3_move_right_expected { 0b0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0111'0000'0000 };

    auto horizontal_vehicle3_moves { horizontal_vehicle3->next_moves() };

    ASSERT_EQ( horizontal_vehicle3_moves.at(0)->bitboard, horizontal_vehicle3_move_left_expected );
    ASSERT_EQ( horizontal_vehicle3_moves.at(1)->bitboard, horizontal_vehicle3_move_right_expected );
}


TEST_F(VehiclesTests, next_moves_player) {

    auto player_vehicle {
        std::make_unique<PlayerVehicle>(0b0000'0000'0000'0000'0000'0000'0000'0110'0000'0000'0000'0000'0000'0000'0000'0000)
    }; 
    uint64_t player_vehicle_move_left_expected { 0b0000'0000'0000'0000'0000'0000'0000'1100'0000'0000'0000'0000'0000'0000'0000'0000 };
    uint64_t player_vehicle_move_right_expected { 0b0000'0000'0000'0000'0000'0000'0000'0011'0000'0000'0000'0000'0000'0000'0000'0000 };

    auto player_vehicle_moves { player_vehicle->next_moves() };

    ASSERT_EQ( player_vehicle_moves.at(0)->bitboard, player_vehicle_move_left_expected );
    ASSERT_EQ( player_vehicle_moves.at(1)->bitboard, player_vehicle_move_right_expected );

}
