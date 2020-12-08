#ifndef TIMER_DEF
#define TIMER_DEF

class Timer{
public:
    Timer();
    ~Timer();
    void start(long nsec);
    void stop();
    int fd;
};

#endif