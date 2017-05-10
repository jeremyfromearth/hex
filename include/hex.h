#pragma once

#include <math.h>
#include <random>
#include <stdlib.h>
#include <stdexcept>
#include <stdint.h>
#include <string>
#include <unordered_set>
#include <vector>

namespace hex {
    struct point {
        float x;
        float y;
    };

    class cell  { 
    public:
        enum orientation {
            flat, 
            sharp
        };

        cell();

        cell(int32_t _x, int32_t _y, int32_t _z);
        
        cell operator+(const cell& rhs) const;

        cell operator-(const cell& rhs) const;

        cell operator*(float scalar) const;

        bool operator==(const cell& rhs) const;

        uint32_t distance(const cell& other);

        int32_t get_x() const { return x; }

        int32_t get_y() const { return y; }

        int32_t get_z() const { return z; }

        std::string to_string();

    private:
        int32_t x, y, z;
    };
}

// hash function for hex::cell
// needs to be placed between cell and grid classes
// adapted from http://www.redblobgames.com/grids/hexagons/implementation.html#map
namespace std {
    template <> struct hash<hex::cell> {
        size_t operator()(const hex::cell& c) const {
            hash<int> int_hash;
            size_t x = int_hash(c.get_x());
            size_t y = int_hash(c.get_y());
            return x ^ (y + 0x9e3779b9 + (x << 6) + (x >> 2));
        }
    };
}

namespace hex {
    class grid : public std::unordered_set<cell> {
        public:
            static std::vector<cell>& neighbors() {
                static std::vector<cell> cells = {
                    cell(1, 0, -1), cell(1, -1, 0), cell(0, -1, 1),
                    cell(-1, 0, 1), cell(-1, 1, 0), cell(0, 1, -1)
                };
                return cells;
            };

            static point hex_to_point(cell& h);

            static cell point_to_hex(point& p);

            static grid get_neighbors(cell& c);

            static grid get_neighbor(cell& c);

            static cell round(uint32_t x, uint32_t y, uint32_t z);

            grid();

            //void set_radius(float new_radius);

            //void set_orientation(orientation new_orientation);

        private:
            float radius;
            cell::orientation orientation;
        };

    class layout {
        public:
            enum options {
                standard,
                flipped, 
                vertical
            };

            static grid hexagonal(size_t radius);

            static grid rectangular(int width, int height);

            static grid parallel(int width, int height, options option = options::standard);

            static grid triangular(int base_width, options option = options::standard);
    };
}
