#pragma once

#include <stdexcept>
#include <stdint.h>

namespace hex {
    class cell  { 
        public:
            cell();

            cell(int32_t _x, int32_t _y, int32_t _z);
            
            cell operator+(const cell& rhs) const;

            cell operator-(const cell& rhs) const;

            int32_t get_x() const { return x; }

            int32_t get_y() const { return y; }

            int32_t get_z() const { return z; }

        private:
            int32_t x, y, z;
    };

    class grid {

    };

    class layout {

    };
}
