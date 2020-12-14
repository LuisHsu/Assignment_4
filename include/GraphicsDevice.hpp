#ifndef GRAPHICSDEVICE_DEF
#define GRAPHICSDEVICE_DEF

#include <vulkan/vulkan.hpp>
#include <Window.hpp>

class GraphicsDevice{
public:
    GraphicsDevice(VkInstance instance, Window& window);
    ~GraphicsDevice();
private:
    VkQueue graphicQueue, presentQueue;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
};


#endif