#ifndef HEURISTICS_HEADER_FILE
#define HEURISTICS_HEADER_FILE

#include "board.hpp"

/* heuristic0
  
  returns '0' as the heuristic (so A* can be used as a BFS - mainly for demo purposes)
  
  parameter:
    board, the game state (or board layout) - irrelevant as it will always return 0
  
  return:
    0
*/
inline auto heuristic0 = [](const Board& board) {
    return 0;
};

/* manhattan_distance_1D
  
  calculate the manhattan distance between the goal location and the leading edge of the player vehicle
  
  parameter:
    board, the game state (or board layout)
  
  return:
    the calculated manhattan distance
*/
inline auto manhattan_distance_1D = [](const Board& board) {
    auto goal{board.get_width() - 1};
    auto leading_edge{board.get_vehicles().at(player_vehicle_id).get_x1()};
    return (goal - leading_edge);
};

/* num_obstacles_1D
  
  calculate the number of obstacles between the goal location and the leading edge of the player vehicle
  
  parameter:
    board, the game state (or board layout)
  
  return:
    the calculated number of obstacles
*/
inline auto num_obstacles_1D = [](const Board& board) {
    auto leading_edge{board.get_vehicles().at(player_vehicle_id).get_x1()};
    auto player_vert_pln{board.get_vehicles().at(player_vehicle_id).get_y0()};
    size_t nobstacle{0};
    for (const auto& vehicle : board.get_vehicles()) {
        // only need to check vertical vehicles (horizontal vehicles cannot be between the leading edge of the player vehicle and the exit 
        // - this is an illegal board configuration and is handled by the input handlers)
        if (vehicle.second.get_direction() == 90) {
            // check if horizontal position is between the leading edge and the board exit
            if (!(vehicle.second.get_x0() > leading_edge)) continue; // input handling ensures all vehicles are "on the board"
            // if the vehicle breaks the verticle plain of the other vehicle
            if ((vehicle.second.get_y0() == player_vert_pln) || // check if vertical origin of vehicle is in the same plain as the player vehicle
                // check if vertical leading edge is in the same plain as the player vehicle
                (vehicle.second.get_y1() == player_vert_pln) || 
                // check if the middle of the vehicle is in the same plain as the player vehicle
                ((player_vert_pln > vehicle.second.get_y0()) &&
                 (player_vert_pln < vehicle.second.get_y1())))
                nobstacle++; // if any of these are true, there is an obstacle, increment the obstacle count
        }
    }
    return nobstacle;
};

/* player_heuristic
  
  a heuristic that combines the manhattan distance between the leading edge of the player vehicle and the board exit and
  the number of obstacles between the leading edge of the player vehicle and the board exit
  
  parameter:
    board, the game state (or board layout)
  
  return:
    the manhattan distance + the number of obstacles
*/
inline auto player_heuristic = [](const Board& board) {
    return manhattan_distance_1D(board) + num_obstacles_1D(board);
};


#endif // HEURISTICS_HEADER_FILE