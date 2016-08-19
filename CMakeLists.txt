cmake_minimum_required(VERSION 3.3)
project(pongInClion)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -lzdk -lncurses")

set(SOURCE_FILES main.c ./library/cab202_graphics.c ./library/cab202_sprites.c ./library/cab202_timers.c library/ball.c library/ball.h naughty_globals.c naughty_globals.h library/additional_sprite_functions.c library/additional_sprite_functions.h library/paddles.c library/paddles.h library/border.c library/border.h)
add_executable(pongInClion ${SOURCE_FILES})