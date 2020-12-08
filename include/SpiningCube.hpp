#ifndef SPINING_CUBE_DEF
#define SPINING_CUBE_DEF

#include <Window.hpp>
#include <Input.hpp>
#include <EventHandler.hpp>
#include <Timer.hpp>

class SpiningCube{
public:
    SpiningCube();
    ~SpiningCube();
    void exec();
private:
    Window window;
    Input input;
    Timer timer;
    EventHandler eventHandler;
};

#endif