#include "VerticalVehicle.hpp"


VerticalVehicle::VerticalVehicle(const uint64_t& bitboard_, const char& symbol_) noexcept :
    Vehicle(bitboard_, symbol_, VEHICLE_ORIENTATION::VERTICAL) {

}


std::unique_ptr<VerticalVehicle> VerticalVehicle::move_down() {

    return std::move(std::make_unique<VerticalVehicle>((bitboard >> 8), symbol));

}


std::unique_ptr<VerticalVehicle> VerticalVehicle::move_up() {

    return std::move(std::make_unique<VerticalVehicle>((bitboard << 8), symbol));

}


std::forward_list<std::unique_ptr<Vehicle>> VerticalVehicle::move_until_collision_with(const uint64_t& board) {

    std::forward_list<std::unique_ptr<Vehicle>> next_moves_for_vehicle { move_down_until_collision_with(board) };
    next_moves_for_vehicle.merge( move_up_until_collision_with(board) );

    return next_moves_for_vehicle;

}


std::array<std::unique_ptr<Vehicle>, 2> VerticalVehicle::next_moves() {

    return { move_down(), move_up() };

}


std::forward_list<std::unique_ptr<Vehicle>> VerticalVehicle::move_down_until_collision_with(const uint64_t& board) {

    std::forward_list<std::unique_ptr<Vehicle>> next_moves_left_for_vehicle { };

    auto next { move_down() };
    uint64_t current_bitboard { next->bitboard };

    while ( !collision_detected( current_bitboard, board ) ) {

        next_moves_left_for_vehicle.emplace_front( std::move( std::make_unique<VerticalVehicle>( current_bitboard, symbol ) ) );
        current_bitboard = ( next_moves_left_for_vehicle.front()->next_moves() ).at(MOVE_DIRECTION::DOWN)->bitboard;

    }

    return next_moves_left_for_vehicle;

}


std::forward_list<std::unique_ptr<Vehicle>> VerticalVehicle::move_up_until_collision_with(const uint64_t& board) {

    std::forward_list<std::unique_ptr<Vehicle>> next_moves_right_for_vehicle { };

    auto next { move_up() };
    uint64_t current_bitboard { next->bitboard };

    while ( !collision_detected( current_bitboard, board ) ) {

        next_moves_right_for_vehicle.emplace_front( std::move( std::make_unique<VerticalVehicle>( current_bitboard, symbol ) ) );
        current_bitboard = ( next_moves_right_for_vehicle.front()->next_moves() ).at(MOVE_DIRECTION::UP)->bitboard;

    }

    return next_moves_right_for_vehicle;

}
