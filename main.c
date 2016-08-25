#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "library/cab202_sprites.h"
#include "library/cab202_timers.h"
#include "library/cab202_graphics.h"
#include "naughty_globals.h"

sprite_id
        right_paddle,
        ball,
        left_paddle,
        gravity_maker;


/*
   ________                                  .__      ___ ___         .__
 /  _____/  ____   ____   ________________  |  |    /   |   \   ____ |  | ______   ___________  ______
/   \  ____/ __ \ /    \_/ __ \_  __ \__  \ |  |   /    ~    \_/ __ \|  | \____ \_/ __ \_  __ \/  ___/
\    \_\  \  ___/|   |  \  ___/|  | \// __ \|  |__ \    Y    /\  ___/|  |_|  |_> >  ___/|  | \/\___ \
 \______  /\___  >___|  /\___  >__|  (____  /____/  \___|_  /  \___  >____/   __/ \___  >__|  /____  >
        \/     \/     \/     \/           \/              \/       \/     |__|        \/           \/
 */


bool sprite_collision(sprite_id sprite_1, sprite_id sprite_2) {

    int sprite_1_left = (int) round(sprite_x(sprite_1)),
            sprite_1_right = (int) sprite_1_left + sprite_width(sprite_1),
            sprite_1_top = (int) round(sprite_y(sprite_1)),
            sprite_1_bottom = sprite_1_top + sprite_height(sprite_1),

            sprite_2_left = (int) round(sprite_x(sprite_2)),
            sprite_2_right = sprite_2_left + sprite_width(sprite_2),
            sprite_2_top = (int) round(sprite_y(sprite_2)),
            sprite_2_bottom = sprite_2_top + sprite_height(sprite_2);

    return
            sprite_1_bottom > sprite_2_top &&
            sprite_1_top < sprite_2_bottom &&
            sprite_1_left < sprite_2_right &&
            sprite_1_right > sprite_2_left;
}

void draw_border(int left, int top, int right, int bottom) {
    // Top line
    draw_line(left, top, right, top, '*');
    // Status line
    draw_line(left, top + 2, right, top + 2, '*');
    // Bottom line
    draw_line(left, bottom, right, bottom, '*');
    // Left line
    draw_line(left, top, left, bottom, '*');
    // Right line
    draw_line(right, top, right, bottom, '*');
}


void hud_functionality(int key, int width, int height) {

    if (key == 'H' ){
        paused = 1;
    }
    if (key == 'D') {
        hud_on = !hud_on;
    }
    if (key == 'R') {
        ball_set(adjusted_screen_width, adjusted_screen_height, 1);
    }

    //  Display a HUD
    if (hud_on) {
        // draw_formatted(0,0,"    Right Paddle   : (%2d, %2d)  ", , Top);
        // draw_formatted(0,1,"    Player Paddle Bottom : (%3d, %3d) ", Right, Bottom);
        draw_formatted(0, 2, "    Ball Coordinates : (%2f, %2f) ", sprite_x(ball), sprite_y(ball));
        draw_line(0, height / 2, width, height / 2, '-');
        draw_line(width / 2, 0, width / 2, height, '|');
    }
}


void reset_game() {
    clear_screen();
    lives = 10;
    score = 0;
}


/*
__________.__       .__     __    __________             .___  .___.__
\______   \__| ____ |  |___/  |_  \______   \_____     __| _/__| _/|  |   ____
|       _/  |/ ___\|  |  \   __\  |     ___/\__  \   / __ |/ __ | |  | _/ __ \
 |    |   \  / /_/  >   Y  \  |    |    |     / __ \_/ /_/ / /_/ | |  |_\  ___/
|____|_  /__\___  /|___|  /__|    |____|    (____  /\____ \____ | |____/\___  >
\/  /_____/      \/                       \/      \/    \/           \/

 */


void handle_right_paddle(int height, int key, int right_paddle_top) {
    if (key == 'w' && right_paddle_top >= 4) {
        sprite_move(right_paddle, 0, -1);
    }

        // Move right paddle down according to specification.
    else if (key == 's' && right_paddle_top < height - paddle_height) {
        sprite_move(right_paddle, 0, +1);
    }
}



/*
__________        .__  .__      ___ ___         .__
\______   \_____  |  | |  |    /   |   \   ____ |  | ______   ___________  ______
|    |  _/\__  \ |  | |  |   /    ~    \_/ __ \|  | \____ \_/ __ \_  __ \/  ___/
|    |   \ / __ \|  |_|  |__ \    Y    /\  ___/|  |_|  |_> >  ___/|  | \/\___ \
 |______  /(____  /____/____/  \___|_  /  \___  >____/   __/ \___  >__|  /____  >
\/      \/                   \/       \/     |__|        \/           \/
*/

