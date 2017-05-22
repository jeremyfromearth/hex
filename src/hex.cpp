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

std::ostream& operator<<(std::ostream& os, cell const& c) {
   os << "cell(" << std::to_string(c.get_x()) << ", " + std::to_string(c.get_y()) << ", " + std::to_string(c.get_z()) << ")";
   return os;
}

// ------------------------------------------------------------
//
// lattice
//
// ------------------------------------------------------------

point lattice::cell_to_point(cell& c, orientation o, float r) {
    float x = 0;
    float y = 0;
    if(o == orientation::flat) {
        x = r * (3.0/2.0) * c.get_x();
        y = r * sqrt(3.0) * (c.get_y() + c.get_x() * 0.5);
    } else {
        x = r * sqrt(3.0) * (c.get_x() + c.get_y() * 0.5);
        y = r * 3.0/2.0 * c.get_y();
    }

    return {x, y};
}

cell point_to_cell(point& p, orientation o, float r) {
    int x = 0;
    int y = 0;
    
    if(o == orientation::flat) {
   	x = p.x * 2/3 / r;
        y = (-p.x / 3 + sqrt(3)/3 * p.y) / r; 
    } else {
	x = (p.x * sqrt(3)/3 - y / 3) / r;
        y = p.y * 2/3 / r;
    }

    return {x, y, -x-y};
}


std::unordered_set<cell> lattice::get_neighbors(cell& c) {
    std::unordered_set<cell> result;
    for(size_t i = 0; i < neighbors().size(); i++) {
        result.emplace(c + neighbors()[i]);
    }

    return result;
}

//static lattice get_neighbor(cell& c, uint8_t side);

/*
static cell round(uint32_t x, uint32_t y, uint32_t z);
*/
