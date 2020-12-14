#ifndef WINDOW_DEF
#define WINDOW_DEF

#include <vulkan/vulkan.hpp>
extern "C"{
	#include <xcb/xcb.h>
}

class Window{
public:
    Window(VkInstance& instance);
    ~Window();
    
    VkSurfaceKHR surface;
    bool checkPresentationSupported(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex);

private:
    VkInstance& instance;
    xcb_connection_t *connection;
	xcb_window_t window;
    xcb_screen_t* screen;
};

#endif