#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>

bool 
    game_over = false, 
    update_screen = true,
    hud_on = false;

int paddle_width = 2, 
    paddle_height = 7,
    ball_width = 1,
    ball_height = 1,
    delay = 100,
    lives = 10,
    score = 0, 
    level = 1,
    time = 0;

//TODO create a dynamic char image                                                          
char * paddle_image_large =
/**/    "|"
/**/    "|"
/**/    "|"
/**/    "|"
/**/    "|"
/**/    "|"
/**/    "|";

char * gravity_maker_image =
/**/    "\\ | /"
/**/    " \\|/ "
/**/    "- -    - -"
/**/    "/|\\"
/**/    "/ | \\";

char * ball_image =
/**/    "O";

char * a_box_img =
/**/    "OOOO"
/**/    "OOOO"
/**/    "OOOO"
/**/    "OOOO";


sprite_id 
    right_paddle, 
    ball,
    left_paddle,
    gravity_maker;

bool sprite_collision( sprite_id sprite_1, sprite_id sprite_2  ) {

    // bool collided = true;

    int sprite_1_left = round(sprite_x(sprite_1)),
        sprite_1_right = sprite_1_left + sprite_width(sprite_1),
        sprite_1_top = round(sprite_y(sprite_1)),
        sprite_1_bottom = sprite_1_top + sprite_height(sprite_1),

        sprite_2_left = round(sprite_x(sprite_2)),
        sprite_2_right = sprite_2_left + sprite_width(sprite_2),
        sprite_2_top = round(sprite_y(sprite_2)),
        sprite_2_bottom = sprite_2_top + sprite_height(sprite_2) ;

    return 
        sprite_1_bottom > sprite_2_top && 
        sprite_1_top < sprite_2_bottom &&
        sprite_1_left < sprite_2_right && 
        sprite_1_right > sprite_2_left;
}

void ball_set( mid_height, mid_width ) {
    srand(get_current_time());
    int angle = rand() % 45;
    sprite_move_to( ball, mid_width, mid_height );
    // sprite_turn(ball, angle);
}

void draw_border( left, top, right, bottom ) {
    // Top line
    draw_line( left, top, right, top, '*' );
    // Status line
    draw_line( left, top + 2, right, top + 2, '*' );
    // Bottom line
    draw_line( left, bottom, right, bottom, '*' );
    // Left line
    draw_line( left, top, left, bottom, '*' );
    // Right line
    draw_line( right, top, right, bottom, '*' );
}


// Setup game.
void setup( void ) {
    // Useful variables.
    int w = screen_width(),
        h = screen_height(), 
        paddle_width = 1,
        paddle_height = 7;

    if (h < 21) {
        paddle_height = ((h - 2)/2);
    }        

    // Screen Setup
    // Draw the border (setup).
    int left = 0, right = w - 1, top = 0, bottom = h - 1;
   
   draw_border( left, top, right, bottom);

    // Initial setup of the ball

    int ball_x,
        ball_y;

    ball_y =  (h-1)/2;

    // ball_x =  h-5;

    ball_x = (w-1)/2;

    ball = sprite_create(ball_x, ball_y, ball_width, ball_height, ball_image);

    // Speed of the ball
    sprite_turn_to(ball, 0.6, -0.04);

    // handling levels
    // TODO turn this into a switch statement
    if( level == 3 ){
        int gravity_maker_x,
            gravity_maker_y;

        gravity_maker_x =  (w-1)/2;

        gravity_maker_y = (h-1)/2;


        gravity_maker = sprite_create( gravity_maker_x-2 , gravity_maker_y-2, 5, 5, gravity_maker_image );

        // Draw the gravity thingy.
        sprite_draw(gravity_maker);
    }

    // Set up the paddle at the centre of the screen.
    int right_paddle_x = w - 4;
    int right_paddle_y = (h-1)/2;
    right_paddle = sprite_create(right_paddle_x, right_paddle_y-3, 1, paddle_height, paddle_image_large);

    // a_box = sprite_create( w/2 + 4 , h/2 - 3 , 4, 4, a_box_img);

    // Draw the right paddle.
    sprite_draw(right_paddle);
    sprite_draw(ball);
 
    show_screen();
}

