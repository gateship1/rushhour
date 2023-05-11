#ifndef __HEURISTICS_H__
#define __HEURISTICS_H__

#include <memory>

#include "Board.hpp"
#include "defines.hpp"


typedef uint8_t (*heuristic_cb)(const std::unique_ptr<Board>&);


/* manhattan_distance_1D
  
  calculate the manhattan distance between the goal location and the leading edge of the player vehicle

*/
uint8_t manhattan_distance_1D(const std::unique_ptr<Board>& board);


/* number_of_obstacles_1D

  calculate the number of obstacles between the goal location and the leading edge of the player vehicle

*/
uint8_t number_of_obstacles_1D(const std::unique_ptr<Board>& board);


/* player_heuristic_1D
  
  a heuristic that combines the manhattan distance between the leading edge of the player vehicle and the goal and
  the number of obstacles between the leading edge of the player vehicle and the goal

*/
uint8_t player_heuristic_1D(const std::unique_ptr<Board>& board);


/* heuristic0

  returns '0' as the heuristic (so A* can be used as a BFS - mainly for demo purposes)

*/
uint8_t heuristic0(const std::unique_ptr<Board>& board=nullptr);


#endif /* __HEURISTICS_H__ */
