#include "App.hpp"


void Tutorial::FirstApp::run() {
  while (!window.shouldClose()) {
    glfwPollEvents();
  }
}  // namespace lve