cmake_minimum_required(VERSION 2.8)

set(GCC_C_FLAGS "-g")

add_executable(GBEmu core.c dma.c instruction_count.c instructions.c io.c joypad.c main.c mem.c timer.c video.c debug.c)

target_link_libraries(GBEmu SDL2) 
