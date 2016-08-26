#pragma once
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "library/cab202_sprites.h"
#include "library/cab202_timers.h"
#include "library/cab202_graphics.h"
#include "naughty_globals.h"



void create_sprites(int right_paddle_x, int right_paddle_y, int left_paddle_x);

bool sprite_collision(sprite_id sprite_1, sprite_id sprite_2);

void set_ball_speed(float mid_width, float mid_height, double speed_modifier);

void ball_set(float mid_width, float mid_height, double speed_modifier);

void wall_bounce_handler(int ball_r, int ball_y, int ball_b, int ball_x);

void draw_border(int left, int top, int right, int bottom);

void hud_functionality(int key, int width, int height);

void game_over_screen();

void reset_game();

void handle_right_paddle(int height, int key, int right_paddle_top);

void handle_left_paddle(int ball_y);

void wait_than_play();

void the_time();

void top_board();

void draw_gravity_maker();

void setup_for_acceleration(void);

void accelerate_ball_around_gravity_maker();

void setup(void);

void process(void);

void handle_game();

void rails_handler(int array[adjusted_screen_width][adjusted_screen_height]);