#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace Tutorial{
    class Window{
    public:
        Window(const char* name,int width,int height);

        Window(const Window &) = delete;
        Window &operator=(const Window &) = delete;

        bool shouldClose() {
            return glfwWindowShouldClose(window);
        }

        void createWindowSurface(VkInstance instance,VkSurfaceKHR* surface);

        ~Window();

        GLFWwindow* window;
    };
}