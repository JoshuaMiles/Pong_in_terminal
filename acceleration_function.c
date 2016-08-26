





void accelerate_station_towards_star(void) {

    double x_diff = x_star - sprite_x(station);

    double y_diff = y_star - sprite_y(station);

    double dist_squared = (x_diff * x_diff) + (y_diff * y_diff);        

    if(dist_squared < 1e-10) {
        dist_squared = 1e-10;
    } 
 
    double dist = sqrt(dist_squared);

    double dx = sprite_dx(station);
    double dy = sprite_dy(station);

    double acceleration = 1.0 / dist_squared;

    dx = dx + (acceleration * x_diff/dist);
    dy = dy + (acceleration * y_diff/dist);
  
    double v = sqrt(dx * dx + dy * dy); 

    if (v > 1 ){
        dx = dx/v;
        dy = dy/v;    
    }

    sprite_turn_to(station, dx, dy);
}