//
// Created by Joshua on 17/08/2016.
//

#include "additional_sprite_functions.h"


bool sprite_collision(sprite_id sprite_1, sprite_id sprite_2) {

    int sprite_1_left = round(sprite_x(sprite_1)),
            sprite_1_right = sprite_1_left + sprite_width(sprite_1),
            sprite_1_top = round(sprite_y(sprite_1)),
            sprite_1_bottom = sprite_1_top + sprite_height(sprite_1),

            sprite_2_left = round(sprite_x(sprite_2)),
            sprite_2_right = sprite_2_left + sprite_width(sprite_2),
            sprite_2_top = round(sprite_y(sprite_2)),
            sprite_2_bottom = sprite_2_top + sprite_height(sprite_2);

    return
            sprite_1_bottom > sprite_2_top &&
            sprite_1_top < sprite_2_bottom &&
            sprite_1_left < sprite_2_right &&
            sprite_1_right > sprite_2_left;
}