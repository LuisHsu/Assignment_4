/**
 * Copyright 2020 Luis Hsu. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#include <GraphicsDevice.hpp>

#include <iostream>
#include <stdexcept>
#include <vector>

GraphicsDevice::GraphicsDevice():
    physicalDevice(VK_NULL_HANDLE)
{
    // Create instance
    VkApplicationInfo appInfo = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = "Assignment 4",
        .applicationVersion = VK_MAKE_VERSION(0, 1, 0),
        .pEngineName = "No Engine",
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_2,
    };
    std::vector<const char*> extensionNames({
        "VK_KHR_wayland_surface"
    });
    VkInstanceCreateInfo instanceCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &appInfo,
        .enabledLayerCount = 0,
        .enabledExtensionCount = static_cast<uint32_t>(extensionNames.size()),
        .ppEnabledExtensionNames = extensionNames.data(),
    };
    if(vkCreateInstance(&instanceCreateInfo, nullptr, &instance) != VK_SUCCESS){
        throw std::runtime_error("Cannot create Vulkan instance");
    }
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
    uint32_t queueFamilyIndex = 0;
    for(VkPhysicalDevice& device : physicalDevices){
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
        if(deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && deviceFeatures.geometryShader){
            uint32_t queueFamilyCount = 0;
            vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
            std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
            vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilyProperties.data());
            for(const VkQueueFamilyProperties& prop : queueFamilyProperties){
                if(prop.queueFlags & VK_QUEUE_GRAPHICS_BIT){
                    physicalDevice = device;
                    break;
                }
                ++queueFamilyIndex;
            }
        }
    }
    if(physicalDevice == VK_NULL_HANDLE){
        throw std::runtime_error("Cannot find proper physical device");
    }
    // Get logical device
    float queuePriority = 1.0f;
    VkDeviceQueueCreateInfo queueInfo = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .queueFamilyIndex = queueFamilyIndex,
        .queueCount = 1,
        .pQueuePriorities = &queuePriority,
    };
    VkPhysicalDeviceFeatures deviceFeatures = {};
    VkDeviceCreateInfo deviceInfo = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = &queueInfo,
        .enabledExtensionCount = 0,
        .pEnabledFeatures = &deviceFeatures,
    };
    if(vkCreateDevice(physicalDevice, &deviceInfo, nullptr, &device) != VK_SUCCESS){
        throw std::runtime_error("Cannot create device");
    }
    // Get graphics queue
    vkGetDeviceQueue(device, queueFamilyIndex, 0, &graphicsQueue);
}

GraphicsDevice::~GraphicsDevice(){
    vkDestroyDevice(device, nullptr);
    vkDestroyInstance(instance, nullptr);
}