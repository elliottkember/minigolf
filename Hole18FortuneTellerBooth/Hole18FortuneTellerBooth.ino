#include <SPI.h>
#include <SerialFlash.h>
#include <FastLED.h>

#define COLOR_ORDER BGR  //if your colors look incorrect, change the color order here
#define NUM_LEDS    300  //change this number for the final LED count
#define BRIGHTNESS  180
#define FRAMES_PER_SECOND 20

#define LEDdata 3
#define LEDclock 4

#define specialFortune 11
#define kioskLight 12
#define kioskBell 15
#define IR_PIN 18
//#define buttonPin 9 //This was used when we had one teensy. This sketch is now for the Fortune Booth teensy which will not interact with the wayfinder.

CRGB leds[NUM_LEDS];

void setup() {
    //delay(3000); // sanity delay
    FastLED.addLeds<SK9822, LEDdata, LEDclock, COLOR_ORDER, DATA_RATE_MHZ(1)>(leds, NUM_LEDS);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 3000);
    FastLED.setBrightness(255);


    Serial.begin(9600);

    pinMode(IR_PIN, INPUT_PULLUP);
    pinMode(specialFortune, OUTPUT);
    pinMode(kioskLight, OUTPUT);

    delay(1000);
}

int hue = 0;

//  *******************
//  *****MAIN CODE*****
//  *******************
void loop() {

int sense_motion = digitalRead(IR_PIN);
unsigned long kioskEndTime;
unsigned long endTime;
unsigned long startTime;

digitalWrite(specialFortune, HIGH);
digitalWrite(kioskLight, HIGH);
fill_solid( leds, NUM_LEDS, CRGB(255,214,170));
FastLED.show();
hue = 0;
//Serial.println(sense_motion);

if (sense_motion == LOW) {
  digitalWrite(specialFortune, LOW);
  delay(10);
  digitalWrite(specialFortune, HIGH);
  digitalWrite(kioskLight, LOW);
// 22 second loop while we do the audio file
   startTime = millis();
   endTime = startTime + 22000;
   kioskEndTime = startTime + 3000;
   Serial.println(startTime);
   Serial.println(endTime);
   while (millis() < endTime) {

     if (millis() > kioskEndTime) {
       digitalWrite(kioskLight, HIGH);
     }
     // Rainbow fill on the LEDs
     fill_rainbow(leds, NUM_LEDS, hue, 7);
     FastLED.show();
     // Moving rainbow chase pattern
     EVERY_N_MILLISECONDS(10) {
       hue++;
       Serial.println(millis());
     }
   }
   delay(1000);
 }

   //digitalWrite(kioskLight, HIGH);

   delay(10);
}
