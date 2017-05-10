#pragma once

#include <math.h>
#include <random>
#include <stdlib.h>
#include <stdexcept>
#include <stdint.h>
#include <string>
#include <unordered_set>
#include <vector>

namespace hexgrid {
    enum orientation {
        flat, 
        sharp
    };

    struct point {
        float x;
        float y;
    };

    class hex  { 
        public:
            hex();

            hex(int32_t _x, int32_t _y, int32_t _z);
            
            hex operator+(const hex& rhs) const;

            hex operator-(const hex& rhs) const;

            hex operator*(float scalar) const;

            bool operator==(const hex& rhs) const;

            uint32_t distance(const hex& other);

            int32_t get_x() const { return x; }

            int32_t get_y() const { return y; }

            int32_t get_z() const { return z; }

            std::string to_string();

        private:
            int32_t x, y, z;
    };
}

// hash function for hexgrid::hex
// needs to be placed between hex and grid classes
// adapted from http://www.redblobgames.com/grids/hexagons/implementation.html#map
namespace std {
    template <> struct hash<hexgrid::hex> {
        size_t operator()(const hexgrid::hex& h) const {
            hash<int> int_hash;
            size_t x = int_hash(h.get_x());
            size_t y = int_hash(h.get_y());
            return x ^ (y + 0x9e3779b9 + (x << 6) + (x >> 2));
        }
    };
}

namespace hexgrid {
    typedef std::unordered_set<hex> hexset; 
    class grid : public std::unordered_set<hex> {

        public:
            static std::vector<hex>& neighbors() {
                static std::vector<hex> hexes = {
                    hex(1, 0, -1), hex(1, -1, 0), hex(0, -1, 1),
                    hex(-1, 0, 1), hex(-1, 1, 0), hex(0, 1, -1)
                };
                return hexes;
            };

            static point hex_to_point(hex& h);

            static hex point_to_hex(point& p);

            static hexset get_neighbors(hex& h);

            static hexset get_neighbor(hex& h);

            static hex round_hex(uint32_t x, uint32_t y, uint32_t z);

            grid();

            void set_radius(float new_radius);

            void set_orientation(orientation new_orientation);

        private:
            float radius;
            orientation orientation;
    };

    class layout {
        enum options {
            standard,
            flipped, 
            vertical
        };

        static hexset hexagonal(size_t radius);

        static hexset grid(int width, int height);

        static hexset parallelogram(int width, int height, options option = options::standard);

        static hexset triangular(int base_width, options option = options::standard);
    };
}
