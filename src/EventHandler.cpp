/**
 * Copyright 2020 Luis Hsu. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#include <EventHandler.hpp>

#include <unistd.h>
#include <stdexcept>

EventHandler::EventHandler(int size):
    epollFd(epoll_create(size)), isRunning(false), events(size)
{
    if(epollFd == -1){
        throw std::runtime_error("Cannot create event handler");
    }
}

EventHandler::~EventHandler(){
    close(epollFd);
}

void EventHandler::setEvent(int fd, uint32_t flags, std::function<void()> callback){
    struct epoll_event event;
    event.events = flags;
    if(epoll_ctl(epollFd, callbackTable.contains(fd) ? EPOLL_CTL_MOD : EPOLL_CTL_ADD, fd, &event)){
        throw std::runtime_error("Unable to set event");
    }
    callbackTable[fd] = callback;
}

void EventHandler::run(){
    isRunning = true;
    for(int count; isRunning && ((count = epoll_wait(epollFd, events.data(), events.size(), -1)) >= 0) ;){
        // TODO:
    }
}

void EventHandler::stop(){
    isRunning = false;
}