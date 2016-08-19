//
// Created by Joshua on 17/08/2016.
//

#include "paddles.h"
#include "naughty_globals.h"

void create_left_paddle(int adjusted_screen_width, int adjusted_screen_height) {

}

void create_right_paddle(int adjusted_screen_width, int adjusted_screen_height) {

    if (adjusted_screen_height < 21) {
        // height of the screen minus the height of the game status minus one (already minused one)
        paddle_height =  ((adjusted_screen_height - 5) / 2);
    }


}