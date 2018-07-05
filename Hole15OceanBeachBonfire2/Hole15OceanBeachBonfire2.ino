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
#define NUM_LEDS          134  //change this number for the final LED count

#define LEDdata  3
#define LEDclock 4

CRGB leds[NUM_LEDS];

void setup() {
  delay(1000); // sanity delay

  FastLED.addLeds<SK9822, LEDdata, LEDclock, COLOR_ORDER, DATA_RATE_MHZ(1)>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 3000);
  FastLED.setBrightness(255);

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

void loop() {
  random16_add_entropy(random());

   if (playSdWav1.isPlaying() == false) {
     playSdWav1.play("SNAP15.WAV");
     delay(10); // wait for library to parse WAV info
   }

   EVERY_N_MILLISECONDS(10) {
    int numberOfRedSparkles = beatsin16(15, 2, 40) + beatsin16(10, 0, 10);
    for (int i = 0; i < numberOfRedSparkles; i++) {
      int pixel = random(NUM_LEDS);
      leds[pixel] = CHSV(0, 255, 255);
    }

    int numberOfOrangeSparkles = beatsin16(20, 0, 10);
    for (int i = 0; i < numberOfOrangeSparkles; i++) {
      int pixel = random(NUM_LEDS);
      leds[pixel] = CHSV(20, 255, 255);
    }

    int numberOfWhiteSparkles = beatsin16(15, 2, 10) + beatsin16(10, 0, 5);
    for (int i = 0; i < numberOfWhiteSparkles; i++) {
      int pixel = random(NUM_LEDS);
      leds[pixel] = CHSV(255, 255, 255);
    }
  }

  fadeToBlackBy(leds, NUM_LEDS, 20);

  FastLED.show();
  FastLED.delay(10);
}
