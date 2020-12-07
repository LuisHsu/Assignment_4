#ifndef SPINING_CUBE_DEF
#define SPINING_CUBE_DEF

#include <Window.hpp>
#include <Input.hpp>
#include <EventHandler.hpp>

class SpiningCube{
public:
    SpiningCube();
    ~SpiningCube();
    void exec();
private:
    Window window;
    Input input;
    EventHandler eventHandler;
};

#endif