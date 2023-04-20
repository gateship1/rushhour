#include "board.hpp"

/* Empty Board constructor
  
  creates an empty board (signature of an input error as the board state cannot be modified after creation)
*/
Board::Board() : width(), height(), exit_row(), vehicles(), signature() {}; 

/* Board constructor
  
  creates a new board state
  
  parameters:
    id_, the character identifying a vehicle (typically a color representation, e.g. 'w' for "white")
    x0_, the leftmost space occupied by the vehicle (for "vertical" vehicles x0 = x1)
    y0_, the bottommost space occupied by the vehicle (for "horizontal" vehicles y0 = y1)
    spaces_, the number of spaces occupied by the vehicle
    direction_, the orientation of the vehicle ("horizontal" or "vertical")
*/
Board::Board(const size_t& width_, const size_t& height_, 
    const size_t& exit_row_, const std::map<char, Vehicle>& vehicles_) :
    width(width_), height(height_), exit_row(exit_row_), vehicles(vehicles_), 
    signature(Board::generate_signature(width_, height_, exit_row_, vehicles_)) {
}

/* is_solution_state
  
  check if the player vehicle (typically "xx") is touching the open space on the right of the board
  
  return:
    true if the leading space occupied by the player vehicle is adjacent to the open space on the right
         of the board in the "exit row"
    false otherwise
*/
auto Board::is_solution_state() const -> bool {
    
    // determine if the board is in a solution state
    return (this->vehicles.at(player_vehicle_id).get_direction() == 0) && // player vehicle must be oriented in the horizontal direction
            (this->vehicles.at(player_vehicle_id).get_y0() == this->exit_row) && // player vehicle must be in the exit row
            // leading space (furthestmost right) occupied by the player vehicle must be adjacent to the board exit
            ((this->vehicles.at(player_vehicle_id).get_x1()) == (this->width - 1)) ? true : false;
}

/* generate_signature
  
  create a simple hash (or signature) of the board layout, specifically the vehicle locations
  
  parameters:
    height, the number of board rows
    width, the number of board columns
    exit_row, the row in which the exit is located
    vehicles, the vehicles on the board and their data
  
  return:
    board_signature, a hash of the board layout (in hexidecimal)
*/
auto Board::generate_signature(const size_t& height, const size_t& width, 
    const size_t& exit_row, const std::map<char, Vehicle>& vehicles) -> std::string {
    
    std::stringstream ss{};
    
    for (size_t i{0}; i < height; ++i) {
        for (size_t j{0}; j < width; ++j) {
            bool occupied{false};
            for (const auto& [vehicle_id, vehicle_data] : vehicles) {
                if ((vehicle_data.get_direction() == 0) && (vehicle_data.get_x0() <= j) && 
                    (vehicle_data.get_x1() >= j) &&
                    (vehicle_data.get_y0() == i)) {
                        ss << std::hex << static_cast<int>(vehicle_id);
                        occupied = true;
                        break;
                } else if ((vehicle_data.get_direction() == 90) && (vehicle_data.get_y0() <= i) && 
                    (vehicle_data.get_y1() >= i) &&
                    (vehicle_data.get_x0() == j)) {
                        ss << std::hex << static_cast<int>(vehicle_id);
                        occupied = true;
                        break;                    
                } 
            }
            if (occupied == false) {
                ss << std::hex << static_cast<int>(' ');
            }
        }
    }
    std::string board_signature{ss.str()};
    return board_signature;
}

auto Board::get_exit_row() const -> size_t {
    return this->exit_row;
}

auto Board::get_height() const -> size_t {
    return this->height;
}

auto Board::get_signature() const -> std::string {
    return this->signature;
}

auto Board::get_vehicles() const -> std::map<char, Vehicle> {
    return this->vehicles;
}

auto Board::get_width() const -> size_t {
    return this->width;
}

