cmake_minimum_required(VERSION 2.8)
project(pusher CXX)

# C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(pusher src/main.cpp
	src/pushhandler.cpp
	src/json/json.cc
	src/simpleini/ConvertUTF.c)

# Libraries
target_link_libraries(pusher curl)

# Install
INSTALL_TARGETS("/bin" pusher)

# Debian package
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_NAME "pusher")

set(CPACK_PACKAGE_VERSION "0.3")
set(CPACK_DEBIAN_PACKAGE_VERSION "0.3")
execute_process(COMMAND dpkg --print-architecture OUTPUT_VARIABLE CPACK_DEBIAN_PACKAGE_ARCHITECTURE)

set(CPACK_DEBIAN_PACKAGE_DEPENDS "libcurl3 (>= 7.37.1), libstdc++6 (>= 4.9.1), libgcc1 (1:4.9.1)")

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Daniel Stein <d.stein@hackherz.com>")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "push it to the limits.")
set(CPACK_DEBIAN_PACKAGE_SECTION "util")

include(CPack)
