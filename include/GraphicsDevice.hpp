#ifndef GRAPHICSDEVICE_DEF
#define GRAPHICSDEVICE_DEF

#include <vulkan/vulkan.hpp>

class GraphicsDevice{
public:
    GraphicsDevice(VkInstance& instance, VkSurfaceKHR& surface);
    ~GraphicsDevice();
private:
    VkQueue graphicQueue, presentQueue;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
};


#endif