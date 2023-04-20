#ifndef VEHICLE_HEADER_FILE
#define VEHICLE_HEADER_FILE

#include <string>
#include <tuple>

/* Vehicle class
  
  data structure containing a vehicle state
  
  data elements:
    id, the character identifying a vehicle (typically a color representation, e.g. player_vehicle_id for "red")
    x0, the leftmost space occupied by the vehicle
    x1, the rightmost space occupied by the vehicle (for "vertical" vehicles x1 = x0)
    y0, the bottommost space occupied by the vehicle
    y1, the uppermost space occupied by the vehicle (for "horizontal" vehicles y1 = y0)
    spaces, the number of spaces occupied by the vehicle
    direction, the orientation of the vehicle ("horizontal" or "vertical")
*/
struct Vehicle {
    
    Vehicle(const char&, const size_t&, const size_t&, const size_t&, const double&);
    
    auto get_coordinates() const -> std::tuple<size_t, size_t, size_t, size_t>;
    auto get_direction() const -> double;
    auto get_id() const -> char;
    auto get_spaces() const -> size_t;
    auto get_x0() const -> size_t;
    auto get_x1() const -> size_t;
    auto get_y0() const -> size_t;
    auto get_y1() const -> size_t;
    
    private:
        const char id;
        const size_t x0, y0, spaces;
        const double direction; // 0 = horizontal, 90 = vertical
        const size_t x1, y1;
        
        static constexpr auto set_x1 = [](const size_t &x0_, const size_t &spaces_, const double &direction_) {
            return direction_ == 0 ? x0_ + spaces_ - 1 : x0_;
        };
        static constexpr auto set_y1 = [](const size_t &y0_, const size_t &spaces_, const double &direction_) {
            return direction_ == 90 ? y0_ + spaces_ - 1 : y0_;
        };
};

#endif // VEHICLE_HEADER_FILE