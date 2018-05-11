#include <SPI.h>
#include <SerialFlash.h>
#include <FastLED.h>

#define COLOR_ORDER BGR  //if your colors look incorrect, change the color order here
#define NUM_LEDS    120  //change this number for the final LED count
#define BRIGHTNESS  180
#define FRAMES_PER_SECOND 20

#define LEDdata 3
#define LEDclock 4

#define specialFortune 11
#define kioskLight 12
#define kioskBell 15
#define IR_PIN 18

CRGB leds[NUM_LEDS];

void setup() {
  delay(3000); // sanity delay
  FastLED.addLeds<APA102, LEDdata, LEDclock, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();

  Serial.begin(9600);

  pinMode(IR_PIN, INPUT_PULLUP);
  pinMode(specialFortune, OUTPUT);
  pinMode(kioskLight, OUTPUT);

  delay(1000);
}

int hue = 0;

void loop() {
  int sense_motion = digitalRead(IR_PIN);
  digitalWrite(specialFortune, HIGH);
  digitalWrite(kioskLight, HIGH);

  Serial.println(sense_motion);

  if(sense_motion == LOW) {
    Serial.println("Motion Sensed");

    digitalWrite(specialFortune, LOW);
    delay(10);
    digitalWrite(specialFortune, HIGH); //these 3 lines give the special fortune trigger

    // 22 second loop while we do the audio file
    uint16_t startTime = millis();
    uint16_t endTime = startTime + 22000;
    uint16_t kioskEndTime = startTime + 3000;
    while (millis() < endTime) {

      if (millis() < kioskEndTime) {
        digitalWrite(kioskLight, HIGH);
      } else {
        digitalWrite(kioskLight, LOW);
      }

      // Rainbow fill on the LEDs
      fill_rainbow(leds, NUM_LEDS, hue, 7);
      FastLED.show();
      // Moving rainbow chase pattern
      EVERY_N_MILLISECONDS(10) {
        hue++;
      }
    }

    digitalWrite(kioskLight, LOW);

    delay(10);
  }
}
