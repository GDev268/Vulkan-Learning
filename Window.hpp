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

        VkExtent2D getExtent() {
            return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
        }

        void createWindowSurface(VkInstance instance,VkSurfaceKHR* surface);

        ~Window();

        GLFWwindow* window;

        const int width,height;
    };
}