#ifndef GAME_HEADER_FILE
#define GAME_HEADER_FILE

#include <algorithm> // find_if
#include <iostream>
#include <map> // map, make_pair
#include <vector>

#include "board.hpp"
#include "utility_funcs.hpp"
#include "vehicle.hpp"

struct Game {
    
    Game();
    Game(const std::string&);
    
    auto retrieve_initial_board() const -> Board;
    
    private:
        const Board initial_board;
        
        auto build_board_from_string(const std::string&) -> std::vector<std::vector<char>>;
        auto build_initial_board(const std::string&) -> Board;
        auto inline find_exit_row(const std::vector<std::vector<char>>&) const -> size_t;
        auto inline get_default_board() -> std::vector<std::vector<char>>;
        auto locate_vehicles(std::vector<std::vector<char>>&) const -> std::map<char, Vehicle>;
    
};

#endif // GAME_HEADER_FILE