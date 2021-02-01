#include "vehicle.hpp"

/* Vehicle constructor
  
  creates a new vehicle state
  
  parameters:
    id_, the character identifying a vehicle (typically a color representation, e.g. player_vehicle_id for "red")
    x0_, the leftmost space occupied by the vehicle
    y0_, the bottommost space occupied by the vehicle
    spaces_, the number of spaces occupied by the vehicle
    direction_, the orientation of the vehicle ("horizontal" or "vertical")
*/
Vehicle::Vehicle(const char& id_, const size_t& x0_, const size_t& y0_, 
    const size_t& spaces_, const double& direction_) :
    id(id_), x0(x0_), y0(y0_), spaces(spaces_), direction(direction_), 
    x1(Vehicle::set_x1(x0_, spaces_, direction)), y1(Vehicle::set_y1(y0_, spaces_, direction)) {
}

/* getters */
auto Vehicle::get_coordinates() const -> std::tuple<size_t, size_t, size_t, size_t> {
    return std::make_tuple(this->x0, this->x1, this->y0, this->y1);
}

auto Vehicle::get_direction() const -> double {
    return this->direction;
}

auto Vehicle::get_id() const -> char {
    return this->id;
}

auto Vehicle::get_spaces() const -> size_t {
    return this->spaces;
}

auto Vehicle::get_x0() const -> size_t {
    return this->x0;
}

auto Vehicle::get_x1() const -> size_t {
    return this->x1;
}

auto Vehicle::get_y0() const -> size_t {
    return this->y0;
}

auto Vehicle::get_y1() const -> size_t {
    return this->y1;
}