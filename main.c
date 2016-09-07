#include "main.h"

/*
  _________            .__  __             ___ ___         .__
 /   _____/____________|__|/  |_  ____    /   |   \   ____ |  | ______   ___________  ______
 \_____  \\____ \_  __ \  \   __\/ __ \  /    ~    \_/ __ \|  | \____ \_/ __ \_  __ \/  ___/
 /        \  |_> >  | \/  ||  | \  ___/  \    Y    /\  ___/|  |_|  |_> >  ___/|  | \/\___ \
/_______  /   __/|__|  |__||__|  \___  >  \___|_  /  \___  >____/   __/ \___  >__|  /____  >
        \/|__|                       \/         \/       \/     |__|        \/           \/
 */


void create_sprites(int right_paddle_x, int right_paddle_y, int left_paddle_x) {
    right_paddle = sprite_create(right_paddle_x, right_paddle_y, paddle_width, paddle_height, paddle_image_large);
    left_paddle = sprite_create(left_paddle_x, (adjusted_screen_height) / 2 - 3, paddle_width, paddle_height,
                                paddle_image_large);
//    gravity_maker = sprite_create(gravity_maker_x - 2, gravity_maker_y - 2, 5, 5, gravity_maker_image);

}


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

//void pause_handler() {
//
//    float seconds = 0;
//
//    double start_time = get_current_time();
//
//    int time_left = 3000;
//
//    int time_left_in_seconds;
//
//
//    // Kinda Works
//    while (time_left >= 0) {
//        show_screen();
//        time_left -= (int) (get_current_time() - start_time);
//        time_left_in_seconds = time_left / 1000;
//        draw_formatted(adjusted_screen_width / 2 - 13, adjusted_screen_height / 2 - 1, "            %d             ",
//                       time_left_in_seconds);
////        timer_pause(100);
//        start_time -= 500;
//    }
//}


/*
__________        .__  .__      ___ ___         .__
\______   \_____  |  | |  |    /   |   \   ____ |  | ______   ___________  ______
|    |  _/\__  \ |  | |  |   /    ~    \_/ __ \|  | \____ \_/ __ \_  __ \/  ___/
|    |   \ / __ \|  |_|  |__ \    Y    /\  ___/|  |_|  |_> >  ___/|  | \/\___ \
 |______  /(____  /____/____/  \___|_  /  \___  >____/   __/ \___  >__|  /____  >
\/      \/                   \/       \/     |__|        \/           \/
*/


void ball_set() {

    ball_dx = adjusted_screen_width - adjusted_screen_width / 2;
    ball_dy = adjusted_screen_height - adjusted_screen_height / 2;
    double dist = sqrt(ball_dx * ball_dx + ball_dy * ball_dy);

    ball_dx = (ball_dx / dist);
    ball_dy = (ball_dy / dist);
    sprite_turn_to(ball, ball_dx, ball_dy);
    angle = rand() % 45;
    sprite_move_to(ball, adjusted_screen_width / 2, adjusted_screen_height / 2);
    sprite_turn(ball, angle);
}


