#include "test_app.hpp"

namespace rrr {

    void TestApp::run() {
        while (!window.shouldClose()) {
            glfwPollEvents();
        }
    }


}