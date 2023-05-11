#include "Vehicle.hpp"


Vehicle::Vehicle(const uint64_t& bitboard_, const char& symbol_, const VEHICLE_ORIENTATION& orientation_) noexcept :
    bitboard(bitboard_), symbol(symbol_), orientation(orientation_) {

}
