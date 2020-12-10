#ifndef WINDOW_DEF
#define WINDOW_DEF

#include <wayland-client.h>

class Window{
public:
    Window();
    ~Window();
    struct wl_surface* surface;

private:
    struct wl_display* display;
    struct wl_registry* registry;
    struct wl_shell_surface* shellSurface;
    static struct wl_registry_listener registryListener;
    static struct wl_compositor* compositor;
    static struct wl_shell* shell;
};

#endif