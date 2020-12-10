#ifndef INPUT_DEF
#define INPUT_DEF

#include <cstdint>
#include <libinput.h>
#include <functional>
#include <utility>
#include <unordered_map>

class Input{
public:
    Input();
    ~Input();
    std::pair<libinput_event_type, struct libinput_event*> getEvent();

    bool isAvailable;
    int fd;
private:
    struct libinput_interface interface;
    struct libinput* input;
    struct udev* udevCtx;
};

#endif