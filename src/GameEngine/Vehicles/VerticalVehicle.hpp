#ifndef __VERTICAL_VEHICLE_H__
#define __VERTICAL_VEHICLE_H__

#include "Vehicle.hpp"

class VerticalVehicle : public Vehicle {

public:

    explicit VerticalVehicle(const uint64_t& bitboard_, const char& symbol_) noexcept;
    ~VerticalVehicle() = default;

    VerticalVehicle(const VerticalVehicle&) = delete;
    VerticalVehicle(VerticalVehicle&&) = delete;
    VerticalVehicle& operator=(const VerticalVehicle&) = delete;
    VerticalVehicle& operator=(VerticalVehicle&&) = delete;

    std::unique_ptr<VerticalVehicle> move_down();
    std::unique_ptr<VerticalVehicle> move_up();

    virtual std::forward_list<std::unique_ptr<Vehicle>> move_until_collision_with(const uint64_t& board) override final;
    virtual std::array<std::unique_ptr<Vehicle>, 2> next_moves() override;

protected:

    enum MOVE_DIRECTION { DOWN, UP };

    virtual std::forward_list<std::unique_ptr<Vehicle>> move_down_until_collision_with(const uint64_t& board);
    virtual std::forward_list<std::unique_ptr<Vehicle>> move_up_until_collision_with(const uint64_t& board);

};

#endif /* __VERTICAL_VEHICLE_H */
