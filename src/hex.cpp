#include "hex.h"

using namespace hexgrid;

// ------------------------------------------------------------
//
// hex
//
// ------------------------------------------------------------

hex::hex()
    : x(0), y(0), z(0) {}

hex::hex(int32_t _x, int32_t _y, int32_t _z)
    : x(_x), y(_y), z(_z) {
    if(x + y + z != 0) throw(std::runtime_error("Invalid hex::hex"));
}

hex hex::operator+(const hex& rhs) const {
    return hex(x + rhs.get_x(), y + rhs.get_y(), z + rhs.get_z());
}

hex hex::operator-(const hex& rhs) const {
    return hex(x - rhs.get_x(), y - rhs.get_y(), z - rhs.get_z());
}

hex hex::operator*(float scalar) const {
    return hex(round(x * scalar), round(y * scalar), round(z * scalar));
}

bool hex::operator==(const hex& rhs) const {
    return x == rhs.get_x() && y == rhs.get_y() && z == rhs.get_z();
}

uint32_t hex::distance(const hex& other) {
    return floor((abs(x - other.get_x()) + abs(y - other.get_y()) + abs(z - other.get_z())) / 2);
}

std::string hex::to_string() {
    return "hex(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}

// ------------------------------------------------------------
//
// grid
//
// ------------------------------------------------------------

grid::grid() {
    orientation = orientation::sharp;
}
