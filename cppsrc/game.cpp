#include "game.hpp"

/* Constructor
  
  No input provided and the default board is used
*/
Game::Game() : initial_board(this->build_initial_board(std::string())) {
}

/* Constructor
  
  Input string provided for the board
*/
Game::Game(const std::string& clistr) : initial_board(this->build_initial_board(clistr)) {
}

/* retrieve_initial_board
  
  return:
    the initial board
*/
auto Game::retrieve_initial_board() const -> Board {
    return this->initial_board;
}

/* build_board_from_string
  
  parameters:
    board_str, the command line string used to build the board
               ' ' represents unoccupied spaces
               a char represents a vehicle (typically but not necessarily a color)
               player vehicle is player_vehicle_id
               '|' represents a new row
  
  return:
    a set of characters representing the board layout
*/
auto Game::build_board_from_string(const std::string& board_str) -> std::vector<std::vector<char>> {
    
    std::vector<std::vector<char>> new_board{};
    std::vector<char> board_row{};
    std::vector<size_t> row_widths{};
    size_t row_width{0};
    
    auto equal_row_widths = [](const std::vector<size_t>& widths) {
        return std::adjacent_find( widths.begin(), widths.end(), std::not_equal_to<>() ) == widths.end() 
               ? true : false;
    };
    
    for (const auto& row_char : board_str) {
        row_width++;
        if (row_char == '|') {
            row_widths.push_back(row_width-1);
            row_width = 0; // reset row width
            new_board.push_back(board_row);
            board_row = {}; // reset the row array
            continue;
        }
        board_row.push_back(row_char);
    }
    row_widths.push_back(row_width);
    new_board.push_back(board_row);
    
    // ensure the rows in the board are all the same width
    if (!equal_row_widths(row_widths)) {
        std::vector<std::vector<char>> bad_board{};
        return bad_board;
    }
    
    return new_board;
}

/* build_initial_board
  
  parameters:
    clistr, command line input string used to determine how to build the initial board
  
  return:
    board, the initial board
*/
auto Game::build_initial_board(const std::string& clistr) -> Board {
    
    std::vector<std::vector<char>> board{};
    
    if (clistr.empty()) {
        board = this->get_default_board();
    } else {
        board = this->build_board_from_string(clistr);
        if (board.empty()) { // input error check
            Board empty_board;
            return empty_board;
        };
    }
    
    const auto board_height{board.size()};
    const auto board_width{board[0].size()};
    // find the exit row (row that contains the player vehicle)
    const auto exit_row{this->find_exit_row(board)};
    // find the vehicles on the board
    const auto vehicles{this->locate_vehicles(board)};
    for (const auto& [vehicle_id, vehicle_data] : vehicles) {
        // check to ensure no horizontally oriented vehicles are in the exit row between
        // the player car and the board exit - this is an illegal configuration
        if (vehicle_id != player_vehicle_id && (vehicle_data.get_direction() == 0 &&
            vehicle_data.get_y0() == vehicles.at(player_vehicle_id).get_y0() &&
            vehicle_data.get_x0() > vehicles.at(player_vehicle_id).get_x0())) {
                return Board(board_width, board_height, exit_row, std::map<char, Vehicle>{});
        }
    }
    
    return Board(board_width, board_height, exit_row, vehicles);
}

/* get_default_board
  
  returns the default game board layout, mostly used for demonstration and testing
*/
auto Game::get_default_board() -> std::vector<std::vector<char>> {
    std::vector<std::vector<char>> default_board{
        {' ', ' ', 'o', ' ', 'a', 'a'},
        {' ', ' ', 'o', ' ', ' ', ' '},
        {player_vehicle_id, player_vehicle_id, 'o', ' ', ' ', ' '},
        {'p', 'p', 'p', ' ', ' ', 'q'},
        {' ', ' ', ' ', ' ', ' ', 'q'},
        {' ', ' ', ' ', ' ', ' ', 'q'}
    };
    return default_board;
}

/* find_exit_row
  
  finds the row containing the player vehicle (and hence the exit)
  
  parameters:
    board, the initial board state
  
  return:
    the row containing the player vehicle, player_vehicle_id
*/
auto Game::find_exit_row(const std::vector<std::vector<char>>& board) const -> size_t {
    
    const auto it{std::find_if(std::begin(board), std::end(board), 
        [](const std::vector<char>& board_row) -> bool {
            return std::find(board_row.begin(), board_row.end(), player_vehicle_id) != board_row.end();
        })
    };
    return it - board.begin();
}

/* locate_vehicles
  
  locate the vehicle positions on the initial board
  
  parameters:
    board, the initial board state
  
  return:
    the set of vehicles on the board, includes -
      vehicle character identifier
      vehicle position
      number of spaces occupied by the vehicle
      vehicle orientation
    NOTE: return is empty if the player vehicle is not found (and correctly oriented)
*/
auto Game::locate_vehicles(std::vector<std::vector<char>>& board) const -> std::map<char, Vehicle> {
    
    auto board_width{board[0].size()};
    bool player_vehicle{false};
    
    std::map<char, Vehicle> vehicles{}; // initialize empty set of vehicles on the board
    
    // find the horizontally oriented vehicles
    size_t i{0}, j{0};
    for (const auto& row : board) {
        j = 1; // track position in row
        size_t vehicle_size{1};
        while (j < row.size()) {
            while ((j < board_width - 1) && (row.at(j) == ' ')) j++; // empties are not vehicles (obviously)
            // vehicle found, determine its size
            while ((j < board_width) && (row.at(j) == row.at(j-1)) && (row.at(j) != ' ')) {
                vehicle_size++;
                j++;
            }
            if (vehicle_size > 1) { // horizontally oriented vehicle found
                // add this vehicle to the set of vehicles
                vehicles.insert(std::make_pair(row.at(j-1), Vehicle(row.at(j-1), j - vehicle_size, i, vehicle_size, 0)));
                if (row.at(j-1) == player_vehicle_id) player_vehicle = true; // player vehicle found and correctly oriented
            }
            vehicle_size = 1;
            j++;
        }
        i++; // move to the next row
    }
    
    // find the vertically oriented vehicles
    auto transposed_board{transpose_vector_of_vectors<char>(board)};
    
    auto board_height{transposed_board[0].size()};
    
    i = 0 , j = 0;
    for (const auto& col : transposed_board) {
        i = 1;
        size_t vehicle_size{1};
        while (i < board_height) {
            while ((i < board_height - 1) && (col.at(i) == ' ')) i++; // empties are not vehicles (obviously)
            // vehicle found, determine its size
            while ((i < board_height) && (col.at(i) == col.at(i-1)) && (col.at(i) != ' ')) {
                vehicle_size++;
                i++;
            }
            if (vehicle_size > 1) { // vertically oriented vehicle found
                // add this vehicle to the set of vehicles
                vehicles.insert(std::make_pair(col.at(i-1), Vehicle(col.at(i-1), 
                                j, i - vehicle_size, vehicle_size, 90)));
            }            
            vehicle_size = 1;
            i++;
        }
        j++;
    }
    
    if (player_vehicle == false) vehicles.clear();
    return vehicles;
}