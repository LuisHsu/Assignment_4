/**
 * Copyright 2020 Luis Hsu. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#include <Input.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>

static int open_restricted(const char *path, int flags, void *){
    int fd = open(path, flags);
    return fd < 0 ? -errno : fd;
}
 
static void close_restricted(int fd, void *){
    close(fd);
}

Input::Input():
    interface({.open_restricted = open_restricted, .close_restricted = close_restricted})
{

}

Input::~Input(){
    
}
