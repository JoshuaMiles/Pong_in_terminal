//
// Created by Joshua on 17/08/2016.
//

#include "ball.h"
#include "cab202_sprites.h"
#include "naughty_globals.h"


void ball_set(float mid_height, float mid_width) {
    double angle = 90;
//    double angle = rand() % 45;
    sprite_move_to(ball, mid_width, mid_height);

    sprite_turn_to(ball, ball_dx, ball_dy);
    sprite_turn(ball, angle);
}



void ball_set_speed(int adjusted_screen_width, int adjusted_screen_height) {


// Handling the inital speed of the ball
    ball_dx = adjusted_screen_width - adjusted_screen_width/2;

    ball_dy = adjusted_screen_height - adjusted_screen_height/2;

    double dist =  sqrt(ball_dx * ball_dx + ball_dy * ball_dy);

    ball_dx =  (ball_dx / dist) ;

    ball_dy =  (ball_dy / dist) ;

//    ball = sprite_create(ball_x, ball_y, ball_width, ball_height, ball_image);

    ball_set(adjusted_screen_height, adjusted_screen_width);
}

