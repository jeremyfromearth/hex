#include "hex.h"

using namespace hex;



// ------------------------------------------------------------
//
// cell
//
// ------------------------------------------------------------

cell::cell()
    : x(0), y(0), z(0) {}

cell::cell(int32_t _x, int32_t _y, int32_t _z)
    : x(_x), y(_y), z(_z) {
    if(x + y + z != 0) throw(std::runtime_error("Invalid hex::cell"));
}

cell cell::operator+(const cell& rhs) const {
    return cell(x + rhs.get_x(), y + rhs.get_y(), z + rhs.get_z());
}

cell cell::operator-(const cell& rhs) const {
    return cell(x - rhs.get_x(), y - rhs.get_y(), z - rhs.get_z());
}

cell cell::operator*(float scalar) const {
    return cell(round(x * scalar), round(y * scalar), round(z * scalar));
}

bool cell::operator==(const cell& rhs) const {
    return x == rhs.get_x() && y == rhs.get_y() && z == rhs.get_z();
}

uint32_t cell::distance(const cell& other) {
    return floor((abs(x - other.get_x()) + abs(y - other.get_y()) + abs(z - other.get_z())) / 2);
}

std::string cell::to_string() {
    return "Cell(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}

// ------------------------------------------------------------
//
// grid
//
// ------------------------------------------------------------

grid::grid() {
    orientation = orientation::sharp;
}

void grid::add(cell_list& new_cells, float probability) {
    /*
    for(auto & c : new_cells) {
        uint32_t x = c.get_x();
        uint32_t y = c.get_y();
        uint32_t z = c.get_z();
    }
    */
}