void wall_bounce_handler(int ball_r, int ball_y, int ball_b, int ball_x) {

    if (dx != sprite_dx(ball) || dy != sprite_dy(ball)) {
        sprite_back(ball);
        sprite_turn_to(ball, dx, dy);
    }

    if (sprite_collision(ball, right_paddle)) {
        if(!(sprite_y(ball)>=sprite_y(right_paddle)) ){
            dy = -dy;
        }

        if(sprite_y(ball)>=((sprite_y(right_paddle)+paddle_width))){
            dy = -dy;
        }
        sprite_move(ball, dx - 2, dy);
        dx = -dx;
        score += 1;
    }

    if (ball_r > adjusted_screen_width - 2) {
        ball_set();
        lives--;
        time_buffered_gravity_maker = get_current_time();
        if (lives > 0) {
            wait_than_play();
        }
    }

    if (sprite_y(ball) < 3 || ball_b > adjusted_screen_height) {
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
}


/*
  ________                                  .__      ___ ___         .__
 /  _____/  ____   ____   ________________  |  |    /   |   \   ____ |  | ______   ___________  ______
/   \  ____/ __ \ /    \_/ __ \_  __ \__  \ |  |   /    ~    \_/ __ \|  | \____ \_/ __ \_  __ \/  ___/
\    \_\  \  ___/|   |  \  ___/|  | \// __ \|  |__ \    Y    /\  ___/|  |_|  |_> >  ___/|  | \/\___ \
 \______  /\___  >___|  /\___  >__|  (____  /____/  \___|_  /  \___  >____/   __/ \___  >__|  /____  >
        \/     \/     \/     \/           \/              \/       \/     |__|        \/           \/
 */

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

    if (key == 'H') {
        paused = 1;
    }
    if (key == 'D') {
        hud_on = !hud_on;
    }
    if(key == 'Q'){
        wait_char();
    }
    if (key == 'R') {
        reset_game();
        ball_set();
    }

    //  Display a HUD
    if (hud_on) {
        // draw_formatted(0,0,"    Right Paddle   : (%2d, %2d)  ", , Top);
        // draw_formatted(0,1,"    Player Paddle Bottom : (%3d, %3d) ", Right, Bottom);
        draw_formatted(0, 2, "    Ball Coordinates : (%2f, %2f) ", sprite_x(ball), sprite_y(ball));
        draw_formatted(0, 2, "    Right Paddle Y: %2f, Ball Y:  %2f ", sprite_y(right_paddle), sprite_y(ball));
        draw_line(0, height / 2, width, height / 2, '-');
        draw_line(width / 2, 0, width / 2, height, '|');
    }
}


// While a key is not pressed
// draw the stuff on the screen and show the screen


void help_screen_maker() {
    clear_screen();
    draw_formatted(screen_width() / 2 - 13, screen_height() / 2 - 3, "CAB202 Assignment 1 - Pong");
    draw_formatted(screen_width() / 2 - 13, screen_height() / 2 - 2, "Joshua Miles");
    draw_formatted(screen_width() / 2 - 13, screen_height() / 2 - 1, "n7176244");
    draw_formatted(screen_width() / 2 - 13, screen_height() / 2 + 1, "Controls:");
    draw_formatted(screen_width() / 2 - 13, screen_height() / 2 + 2, "w: Move Up");
    draw_formatted(screen_width() / 2 - 13, screen_height() / 2 + 3, "s: Move Down");
    draw_formatted(screen_width() / 2 - 13, screen_height() / 2 + 4, "h: show this help screen");
    draw_formatted(screen_width() / 2 - 13, screen_height() / 2 + 5, "q: quit game");
    draw_formatted(screen_width() / 2 - 13, screen_height() / 2 + 6, "l: cycle levels");
    draw_formatted(screen_width() / 2 - 13, screen_height() / 2 + 8, "Press a key to play...");
    show_screen();
}

/*

  ________                        ________                        ___ ___         .__
 /  _____/_____    _____   ____   \_____  \___  __ ___________   /   |   \   ____ |  | ______   ___________  ______
/   \  ___\__  \  /     \_/ __ \   /   |   \  \/ // __ \_  __ \ /    ~    \_/ __ \|  | \____ \_/ __ \_  __ \/  ___/
\    \_\  \/ __ \|  Y Y  \  ___/  /    |    \   /\  ___/|  | \/ \    Y    /\  ___/|  |_|  |_> >  ___/|  | \/\___ \
 \______  (____  /__|_|  /\___  > \_______  /\_/  \___  >__|     \___|_  /  \___  >____/   __/ \___  >__|  /____  >
        \/     \/      \/     \/          \/          \/               \/       \/     |__|        \/           \/

 */

