#include <Window.hpp>

#include <stdexcept>
#include <iostream>
#include <string>

struct wl_compositor* Window::compositor = nullptr;
struct wl_shell* Window::shell = nullptr;

struct wl_registry_listener Window::registryListener = {
    [](void *, struct wl_registry *registry, uint32_t id,const char *interface, uint32_t version){
        if(std::string(interface) == "wl_compositor"){
            compositor = (struct wl_compositor*)wl_registry_bind(registry, id, &wl_compositor_interface, version);
        }else if(std::string(interface) == "wl_shell"){
            shell = (struct wl_shell*)wl_registry_bind(registry, id, &wl_shell_interface, version);
        }
    },
    [](void* , struct wl_registry* , uint32_t id){
    }
};

Window::Window():
    display(wl_display_connect(nullptr))
{
    if(!display){
        throw std::runtime_error("Cannot connect wayland display");
    }
    if((registry = wl_display_get_registry(display)) == nullptr){
        throw std::runtime_error("Cannot get wayland registry");
    };
    if(wl_registry_add_listener(registry, &registryListener, nullptr) < 0){
        throw std::runtime_error("Cannot add wayland registry listener");
    }
    if(wl_display_dispatch(display) == -1){
        throw std::runtime_error("Cannot dispatch wayland display");
    }
    if(wl_display_roundtrip(display) == -1){
        throw std::runtime_error("Cannot roundtrip wayland display");
    }
    if((surface = wl_compositor_create_surface(compositor)) == nullptr){
        throw std::runtime_error("Cannot create wayland surface");
    }
    if((shellSurface = wl_shell_get_shell_surface(shell, surface)) == nullptr){
        throw std::runtime_error("Cannot get wayland shell surface");
    }
    wl_shell_surface_set_toplevel(shellSurface);
}

Window::~Window(){
    wl_display_disconnect(display);
}