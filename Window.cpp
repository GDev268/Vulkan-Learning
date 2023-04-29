#include "Window.hpp"

#include <stdexcept>

Tutorial::Window::Window(const char *name, int width, int height) : width{width}, height{height}
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, name, nullptr, nullptr);
};

void Tutorial::Window::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface)
{
    if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS)
    {
        throw std::runtime_error("Couldn't create window surface");
    }
}

Tutorial::Window::~Window(){

};
