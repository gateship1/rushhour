#ifndef BOARD_HEADER_FILE
#define BOARD_HEADER_FILE

#include <algorithm> // find_if, min
#include <iostream>
#include <map> // map
#include <cmath> // cos, sin
#include <sstream> // stringstream
#include <vector>

#include "vehicle.hpp"

// player vehicle is a global variable and is 'x'
const char player_vehicle_id = 'x'; 

/* Board class
  
  data structure containing a board state
  
  data elements:
    width, width of the playable board (default 6 spaces)
    height, height of the playable board (default 6 spaces)
    exit_row, the row in which the player vehicle is located (exit on right)
    vehicles, the set of vehicles on the board
    signature, the string representation (or signature) of the vehicle layout on the board
*/
struct Board {
    
    Board(); // only used for error checking input
    Board(const size_t&, const size_t&, const size_t&, const std::map<char, Vehicle>&);
    
    auto is_solution_state() const -> bool;
    
    static auto generate_signature(const size_t&, const size_t&, 
        const size_t&, const std::map<char, Vehicle>&) -> std::string;
    
    // getters
    auto get_exit_row() const -> size_t;
    auto get_height() const -> size_t;
    auto get_signature() const -> std::string;
    auto get_vehicles() const -> std::map<char, Vehicle>;
    auto get_width() const -> size_t;
    
    static auto hboard_border(const size_t&) -> std::string;
    auto move_down(const Vehicle&, const size_t&) const -> bool;
    auto move_left(const Vehicle&, const size_t&) const -> bool;
    auto move_right(const Vehicle&, const size_t&) const -> bool;
    auto move_up(const Vehicle&, const size_t&) const -> bool;
    auto next() const -> std::vector<Board>;
    auto next_for_vehicle(const Vehicle&) const -> std::vector<Board>;
    static auto print_board_set(const std::vector<Board>&) -> void;
    static auto print_path(const std::vector<Board>&, const size_t& n=6) -> void;
    
    friend std::ostream& operator<<(std::ostream&, const Board&);
    
    private:
        const size_t width, height, exit_row;
        const std::map<char, Vehicle> vehicles;
        const std::string signature;
    
};

#endif // BOARD_HEADER_FILE