cmake_minimum_required(VERSION 3.21)
project(ProjektC C)

set(CMAKE_C_STANDARD 17)

file(MAKE_DIRECTORY ProjektC/Saves)
add_executable(Run.o ProjektC/Code/main.c ProjektC/Code/Header.h ProjektC/Code/Handlers/CreateFileHandler.c ProjektC/Code/Handlers/CreateFileHandler.h ProjektC/Code/Handlers/DataHandler.c ProjektC/Code/Handlers/DataHandler.h ProjektC/Code/Handlers/DateHandler.c ProjektC/Code/Handlers/DateHandler.h ProjektC/Code/Handlers/Vector.c ProjektC/Code/Handlers/Vector.h)