// Play one turn of game.
void process(void) {
    int w = screen_width(),
        h = screen_height(),
        key = get_char(),
        // Position of the right paddle

        right_paddle_y = round(sprite_y(right_paddle));


    int top = 0, bottom = h - 1 , left = 0, right = w - 1;

    sprite_step( ball );

    draw_formatted( 1, 1, " Lives = %d", lives);
    draw_formatted( w * 1/4, 1, " * Score = %d", score );
    draw_formatted( w * 2/4, 1, " * Level = %d", level );
    draw_formatted( w * 3/4, 1," * Time = %2d", level );

    double dx = sprite_dx( ball );
    double dy = sprite_dy( ball );

    int ball_y = round(sprite_y(ball)), 
        ball_b = ball_y + sprite_height(ball) - 1, 
        ball_x = round(sprite_x(ball)),     
        ball_r = ball_x + sprite_width(ball) - 1;

    int right_paddle_left = round(sprite_x(right_paddle)),
        right_paddle_top = round(sprite_y(right_paddle)),
        right_paddle_right = right_paddle_left + paddle_width - 1,
        right_paddle_bottom = right_paddle_top + paddle_height - 1;


    // TODO reset the game ie the position of the ball


    // if(sprite_collision( ball, a_box )){
    //     draw_formatted(0,3,"It works");
    // } 

    if ( sprite_collision( ball, right_paddle ) ) {
        dx = -dx;
    }

    if ( ball_r > w - 1 ) {
    	lives--;
        // ball_set( (h-1)/2, (w-1)/2 );
    }

    if(ball_y < 1 || ball_b > h - 1) {
        dy = -dy;
    }

    // Top wall collision
    if( ball_y < 4 ) {
        ball_y = 5;
        dy = -dy;
    }

    // Bottom wall collision with ball 
    if( ball_b > h - 2 ) {
        // TODO why is it 2 and 3 ?
        ball_b = h - 3 ;
        dy = -dy;
    }

    // Left and right wall collision
    if( ball_x < 1  ) {
        dx = -dx;
    }

    if ( dx != sprite_dx(ball) || dy != sprite_dy(ball) ) {
        sprite_back(ball);
        sprite_turn_to(ball, dx, dy);
    }

    sprite_turn_to(ball, dx, dy);

    // Move right paddle up according to specification.
    if ( key == 'w' && right_paddle_top > 3 ) {
        sprite_move(right_paddle, 0, -1);
    }

     // Move right paddle down according to specification.
    else if ( key  == 's' && right_paddle_top < h - paddle_height - 1) {
        sprite_move(right_paddle, 0, +1);
    }


    // if ( key == 'w' && sprite_y(a_box) > 3 ) {
    //     sprite_move( a_box, 0, -1);
    // }

     // Move right paddle down according to specification.
    // else if ( key  == 's' &&  sprite_y(a_box) < h - 4 - 1) {
    //     sprite_move( a_box, 0, +1);
    // }

    // if ( key == 'a' && sprite_x(a_box) > 1 ) {
    //     sprite_move(a_box, -1, 0);
    // }

     // Move right paddle down according to specification.
    // else if ( key  == 'd' ) {
    //     sprite_move(a_box, +1, 0);
    // }



    
    //TODO when should i show the screen?
    show_screen();

    clear_screen();

    draw_border( left, top, right, bottom);

    // Draw the paddles.
    sprite_draw( right_paddle );
    sprite_draw( ball );
    // sprite_draw( a_box );


    if(key == 'D'){
        hud_on = !hud_on;
    }

    if( key == 'R'){
        ball_set( h, w );
    }

    //  Display a HUD 
    if (hud_on){
        // draw_formatted(0,0,"    Right Paddle   : (%2d, %2d)  ", , Top);
        // draw_formatted(0,1,"    Player Paddle Bottom : (%3d, %3d) ", Right, Bottom);	
        draw_formatted( 0, 2, "    Ball Coordinates : (%2d, %2d) ", ball_x, ball_y);
        draw_formatted( 0, 3, "    Ball Collision : (%1d)", sprite_collision(ball,right_paddle));
        draw_formatted( 0, 4, "    Screen Width (x) : (%2d) Screen Height (y) : (%2d)", w, h);
        
        // draw_formatted(0,3,"    Hero Top-Right : (%3d, %3d) ", Right, Top);
        // draw_formatted(0,4,"    Collided   :%d     " , (int) collided);

        draw_line(left, bottom/2, right, bottom/2, '-');

        draw_line(right/2, top, right/2, bottom, '|');
    }
}

int main( void ) {
    setup_screen();
    setup();
    show_screen();

    while ( !game_over ) {
        process();

        // Do a check to see which game mode 
        // if ( update_screen ) {
        //     show_screen();
        // }

        if (lives == 0){
            game_over = true;
        }
        timer_pause( delay );
    }
    cleanup_screen();

    return 0;
}