#pragma once

#include <math.h>
#include <stdlib.h>
#include <stdexcept>
#include <stdint.h>
#include <string>
#include <unordered_set>

namespace hex {
    enum orientation {
        flat, 
        sharp
    };

    struct point {
        float x;
        float y;
    };

    class cell  { 
        public:
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
    typedef std::unordered_set<cell> cell_list;

    class grid {

        public:
            static cell_list& neighbors() {
                static cell_list ns = {
                    cell(1, 0, -1), cell(1, -1, 0), cell(0, -1, 1),
                    cell(-1, 0, 1), cell(-1, 1, 0), cell(0, 1, -1)
                };
                return ns;
            };

            grid();

            void add(cell_list& new_cells, float probability = 1.0f);

            bool contains(cell c);

            void set_cell_radius(float new_radius);

            void set_cell_orientation(orientation new_orientation);

            cell get_neighbor(cell c, int side);

            cell_list get_neighbors(cell c);

            point hex_to_point(cell c);

            cell point_to_hex(point p);

        private:
            cell_list cells;
            float cell_radius;
            orientation orientation;

            cell round_cell(uint32_t x, uint32_t y, uint32_t z);
    };

    class layout {
        enum options {
            standard,
            flipped, 
            vertical
        };

        static cell_list hexagonal(size_t radius);

        static cell_list grid(int width, int height);

        static cell_list parallelogram(int width, int height, options option = options::standard);

        static cell_list triangular(int base_width, options option = options::standard);
    };
}
