#include <bitset>
#include <iostream>

#include "Board.hpp"
#include "defines.hpp"


Board::Board(std::forward_list<std::unique_ptr<Vehicle>>&& vehicles_) noexcept :
    vehicles( std::move(vehicles_) ) {

}


std::string Board::as_string() const {

    std::string board { border_as_string() };

    uint8_t bits64 ( sizeof(uint64_t) * 8 );

    for (const auto& vehicle : vehicles) {

        for (uint8_t i { 0 }; i < bits64; ++i ) {

            uint8_t bitshift ( static_cast<uint8_t>(bits64 - (i + 1)) );

            if ( ( (vehicle->bitboard >> bitshift) & 1 ) == 1 ) 
                board.at(i) = vehicle->symbol;
        }

    }

    return board;

}


uint64_t Board::get_state() const {

    uint64_t board_state { border };

    for (const auto& vehicle : vehicles)
        board_state |= vehicle->bitboard;

    return board_state;

}


uint64_t Board::get_state_of_vehicle(const char& vehicle_id) const {

    for (const auto& vehicle_on_board : vehicles) {
        if (vehicle_on_board->symbol == vehicle_id)
            return vehicle_on_board->bitboard;
    }

    return 0;

}


uint64_t Board::get_state_wout_vehicle(const char& vehicle_id) const {

    return (get_state() ^ get_state_of_vehicle(vehicle_id));

}


bool Board::is_solution_state() const {

    uint64_t player_bitboard { get_state_of_vehicle(PLAYER_VEHICLE_ID) };

    return ( player_bitboard & GOAL );

}


std::forward_list<std::unique_ptr<Board>> Board::next() {

    std::forward_list<std::unique_ptr<Board>> next_boards { };

    for (const auto& vehicle : vehicles) {

        uint64_t state_without_vehicle { get_state() ^ vehicle->bitboard };

        for (const auto& moved_vehicle: vehicle->move_until_collision_with(state_without_vehicle)) {

            std::forward_list<std::unique_ptr<Vehicle>> new_list_of_vehicles { build_list_of_next_vehicles(moved_vehicle) };

            next_boards.emplace_front( std::make_unique<Board>( std::move( new_list_of_vehicles ) ) );

        }

    }

    return next_boards;

}


void Board::print() const {

    std::string board_str { as_string() };

    uint8_t bits64 ( sizeof(uint64_t) * 8 );

    for (uint8_t i { 0 }; i < bits64; ++i ) {
        if (i % 8 == 0) std::cout << "\n";
        std::cout << board_str.at(i);
    }

}



void Board::add_vehicle_to_list(const std::unique_ptr<Vehicle>& vehicle_to_add,
    std::forward_list<std::unique_ptr<Vehicle>>& list_of_vehicles) {

    switch(vehicle_to_add->orientation) {
        case VEHICLE_ORIENTATION::HORIZONTAL:
            list_of_vehicles.emplace_front(
                std::make_unique<HorizontalVehicle>(vehicle_to_add->bitboard, vehicle_to_add->symbol) );
            break;
        case VEHICLE_ORIENTATION::VERTICAL:
            list_of_vehicles.emplace_front(
                std::make_unique<VerticalVehicle>(vehicle_to_add->bitboard, vehicle_to_add->symbol) );
            break;
        case VEHICLE_ORIENTATION::PLAYER:
            list_of_vehicles.emplace_front(
                std::make_unique<PlayerVehicle>(vehicle_to_add->bitboard) );
            break;
        default:
            return;
    }

}


std::string Board::border_as_string() const {

    std::string board { };
    uint8_t bits64 ( sizeof(uint64_t) * 8 );

    for (uint8_t i { 0 }; i < bits64; ++i ) {

        uint8_t bitshift ( static_cast<uint8_t>(bits64 - (i + 1)) );
        std::string ch { };

        ( i < sizeof(uint64_t) || i > bits64 - (sizeof(uint64_t) + 1) ) ? ch = "-" : ch = "|";

        ( ( (border >> bitshift) & 1 ) == 1 ) ? board.append(ch) : board.append(" ");

    }

    board.at(63) = ' ';
    board.at(56) = ' ';
    board.at(7) = ' ';
    board.at(0) = ' ';

    return board;

}


std::forward_list<std::unique_ptr<Vehicle>> Board::build_list_of_next_vehicles(const std::unique_ptr<Vehicle>& vehicle) {

    std::forward_list<std::unique_ptr<Vehicle>> new_list_of_vehicles { };
    add_vehicle_to_list(vehicle, new_list_of_vehicles);

    for (const auto& other_vehicle : vehicles) {

        if (other_vehicle->symbol != vehicle->symbol) {

            add_vehicle_to_list(other_vehicle, new_list_of_vehicles);

        }

    }

    return new_list_of_vehicles;

}
