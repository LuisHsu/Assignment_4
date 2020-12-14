/**
 * Copyright 2020 Luis Hsu. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#include <Window.hpp>

#include <stdexcept>
#include <string>
#include <xcb/xcb.h>
#include <vulkan/vulkan_xcb.h>

Window::Window(VkInstance& instance):
    instance(instance)
{
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
}

Window::~Window(){
    //vkDestroySurfaceKHR(instance, surface, nullptr);
    xcb_destroy_window(connection, window);
    xcb_disconnect(connection);
}

bool Window::checkPresentationSupported(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex){
    return vkGetPhysicalDeviceXcbPresentationSupportKHR(physicalDevice, queueFamilyIndex, connection, screen->root_visual) == VK_TRUE;
}