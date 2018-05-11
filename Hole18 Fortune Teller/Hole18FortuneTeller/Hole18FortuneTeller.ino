#include <SPI.h>
#include <SerialFlash.h>
#include <FastLED.h>

#define COLOR_ORDER BGR  //if your colors look incorrect, change the color order here
#define NUM_LEDS    120  //change this number for the final LED count
#define BRIGHTNESS  180
#define FRAMES_PER_SECOND 20
#define TEMPERATURE_1 Tungsten100W //This is the basic temp without Hole in One

#define LEDdata 3
#define LEDclock 4

#define specialFortune 11
#define kioskLight 12
#define kioskBell 15
#define IR_PIN 18

CRGB leds[NUM_LEDS];

void setup() {
  delay(3000); // sanity delay
  FastLED.addLeds<APA102, LEDdata, LEDclock, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.setTemperature(TEMPERATURE_1);
  FastLED.show();

  Serial.begin(9600);

  pinMode(IR_PIN, INPUT_PULLUP);
  pinMode(specialFortune, OUTPUT);
  pinMode(kioskLight, OUTPUT);
  //pinMode(buttonPin, INPUT_PULLUP);
  
  delay(1000);
}

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

    fill_rainbow(leds, NUM_LEDS, 0, 7);
    FastLED.show();
    delay(22000); //this should be the duration of the message
    FastLED.setTemperature(TEMPERATURE_1);
    FastLED.show();

    digitalWrite(kioskLight, LOW);
    delay(3000);
    digitalWrite(kioskLight, HIGH);
    delay(10);
  }
}
