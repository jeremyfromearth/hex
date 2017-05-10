#include <assert.h>
#include <iostream>
#include <stdio.h>
#include "hex.h"

using namespace hexgrid;
int main() {
    std::cout << "-------------------- hextests --------------------" << std::endl;
    
    try {
        hex(-1, -1, -1);
        std::cerr << "An invalid hex::hex was created" << std::endl;
    } catch(std::runtime_error e) {
        std::cout << "Attempt to create an invalid hex::hex failed and threw a runtime error. This is the expected behavior" << std::endl;
    }

    hex c1;
    hex c2(-1, 0, 1);
    hex c3(-2, 2, 0);
    hex c4(-3, 2, 1); 

    std::cout << "hex() tests" << std::endl;
    std::cout << "c1: " << c1.to_string() << std::endl;
    std::cout << "c2: " << c2.to_string() << std::endl;
    std::cout << "c3: " << c3.to_string() << std::endl;
    std::cout << "c4: " << c4.to_string() << std::endl;
    std::cout << "c2 + c3: " << (c2 + c3).to_string() << std::endl;
    std::cout << "c4 * 0.5: " << (c4 * 0.5).to_string() << std::endl;
    std::cout << "c3 - c2: " << (c3 - c2).to_string() << std::endl;

    assert((c2 + c3) == c4);
    assert((c3 - c2) == hex(-1, 2, -1));
    assert((c4 * 0.5) == hex(-2, 1 , 1));

    std::cout << "\ngrid() tests" << std::endl;

    grid g;
    g.insert({hex(0, 0, 0), hex(-1, 0, 1), hex(-1, 1, 0)});
    assert(g.count(hex(0, 0, 0)) != 0);
    assert(g.count(hex(1, 1, -2)) == 0);
    assert(g.count(c4) == 0);

    return 0;
}
