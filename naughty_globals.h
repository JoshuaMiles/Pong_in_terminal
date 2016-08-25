//
// Created by Joshua on 17/08/2016.
//

#include "library/cab202_timers.h"
#include "library/cab202_sprites.h"

#ifndef PONGINCLION_NAUGHTY_GLOBALS_H
#define PONGINCLION_NAUGHTY_GLOBALS_H

#endif //PONGINCLION_NAUGHTY_GLOBALS_H


 sprite_id
        right_paddle,
        ball,
        left_paddle,
        help_screen;

double  ball_dx,
        ball_dy,
        time_buffered,
        angle;

char *paddle_image_large =
/**/    "|"
/**/    "|"
/**/    "|"
/**/    "|"
/**/    "|"
/**/    "|"
/**/    "|";

char *gravity_maker_image =
/**/    "\\ | /"
/**/    " \\|/ "
/**/    "- -    - -"
/**/    "/ | \\"
/**/    "/  |  \\";

char *ball_image =
/**/    "O";
char *rail_image =
/**/    "=";


char *help_screen_image =
/**/    "CAB202 Assignment 1 - Pong"
/**/    "   Joshua Miles"
/**/    "n7176244"
/**/    "\n"
/**/    "Controls:"
/**/    "Arrow keys: move up/down"
/**/    "h: show this help screen"
/**/    "q: quit game"
/**/    "l: cycle levels"
/**/    "\n"
/**/    "Press a key to play...";


bool
        game_over = false,
        hud_on = false,
        draw_everything = true,
        trig_bool = true;
int     paddle_width = 1,
        paddle_height = 7,

        ball_width = 1,
        ball_height = 1,

        delay = 15,
        lives = 1,
        score = 0,
        level = 3,

        timer_mins = 0,
        timer_seconds = 0,
        linear_distance = 0,
        adjusted_screen_height,
        adjusted_screen_width,
        key,
        paused = 0,
        temp_seconds = 0,
        temp_minutes = 0;

unsigned int now;
double dx, dy;
timer_id wait_5_seconds;