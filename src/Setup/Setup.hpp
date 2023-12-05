#ifndef __INITIALIZER_H__
#define __INITIALIZER_H__

#include <cstdint>
#include <forward_list>
#include <map>
#include <memory>
#include <stdexcept>
#include <vector>

#include "Board.hpp"


class Setup {

public:

    Setup() = default;
    virtual ~Setup() = default;

    Setup(const Setup&) = delete;
    Setup(Setup&&) = delete;
    Setup& operator=(const Setup&) = delete;
    Setup& operator=(Setup&&) = delete;

    virtual std::unique_ptr<Board> build_starting_board() = 0;

protected:

    using boardstrings = std::map<char, std::vector<uint8_t>>;
    using linkedlist_of_vehicles = std::forward_list<std::unique_ptr<Vehicle>>;
    using vehicle_map = std::map<char, std::vector<uint8_t>>;

    linkedlist_of_vehicles initialize_vehicles(const vehicle_map& vehicles);
    boardstrings parse_board_string(const std::string& board_string);

    bool board_is_empty(const uint64_t& bitboard);
    bool board_has_player_vehicle(const boardstrings& vehicles);

    const uint8_t NUM_CHARACTERS_IN_CMD_LINE_STRING { 36 };

};

#endif /* __INITIALIZER_H__ */
