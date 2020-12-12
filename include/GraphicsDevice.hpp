#ifndef GRAPHICSDEVICE_DEF
#define GRAPHICSDEVICE_DEF

#include <vulkan/vulkan.hpp>
#include <wayland-client.h>

class GraphicsDevice{
public:
    GraphicsDevice();
    ~GraphicsDevice();

private:
    VkQueue graphicsQueue;
    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
};


#endif