#ifndef __HORIZONTAL_VEHICLE_H__
#define __HORIZONTAL_VEHICLE_H__

#include "Vehicle.hpp"

class HorizontalVehicle : public Vehicle {

public:

    explicit HorizontalVehicle(const uint64_t& bitboard_, const char& symbol_,
        const VEHICLE_ORIENTATION& orientation_=VEHICLE_ORIENTATION::HORIZONTAL) noexcept;
    ~HorizontalVehicle() = default;

    HorizontalVehicle(const HorizontalVehicle&) = delete;
    HorizontalVehicle(HorizontalVehicle&&) = delete;
    HorizontalVehicle& operator=(const HorizontalVehicle&) = delete;
    HorizontalVehicle& operator=(HorizontalVehicle&&) = delete;

    std::unique_ptr<HorizontalVehicle> move_left();
    std::unique_ptr<HorizontalVehicle> move_right();

    virtual std::forward_list<std::unique_ptr<Vehicle>> move_until_collision_with(const uint64_t& board) override;
    virtual std::array<std::unique_ptr<Vehicle>, 2> next_moves() override;

protected:

    enum MOVE_DIRECTION { LEFT, RIGHT };

    virtual std::forward_list<std::unique_ptr<Vehicle>> move_left_until_collision_with(const uint64_t& board);
    virtual std::forward_list<std::unique_ptr<Vehicle>> move_right_until_collision_with(const uint64_t& board);

};

#endif /* __HORIZONTAL_VEHICLE_H__ */
