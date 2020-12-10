/**
 * Copyright 2020 Luis Hsu. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#include <exception>
#include <iostream>
#include <unistd.h>
#include <termios.h>

#include <SpiningCube.hpp>

int main(int argc, char const *argv[]){
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    {
		struct termios rawterm = term;
		cfmakeraw(&rawterm);
		rawterm.c_oflag |= OPOST;
        rawterm.c_lflag |= ISIG;
		tcsetattr(STDIN_FILENO, TCSANOW, &rawterm);
	}
    try{
        SpiningCube app;
        app.exec();
    }catch(std::exception& err){
        std::cerr << err.what() << std::endl;
        tcflush(STDIN_FILENO, TCIFLUSH);
	    tcsetattr(STDIN_FILENO, TCSANOW, &term);
        return -1;
    }
    tcflush(STDIN_FILENO, TCIFLUSH);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
    return 0;
}
