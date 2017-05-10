#include "hex.h"

using namespace hex;

// ------------------------------------------------------------
//
// cell
//
// ------------------------------------------------------------

cell cell::round(float x, float y, float z) {
    int xr = std::round(x);
    int yr = std::round(y);
    int zr = std::round(z);

    int xd = std::abs(x - xr);
    int yd = std::abs(y - yr);
    int zd = std::abs(z - zr);

    if(xd > yd && xd > zd) {
	xr = -yr - zr;
    } else if(yd > zd) {
	yr = -xr - zr;
    } else {
	zr = -xr - yr;
    }

    return cell(xr, yr, zr);
}

cell::cell() : x(0), y(0), z(0) {}

cell::cell(int32_t _x, int32_t _y, int32_t _z)
    : x(_x), y(_y), z(_z) {
    if(x + y + z != 0) throw(std::runtime_error("Invalid cell"));
}

cell cell::operator+(const cell& rhs) const {
    return cell(x + rhs.get_x(), y + rhs.get_y(), z + rhs.get_z());
}

cell cell::operator-(const cell& rhs) const {
    return cell(x - rhs.get_x(), y - rhs.get_y(), z - rhs.get_z());
}

cell cell::operator*(float scalar) const {
    return cell(std::round(x * scalar), std::round(y * scalar), std::round(z * scalar));
}

bool cell::operator==(const cell& rhs) const {
    return x == rhs.get_x() && y == rhs.get_y() && z == rhs.get_z();
}

uint32_t cell::distance(const cell& other) {
    return (std::abs(x - other.get_x()) + std::abs(y - other.get_y()) + std::abs(z - other.get_z())) / 2;
}

std::string cell::to_string() {
    return "cell(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}

// ------------------------------------------------------------
//
// grid
//
// ------------------------------------------------------------

grid::grid() {
    orientation = cell::orientation::sharp;
}
