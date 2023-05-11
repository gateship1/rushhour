#ifndef __VEHICLE_H__
#define __VEHICLE_H__

#include <array>
#include <cstdint>
#include <forward_list>
#include <memory>

#include "collision_detected.hpp"


enum class VEHICLE_ORIENTATION { HORIZONTAL, PLAYER, VERTICAL };


class Vehicle {

public:

    const uint64_t bitboard;
    const char symbol;
    VEHICLE_ORIENTATION orientation;

    explicit Vehicle(const uint64_t& bitboard_, const char& symbol_, const VEHICLE_ORIENTATION& orientation_) noexcept;
    virtual ~Vehicle() = default;

    Vehicle(const Vehicle&) = delete;
    Vehicle(Vehicle&&) = delete;

    virtual std::array<std::unique_ptr<Vehicle>, 2> next_moves() = 0;
    virtual std::forward_list<std::unique_ptr<Vehicle>> move_until_collision_with(const uint64_t& board) = 0;

};

#endif /* __VEHICLE_H__ */
