/**
 * Copyright 2020 Luis Hsu. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#include <SpiningCube.hpp>

SpiningCube::SpiningCube():
    eventHandler(1)
{

}

SpiningCube::~SpiningCube(){

}

void SpiningCube::exec(){
    eventHandler.run();
}