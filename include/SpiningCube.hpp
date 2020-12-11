#ifndef SPINING_CUBE_DEF
#define SPINING_CUBE_DEF

#include <Window.hpp>
#include <Input.hpp>
#include <EventHandler.hpp>
#include <Timer.hpp>
#include <GraphicsDevice.hpp>

class SpiningCube{
public:
    SpiningCube();
    ~SpiningCube();
    void exec();
private:
    Window window;
    GraphicsDevice graphics;
    Timer timer;
    EventHandler eventHandler;
    Input input;
    void onTimerTick(uint32_t);
    void onInput(uint32_t);
    const long interval = 500000000L;
};

#endif