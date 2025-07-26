
#include <Wire.h>
#include <Adafruit_SSD1306.h>

//define all pins
//buttons
#define up_btn 6
#define left_btn 5
#define right_btn 4
#define down_btn 3
//potentiometer
#define dial A0
//screen
#define SDA A4
#define SCREEN_ADDR 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int dialVal{ 0 };

void setup() {
  pinMode(up_btn, INPUT);
  pinMode(left_btn, INPUT);
  pinMode(right_btn, INPUT);
  pinMode(down_btn, INPUT);
  pinMode(dial, INPUT);
  pinMode(SDA, OUTPUT);

  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDR)){
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }

  //display initial buffer and 
  display.display();
  delay(1000);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

}

void loop() {
  
  dialVal = analogRead(dial);
  Serial.println(dialVal);

  display.clearDisplay();
  display.setCursor(0,18);

  display.print("Dial: ");
  display.println(dialVal);
  display.print("Button1: ");
  display.println(digitalRead(up_btn));
  display.print("Button2: ");
  display.println(digitalRead(left_btn));
  display.print("Button3: ");
  display.println(digitalRead(right_btn));
  display.print("Button4: ");
  display.println(digitalRead(down_btn));

  display.display();
  delay(100);
}
