#ifndef WINDOW_DEF
#define WINDOW_DEF

#include <wayland-client.h>

class Window{
public:
    Window();
    ~Window();
private:
    struct wl_display* display;
};

#endif