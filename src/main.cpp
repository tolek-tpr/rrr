#include "test_app.hpp"

#include <iostream>
#include <stdexcept>

int main() {
    rrr::TestApp app {};

    try {
        app.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}