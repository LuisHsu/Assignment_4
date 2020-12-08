/**
 * Copyright 2020 Luis Hsu. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#include <SpiningCube.hpp>

#include <iostream>

SpiningCube::SpiningCube():
    eventHandler(1)
{
    eventHandler.setEvent(timer.fd, EPOLLIN, [](uint32_t){
        // TODO:
        std::cout << "tick" << std::endl; // FIXME:
    });
}

SpiningCube::~SpiningCube(){

}

void SpiningCube::exec(){
    timer.start(1000000L);
    eventHandler.run();
}