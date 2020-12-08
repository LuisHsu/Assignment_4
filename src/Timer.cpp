/**
 * Copyright 2020 Luis Hsu. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#include <Timer.hpp>
#include <unistd.h>
#include <sys/timerfd.h>
#include <stdexcept>

Timer::Timer():
    fd(timerfd_create(CLOCK_MONOTONIC, 0))
{
    if(fd == -1){
        throw std::runtime_error("Cannot create timer");
    }
}

Timer::~Timer(){
    close(fd);
}

void Timer::start(long nsec){
    struct itimerspec newspec;
    newspec.it_interval.tv_sec = 0;
    newspec.it_interval.tv_nsec = nsec;
    newspec.it_value.tv_sec = 0;
    newspec.it_value.tv_nsec = nsec;
    if(timerfd_settime(fd, 0, &newspec, nullptr)){
        throw std::runtime_error("Cannot start timer");
    }
}

void Timer::stop(){
    struct itimerspec newspec;
    newspec.it_interval.tv_sec = 0;
    newspec.it_interval.tv_nsec = 0;
    newspec.it_value.tv_sec = 0;
    newspec.it_value.tv_nsec = 0;
    if(timerfd_settime(fd, 0, &newspec, nullptr)){
        throw std::runtime_error("Cannot stop timer");
    }
}