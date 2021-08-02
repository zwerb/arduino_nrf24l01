/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Libs for OLED
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// DEFAULTS FOR OLED

#define OLED_RESET 4 // not used / nicht genutzt bei diesem Display
Adafruit_SSD1306 display(OLED_RESET);

 char inChar;
 String string;

// DEFAULTS FOR RF

RF24 radio(10, 9); // CE, CSN

const byte address[6] = "00001";

void setup() {

  // SETUP RF
  Serial.begin(115200);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  // SETUP OLED
  // initialize with the I2C addr 0x3C / mit I2C-Adresse 0x3c initialisieren
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
                 
  Serial.begin(115200);
  
  string.reserve(200);

  display.display();
  delay(500);
  display.clearDisplay();
  display.setTextSize(0.5);
  display.setTextColor(INVERSE); 

  display.setCursor(0,0); 
  display.print("BOOT");               
  display.display();  

  delay(500);
  display.clearDisplay();
}

void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
          Serial.println("rx: "+String(text));
          display.clearDisplay();        
          display.setCursor(0,0); 
          display.print(String(text));               
          display.display(); 
  delay(2000);
  display.clearDisplay();
  display.display();
  }


  
}