void game_over_screen() {
    clear_screen();
    draw_everything = false;
    draw_formatted(screen_width() / 2 - 13, screen_height() / 2 - 3, "+-------------------------+ ");
    draw_formatted(screen_width() / 2 - 13, screen_height() / 2 - 2, "|                         |");
    draw_formatted(screen_width() / 2 - 13, screen_height() / 2 - 1, "|        Game Over        |");
    draw_formatted(screen_width() / 2 - 13, screen_height() / 2, "|    Play again (y/n)?    |");
    draw_formatted(screen_width() / 2 - 13, screen_height() / 2 + 1, "|                         |");
    draw_formatted(screen_width() / 2 - 13, screen_height() / 2 + 2, "+-------------------------+");
}

void reset_game() {
    clear_screen();
    lives = 10;
    score = 0;
    trig_bool = 1;
    time_buffered_gravity_maker = get_current_time();
//    time_buffered = 0;
    ball_set();

}


/*
__________             .___  .___.__             ___ ___         .__
\______   \_____     __| _/__| _/|  |   ____    /   |   \   ____ |  | ______   ___________  ______
 |     ___/\__  \   / __ |/ __ | |  | _/ __ \  /    ~    \_/ __ \|  | \____ \_/ __ \_  __ \/  ___/
 |    |     / __ \_/ /_/ / /_/ | |  |_\  ___/  \    Y    /\  ___/|  |_|  |_> >  ___/|  | \/\___ \
 |____|    (____  /\____ \____ | |____/\___  >  \___|_  /  \___  >____/   __/ \___  >__|  /____  >
                \/      \/    \/           \/         \/       \/     |__|        \/           \/
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

void handle_left_paddle() {
    if (lives > 0) {
        sprite_draw(left_paddle);
    }
    int paddle_can_move = sprite_y(ball) > 6 && sprite_y(ball) < adjusted_screen_height - 4;

    if (paddle_can_move) {
        sprite_move_to(left_paddle, 3, (int) round(sprite_y(ball)) - 3);
    }

    if (sprite_collision(left_paddle, ball)) {
        if(sprite_y(ball)<sprite_y(left_paddle) && sprite_dx(ball) > 0 ){
            dy = -dy;
        }

        if(sprite_y(ball)>=((sprite_y(left_paddle)+paddle_width))){
            dy = -dy;
        }
        dx = -dx;
    }


}


/*
___________.__                   ___ ___         .__
\__    ___/|__| _____   ____    /   |   \   ____ |  | ______   ___________
  |    |   |  |/     \_/ __ \  /    ~    \_/ __ \|  | \____ \_/ __ \_  __ \
  |    |   |  |  Y Y  \  ___/  \    Y    /\  ___/|  |_|  |_> >  ___/|  | \/
  |____|   |__|__|_|  /\___  >  \___|_  /  \___  >____/   __/ \___  >__|
                    \/     \/         \/       \/     |__|        \/
 */

void wait_than_play() {
//    seconds = 0;
    start_time = (int) get_current_time();
//        waiting = true;
    timer_id main_timer = create_timer(300);
    seconds = 3;

    while (!timer_expired(main_timer)) {
        seconds--;
        draw_formatted(adjusted_screen_width / 2 - 13, adjusted_screen_height / 2 - 3,
                       "+-------------------------+");
        draw_formatted(adjusted_screen_width / 2 - 13, adjusted_screen_height / 2 - 2,
                       "|                         |");
        draw_formatted(adjusted_screen_width / 2 - 13, adjusted_screen_height / 2 - 1,
                       "|            %d            |",
                       seconds);
        draw_formatted(adjusted_screen_width / 2 - 13, adjusted_screen_height / 2, "|                         |");
        draw_formatted(adjusted_screen_width / 2 - 13, adjusted_screen_height / 2 + 1,
                       "|                         |");
        draw_formatted(adjusted_screen_width / 2 - 13, adjusted_screen_height / 2 + 2,
                       "+-------------------------+");
        timer_pause(100);
        show_screen();
    }
    waiting = false;
    seconds = 0;
};


