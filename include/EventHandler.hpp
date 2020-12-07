#ifndef EVENTHANDLER_DEF
#define EVENTHANDLER_DEF

#include <sys/epoll.h>
#include <cstdint>
#include <vector>
#include <functional>
#include <unordered_map>

class EventHandler{
public:
    EventHandler(int size);
    ~EventHandler();
    void run();
    void stop();
    void setEvent(int fd, uint32_t flags, std::function<void()> callback);
private:
    int epollFd;
    bool isRunning;
    std::vector<struct epoll_event> events;
    std::unordered_map<int, std::function<void()>> callbackTable;
};

#endif