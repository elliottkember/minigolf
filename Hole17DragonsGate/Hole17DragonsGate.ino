#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <FastLED.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=105,182
AudioOutputAnalogStereo  dacs1;          //xy=321,188
AudioConnection          patchCord1(playSdWav1, 0, dacs1, 0);
AudioConnection          patchCord2(playSdWav1, 1, dacs1, 1);
// GUItool: end automatically generated code

#define SDCARD_CS_PIN     BUILTIN_SDCARD
#define COLOR_ORDER       BGR  //if your colors look incorrect, change the color order here
#define NUM_LEDS          97  //change this number for the final LED count
#define BRIGHTNESS        255
#define FRAMES_PER_SECOND 20

#define IR_Pin 18
#define LEDdata 3
#define LEDclock 4

CRGB leds[NUM_LEDS];

void setup() {
  //delay(3000); // sanity delay
  pinMode(IR_Pin, INPUT_PULLUP);
  FastLED.addLeds<SK9822, LEDdata, LEDclock, COLOR_ORDER, DATA_RATE_MHZ(1)>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 3000);
  FastLED.setBrightness(BRIGHTNESS);
  fill_solid(leds, NUM_LEDS, CRGB(255,147,41)); //fill eyes with warm white
  FastLED.show();

  Serial.begin(9600);
  AudioMemory(20);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  delay(1000);
}

int hue = 0;

void ambient() {
  int brightness = beatsin16(30, 180, 200);
  hue = beatsin16(20, 0, 32);
  fill_solid(leds, NUM_LEDS, CHSV(hue, 255, brightness));
  FastLED.show();
}

void triggered() {
  int brightness = beatsin16(60, 150, 255);
  hue = beatsin16(80, 0, 100);
  fill_solid(leds, NUM_LEDS, CHSV(hue, 255, brightness));
  FastLED.show();
}

void loop() {
  int senseMotion = digitalRead(IR_Pin);
  ambient();
  if (senseMotion == LOW) {
    Serial.println("Start playing");
    playSdWav1.play("DRAGON17.WAV");
    delay(10); // wait for library to parse WAV info
    while(playSdWav1.isPlaying()) {
      triggered();
    }
  }
}
