#include <assert.h>
#include <iostream>
#include <stdio.h>
#include "hex.h"

using namespace hex;

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

    std::cout << "cell() tests" << std::endl;
    std::cout << "c1: " << c1.to_string() << std::endl;
    std::cout << "c2: " << c2.to_string() << std::endl;
    std::cout << "c3: " << c3.to_string() << std::endl;
    std::cout << "c4: " << c4.to_string() << std::endl;
    std::cout << "c2 + c3: " << (c2 + c3).to_string() << std::endl;
    std::cout << "c4 * 0.5: " << (c4 * 0.5).to_string() << std::endl;
    std::cout << "c3 - c2: " << (c3 - c2).to_string() << std::endl;

    assert((c2 + c3) == c4);
    assert((c3 - c2) == cell(-1, 2, -1));
    assert((c4 * 0.5) == cell(-2, 1 , 1));
    assert(c1.distance(c4) == 3);
    assert(c3.distance(c4) == 1);

    std::cout << "\ngrid() tests" << std::endl;

    grid g;
    g.insert({cell(0, 0, 0), cell(-1, 0, 1), cell(-1, 1, 0)});
    assert(g.count(cell(0, 0, 0)) != 0);
    assert(g.count(cell(1, 1, -2)) == 0);
    assert(g.count(c4) == 0);

    return 0;
}
