#include <stdexcept>

#include "defines.hpp"
#include "HorizontalVehicle.hpp"
#include "Setup.hpp"
#include "Vehicle.hpp"
#include "VerticalVehicle.hpp"


Setup::linkedlist_of_vehicles Setup::initialize_vehicles(const vehicle_map& vehicles) {

    linkedlist_of_vehicles list_of_vehicles { };
    uint64_t initial_game_bitboard { };

    for (auto vehicle : vehicles) {

        uint64_t vehicle_bitboard { };

        std::array<uint8_t, 3> cells { };
        uint8_t i { };

        for (auto val : vehicle.second) {

            cells[i++] = val;

            val = static_cast<uint8_t>(val + 9);
            if (val > 14) val = static_cast<uint8_t>(val + 2);
            if (val > 22) val = static_cast<uint8_t>(val + 2);
            if (val > 30) val = static_cast<uint8_t>(val + 2);
            if (val > 38) val = static_cast<uint8_t>(val + 2);
            if (val > 46) val = static_cast<uint8_t>(val + 2);

            vehicle_bitboard |= (static_cast<uint64_t>(1) << val);

        }

        initial_game_bitboard |= vehicle_bitboard;

        if (vehicle.first == 'x')
            list_of_vehicles.emplace_front( std::make_unique<PlayerVehicle>(vehicle_bitboard) );
        else {
            if (cells.at(0) - 1 == cells.at(1))
                list_of_vehicles.emplace_front( std::make_unique<HorizontalVehicle>(vehicle_bitboard, vehicle.first) );
            else
                list_of_vehicles.emplace_front( std::make_unique<VerticalVehicle>(vehicle_bitboard, vehicle.first) );
        }

    }

    if ( board_is_empty(initial_game_bitboard) )
        throw std::invalid_argument("board is empty!");

    return list_of_vehicles;

}


Setup::boardstrings Setup::parse_board_string(const std::string& board_string) {

    if (board_string.length() != NUM_CHARACTERS_IN_CMD_LINE_STRING)
        throw std::invalid_argument("Malformed board string!");

    boardstrings vehicles { };

    uint8_t i { };
    for (const auto& character : board_string) {
        
        if (character == ' ') {
            ++i;
            continue;
        }

        if (vehicles.find(character) == vehicles.end()) {
            uint8_t offset ( static_cast<uint8_t>(NUM_CHARACTERS_IN_CMD_LINE_STRING - 1 - i) );
            vehicles.insert( std::make_pair( character, std::vector<uint8_t>( { offset } ) ) );
        } else {
            vehicles.at(character).push_back(static_cast<uint8_t>(NUM_CHARACTERS_IN_CMD_LINE_STRING - 1 - i) );
        }
        ++i;
    }

    if ( !board_has_player_vehicle(vehicles) )
        throw std::invalid_argument("board does not have a player vehicle!");

    return vehicles;

}


bool Setup::board_is_empty(const uint64_t& bitboard) {

    return !(bitboard & (0xFFFF'FFFF'FFFF'FFFF)) ? true : false; 

}


bool Setup::board_has_player_vehicle(const boardstrings& vehicles) {

    return (vehicles.find(PLAYER_VEHICLE_ID) != vehicles.end()) ? true : false;

}