/* hboard_border
  
  saves the horizontal board boarder into a string for output to the terminal
  
  parameters:
    board_width, the width of the board (or the length of the boarder string)
  
  return:
    string representing the horizontal board border
*/
auto Board::hboard_border(const size_t& board_width) -> std::string {
    std::string boarder{};
    boarder.reserve(board_width);
    for (size_t i{0}; i < board_width; ++i)
        boarder.append("-");
    return boarder;
}

/* move_down
  
  detect collisions for a vehicle attempting to move down
  
  parameters:
      vehicle, the vehicle attempting to be moved
      move_space, the bottommost space for the vehicle to potentially occupy
  
  return:
      true if the vehicle can move down move_space without a collision
      false otherwise
*/
auto Board::move_down(const Vehicle& vehicle, const size_t& move_space) const -> bool {
        
    // first check if the vehicle is within the board boundaries
    if (move_space == this->height - 1) return false; // if it is, it cannot move down
    
    for (const auto& [other_vehicle, other_vehicle_data] : this->vehicles) {
        
        // if the vehicle to move is the current vehicle retrieved, skip the retrieved vehicle
        if (vehicle.get_id() == other_vehicle) 
            continue;
        
        // if the vehicle to move isn't in the same horizontal plain as the current vehicle retrieved,
        // skip the retrieved vehicle
        else if (vehicle.get_x0() != other_vehicle_data.get_x0() && other_vehicle_data.get_direction() == 90) 
            continue;
        
        // other vehicle above of current vehicle and cannot cause a collision moving down
        else if (vehicle.get_y1() > other_vehicle_data.get_y0())
            continue;
        
        else {
            // the vehicle cannot move into this space because the space is occupied
            if (move_space + 1 == other_vehicle_data.get_y0() && (
                (vehicle.get_x0() >= other_vehicle_data.get_x0() && vehicle.get_x1() <= other_vehicle_data.get_x1()))
            ) return false;
        }
    }
    return true; // no collisions detected, vehicle can move vertically down move_space
}

/* move_left
  
  detect collisions for a vehicle attempting to move left
  
  parameters:
      vehicle, the vehicle attempting to be moved
      move_space, the leftmost space for the vehicle to potentially occupy
  
  return:
      true if the vehicle can move left move_space without a collision
      false otherwise
*/
auto Board::move_left(const Vehicle& vehicle, const size_t& move_space) const -> bool {
        
    // first check if the vehicle is within the board boundaries
    if (move_space == 0) return false; // if it is, it cannot move left
    
    for (const auto& [other_vehicle, other_vehicle_data] : this->vehicles) {
        
        // if the vehicle to move is the current vehicle retrieved, skip the retrieved vehicle
        if (vehicle.get_id() == other_vehicle) 
            continue;
        
        // if the vehicle to move isn't in the same vertical plain as the current vehicle retrieved, 
        // skip the retrieved vehicle
        else if (vehicle.get_y0() != other_vehicle_data.get_y0() && other_vehicle_data.get_direction() == 0) 
            continue;
        
        // other vehicle to the left of current vehicle and cannot cause a collision moving left
        else if (vehicle.get_x1() < other_vehicle_data.get_x0())
            continue;
        
        else {
            // the vehicle cannot move into this space because the space is occupied
            if (move_space - 1 == other_vehicle_data.get_x1() && (
                (vehicle.get_y0() >= other_vehicle_data.get_y0() && vehicle.get_y1() <= other_vehicle_data.get_y1()))
            ) return false;
        }
    }
    return true; // no collisions detected, vehicle can move horizontally move_space to the left
}

