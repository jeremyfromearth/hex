#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>
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

        static cell round(float x, float y, float z);

        static std::vector<point> flat_vertices;

        static std::vector<point> sharp_vertices;

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

    private:
        int32_t x, y, z;
    };

}

std::ostream& operator<<(std::ostream& os, hex::cell const& c);


// hash function for hex::cell
// needs to be placed between cell and lattice classes
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
    

    enum orientation {
        flat, 
        sharp
    };

    class lattice: public std::unordered_set<cell> {
        public:
            static std::vector<cell>& neighbors() {
                static std::vector<cell> cells = {
                    cell(1, -1, 0), cell(0, -1, 1), cell(-1, 0, 1), 
                    cell(-1, 1, 0), cell(0, 1, -1), cell(1, 0, -1), 
                };
                return cells;
            };

            static point cell_to_point(cell& c, orientation o, float r);

            static cell point_to_cell(point& p, orientation o, float r);

            static std::unordered_set<cell> get_neighbors(cell& c);

            static cell get_neighbor(cell& c, uint8_t side);
        };

    class layout {
        public:
            enum options {
                standard,
                flipped, 
                vertical
            };

            static lattice hexagonal(int radius);

            static lattice rectangular(int width, int height);

            static lattice parallelogram(int width, int height, options direction = options::standard);

            static lattice triangular(int base_width, options option = options::standard);
    };
}
