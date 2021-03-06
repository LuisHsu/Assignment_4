/**
 * Copyright 2020 Luis Hsu. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#include <GraphicsInstance.hpp>

#include <iostream>
#include <stdexcept>
#include <vector>

GraphicsInstance::GraphicsInstance(){
    // Create instance
    VkApplicationInfo appInfo = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = "Assignment 4",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName = "No Engine",
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_0,
    };
    std::vector<const char*> extensionNames({
        "VK_KHR_surface",
        "VK_KHR_xcb_surface"
    });
    std::vector<const char*> validationLayers({
        "VK_LAYER_KHRONOS_validation"
    });
    VkInstanceCreateInfo instanceCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &appInfo,
        .enabledLayerCount = static_cast<uint32_t>(validationLayers.size()),
        .ppEnabledLayerNames = validationLayers.data(),
        .enabledExtensionCount = static_cast<uint32_t>(extensionNames.size()),
        .ppEnabledExtensionNames = extensionNames.data(),
    };
    if(vkCreateInstance(&instanceCreateInfo, nullptr, &instance) != VK_SUCCESS){
        throw std::runtime_error("Cannot create Vulkan instance");
    }
}

GraphicsInstance::~GraphicsInstance(){
    vkDestroyInstance(instance, nullptr);
}