void the_time() {

    timer_seconds = (int) (get_current_time() - time_buffered);
    int timer_seconds_storage = 0;
    int temp = 0;
    if (key == 'P') {
        timer_seconds_storage = (int) get_current_time();
        while (key != 'H') {
            temp = (int) (get_current_time() - timer_seconds_storage);

            draw_formatted(adjusted_screen_width * 3 / 4, 1, " * Time = %2d:%02d", timer_mins, timer_seconds);
            help_screen_maker();
            show_screen();
            key = get_char();
        }
        time_buffered += temp;
    }

    if (timer_seconds > 59) {
        // TODO timermins going up every time the L is pushed
        time_buffered = get_current_time();
//        timer_mins += 1;
    }

    draw_formatted(adjusted_screen_width * 3 / 4, 1, " * Time = %2d:%02d", timer_mins, timer_seconds);
}


void top_board() {
    draw_formatted(1, 1, " Lives = %d", lives);
    draw_formatted(adjusted_screen_width * 1 / 4, 1, " * Score = %d", score);
    draw_formatted(adjusted_screen_width * 2 / 4, 1, " * Level = %d", level);
    the_time();
}


/*
.____                      .__    ________     ___ ___         .__
|    |    _______  __ ____ |  |   \_____  \   /   |   \   ____ |  | ______   ___________  ______
|    |  _/ __ \  \/ // __ \|  |     _(__  <  /    ~    \_/ __ \|  | \____ \_/ __ \_  __ \/  ___/
|    |__\  ___/\   /\  ___/|  |__  /       \ \    Y    /\  ___/|  |_|  |_> >  ___/|  | \/\___ \
|_______ \___  >\_/  \___  >____/ /______  /  \___|_  /  \___  >____/   __/ \___  >__|  /____  >
\/   \/          \/              \/         \/       \/     |__|        \/           \/
*/

void draw_gravity_maker() {
    int count_up_to_to_up_to_5_seconds = (int) (get_current_time() - time_buffered_gravity_maker);

    if ((count_up_to_to_up_to_5_seconds >= 5) && (lives > 0)) {
        int gravity_maker_center_x = (adjusted_screen_width) / 2;
        int gravity_maker_center_y = (adjusted_screen_height) / 2;
        double dx = gravity_maker_center_x - sprite_x(ball);
        double dy = gravity_maker_center_y - sprite_y(ball);
        double dist = sqrt((dx * dx) + (dy * dy));
        if (dist < 15) {
            setup_for_acceleration();
            accelerate_ball_around_gravity_maker();
        }
        draw_formatted((adjusted_screen_width / 2) - 3, adjusted_screen_height / 2 - 2, " \\ | /");
        draw_formatted((adjusted_screen_width / 2) - 3 , adjusted_screen_height / 2 - 1, "  \\|/ ");
        draw_formatted((adjusted_screen_width / 2) - 4, adjusted_screen_height / 2, "- -  - -");
        draw_formatted((adjusted_screen_width / 2) - 3, adjusted_screen_height / 2 + 1, " / | \\");
        draw_formatted((adjusted_screen_width / 2) - 3, adjusted_screen_height / 2 + 2, "/  |  \\");
        show_screen();
    }
}


void setup_for_acceleration(void) {
    int gravity_maker_center_x = (adjusted_screen_width) / 2;
    int gravity_maker_center_y = (adjusted_screen_height) / 2;
    double dx = gravity_maker_center_x - sprite_x(ball);
    double dy = gravity_maker_center_y - sprite_y(ball);
    double dist = sqrt((dx * dx) + (dy * dy));

    dx = dx / dist;
    dy = dy / dist;

    dx *= 10;
    dy *= 10;

    sprite_turn_to(ball, dx, dy);
    // TODO ball getting caught at one point and not even starting when level started from L
    sprite_turn(ball, 90.0);
}

