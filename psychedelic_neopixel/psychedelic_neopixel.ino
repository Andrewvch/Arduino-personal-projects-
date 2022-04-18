#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
int but1 = 31;
int but2 = 33;
int val = 0;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(147, 6, NEO_GRB + NEO_KHZ400);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket

  // End of trinket special code
  pinMode(but1, INPUT);
  pinMode(but2, INPUT);
  strip.begin();
  strip.setBrightness(255);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
 rainbowCycle(200);

}
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<150; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
  for(j=150; j>0; j--) {
     for(i=strip.numPixels(); i>0; i--) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void test(uint8_t wait){
    uint16_t i, j;
     int but1 = 31;
 

  for(j=0; j<2000; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i=i+3) {
      strip.setPixelColor(i, Wheel(((i * 1000 / strip.numPixels()) + j) & 255));
        if (digitalRead(but1)== HIGH){
            delay(300);
            test3(5);
            }
    }
    strip.show();
    delay(wait);
  }
   for(j=2000; j>0; j--) { // 5 cycles of all colors on wheel
    for(i=strip.numPixels(); i>0; i=i-3) {
      strip.setPixelColor(i, Wheel(((i * 1000 / strip.numPixels()) + j) & 255));
        if (digitalRead(but1)== HIGH){
            delay(300);
            test3(5);
          }
    }
    strip.show();
    delay(wait);
  }
   test(100);
}
void pulseWhite(uint8_t wait) {
  for(int j=0; j<256; j++) { // Ramp up from 0 to 255
    // Fill entire strip with white at gamma-corrected brightness level 'j':
    strip.fill(strip.Color(25,255,j, strip.gamma8(j)));
    strip.show();
    delay(wait);
  }
  delay(5000);

  for(int j=255; j>=0; j--) { // Ramp down from 255 to 0
    strip.fill(strip.Color(25,255,j, strip.gamma8(j)));
    strip.show();
    delay(wait);
    
  }
  pulseWhite(25);
}
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  int but1 = 31;


  for(j=0; j<2000; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 1000 / strip.numPixels()) + j) & 255));
        if (digitalRead(but1)== HIGH){
            delay(300);
            test(100);
            }
    }
    strip.show();
    delay(wait);
  }
   for(j=2000; j>0; j--) { // 5 cycles of all colors on wheel
    for(i=strip.numPixels(); i>0; i--) {
      strip.setPixelColor(i, Wheel(((i * 1000 / strip.numPixels()) + j) & 255));
        if (digitalRead(but1)== HIGH){
            delay(300);
            test(100);
            }
    }
    strip.show();
    delay(wait);
    
  }
  rainbowCycle(200);
}

//Theatre-style crawling lights.

void test3(uint8_t wait) {
  uint16_t i, j;
   int but1 = 31;

  for(j=0; j<2000; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 500 / strip.numPixels()) + j) & 50));
        if (digitalRead(but1)== HIGH){
           whiteOverRainbow(10, 150);
            delay(300);
            }
            
    }
    strip.show();
    delay(wait);
  }
   for(j=2000; j>0; j--) { // 5 cycles of all colors on wheel
    for(i=strip.numPixels(); i>0; i--) {
      strip.setPixelColor(i, Wheel(((i * 500 / strip.numPixels()) + j) & 50));
        if (digitalRead(but1)== HIGH){
            whiteOverRainbow(10, 150);
            delay(300);
            }
    }
    strip.show();
    delay(wait);
  }
  test3(5);
}



void whiteOverRainbow(int whiteSpeed, int whiteLength) {
int but1 = 31;

  if(whiteLength >= strip.numPixels()) whiteLength = strip.numPixels() - 1;

  int      head          = whiteLength - 1;
  int      tail          = 0;
  int      loops         = 10000;
  int      loopNum       = 0;
  uint32_t lastTime      = millis();
  uint32_t firstPixelHue = 0;
//  if (digitalRead(but1)== HIGH){
//            delay(300);
//            pulseWhite(25);
//            }

  for(;;) {
     for(int j=0; j<220; j++) { // Ramp up from 0 to 255
    delay(25);
    for(int i=0; i<strip.numPixels(); i++) {  // For each pixel in strip...
      if(((i >= tail) && (i <= head)) ||      //  If between head & tail...
         ((tail > head) && ((i >= tail) || (i <= head)))) {
        strip.setPixelColor(i, strip.Color(25,255,j, strip.gamma8(j))); 
       
      }
      
      
         else {                                             // else set rainbow
        int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
        strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
      } 
    }
    

   strip.show();///
    
    
    firstPixelHue += 40; // Advance just a little along the color wheel

    if((millis() - lastTime) > whiteSpeed) { // Time to update head/tail?
      if(++head >= strip.numPixels()) {      // Advance head, wrap around
        head = 0;
        if(++loopNum >= loops) return;
      }
      if(++tail >= strip.numPixels()) {      // Advance tail, wrap around
        tail = 0;
      }
      lastTime = millis();                   // Save time of last movement
    }
  
  }
for(int j=220; j>0; j--) { // Ramp down from 255 to 0
 delay(50);
    for(int i=0; i<strip.numPixels(); i++) {  // For each pixel in strip...
      if(((i >= tail) && (i <= head)) ||      //  If between head & tail...
         ((tail > head) && ((i >= tail) || (i <= head)))) {
        strip.setPixelColor(i, strip.Color(25,255,j, strip.gamma8(j))); 
       
      }
      
      
         else {                                             // else set rainbow
        int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
        strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
      } 
    }
    

    strip.show();  
    
    firstPixelHue += 40; // Advance just a little along the color wheel

    if((millis() - lastTime) > whiteSpeed) { // Time to update head/tail?
      if(++head >= strip.numPixels()) {      // Advance head, wrap around
        head = 0;
        if(++loopNum >= loops) return;
      }
      if(++tail >= strip.numPixels()) {      // Advance tail, wrap around
        tail = 0;
      }
      lastTime = millis();                   // Save time of last movement
    }
 
  }
}
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