/* move_right
  
  detect collisions for a vehicle attempting to move right
  
  parameters:
      vehicle, the vehicle attempting to be moved
      move_space, the rightmost space for the vehicle to potentially occupy
  
  return:
      true if the vehicle can move right move_space without a collision
      false otherwise
*/
auto Board::move_right(const Vehicle& vehicle, const size_t& move_space) const -> bool {
        
    // first check if the vehicle is within the board boundaries
    if (move_space == this->width - 1) return false; // if it is, it cannot move right
    
    for (const auto& [other_vehicle, other_vehicle_data] : this->vehicles) {
        
        // if the vehicle to move is the current vehicle retrieved, skip the retrieved vehicle
        if (vehicle.get_id() == other_vehicle) 
            continue;
        
        // if the vehicle to move isn't in the same vertical plain as the current vehicle retrieved, 
        // skip the retrieved vehicle
        else if (vehicle.get_y0() != other_vehicle_data.get_y0() && other_vehicle_data.get_direction() == 0) 
            continue;
        
        // other vehicle to the left of current vehicle and cannot cause a collision moving right
        else if (vehicle.get_x0() > other_vehicle_data.get_x1())
            continue;
        
        else {
            // the vehicle cannot move into this space because the space is occupied
            if (move_space + 1 == other_vehicle_data.get_x0() && (
                (vehicle.get_y0() >= other_vehicle_data.get_y0() && vehicle.get_y1() <= other_vehicle_data.get_y1()))
            ) return false;
        }
    }
    return true; // no collisions detected, vehicle can move horizontally move_space to the right
}

/* move_up
  
  detect collisions for a vehicle attempting to move up
  
  parameters:
      vehicle, the vehicle attempting to be moved
      move_space, the uppermost space for the vehicle to potentially occupy
  
  return:
      true if the vehicle can move up move_space without a collision
      false otherwise
*/
auto Board::move_up(const Vehicle& vehicle, const size_t& move_space) const -> bool {
        
    // first check if the vehicle is within the board boundaries
    if (move_space == 0) return false; // if it is, it cannot move up
    
    for (const auto& [other_vehicle, other_vehicle_data] : this->vehicles) {
        
        // if the vehicle to move is the current vehicle retrieved, skip the retrieved vehicle
        if (vehicle.get_id() == other_vehicle) 
            continue;
        
        // if the vehicle to move isn't in the same horizontal plain as the current vehicle retrieved,
        // skip the retrieved vehicle
        else if (vehicle.get_x0() != other_vehicle_data.get_x0() && other_vehicle_data.get_direction() == 90) 
            continue;
        
        // other vehicle above of current vehicle and cannot cause a collision moving up
        else if (vehicle.get_y0() < other_vehicle_data.get_y1())
            continue;
        
        else {
            // the vehicle cannot move into this space because the space is occupied
            if (move_space - 1 == other_vehicle_data.get_y1() && (
                (vehicle.get_x0() >= other_vehicle_data.get_x0() && vehicle.get_x1() <= other_vehicle_data.get_x1()))
            ) return false;
        }
    }
    return true; // no collisions detected, vehicle can move vertically up move_space
}

/* next
  
  get set of next board states
  
  return:
    set of next board states from the current board state
*/
auto Board::next() const -> std::vector<Board> {
    std::vector<Board> next_boards{};
    for (const auto& vehicle : this->vehicles) {
        auto next_boards_for_vehicle{this->next_for_vehicle(vehicle.second)};
        for (const auto& board: next_boards_for_vehicle) {
            next_boards.push_back(board);
        }
    }
    return next_boards;
}

