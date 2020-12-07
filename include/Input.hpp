#ifndef INPUT_DEF
#define INPUT_DEF

#include <libinput.h>

class Input{
public:
    Input();
    ~Input();
    int getFd();

    bool isAvailable;
    
private:
    struct libinput_interface interface;
    struct libinput* input;
    struct udev* udevCtx;
};

#endif