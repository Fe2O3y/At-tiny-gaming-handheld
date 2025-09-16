#include "ball.h"

Ball::Ball(int x, int y, int box_height, int box_width){
  x_pos = new_x = x;
  y_pos = new_y = y;
  heading[0] = 0.7;
  heading[1] = 0.3;
}

//move the ball one step
void Ball::iterate(Adafruit_SSD1306 dis){
  new_x += heading[0];
  new_y += heading[1];
  
  //hit top or bottom
  if(new_y <= 0 || new_y >= 64){
    heading[1] = -heading[1];
    new_x = x_pos;
    new_y = y_pos;
    new_x += heading[0];
    new_y += heading[1];
  }
  //hit left or right
  if(new_x <= 0 || new_x >= 128){
    heading[0] = -heading[0];
    new_x = x_pos;
    new_y = y_pos;
    new_x += heading[0];
    new_y += heading[1];
  }
  //other collisions
  if( check_collision(dis) ){
    Serial.println("collision");
    calc_new_heading(dis);
  }
  x_pos = round(new_x);
  y_pos = round(new_y);

}

//check if the ball is going to collide with anythin on the next step
bool Ball::check_collision(Adafruit_SSD1306 dis){   //run each iteration to see if it is colliding, if it is colliding, alter heading   //maybe use getPixel() to see if anything in front of it
  if( dis.getPixel( round(new_x), round(new_y) ) ){
    return true;
  }else{
    return false;
  }
}

//calculate a new heading depending on pixels surrounding   
void Ball::calc_new_heading(Adafruit_SSD1306 dis){    //intended to be run only when the ball is to collide with another object, alters the heading variables to appear a bounce
  //check surrounding pixels to see what sort of surface it is hitting
    //start at the pixel the ball is going to collide from (x_pos, y_pos)
    //find two nearest in the cw and ccw direction -> this gives rough idea of surface it is hitting, not super precise but this is running on an arduino for Peet's sake
    //    {x+y, x+y-, xy-, x-y-, x-y, x-y+, xy+, x+y+}      all possible pixels around the collision point
  
    //need to find where the ball is in ref to the collision point (+ or - x, etc)
    //x_pos - round(new_x)

  while( ! dis.getPixel(check_x, check_y) ){
    
  }
      //current loc of the ball -> x_pos and y_pos
      //projected collision of the ball -> round(new_x) and round(new_y)
      //start from current loc and circle around collision point
      //record when you find a pixel in the clockwise, then record the counter clockwise, these are the two pixels
      
  //calc angle of surface it is hitting
    //find angle between two nearest pixels
      //options:
        //use trig
        //switch statement between possible angles, 8?
  //alter ball angle using trig to simulate bounce
        //options:
          //useing vector addition-fairly easy i think
          //is relative angle easier to calculate/use? -i think slightly harder

}

void Ball::set_position(int x, int y){
  new_x = x;
  new_y = y;
}