/* next_for_vehicle
  
  determine all possible move states for a vehicle given its current state
  
  parameters:
    vehicle, the current vehicle state
  
  return:
    the set of all possible move states for the vehicle
*/
auto Board::next_for_vehicle(const Vehicle& vehicle) const -> std::vector<Board> {
    
    std::vector<Board> next_boards{};
    
    // horizontal moves
    if (vehicle.get_direction() == 0) {
        
        // right moves    
        size_t rspace{0}; // number of horizontal spaces to the right
        size_t x0{vehicle.get_x0()}; // left most space of the vehicle
        size_t x1{vehicle.get_x1()}; // right most space of the vehicle
        
        while (this->move_right(vehicle, x1 + rspace)) {
            rspace++; // check the next space horizontal space to the right
            auto vehicles{this->vehicles};  // copy the set of vehicles on the board
            vehicles.erase(vehicle.get_id()); // remove the current vehicle from the dictionary
            // add the vehicle back into the dictionary in its modified position
            vehicles.insert(
                std::pair<char, Vehicle>(
                    vehicle.get_id(), 
                    Vehicle(vehicle.get_id(), x0 + rspace, // move vehicle horizontal origin right "rspace" spaces
                        vehicle.get_y0(), vehicle.get_spaces(), vehicle.get_direction()
                    )
                )
            );
            // add the new board state to the list of possible next boards
            next_boards.push_back(Board(this->width, this->height, this->exit_row, vehicles));
        }
        
        // left moves
        size_t lspace{0}; // number of horizontal spaces to the left
        
        while (this->move_left(vehicle, x0 - lspace)) {
            lspace++; // check the next space horizontal space to the left
            auto vehicles{this->vehicles};  // copy the set of vehicles on the board
            vehicles.erase(vehicle.get_id()); // remove the current vehicle from the dictionary
            // add the vehicle back into the dictionary in its modified position
            vehicles.insert(
                std::pair<char, Vehicle>(
                    vehicle.get_id(), 
                    Vehicle(vehicle.get_id(), x0 - lspace, // move vehicle horizontal origin left "lspace" spaces
                        vehicle.get_y0(), vehicle.get_spaces(), vehicle.get_direction()
                    )
                )
            );
            // add the new board state to the list of possible next boards
            next_boards.push_back(Board(this->width, this->height, this->exit_row, vehicles));
        }
    
    } else if (vehicle.get_direction() == 90) { //vertical moves
        
        // up moves    
        size_t uspace{0}; // number of vertical spaces upward
        size_t y0{vehicle.get_y0()}; // uppermost space of the vehicle
        size_t y1{vehicle.get_y1()}; // bottommost space of the vehicle
        
        while (this->move_up(vehicle, y0 - uspace)) {
            uspace++; // check the next space vertical space upward
            auto vehicles{this->vehicles};  // copy the set of vehicles on the board
            vehicles.erase(vehicle.get_id()); // remove the current vehicle from the dictionary
            // add the vehicle back into the dictionary in its modified position
            vehicles.insert(
                std::pair<char, Vehicle>(
                    vehicle.get_id(), 
                    Vehicle(vehicle.get_id(), vehicle.get_x0(), y0 - uspace, // move vehicle vertical origin up "uspace" spaces
                        vehicle.get_spaces(), vehicle.get_direction()
                    )
                )
            );
            // add the new board state to the list of possible next boards
            next_boards.push_back(Board(this->width, this->height, this->exit_row, vehicles));
        }
        
        // down moves    
        size_t dspace{0}; // number of vertical spaces downward
        
        while (this->move_down(vehicle, y1 + dspace)) {
            dspace++; // check the next space vertical space downward
            auto vehicles{this->vehicles};  // copy the set of vehicles on the board
            vehicles.erase(vehicle.get_id()); // remove the current vehicle from the dictionary
            // add the vehicle back into the dictionary in its modified position
            vehicles.insert(
                std::pair<char, Vehicle>(
                    vehicle.get_id(), 
                    Vehicle(vehicle.get_id(), vehicle.get_x0(), y0 + dspace, // move vehicle vertical origin down "dspace" spaces
                        vehicle.get_spaces(), vehicle.get_direction()
                    )
                )
            );
            // add the new board state to the list of possible next boards
            next_boards.push_back(Board(this->width, this->height, this->exit_row, vehicles));
        }
    }
    return next_boards; // default empty move set for invalid direction
}

