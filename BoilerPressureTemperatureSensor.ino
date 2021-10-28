#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>

#include <WiFiManager.h>

#include <time.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     0 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;


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
  
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
    // it is a good practice to make sure your code sets wifi mode how you want it.
    
    //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wm;

    // reset settings - wipe stored credentials for testing
    // these are stored by the esp library
    //wm.resetSettings();

    // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
    // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
    // then goes into a blocking loop awaiting configuration and will return success result

  bool res;
    // res = wm.autoConnect(); // auto generated AP name from chipid
    // res = wm.autoConnect("AutoConnectAP"); // anonymous ap

  display.clearDisplay();
  display.setCursor(0, 12);
  display.print("password");
  display.display();
  delay(200);
  
  res = wm.autoConnect("AutoConnectAP","password"); // password protected ap

  if(!res) {
    display.clearDisplay();
    display.setCursor(0, 12);
    display.print("WiFi failed!");
    display.display();
    delay(5000);
    Serial.println("Failed to connect!");
   // ESP.restart();
    } 
  else {
      //if you get here you have connected to the WiFi    
    display.clearDisplay();
    display.setCursor(0, 12);
    display.print("WiFi OK!");
    display.display();
    delay(5000);
    Serial.println("connected...yeey :)");
    }
  delay(1000);
  // Get the NTP time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop() {

  int SrcVal = analogRead(A0);

  float PressureSensorValue= ((float)analogRead(A0)/1024*3.3 - 0.5)*5/4;
  
  Serial.println(SrcVal);
  Serial.println(PressureSensorValue);
  
  
  display.clearDisplay();

  display.setCursor(0, 12);
  display.print("P: ");
  display.print(PressureSensorValue);
  display.print(" bar");

  display.setCursor(0, 31);
  display.print("T: ");
  display.print(SrcVal);
  display.println(" C");

  display.display();

  struct tm timeinfo;
//  if (getLocalTime(&timeinfo)) {
//      char time_str[16];
//      strftime(time_str, 16, "%H:%M:%S", &timeinfo);
//
//      //draw_time(time_str);
//  }  
  delay(500);
  
}
