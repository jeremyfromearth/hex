#pragma once

#include <math.h>
#include <stdlib.h>
#include <stdexcept>
#include <stdint.h>
#include <string>

namespace hex {
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

    class grid {

    };

    class layout {

    };
}
