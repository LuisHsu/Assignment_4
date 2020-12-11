#ifndef GRAPHICSDEVICE_DEF
#define GRAPHICSDEVICE_DEF

#include <vulkan/vulkan.hpp>
#include <wayland-client.h>

class GraphicsDevice{
public:
    GraphicsDevice(struct wl_surface* surface);
    ~GraphicsDevice();
private:
    VkInstance instance;
};


#endif