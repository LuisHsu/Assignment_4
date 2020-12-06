/**
 * Copyright 2020 Luis Hsu. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#include <exception>
#include <iostream>

#include <SpiningCube.hpp>

int main(int argc, char const *argv[]){
    try{
        SpiningCube app;
        app.exec();
    }catch(std::exception& err){
        std::cerr << err.what() << std::endl;
        return -1;
    }
    return 0;
}
