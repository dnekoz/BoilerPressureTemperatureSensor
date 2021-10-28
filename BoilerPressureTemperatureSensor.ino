#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     0 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// float PressuareSensorValue = 0;

void setup() {
  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(500);
  
  display.setFont(&FreeSans9pt7b);
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text

}

void loop() {

  float PressuareSensorValue= ((float)analogRead(A0)/1024*3.3 - 0.5)*5/4; //*3,3) - 0,5)*5)/4
  
  Serial.println(SrcVal);
  Serial.println(PressureSensorValue);
  
  
  display.clearDisplay();

  display.setCursor(0, 12);
  display.print("P: ");
  display.print(PressuareSensorValue);
  display.print(" bar");

  display.setCursor(0, 31);
  display.print("T: ");
  display.print(SrcVal);
  display.println(" C");

  display.display();
  delay(200);
}
