# Try to find Wayland on a Unix system
#
# This will define:
#
#   Wayland_FOUND       - True if Wayland is found
#   Wayland_LIBRARIES   - Link these to use Wayland
#   Wayland_INCLUDE_DIR - Include directory for Wayland
#   Wayland_DEFINITIONS - Compiler flags for using Wayland
#
# In addition the following more fine grained variables will be defined:
#
#   Wayland_CLIENT_FOUND  Wayland_CLIENT_INCLUDE_DIR  Wayland_CLIENT_LIBRARIES
#   Wayland_SERVER_FOUND  Wayland_SERVER_INCLUDE_DIR  Wayland_SERVER_LIBRARIES
#   Wayland_EGL_FOUND     Wayland_EGL_INCLUDE_DIR     Wayland_EGL_LIBRARIES
#
# Copyright (c) 2013 Martin Gräßlin <mgraesslin@kde.org>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

IF (NOT WIN32)
  IF (Wayland_INCLUDE_DIR AND Wayland_LIBRARIES)
    # In the cache already
    SET(Wayland_FIND_QUIETLY TRUE)
  ENDIF ()

  # Use pkg-config to get the directories and then use these values
  # in the FIND_PATH() and FIND_LIBRARY() calls
  FIND_PACKAGE(PkgConfig)
  PKG_CHECK_MODULES(PKG_WAYLAND QUIET wayland-client wayland-server wayland-egl wayland-cursor)

  SET(Wayland_DEFINITIONS ${PKG_WAYLAND_CFLAGS})

  FIND_PATH(Wayland_CLIENT_INCLUDE_DIR  NAMES wayland-client.h HINTS ${PKG_WAYLAND_INCLUDE_DIRS})
  FIND_PATH(Wayland_SERVER_INCLUDE_DIR  NAMES wayland-server.h HINTS ${PKG_WAYLAND_INCLUDE_DIRS})
  FIND_PATH(Wayland_EGL_INCLUDE_DIR     NAMES wayland-egl.h    HINTS ${PKG_WAYLAND_INCLUDE_DIRS})
  FIND_PATH(Wayland_CURSOR_INCLUDE_DIR  NAMES wayland-cursor.h HINTS ${PKG_WAYLAND_INCLUDE_DIRS})

  FIND_LIBRARY(Wayland_CLIENT_LIBRARIES NAMES wayland-client   HINTS ${PKG_WAYLAND_LIBRARY_DIRS})
  FIND_LIBRARY(Wayland_SERVER_LIBRARIES NAMES wayland-server   HINTS ${PKG_WAYLAND_LIBRARY_DIRS})
  FIND_LIBRARY(Wayland_EGL_LIBRARIES    NAMES wayland-egl      HINTS ${PKG_WAYLAND_LIBRARY_DIRS})
  FIND_LIBRARY(Wayland_CURSOR_LIBRARIES NAMES wayland-cursor   HINTS ${PKG_WAYLAND_LIBRARY_DIRS})

  set(Wayland_INCLUDE_DIR ${Wayland_CLIENT_INCLUDE_DIR} ${Wayland_SERVER_INCLUDE_DIR} ${Wayland_EGL_INCLUDE_DIR} ${Wayland_CURSOR_INCLUDE_DIR})

  set(Wayland_LIBRARIES ${Wayland_CLIENT_LIBRARIES} ${Wayland_SERVER_LIBRARIES} ${Wayland_EGL_LIBRARIES} ${Wayland_CURSOR_LIBRARIES})

  list(REMOVE_DUPLICATES Wayland_INCLUDE_DIR)

  include(FindPackageHandleStandardArgs)

  FIND_PACKAGE_HANDLE_STANDARD_ARGS(Wayland_CLIENT  DEFAULT_MSG  Wayland_CLIENT_LIBRARIES  Wayland_CLIENT_INCLUDE_DIR)
  FIND_PACKAGE_HANDLE_STANDARD_ARGS(Wayland_SERVER  DEFAULT_MSG  Wayland_SERVER_LIBRARIES  Wayland_SERVER_INCLUDE_DIR)
  FIND_PACKAGE_HANDLE_STANDARD_ARGS(Wayland_EGL     DEFAULT_MSG  Wayland_EGL_LIBRARIES     Wayland_EGL_INCLUDE_DIR)
  FIND_PACKAGE_HANDLE_STANDARD_ARGS(Wayland_CURSOR  DEFAULT_MSG  Wayland_CURSOR_LIBRARIES  Wayland_CURSOR_INCLUDE_DIR)
  FIND_PACKAGE_HANDLE_STANDARD_ARGS(Wayland         DEFAULT_MSG  Wayland_LIBRARIES         Wayland_INCLUDE_DIR)

  MARK_AS_ADVANCED(
        Wayland_INCLUDE_DIR         Wayland_LIBRARIES
        Wayland_CLIENT_INCLUDE_DIR  Wayland_CLIENT_LIBRARIES
        Wayland_SERVER_INCLUDE_DIR  Wayland_SERVER_LIBRARIES
        Wayland_EGL_INCLUDE_DIR     Wayland_EGL_LIBRARIES
        Wayland_CURSOR_INCLUDE_DIR  Wayland_CURSOR_LIBRARIES
  )

ENDIF ()
