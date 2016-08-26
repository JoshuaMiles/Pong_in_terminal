#include "main.h"





//        show_screen();

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
    help_screen = sprite_create(adjusted_screen_width / 2 - 10, adjusted_screen_height / 2 - 6, 11, 10,
                                help_screen_image);
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


void wall_bounce_handler(int ball_r, int ball_y, int ball_b, int ball_x) {
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
        wait_than_play();
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

void handle_left_paddle(int ball_y) {
    int paddle_can_move = sprite_y(ball) > 6 && sprite_y(ball) < adjusted_screen_height - 4;

    if (paddle_can_move) {
        sprite_move_to(left_paddle, 3, ball_y - 3);
    }

    if (sprite_collision(left_paddle, ball)) {
        dx = -dx;
    }
    sprite_visible(left_paddle);
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
//
//    seconds = 0;
    while (seconds < 3) {
        seconds = (int) (get_current_time() - start_time);
        draw_formatted(adjusted_screen_width / 2 - 13, adjusted_screen_height / 2 - 3,
                       "+-------------------------+");
        draw_formatted(adjusted_screen_width / 2 - 13, adjusted_screen_height / 2 - 2,
                       "|                         |");
        draw_formatted(adjusted_screen_width / 2 - 13, adjusted_screen_height / 2 - 1,
                       "|            %d            |",
                        3 - seconds);
        draw_formatted(adjusted_screen_width / 2 - 13, adjusted_screen_height / 2, "|                         |");
        draw_formatted(adjusted_screen_width / 2 - 13, adjusted_screen_height / 2 + 1,
                       "|                         |");
        draw_formatted(adjusted_screen_width / 2 - 13, adjusted_screen_height / 2 + 2,
                       "+-------------------------+");
        show_screen();
    }
};


void the_time() {

    timer_seconds = (int) (get_current_time() - time_buffered);

    if (key == 'P') {
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

    if (!paused) {
        draw_formatted(adjusted_screen_width * 3 / 4, 1, " * Time = %2d:%02d", timer_mins, timer_seconds);
    } else if (paused) {
        draw_formatted(adjusted_screen_width * 3 / 4, 1, " * Time = %2d:0%2d", temp_minutes, temp_seconds);
    }
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
    int count_up_to_5_seconds = (int) (get_current_time() - time_buffered);


    if ((count_up_to_5_seconds >= 5) && (lives > 0)) {
        setup_for_acceleration();
        accelerate_ball_around_gravity_maker();
        draw_formatted(adjusted_screen_width / 2, adjusted_screen_height / 2 - 2, " \\ | /");
        draw_formatted(adjusted_screen_width / 2, adjusted_screen_height / 2 - 1, "  \\|/ ");
        draw_formatted(adjusted_screen_width / 2 - 1, adjusted_screen_height / 2, "- -   - -");
        draw_formatted(adjusted_screen_width / 2, adjusted_screen_height / 2 + 1, " / | \\");
        draw_formatted(adjusted_screen_width / 2, adjusted_screen_height / 2 + 2, "/  |  \\");
    }
}


void setup_for_acceleration(void) {
    int gravity_maker_center_x = (adjusted_screen_width) / 2;
    int gravity_maker_center_y = (adjusted_screen_height) / 2;


    double dx = gravity_maker_center_x - sprite_x(ball);
    double dy = gravity_maker_center_y - sprite_y(ball);


    double dist = sqrt((dx * dx) + (dy * dy));

    dx = dx / dist * 0.01;
    dy = dy / dist * 0.01;

    sprite_turn_to(ball, dx, dy);

    sprite_turn(ball, -45.0);
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

    double a = 100 / dist_squared;

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
                ((j == rail_height_bottom) || (j == rail_height_top)) && (array[i][j] == 1)) {

                draw_formatted(i, j, "=");
                array[i][j] = 1;
                if (round(sprite_x(ball)) == i &&
                    round(sprite_y(ball)) == j) {
                    dy = -dy;
                    array[i][j] = 0;
                }
            }
        }
    }
}


// Setup game.
void setup(void) {

    adjusted_screen_width = screen_width() - 1;
    adjusted_screen_height = screen_height() - 1;

    start_time = (int) get_current_time();

    int
            left_paddle_x = 3,
            right_paddle_x = adjusted_screen_width - 3,
            right_paddle_y = (adjusted_screen_height - 1) / 2 - 3,

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

    create_sprites(right_paddle_x, right_paddle_y, left_paddle_x);

    // Draw the right paddle.
    sprite_draw(right_paddle);

    sprite_draw(ball);

    show_screen();
}

void process(void) {

    dx = sprite_dx(ball);
    dy = sprite_dy(ball);
    key = get_char();
//    int right_paddle_y = (int) round(sprite_y(right_paddle));
    int screen_array[adjusted_screen_width][adjusted_screen_height];

    int ball_y = (int) round(sprite_y(ball));
    int ball_b = ball_y + sprite_height(ball) - 1;
    int ball_x = (int) round(sprite_x(ball));
    int ball_r = ball_x + sprite_width(ball) - 1;


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
            handle_left_paddle(ball_y);
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
            handle_left_paddle(ball_y);
            draw_gravity_maker();


            break;

            /*
             __________        .__.__
            \______   \_____  |__|  |   ______
             |       _/\__  \ |  |  |  /  ___/
             |    |   \ / __ \|  |  |__\___ \
             |____|_  /(____  /__|____/____  >
                    \/      \/             \/
             */
        case 4 :
            handle_left_paddle(ball_y);
            rails_handler(screen_array);

            break;
        default :
            draw_formatted(adjusted_screen_width / 2, adjusted_screen_height / 2, "%d is not a valid level", level);
    }


    handle_right_paddle(adjusted_screen_height, key, right_paddle_top);
    wall_bounce_handler(ball_r, ball_y, ball_b, ball_x);
    sprite_step(ball);
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
        wait_than_play();
        process();
        top_board();
//        }
        timer_pause(delay);
        // Do a check to see which game mode
        // if ( update_screen ) {
        //     show_screen();
        // }

        if (lives <= 0) {
            game_over_screen();
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
