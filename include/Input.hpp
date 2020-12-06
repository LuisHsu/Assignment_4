#ifndef INPUT_DEF
#define INPUT_DEF

#include <libinput.h>

class Input{
public:
    Input();
    ~Input();
    void dispatch();
private:
    struct libinput_interface interface;
    struct libinput* input;
};

#endif