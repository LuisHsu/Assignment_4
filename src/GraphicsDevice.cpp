/**
 * Copyright 2020 Luis Hsu. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#include <GraphicsDevice.hpp>

#include <iostream>
#include <stdexcept>
#include <vector>

GraphicsDevice::GraphicsDevice(VkInstance& instance, VkSurfaceKHR& surface):
    physicalDevice(VK_NULL_HANDLE)
{
    // Get physical device
    uint32_t physicalDeviceCount = 0;
    if(vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr) != VK_SUCCESS){
        throw std::runtime_error("Cannot get Vulkan physical device count");
    }else if(physicalDeviceCount == 0){
        throw std::runtime_error("No physical devices");
    }
    std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
    if(vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices.data()) != VK_SUCCESS){
        throw std::runtime_error("Cannot get Vulkan physical devices");
    }
    uint32_t graphicFamily, presentFamily;
    for(VkPhysicalDevice& device : physicalDevices){
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
        if(deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && deviceFeatures.geometryShader){
            physicalDevice = device;
            uint32_t queueFamilyCount = 0;
            vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
            std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
            vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilyProperties.data());
            for(uint32_t index = 0; index < queueFamilyCount; ++index){
                if(queueFamilyProperties[index].queueFlags & VK_QUEUE_GRAPHICS_BIT){
                    graphicFamily = index;
                }
                VkBool32 presentSupport = false;
                if(vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, index, surface, &presentSupport) != VK_SUCCESS){
                    throw std::runtime_error("Cannot check surface support");
                }else if(presentSupport){
                    presentFamily = index;
                }
            }
        }
    }
    if(physicalDevice == VK_NULL_HANDLE){
        throw std::runtime_error("Cannot find proper physical device");
    }

    // Create device queues
    float queuePriority = 1.0f;
    std::vector<VkDeviceQueueCreateInfo> queueInfos(2, {
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .queueCount = 1,
        .pQueuePriorities = &queuePriority,
    });
    queueInfos[0].queueFamilyIndex = graphicFamily;
    queueInfos[1].queueFamilyIndex = presentFamily;

    // Create logical device
    VkPhysicalDeviceFeatures deviceFeatures = {};
    VkDeviceCreateInfo deviceInfo = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount = static_cast<uint32_t>(queueInfos.size()),
        .pQueueCreateInfos = queueInfos.data(),
        .enabledExtensionCount = 0,
        .pEnabledFeatures = &deviceFeatures,
    };
    if(vkCreateDevice(physicalDevice, &deviceInfo, nullptr, &device) != VK_SUCCESS){
        throw std::runtime_error("Cannot create device");
    }
    
    // Get queues
    vkGetDeviceQueue(device, graphicFamily, 0, &graphicQueue);
    vkGetDeviceQueue(device, presentFamily, 0, &presentQueue);
}

GraphicsDevice::~GraphicsDevice(){
    vkDestroyDevice(device, nullptr);
}