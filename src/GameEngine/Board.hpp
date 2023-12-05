#ifndef __BOARD_H__
#define __BOARD_H__

#include <cstdint>
#include <forward_list>
#include <memory>
#include <string>

#include "HorizontalVehicle.hpp"
#include "PlayerVehicle.hpp"
#include "Vehicle.hpp"
#include "VerticalVehicle.hpp"

class Board {

public:

    explicit Board(std::forward_list<std::unique_ptr<Vehicle>>&& vehicles_) noexcept;
    ~Board() = default;

    Board(const Board&) = delete;
    Board(Board&&) = delete;
    Board& operator=(const Board&) = delete;
    Board& operator=(Board&&) = delete;

    std::string as_string() const;
    uint64_t get_state() const;
    uint64_t get_state_of_vehicle(const char& vehicle_id) const;
    uint64_t get_state_wout_vehicle(const char& vehicle_id) const;
    bool is_solution_state() const;
    std::forward_list<std::unique_ptr<Board>> next();
    void print() const;

protected:

    void add_vehicle_to_list(const std::unique_ptr<Vehicle>& vehicle_to_add,
        std::forward_list<std::unique_ptr<Vehicle>>& list_of_vehicles);
    std::string border_as_string() const;
    std::forward_list<std::unique_ptr<Vehicle>> build_list_of_next_vehicles(
        const std::unique_ptr<Vehicle>& vehicle);

    static const uint64_t border { 0b1111'1111'1000'0001'1000'0001'1000'0000'1000'0001'1000'0001'1000'0001'1111'1111 };
    const std::forward_list<std::unique_ptr<Vehicle>> vehicles;

};


#endif /* __BOARD_H__ */
