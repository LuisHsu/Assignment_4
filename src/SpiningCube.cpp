/**
 * Copyright 2020 Luis Hsu. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#include <SpiningCube.hpp>

#include <iostream>
#include <linux/input-event-codes.h>

SpiningCube::SpiningCube():
    eventHandler(2)
{
    eventHandler.setEvent(timer.fd, EPOLLIN | EPOLLET, std::bind(&SpiningCube::onTimerTick, this, std::placeholders::_1));
    eventHandler.setEvent(input.fd, EPOLLIN | EPOLLET, std::bind(&SpiningCube::onInput, this, std::placeholders::_1));
    // TODO:
}

SpiningCube::~SpiningCube(){

}

void SpiningCube::exec(){
    timer.start(interval);
    eventHandler.run();
}

void SpiningCube::onTimerTick(uint32_t){
    // TODO:
    timer.dispatch();
}

void SpiningCube::onInput(uint32_t){
    auto eventPair = input.getEvent();
    if(eventPair.first == LIBINPUT_EVENT_KEYBOARD_KEY){
        struct libinput_event_keyboard* kbevent = libinput_event_get_keyboard_event(eventPair.second);
        if(libinput_event_keyboard_get_key_state(kbevent) == LIBINPUT_KEY_STATE_PRESSED){
            switch(libinput_event_keyboard_get_key(kbevent)){
                case KEY_A:
                    std::cout << "Key A" << std::endl; // TODO:
                break;
                case KEY_P:
                    std::cout << "Key P" << std::endl; // TODO:
                break;
                case KEY_G:
                    std::cout << "Key G" << std::endl; // TODO:
                break;
            }
        }
    }
    libinput_event_destroy(eventPair.second);
}