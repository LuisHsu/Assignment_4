#include <Window.hpp>

#include <stdexcept>

Window::Window():
    display(wl_display_connect(nullptr))
{
    if(!display){
        throw std::runtime_error("Cannot connect wayland display");
    }
    // TODO:
}

Window::~Window(){
    wl_display_disconnect(display);
}