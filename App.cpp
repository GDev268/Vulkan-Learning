#include "App.hpp"

void Tutorial::FirstApp::run()
{
    while(!glfwWindowShouldClose(window.window)){
        glfwPollEvents();
    }
}