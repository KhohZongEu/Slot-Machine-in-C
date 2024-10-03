cmake_minimum_required(VERSION 3.21)
project(Slotmachine LANGUAGES C VERSION 1.0)


set(CMAKE_C_STANDARD 99)
set(C_STANDARD_REQUIRED True)


add_executable(Slotmachine ./src/main.c)