/* print_board_set
  
  print a set of boards to the console
  
  parameters:
    boards, the set of boards to be output
  
*/
auto Board::print_board_set(const std::vector<Board>& boards) -> void {
    
    if (boards.empty()) return; // ensure some board set is sent in
    
    // define lambda to print the upper and lower (horizontal boarders)
    auto print_boarder = [&boards = std::as_const(boards)]() {
        for (const auto& board : boards) {
            std::cout << ' ';
            for (size_t j{0}; j < board.get_width(); ++j) {
                std::cout << '-'; // print the upper boarder of the game board
            }
            std::cout << "  ";
        }
        std::cout << '\n';
    };
    
    // upper boarder
    print_boarder();
    
    // print the board set to the terminal
    for (size_t i{0}; i < boards.at(0).get_height(); ++i) {
        for (const auto& board : boards) {
            std::cout << '|'; // left border
            for (size_t j{0}; j < board.get_width(); ++j) {
                bool occupied{false};
                for (const auto& [vehicle_id, vehicle_data] : board.get_vehicles()) {
                    if (vehicle_data.get_direction() == 0 && vehicle_data.get_x0() <= j &&
                        vehicle_data.get_x1() >= j &&
                        vehicle_data.get_y0() == i) {
                        std::cout << vehicle_id;
                        occupied = true;
                        break;
                    } else if (vehicle_data.get_direction() == 90 && vehicle_data.get_y0() <= i &&
                        vehicle_data.get_y1() >= i &&
                        vehicle_data.get_x0() == j) {
                        std::cout << vehicle_id;
                        occupied = true;
                        break;
                    }
                }
                if (occupied == false) std::cout << ' ';
            }
            if (i == board.get_exit_row()) std::cout << ' '; // exit
            else std::cout << '|'; // right boarder of the game board
            std::cout << ' ';
        }
        std::cout << '\n';
    }
    
    // lower boarder
    print_boarder();
    
    return;
}

/* print_path
  
  print the current path
  
  parameters:
    n, the number of boards to print the terminal before a new row
*/
auto Board::print_path(const std::vector<Board>& sol_path, const size_t& n) -> void {
    
    // extract a sublist of boards from the board list
    auto sub_path = [&sol_path = std::as_const(sol_path)] (const size_t& m, const size_t& n) {
            auto first{sol_path.begin() + m};
            auto last{std::min(sol_path.begin() + n, sol_path.end())};
            std::vector<Board> sub_vector(first, last);
            return sub_vector;
        };
    
    size_t i{0};
    while (i < sol_path.size()) {
        Board::print_board_set(sub_path(i, i + n));
        i += n;
    }
    
    return;
}

/* overloaded cout for Board class
  
  prints the input board start to the terminal.
  
  parameters:
    os, the outstream
    board, the board state to print
  
  return:
    the outstream
*/
std::ostream& operator<<(std::ostream& os, const Board& board) {
    
    auto board_width{board.get_width()};
    auto board_height{board.get_height()};
    auto board_vehicles{board.get_vehicles()};
    auto exit_row{board.get_exit_row()};
    
    // print the upper border of the board
    os << "\n " << Board::hboard_border(board_width) << " \n";
    
    // print the board layout
    for (size_t j{0}; j < board_height; ++j) {
        os << "|"; // left boarder of the game board
        for (size_t i{0}; i < board_width; ++i) {
            auto occupied{false};
            for (const auto& [vehicle_id, vehicle_data] : board_vehicles) {
                if ((vehicle_data.get_direction() == 0) && (vehicle_data.get_x0() <= i) && 
                    (vehicle_data.get_x1() >= i) && (vehicle_data.get_y0() == j)) {
                    os << vehicle_id;
                    occupied = true;
                    break;
                } else if ((vehicle_data.get_direction() == 90) && (vehicle_data.get_y0() <= j) && 
                    (vehicle_data.get_y1() >= j) && (vehicle_data.get_x0() == i)) {
                    os << vehicle_id;
                    occupied = true;
                    break;
                }
            }
            if (occupied == false)
                os << " "; // unoccupied space
        }
        if (j == exit_row)
            os << " "; // exit
        else
            os << "|"; // right board of the game board
        os << "\n";
    }
    
    // print the lower border of the board
    os << " " << Board::hboard_border(board_width) << "\n";
    
    return os;
}
