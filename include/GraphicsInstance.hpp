#ifndef GRAPHICSINSTANCE_DEF
#define GRAPHICSINSTANCE_DEF

#include <vulkan/vulkan.hpp>

class GraphicsInstance{
public:
    GraphicsInstance();
    ~GraphicsInstance();
    VkInstance instance;
};


#endif