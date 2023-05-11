#include "defines.hpp"
#include "PlayerVehicle.hpp"


PlayerVehicle::PlayerVehicle(const uint64_t& bitboard_) noexcept :
    HorizontalVehicle(bitboard_, PLAYER_VEHICLE_ID, VEHICLE_ORIENTATION::PLAYER) {

}


std::unique_ptr<PlayerVehicle> PlayerVehicle::move_left() {

    return std::move(std::make_unique<PlayerVehicle>((bitboard << 1)));

}


std::unique_ptr<PlayerVehicle> PlayerVehicle::move_right() {

    return std::move(std::make_unique<PlayerVehicle>((bitboard >> 1)));

}


std::forward_list<std::unique_ptr<Vehicle>> PlayerVehicle::move_left_until_collision_with(const uint64_t& board) {

    std::forward_list<std::unique_ptr<Vehicle>> next_moves_left_for_vehicle { };

    auto next { move_left() };
    uint64_t current_bitboard { next->bitboard };

    while ( !collision_detected( current_bitboard, board ) ) {

        next_moves_left_for_vehicle.emplace_front( std::move( std::make_unique<PlayerVehicle>( current_bitboard ) ) );
        current_bitboard = ( next_moves_left_for_vehicle.front()->next_moves() ).at(MOVE_DIRECTION::LEFT)->bitboard;

    }

    return next_moves_left_for_vehicle;

}


std::forward_list<std::unique_ptr<Vehicle>> PlayerVehicle::move_right_until_collision_with(const uint64_t& board) {

    std::forward_list<std::unique_ptr<Vehicle>> next_moves_right_for_vehicle { };

    auto next { move_right() };
    uint64_t current_bitboard { next->bitboard };

    while ( !collision_detected( current_bitboard, ( board | (GOAL >> 1) ) ) ) {

        next_moves_right_for_vehicle.emplace_front( std::move( std::make_unique<PlayerVehicle>( current_bitboard ) ) );
        current_bitboard = ( next_moves_right_for_vehicle.front()->next_moves() ).at(MOVE_DIRECTION::RIGHT)->bitboard;

    }

    return next_moves_right_for_vehicle;

}
