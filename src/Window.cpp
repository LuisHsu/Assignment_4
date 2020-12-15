/**
 * Copyright 2020 Luis Hsu. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#include <Window.hpp>

#include <stdexcept>
#include <xcb/xcb.h>
#include <vulkan/vulkan_xcb.h>

Window::Window(VkInstance& instance):
    instance(instance)
{
	// Create XCB window
	connection = xcb_connect(nullptr, nullptr);
    if(xcb_connection_has_error(connection)){
        throw std::runtime_error("Error connect to xcb");
    }
	xcb_screen_iterator_t screenIter = xcb_setup_roots_iterator(xcb_get_setup(connection));
	screen = screenIter.data;
    window = xcb_generate_id(connection);
	xcb_create_window(connection,
		XCB_COPY_FROM_PARENT,
		window,
		screen->root,
		0, 0,
		screen->width_in_pixels, screen->height_in_pixels,
		0,
		XCB_WINDOW_CLASS_INPUT_OUTPUT,
		screen->root_visual,
		0, nullptr
	);
    xcb_map_window(connection, window);
	xcb_flush(connection);
	// Create surface
	struct VkXcbSurfaceCreateInfoKHR surfaceInfo = {
		.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR,
		.pNext = nullptr,
		.flags = 0,
		.connection = connection,
		.window = window,
	};
	if(vkCreateXcbSurfaceKHR(instance, &surfaceInfo, nullptr, &surface) != VK_SUCCESS){
		throw std::runtime_error("Cannot create Vulkan surface");
	}
}

Window::~Window(){
    vkDestroySurfaceKHR(instance, surface, nullptr);
    xcb_destroy_window(connection, window);
    xcb_disconnect(connection);
}

bool Window::checkPresentationSupported(VkPhysicalDevice& physicalDevice, uint32_t queueFamilyIndex){
    VkBool32 result;
	if(vkGetPhysicalDeviceSurfaceSupportKHR(
		physicalDevice,
		queueFamilyIndex,
		surface,
		&result
	) != VK_SUCCESS){
		throw std::runtime_error("Cannot get Vulkan surface support");
	};
	return result == VK_TRUE;
}