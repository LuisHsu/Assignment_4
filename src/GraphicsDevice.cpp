/**
 * Copyright 2020 Luis Hsu. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#include <GraphicsDevice.hpp>

#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <optional>
#include <algorithm>

GraphicsDevice::GraphicsDevice(VkInstance instance, Window& window):
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
    std::optional<uint32_t> graphicFamily, presentFamily;
    for(VkPhysicalDevice& candidateDevice : physicalDevices){
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(candidateDevice, &deviceProperties);
        vkGetPhysicalDeviceFeatures(candidateDevice, &deviceFeatures);
        if(deviceFeatures.geometryShader){
            // Check device extentions
            const std::vector<const char*> requiredExtensions = {
                VK_KHR_SWAPCHAIN_EXTENSION_NAME
            };
            uint32_t extensionCount;
            vkEnumerateDeviceExtensionProperties(candidateDevice, nullptr, &extensionCount, nullptr);
            std::vector<VkExtensionProperties> availableExtensionsProp(extensionCount);
            vkEnumerateDeviceExtensionProperties(candidateDevice, nullptr, &extensionCount, availableExtensionsProp.data());
            bool isSuitable = true;
            for(const char* extension : requiredExtensions){
                if(std::find_if(availableExtensionsProp.begin(), availableExtensionsProp.end(), [extension](VkExtensionProperties& prop){
                    return strcmp(prop.extensionName, extension) == 0;
                }) == availableExtensionsProp.end()){
                    isSuitable = false;
                }
            }
            if(isSuitable){
                physicalDevice = candidateDevice;
                // Check device queue family support
                uint32_t queueFamilyCount = 0;
                vkGetPhysicalDeviceQueueFamilyProperties(candidateDevice, &queueFamilyCount, nullptr);
                std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
                vkGetPhysicalDeviceQueueFamilyProperties(candidateDevice, &queueFamilyCount, queueFamilyProperties.data());
                graphicFamily.reset();
                presentFamily.reset();
                for(uint32_t index = 0; index < queueFamilyCount; ++index){
                    if(queueFamilyProperties[index].queueFlags & VK_QUEUE_GRAPHICS_BIT){
                        graphicFamily = index;
                    }
                    if(window.checkPresentationSupported(candidateDevice, index)){
                        presentFamily = index;
                    }
                }
            }
        }
    }
    if(physicalDevice == VK_NULL_HANDLE){
        throw std::runtime_error("Cannot find proper physical device");
    }else if(!(graphicFamily.has_value() && presentFamily.has_value())){
        throw std::runtime_error("No suitable graphics or present queue family");
    }

    // Create device queues
    float queuePriority = 1.0f;
    std::vector<VkDeviceQueueCreateInfo> queueInfos(2, {
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .queueCount = 1,
        .pQueuePriorities = &queuePriority,
    });
    queueInfos[0].queueFamilyIndex = graphicFamily.value();
    queueInfos[1].queueFamilyIndex = presentFamily.value();

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
    vkGetDeviceQueue(device, graphicFamily.value(), 0, &graphicQueue);
    vkGetDeviceQueue(device, presentFamily.value(), 0, &presentQueue);
}

GraphicsDevice::~GraphicsDevice(){
    vkDestroyDevice(device, nullptr);
}