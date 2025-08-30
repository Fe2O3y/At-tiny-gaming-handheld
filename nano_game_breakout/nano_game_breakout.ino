
#include <Wire.h>
#include <Adafruit_SSD1306.h>

//define all pins
//buttons
#define up_btn 950    //actual read: 941
#define left_btn 970  //actual read: 960
#define down_btn 990  //actual read: 980
#define right_btn 1010 //actual read: 1001
#define menu_btn 1023 //actual read: 1023
#define btn_in A1
//potentiometer
#define dial A0
//screen
#define SDA A4
#define SCREEN_ADDR 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int get_btn_press();      //gets button pin value and translates it to a a value [1,5]
void display_paddle(int); //displays the paddle on bottom of the screen based on the analog value of the pot pin
void display_buffer();    //regulates fps by waiting to send the display command until the right time

void setup() {
  pinMode(btn_in, INPUT);
  pinMode(dial, INPUT);
  pinMode(SDA, OUTPUT);

  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDR)){
    Serial.println("SSD1306 allocation failed");
    for(;;);    //loop forever if screen not successfully allocated
  }

  //display initial buffer and 
  display.display();
  delay(1000);
  display.setTextColor(SSD1306_WHITE);

}

void loop() {
  
  const int dialVal = analogRead(dial);
  Serial.println(dialVal);

  display.clearDisplay();
  display.setCursor(0,16);

  switch( get_btn_press() ){
    case 0: break;  //no button is being pressed
    case 1: display.println("UP_BUTTON");
      break;
    case 2: display.println("LEFT_BUTTON");
      break;
    case 3: display.println("DOWN_BUTTON");
      break;
    case 4: display.println("RIGHT_BUTTON");
      break;
    case 5: display.println("MENU_BUTTON");
      break;
  }

  display_paddle(dialVal);
  display_buffer();
}

int get_btn_press(){
  const int x = analogRead(btn_in);
  Serial.print("btn_read: ");
  Serial.println(x);
  if(x < up_btn - 20)
    return 0;
  else if(x < up_btn)
    return 1;
  else if(x < left_btn)
    return 2;
  else if(x < down_btn)
    return 3;
  else if(x < right_btn)
    return 4;
  else return 5;
}

void display_paddle(int xPos){      //TODO: i think the writeFillRect is not great, implement this myself
  static const int p_w{ 16 };  //paddle width
  static const int p_h{ 8 };   //paddle height

  int pos = (1023 - xPos)/8;
  pos = pos-(p_w/2);
  display.writeFillRect(pos, 56, p_w, p_h, 0xFF);
}

void display_buffer(){
  static const int goal_fps{ 20 };
  static unsigned long p_time{ millis() };
  unsigned long c_time{ millis() };
  if( c_time - p_time < 1000/goal_fps ){
    //output real fps
    display.setCursor(0, 0);
    display.print( 1000/(c_time - p_time) );
    display.print( '/' );           //displays the real fps(x) as x/goal_fps
    display.println( goal_fps );
    while( millis() - p_time < 1000/goal_fps ){} //do nothing          //TODO: this time could be used in future for other calculations
  }
  p_time += 1000/goal_fps;       //adding a const amount like this should make the processor go as fast as it can in other frames to catch up
  display.display();
}
