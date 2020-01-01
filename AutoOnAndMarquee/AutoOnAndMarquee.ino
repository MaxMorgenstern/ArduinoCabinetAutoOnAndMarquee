#include <IRremote.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// LED Count
int led_count = 34; 
// LED Controll pin
int led_1_pin = 2;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(led_count, led_1_pin, NEO_GRB + NEO_KHZ800);

// Remote
IRsend irsend;

void setup() {
  // Init the LED
  pixels.begin();
  pixels.show();

  // Delay and Turn n TV
  delay(5000);
  irsend.sendRC5(0x84C, 12);
  delay(500);
  irsend.sendRC5(0x84C, 12);
}


void loop() {
  // draw th rainbow effect
  rainbow(50);
}


void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