void set_ball_speed(float mid_width, float mid_height, double speed_modifier) {
    ball_dx = mid_width * 2 - mid_width;
    ball_dy = mid_height * 2 - mid_height;
    double dist = sqrt(ball_dx * ball_dx + ball_dy * ball_dy);
    ball_dx = (ball_dx / dist) * speed_modifier;
    ball_dy = (ball_dy / dist) * speed_modifier;
    sprite_turn_to(ball, ball_dx, ball_dy);
}

void ball_set(float mid_width, float mid_height, double speed_modifier) {

    set_ball_speed(mid_width, mid_height, speed_modifier);
    angle = rand() % 45;
    sprite_move_to(ball, mid_width, mid_height);
    sprite_turn(ball, angle);
}

/*
 *
 */


void create_sprites(int right_paddle_x, int right_paddle_y, int left_paddle_x, int gravity_maker_x,
                    int gravity_maker_y) {
    right_paddle = sprite_create(right_paddle_x, right_paddle_y, paddle_width, paddle_height, paddle_image_large);
    left_paddle = sprite_create(left_paddle_x, (adjusted_screen_height) / 2 - 3, paddle_width, paddle_height,
                                paddle_image_large);
//    gravity_maker = sprite_create(gravity_maker_x - 2, gravity_maker_y - 2, 5, 5, gravity_maker_image);
    help_screen = sprite_create(adjusted_screen_width/2 - 10, adjusted_screen_height/2 - 6, 11, 10, help_screen_image);
}


void the_time() {

    timer_seconds = (int) (get_current_time() - time_buffered);

    if ( key == 'P' ) {
        paused = !paused;
        temp_seconds = timer_seconds;
        temp_minutes = timer_mins;
//        timer_seconds
    }

    if (timer_seconds > 59) {
        time_buffered = get_current_time();
        timer_mins += 1;
    }

//    if(paused) {
//        temp_seconds = timer_seconds;
//        temp_minutes = timer_mins;
//    }

    if ( !paused ) {
        draw_formatted(adjusted_screen_width * 3 / 4, 1, " * Time = %2d:%2d", timer_mins, timer_seconds);
    } else if( paused ) {
        draw_formatted(adjusted_screen_width * 3 / 4, 1, " * Time = %2d:0%2d", temp_minutes, temp_seconds);
    }
}



void top_board() {

        draw_formatted(1, 1, " Lives = %d", lives);
        draw_formatted(adjusted_screen_width * 1 / 4, 1, " * Score = %d", score);
        draw_formatted(adjusted_screen_width * 2 / 4, 1, " * Level = %d", level);
        the_time();
}

void pause_handler(int width, int height) {

    float seconds  = 0 ;

    double start_time = get_current_time();

    int time_left = 3000 ;

    int time_left_in_seconds;


    // Kinda Works
    while(time_left >= 0) {
        show_screen();
        time_left -=  (int) ( get_current_time() - start_time);
        time_left_in_seconds =  time_left /1000;
        draw_formatted( adjusted_screen_width / 2 - 13, adjusted_screen_height / 2 - 1, "            %d             ", time_left_in_seconds);
//        timer_pause(100);
        start_time -= 500;
    }
}

/*

.____                      .__       _____     ___ ___         .__
|    |    _______  __ ____ |  |     /  |  |   /   |   \   ____ |  | ______   ___________  ______
|    |  _/ __ \  \/ // __ \|  |    /   |  |_ /    ~    \_/ __ \|  | \____ \_/ __ \_  __ \/  ___/
|    |__\  ___/\   /\  ___/|  |__ /    ^   / \    Y    /\  ___/|  |_|  |_> >  ___/|  | \/\___ \
|_______ \___  >\_/  \___  >____/ \____   |   \___|_  /  \___  >____/   __/ \___  >__|  /____  >
        \/   \/          \/            |__|         \/       \/     |__|        \/           \/

 */
void draw_gravity_maker () {
    draw_formatted(adjusted_screen_width/2,adjusted_screen_height/2-2," \\ | /");
    draw_formatted(adjusted_screen_width/2,adjusted_screen_height/2-1,"  \\|/ ");
    draw_formatted(adjusted_screen_width/2-1,adjusted_screen_height/2, "- -   - -");
    draw_formatted(adjusted_screen_width/2,adjusted_screen_height/2+1, " / | \\");
    draw_formatted(adjusted_screen_width/2,adjusted_screen_height/2+2, "/  |  \\");
}




