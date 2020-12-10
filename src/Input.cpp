/**
 * Copyright 2020 Luis Hsu. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#include <Input.hpp>

#include <iostream>
#include <cerrno>
#include <stdexcept>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <systemd/sd-login.h>
#include <libudev.h>

static int open_restricted(const char *path, int flags, void *){
    int fd = open(path, flags);
    return (fd < 0) ? -errno : fd;
}
 
static void close_restricted(int fd, void *){
    close(fd);
}

Input::Input():
    isAvailable(false),
    interface({.open_restricted = open_restricted, .close_restricted = close_restricted})
{
    // Create udev context
    udevCtx = udev_new();
    // Find seat
    char** seats;
    if(sd_get_seats(&seats) == 0){
        std::cerr << "[WARNING]: Cannot find systemd seats, input will be unavailable" << std::endl;
        return;
    }
    // Create context & assign seat
    input = libinput_udev_create_context(&interface, nullptr, udevCtx);
    if(libinput_udev_assign_seat(input, seats[0])){
        std::cerr << "[WARNING]: Cannot assign seat to libinput, input will be unavailable" << std::endl;
        libinput_unref(input);
        udev_unref(udevCtx);
        return;
    }
    // Expose fd
    fd = libinput_get_fd(input);
    // Initialized
    isAvailable = true;
}

Input::~Input(){
    if(isAvailable){
        libinput_unref(input);
        udev_unref(udevCtx);
    }
}

std::pair<libinput_event_type, struct libinput_event*> Input::getEvent(){
    if(libinput_dispatch(input)){
        throw std::runtime_error("Cannot dispatch input");
    }
    return std::pair<libinput_event_type, struct libinput_event*>(libinput_next_event_type(input), libinput_get_event(input));
}