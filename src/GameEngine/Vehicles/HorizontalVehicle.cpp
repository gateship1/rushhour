#include "HorizontalVehicle.hpp"


HorizontalVehicle::HorizontalVehicle(const uint64_t& bitboard_, const char& symbol_,
    const VEHICLE_ORIENTATION& orientation_) noexcept : Vehicle(bitboard_, symbol_, orientation_) {

}


std::unique_ptr<HorizontalVehicle> HorizontalVehicle::move_left() {

    return std::move(std::make_unique<HorizontalVehicle>((bitboard << 1), symbol));

}


std::unique_ptr<HorizontalVehicle> HorizontalVehicle::move_right() {

    return std::move(std::make_unique<HorizontalVehicle>((bitboard >> 1), symbol));

}


std::forward_list<std::unique_ptr<Vehicle>> HorizontalVehicle::move_until_collision_with(const uint64_t& board) {

    std::forward_list<std::unique_ptr<Vehicle>> next_left_moves_for_vehicle { move_left_until_collision_with(board) };

    std::forward_list<std::unique_ptr<Vehicle>> next_moves_for_vehicle { move_right_until_collision_with(board) };

    for (auto& left_move : next_left_moves_for_vehicle) {
        next_moves_for_vehicle.emplace_front( std::move(left_move) );
    }

    return next_moves_for_vehicle;

}


std::array<std::unique_ptr<Vehicle>, 2> HorizontalVehicle::next_moves() {

    return { move_left(), move_right() };

}


std::forward_list<std::unique_ptr<Vehicle>> HorizontalVehicle::move_left_until_collision_with(const uint64_t& board) {

    std::forward_list<std::unique_ptr<Vehicle>> next_moves_left_for_vehicle { };

    auto next { move_left() };
    uint64_t current_bitboard { next->bitboard };

    while ( !collision_detected( current_bitboard, board ) ) {

        next_moves_left_for_vehicle.emplace_front(std::move(std::make_unique<HorizontalVehicle>(current_bitboard, symbol)));
        current_bitboard = (next_moves_left_for_vehicle.front()->next_moves()).at(MOVE_DIRECTION::LEFT)->bitboard;

    }

    return next_moves_left_for_vehicle;

}


std::forward_list<std::unique_ptr<Vehicle>> HorizontalVehicle::move_right_until_collision_with(const uint64_t& board) {

    std::forward_list<std::unique_ptr<Vehicle>> next_moves_right_for_vehicle { };

    auto next { move_right() };
    uint64_t current_bitboard { next->bitboard };

    while ( !collision_detected( current_bitboard, board ) ) {

        next_moves_right_for_vehicle.emplace_front(std::move(std::make_unique<HorizontalVehicle>(current_bitboard, symbol)));
        current_bitboard = (next_moves_right_for_vehicle.front()->next_moves()).at(MOVE_DIRECTION::RIGHT)->bitboard;

    }

    return next_moves_right_for_vehicle;

}
