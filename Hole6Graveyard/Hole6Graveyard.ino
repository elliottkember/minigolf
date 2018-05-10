#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>

AudioPlaySdWav           playSdWav1;
AudioOutputI2S           i2s1;
AudioConnection          patchCord1(playSdWav1, 0, i2s1, 0);
AudioConnection          patchCord2(playSdWav1, 1, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;


//Here is where you define which actions go with which pins.
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN 14

#define buttonPin 18

void setup() {
    Serial.begin(9600);
    AudioMemory(8);
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.75);
    SPI.setMOSI(SDCARD_MOSI_PIN);
    SPI.setSCK(SDCARD_SCK_PIN);
    if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
      
    pinMode(buttonPin, INPUT_PULLUP);

    delay(1000);
}
}

void loop() {

int wayfinderButton = digitalRead(buttonPin);
Serial.println(wayfinderButton);

    if(wayfinderButton == LOW) {
          Serial.println("Start playing");
          playSdWav1.play(HOLE_06_WAYFINDER_GRAVEYARD.WAV"); //change the sound file here for each hole.
          delay(10); // wait for library to parse WAV info
       }
}
