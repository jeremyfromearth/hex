#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <unordered_set>

#include "hex.h"

using namespace hex;

class grid : public std::unordered_set<cell> {
    public:
        void add(const cell & c) {
            emplace(c);
        }

        void operator+=(grid& rhs);
        bool operator==(const grid& rhs) const;
};

bool grid::operator==(const grid& rhs) const {
    for(auto & c : rhs) {
        if(!count(c)) return false;
    }
    return true;
}

void grid::operator+=(grid& rhs) {
    //for(auto & c: rhs) insert(c);
    cell c;
    emplace(c);
}

int main() {
    std::cout << "-------------------- hextests --------------------" << std::endl;
    
    try {
        cell(-1, -1, -1);
        std::cerr << "An invalid hex::cell was created" << std::endl;
    } catch(std::runtime_error e) {
        std::cout << "Attempt to create an invalid hex::cell failed and threw a runtime error. This is the expected behavior" << std::endl;
    }

    cell c1;
    cell c2(-1, 0, 1);
    cell c3(-2, 2, 0);
    cell c4(-3, 2, 1); 

    grid g;
    std::cout << "cell() tests" << std::endl;
    std::cout << "c1: " << c1 << std::endl;
    std::cout << "c2: " << c2 << std::endl;
    std::cout << "c3: " << c3 << std::endl;
    std::cout << "c4: " << c4 << std::endl;
    std::cout << "c2 + c3: " << (c2 + c3) << std::endl;
    std::cout << "c4 * 0.5: " << (c4 * 0.5) << std::endl;
    std::cout << "c3 - c2: " << (c3 - c2) << std::endl;

    assert((c2 + c3) == c4);
    assert((c3 - c2) == cell(-1, 2, -1));
    assert((c4 * 0.5) == cell(-2, 1 , 1));
    assert(c1.distance(c4) == 3);
    assert(c3.distance(c4) == 1);

    std::cout << "\nlattice() tests" << std::endl;

    lattice l;
    l.insert({cell(0, 0, 0), cell(-1, 0, 1), cell(-1, 1, 0)});
    assert(l.count(cell(0, 0, 0)) != 0);
    assert(l.count(cell(1, 1, -2)) == 0);
    assert(l.count(c4) == 0);

    float r = 32;
    orientation o = orientation::flat;
    point p = lattice::cell_to_point(c1, o, r);
    assert(p.x == 0);
    assert(p.y == 0);

    std::unordered_set<cell> expectation = {
        cell(1, 0, -1), cell(1, -1, 0), cell(0, -1, 1),
        cell(-1, 0, 1), cell(-1, 1, 0), cell(0, 1, -1)
    };

    std::unordered_set<cell> result = l.get_neighbors(c1);
    assert(result == expectation);

    cell center_cell = cell(-2, 2, 0);
    expectation = {
        cell(-1, 2, -1), cell(-1, 1, 0), cell(-2, 1, 1),
        cell(-3, 2, 1), cell(-3, 3, 0), cell(-2, 3, -1)
    };

    result = lattice::get_neighbors(center_cell);
    assert(result == expectation);

    center_cell = cell(0, 0, 0);
    cell c5 = lattice::get_neighbor(center_cell, 2);
    assert(c5 == cell(-1, 0, 1));

    try {
        lattice::get_neighbor(center_cell, 8);
    } catch(std::runtime_error e) {
        std::cout << e.what() << std::endl;
        std::cout << "Caught runtime error, as expected" << std::endl;
    }

    // layouts
    // empty the lattice
    l.clear();

    // add cells for a hex layout or radius 6
    l += layout::hexagonal(6);

    // test for a cell on the perimeter
    assert(l.count(cell(5, 1, -6)) > 0);

    // remove a hex layout of radius 3
    l -= layout::hexagonal(3);

    // test that the center cell is removed
    assert(l.count(cell(0, 0, 0)) == 0);

    // test += 
    cell c6(1, 0, -1);
    cell c7(-2, 0, 2);
    cell c8(-1, 0, 1);
    c6 += c7;
    assert(c6 == c8);

    // test -=
    c6 -= c5;
    assert(c6 == cell(0, 0, 0));

    return 0;
}
