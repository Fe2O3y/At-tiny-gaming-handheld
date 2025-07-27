
#include <Wire.h>
#include <Adafruit_SSD1306.h>

//define all pins
//buttons
#define up_btn 720    //actual read: 711-712
#define left_btn 780  //actual read: 770-771
#define right_btn 850 //actual read: 840-841
#define down_btn 935  //actual read: 923
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

int get_btn_press();
int dialVal{ 0 };

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
  
  dialVal = analogRead(dial);
  Serial.println(dialVal);

  display.clearDisplay();
  display.setCursor(0,16);
  display.print("Dial: ");
  display.println(dialVal);
  switch( get_btn_press() ){
    case 0: break;  //no button is being pressed
    case 1: display.println("UP_BUTTON");
      break;
    case 2: display.println("LEFT_BUTTON");
      break;
    case 3: display.println("RIGHT_BUTTON");
      break;
    case 4: display.println("DOWN_BUTTON");
      break;
    case 5: display.println("MENU_BUTTON");
      break;
  }

  display.display();
  delay(100);
}

int get_btn_press(){
  int x = analogRead(btn_in);
  if(x == 0)
    return 0;
  else if(x < up_btn)
    return 1;
  else if(x < left_btn)
    return 2;
  else if(x < right_btn)
    return 3;
  else if(x < down_btn)
    return 4;
  else return 5;
}