// Setup game.
void setup(void) {

    adjusted_screen_width = screen_width() - 1;
    adjusted_screen_height = screen_height() - 1;

    int
            left_paddle_x = 3,
            right_paddle_x = adjusted_screen_width - 3,
            right_paddle_y = (adjusted_screen_height - 1) / 2 - 3,

            gravity_maker_x = adjusted_screen_width / 2,
            gravity_maker_y = adjusted_screen_height / 2,

            ball_x = adjusted_screen_width / 2,
            ball_y = adjusted_screen_height / 2;

    time_buffered = get_current_time();

    wait_5_seconds = create_timer(5000);

    if (adjusted_screen_height < 21) {
        // height of the screen minus the height of the game status minus one (already minused one)
        paddle_height = ((adjusted_screen_height - 5) / 2);
    }

    // Screen Setup
    draw_border(0, 0, adjusted_screen_width, adjusted_screen_height);
    // Handling the inital speed of the ball
    ball_dx = adjusted_screen_width - adjusted_screen_width / 2;
    ball_dy = adjusted_screen_height - adjusted_screen_height / 2;
    double dist = sqrt(ball_dx * ball_dx + ball_dy * ball_dy);
    ball_dx = (ball_dx / dist);
    ball_dy = (ball_dy / dist);
    ball = sprite_create(ball_x, ball_y, ball_width, ball_height, ball_image);
    ball_set(adjusted_screen_width / 2, adjusted_screen_height / 2, 0.5);




    // Set up the paddle at the centre of the screen.

    create_sprites(right_paddle_x, right_paddle_y, left_paddle_x, gravity_maker_x, gravity_maker_y);


    // Draw the right paddle.
    sprite_draw(right_paddle);

    sprite_draw(ball);

    show_screen();
}


