#include "collision_detected.hpp"

#include <iostream>

bool collision_detected(const uint64_t& board_state, const uint64_t& move_board) {

    return ( (board_state & move_board) > 0 );

}