void accelerate_ball_around_gravity_maker() {

    int gravity_maker_center_x = (adjusted_screen_width) / 2;
    int gravity_maker_center_y = (adjusted_screen_height) / 2;


    double x_diff = gravity_maker_center_x - sprite_x(ball);
    double y_diff = gravity_maker_center_y - sprite_y(ball);

    double dist_squared = pow(x_diff, 2) + pow(y_diff, 2);

    if (dist_squared < pow(10, -9)) {
        dist_squared = pow(10, -9);
    }

    double dist = sqrt(dist_squared);

    double dx = sprite_dx(ball);
    double dy = sprite_dy(ball);

    double a = 1 / dist_squared;

    dx += (a * x_diff / dist);
    dy += (a * y_diff / dist);

    double v = sqrt(pow(dx, 2) + pow(dy, 2));

    if (v > 1) {
        dx = dx / v;
        dy = dy / v;
    }
    sprite_turn_to(ball, dx, dy);
}


/*

.____                      .__       _____     ___ ___         .__
|    |    _______  __ ____ |  |     /  |  |   /   |   \   ____ |  | ______   ___________  ______
|    |  _/ __ \  \/ // __ \|  |    /   |  |_ /    ~    \_/ __ \|  | \____ \_/ __ \_  __ \/  ___/
|    |__\  ___/\   /\  ___/|  |__ /    ^   / \    Y    /\  ___/|  |_|  |_> >  ___/|  | \/\___ \
|_______ \___  >\_/  \___  >____/ \____   |   \___|_  /  \___  >____/   __/ \___  >__|  /____  >
        \/   \/          \/            |__|         \/       \/     |__|        \/           \/

 */


void rails_handler(int array[adjusted_screen_width][adjusted_screen_height]) {
    int rail_width_left = (int) round(adjusted_screen_width * 0.25);
    int rail_width_right = (int) round(adjusted_screen_width * 0.75);
    int rail_height_top = (int) round(adjusted_screen_height * 0.333333);
    int rail_height_bottom = (int) round(adjusted_screen_height * 0.66666);

    if (trig_bool) {
        for (int i = 0; i < adjusted_screen_width; ++i) {
            for (int j = 0; j < adjusted_screen_height; ++j) {
                if ((i > rail_width_left && (i < rail_width_right)) &&
                    ((j == rail_height_bottom) || (j == rail_height_top))) {
                    draw_formatted(i, j, "=");
                    array[i][j] = 1;
                }
            }
        }
    }
    trig_bool = false;
    for (int i = 0; i < adjusted_screen_width; ++i) {
        for (int j = 0; j < adjusted_screen_height; ++j) {
            if ((i > rail_width_left && (i < rail_width_right)) &&
                ((j == rail_height_bottom) || (j == rail_height_top)) && (array[i][j] == 1) && (lives > 0)) {
                draw_formatted(i, j, "=");
                array[i][j] = 1;
                // Get the position of the left and right
                if (round(sprite_x(ball)) == i &&
                    round(sprite_y(ball)) == j) {
                    dy = -dy;
                    array[i][j] = 0;
                    array[i + 1][j] = 0;
                    array[i - 1][j] = 0;
                }
            }
        }
    }
}


// Setup game.
void setup(void) {


    adjusted_screen_width = screen_width() - 1;
    adjusted_screen_height = screen_height() - 1;


    int
            left_paddle_x = 3,
            right_paddle_x = adjusted_screen_width - 3,
            right_paddle_y = (adjusted_screen_height - 1) / 2 - 3,

            ball_x = adjusted_screen_width / 2,
            ball_y = adjusted_screen_height / 2;

    time_buffered = get_current_time();
    time_buffered_gravity_maker = get_current_time();

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
    ball_set();


    // Set up the paddle at the centre of the screen.

    create_sprites(right_paddle_x, right_paddle_y, left_paddle_x);
    sprite_draw(right_paddle);
    sprite_draw(ball);
}