void process(void) {



//        seconds = (int) (get_current_time() - start_time);
//        time_left = (int) (time_left - seconds);
//        draw_formatted( adjusted_screen_width / 2 - 13, adjusted_screen_height / 2 - 3, "+-------------------------+");
//        draw_formatted( adjusted_screen_width / 2 - 13, adjusted_screen_height / 2 - 2, "|                         |");
//        draw_formatted( adjusted_screen_width / 2 - 13, adjusted_screen_height / 2 - 1, "|            %d             |", seconds);
//        draw_formatted( adjusted_screen_width / 2 - 13, adjusted_screen_height / 2,     "|                       |");
//        draw_formatted( adjusted_screen_width / 2 - 13, adjusted_screen_height / 2 + 1, "|                         |");
//        draw_formatted( adjusted_screen_width / 2 - 13, adjusted_screen_height / 2 + 2, "+-------------------------+");
//        timer_pause(100);

    dx = sprite_dx(ball);
    dy = sprite_dy(ball);
    int adjusted_screen_width = screen_width() - 1;
    int adjusted_screen_height = screen_height() - 1;
    key = get_char();
//    int right_paddle_y = (int) round(sprite_y(right_paddle));
    int screen_array[adjusted_screen_width][adjusted_screen_height];

    int rail_width_left = (int) round(adjusted_screen_width * 0.25);
    int rail_width_right = (int) round(adjusted_screen_width * 0.75);
    int rail_height_top = (int) round(adjusted_screen_height * 0.333333);
    int rail_height_bottom = (int) round(adjusted_screen_height * 0.66666);

    now = (unsigned int) get_current_time();
    srand(now);
//   angle = rand() % 360 ;

    if (key == 'L' && level <= 4) {
        ball_set(adjusted_screen_width, adjusted_screen_height, 2);
        timer_reset(wait_5_seconds);
        level += 1;
    } else if (level > 4) {
        level = 1;
    }

    sprite_step(ball);
    int ball_y = (int) round(sprite_y(ball));
    int ball_b = ball_y + sprite_height(ball) - 1;
    int ball_x = (int) round(sprite_x(ball));
    int ball_r = ball_x + sprite_width(ball) - 1;

//    int right_paddle_left = (int) round(sprite_x(right_paddle));
    int right_paddle_top = (int) round(sprite_y(right_paddle));
//    int  right_paddle_right = right_paddle_left + paddle_width - 1;
//    int  right_paddle_bottom = right_paddle_top + paddle_height - 1;

    bool paddle_can_move = 0;
//    screen_array[adjusted_screen_width][adjusted_screen_height] ;
    switch (level) {
        // wall ball
        case 1 :

//            sprite_turn_to(ball, ball_dx * 0.5, ball_dy * 0.5);
            break;

            // robopong
        case 2 :

            paddle_can_move = sprite_y(ball) > 6 && sprite_y(ball) < adjusted_screen_height - 4;

            if (paddle_can_move) {
                sprite_move_to(left_paddle, 3, ball_y - 3);
            }

            if (sprite_collision(left_paddle, ball)) {
                dx = -dx;
            }
            sprite_visible(left_paddle);
            break;

            //Singularity
        case 3 :
            paddle_can_move = sprite_y(ball) > 6 && sprite_y(ball) < adjusted_screen_height - 4;

            if (paddle_can_move) {
                sprite_move_to(left_paddle, 3, ball_y - 3);
            }

            if (sprite_collision(left_paddle, ball)) {
                dx = -dx;
            }
            sprite_visible(left_paddle);

            int count_up_to_5_seconds = (int) (get_current_time() - time_buffered);

            if ((count_up_to_5_seconds >= 5) && !game_over) {
                draw_gravity_maker();
            }

            sprite_visible(left_paddle);



            break;
            // rails
        case 4 :
            paddle_can_move = sprite_y(ball) > 6 && sprite_y(ball) < adjusted_screen_height - 4;

            if (paddle_can_move) {
                sprite_move_to(left_paddle, 3, ball_y - 3);
            }

            if (sprite_collision(left_paddle, ball)) {
                dx = -dx;
            }


//            handle_left_paddle();
            if (trig_bool) {
                for (int i = 0; i < adjusted_screen_width; ++i) {
                    for (int j = 0; j < adjusted_screen_height; ++j) {
                        if ((i > rail_width_left && (i < rail_width_right)) &&
                            ((j == rail_height_bottom) || (j == rail_height_top))) {
                            draw_formatted(i, j, "=");
                            screen_array[i][j] = 1;
                        }
                    }
                }
            }

            trig_bool = false;
            for (int i = 0; i < adjusted_screen_width; ++i) {
                for (int j = 0; j < adjusted_screen_height; ++j) {
                    if ((i > rail_width_left && (i < rail_width_right)) &&
                        ((j == rail_height_bottom) || (j == rail_height_top)) && (screen_array[i][j] == 1)) {

                        draw_formatted(i, j, "=");
                        screen_array[i][j] = 1;
                        if (round(sprite_x(ball)) == i &&
                            round(sprite_y(ball)) == j) {
                            dy = -dy;
                            screen_array[i][j] = 0;
                        }
                    }
                }
            }
            break;
        default :
            draw_formatted(0, 1, "%d is not a valid level", level);
    }


    handle_right_paddle(adjusted_screen_height, key, right_paddle_top);

    // handling all of the collision with the walls and the right paddle

    if (dx != sprite_dx(ball) || dy != sprite_dy(ball)) {
        sprite_back(ball);
        sprite_turn_to(ball, dx, dy);
    }

    if (sprite_collision(ball, right_paddle)) {
        dx = -dx;
        score += 1;
    }

    if (ball_r > adjusted_screen_width) {
        ball_set((adjusted_screen_width) / 2, (adjusted_screen_height) / 2, 1);
        lives--;
        pause_handler(adjusted_screen_width, adjusted_screen_height);
    }


    if (ball_y < 1 || ball_b > adjusted_screen_height) {
        dy = -dy;
    }

    // Top wall collision
    if (ball_y < 3) {
        ball_y = 5;
        dy = -dy;
    }

    // Bottom wall collision with ball
    if (ball_b > adjusted_screen_height - 1) {
        ball_b = adjusted_screen_height - 2;
        dy = -dy;
    }

    // Left and right wall collision
    if (ball_x < 1) {
        dx = -dx;
    }

    if (dx != sprite_dx(ball) || dy != sprite_dy(ball)) {
        sprite_back(ball);
        sprite_turn_to(ball, dx, dy);
    }
    show_screen();
    clear_screen();
    draw_border(0, 0, adjusted_screen_width, adjusted_screen_height);

    sprite_draw(right_paddle);
    sprite_draw(ball);
    sprite_draw(left_paddle);



    hud_functionality(key, adjusted_screen_width, adjusted_screen_height);

}

void handle_game() {
    show_screen();
    while (!game_over) {
//        if (draw_everything) {
            process();
            top_board();
//        }
        timer_pause(delay);
        // Do a check to see which game mode
        // if ( update_screen ) {
        //     show_screen();
        // }

        if (lives <= 0) {
            clear_screen();
            draw_everything = false;
            draw_formatted(screen_width() / 2 - 13, screen_height() / 2 - 3, "+-------------------------+ ");
            draw_formatted(screen_width() / 2 - 13, screen_height() / 2 - 2, "|                         |");
            draw_formatted(screen_width() / 2 - 13, screen_height() / 2 - 1, "|        Game Over        |");
            draw_formatted(screen_width() / 2 - 13, screen_height() / 2, "|    Play again (y/n)?    |");
            draw_formatted(screen_width() / 2 - 13, screen_height() / 2 + 1, "|                         |");
            draw_formatted(screen_width() / 2 - 13, screen_height() / 2 + 2, "+-------------------------+");
            if (key == 'n') {
                game_over = true;
            }
            if (key == 'y') {
                draw_everything = true;
                reset_game();
                show_screen();
            }
        }

    }
}

int main(void) {
    setup_screen();

    setup();
    handle_game();

    cleanup_screen();

    return 0;
}
