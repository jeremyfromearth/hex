#pragma once

#include <math.h>
#include <stdlib.h>
#include <stdexcept>
#include <stdint.h>
#include <string>
#include <unordered_map>
#include <vector>

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

    typedef std::vector<cell> cell_list;
    typedef std::unordered_map<int32_t, std::unordered_map<int32_t, std::unordered_map<uint32_t, cell>>> cell_map;
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

            void add_cells(cell_list new_cells, float probability);

            bool contains(cell c);

            void set_cell_radius(float new_radius);

            void set_cell_orientation(orientation new_orientation);

            cell get_neighbor(cell c, int side);

            cell_list get_neighbors(cell c);

            point hex_to_point(cell c);

            cell point_to_hex(point p);

        private:
            cell_list cells;
            cell_map lookup;
            float cell_radius;
            orientation orientation;

            cell round_cell(uint32_t x, uint32_t y, uint32_t z);
    };

    class layout {

    };
}
