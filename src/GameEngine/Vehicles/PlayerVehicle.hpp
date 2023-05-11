#ifndef __PLAYER_VEHICLE_H__
#define __PLAYER_VEHICLE_H__

#include "HorizontalVehicle.hpp"

class PlayerVehicle : public HorizontalVehicle {

public:

    explicit PlayerVehicle(const uint64_t& bitboard_) noexcept;
    ~PlayerVehicle() = default;

    PlayerVehicle(const PlayerVehicle&) = delete;
    PlayerVehicle(PlayerVehicle&&) = delete;

    std::unique_ptr<PlayerVehicle> move_left();
    std::unique_ptr<PlayerVehicle> move_right();

protected:

    virtual std::forward_list<std::unique_ptr<Vehicle>> move_left_until_collision_with(const uint64_t& board) override final;
    virtual std::forward_list<std::unique_ptr<Vehicle>> move_right_until_collision_with(const uint64_t& board) override final;

};

#endif /* __PLAYER_VEHICLE_H__ */