void process(void) {

    key = get_char();
    dx = sprite_dx(ball);
    dy = sprite_dy(ball);

//    int right_paddle_y = (int) round(sprite_y(right_paddle));
    int screen_array[adjusted_screen_width][adjusted_screen_height];
    int ball_y = (int) round(sprite_y(ball));
    int ball_b = ball_y + sprite_height(ball);
    int ball_x = (int) round(sprite_x(ball));
    int ball_r = ball_x + sprite_width(ball);


//   angle = rand() % 360 ;

    if (key == 'L' && level <= 4) {

        timer_reset(wait_5_seconds);
        level += 1;
        reset_game();
        timer_mins = 0;
    } else if (level > 4) {
        level = 1;
    }

//    int right_paddle_left = (int) round(sprite_x(right_paddle));
    int right_paddle_top = (int) round(sprite_y(right_paddle));
//    int  right_paddle_right = right_paddle_left + paddle_width - 1;
//    int  right_paddle_bottom = right_paddle_top + paddle_height - 1;


    switch (level) {
        /*
         __      __        .__  .__    __________        .__  .__
        /  \    /  \_____  |  | |  |   \______   \_____  |  | |  |
        \   \/\/   /\__  \ |  | |  |    |    |  _/\__  \ |  | |  |
         \        /  / __ \|  |_|  |__  |    |   \ / __ \|  |_|  |__
          \__/\  /  (____  /____/____/  |______  /(____  /____/____/
               \/        \/                    \/      \/
         */

        case 1 :
            break;

            /*
            __________      ___.
            \______   \ ____\_ |__   ____ ______   ____   ____    ____
             |       _//  _ \| __ \ /  _ \\____ \ /  _ \ /    \  / ___\
             |    |   (  <_> ) \_\ (  <_> )  |_> >  <_> )   |  \/ /_/  >
             |____|_  /\____/|___  /\____/|   __/ \____/|___|  /\___  /
                    \/           \/       |__|               \//_____/
             */
        case 2 :
            handle_left_paddle();
            break;
            /*
              _________.__                     .__               .__  __
             /   _____/|__| ____    ____  __ __|  | _____ _______|__|/  |_ ___.__.
             \_____  \ |  |/    \  / ___\|  |  \  | \__  \\_  __ \  \   __<   |  |
             /        \|  |   |  \/ /_/  >  |  /  |__/ __ \|  | \/  ||  |  \___  |
            /_______  /|__|___|  /\___  /|____/|____(____  /__|  |__||__|  / ____|
                    \/         \//_____/                 \/                \/
             */
        case 3 :
            handle_left_paddle();
            draw_gravity_maker();
            break;
            /*

            */
        case 4 :
            handle_left_paddle();
            rails_handler(screen_array);
            break;
        default :
            draw_formatted(adjusted_screen_width / 2, adjusted_screen_height / 2, "%d is not a valid level", level);
    }

    //TODO reset game when going up level
    handle_right_paddle(adjusted_screen_height, key, right_paddle_top);
    wall_bounce_handler(ball_r, ball_y, ball_b, ball_x);
    sprite_step(ball);
    show_screen();
    clear_screen();
    draw_border(0, 0, adjusted_screen_width, adjusted_screen_height);
    sprite_draw(right_paddle);
    sprite_draw(ball);
    hud_functionality(key, adjusted_screen_width, adjusted_screen_height);
}

void handle_game() {
    show_screen();
    int first_time_in = 1;
    while (!game_over) {
        if (first_time_in) {
            now = (unsigned int) get_current_time();
            srand(now);
            help_screen_maker();
            wait_char();
            clear_screen();
            wait_than_play();
            first_time_in = 0;
        }

//        if (draw_everything) {
        process();
        timer_pause(delay);
        top_board();

        if (lives <= 0) {
            game_over_screen();
            if (key == 'n') {
                game_over = true;
            }
            if (key == 'y') {
                draw_everything = true;
                reset_game();
                help_screen_maker();
                wait_char();
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
