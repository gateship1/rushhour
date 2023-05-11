#include "heuristics.hpp"


uint8_t manhattan_distance_1D(const std::unique_ptr<Board>& board) {

    uint8_t moves_to_goal { 0 };
    uint64_t player_car_position { board->get_state_of_vehicle(PLAYER_VEHICLE_ID) };

    while ( !(player_car_position & GOAL) ) {
        ++moves_to_goal;
        player_car_position >>= 1;
    }

    return moves_to_goal;

}


uint8_t number_of_obstacles_1D(const std::unique_ptr<Board>& board) {

    uint8_t obstacle_count { 0 };
    uint64_t player_car_position { board->get_state_of_vehicle(PLAYER_VEHICLE_ID) };
    uint64_t board_state { board->get_state() ^ player_car_position };

    while ( !(player_car_position & GOAL) ) {

        player_car_position >>= 1;

        uint64_t collision_cell { player_car_position & board_state };

        if ( collision_cell ) {
            board_state ^= collision_cell;
            ++obstacle_count;
        }

    }

    return obstacle_count;

}


uint8_t player_heuristic_1D(const std::unique_ptr<Board>& board) {

    return static_cast<uint8_t>( manhattan_distance_1D(board) + number_of_obstacles_1D(board) );

}


uint8_t heuristic0(const std::unique_ptr<Board>& board)  {

    static_cast<void>(board); // unused parameter
    return static_cast<uint8_t>(0);

}
