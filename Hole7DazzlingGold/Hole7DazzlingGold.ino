#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=105,182
AudioOutputAnalogStereo  dacs1;          //xy=321,188
AudioConnection          patchCord1(playSdWav1, 0, dacs1, 0);
AudioConnection          patchCord2(playSdWav1, 1, dacs1, 1);
// GUItool: end automatically generated code

#define SDCARD_CS_PIN    BUILTIN_SDCARD

#define buttonPin 18

void setup() {
    Serial.begin(9600);
    AudioMemory(20);
    if (!(SD.begin(SDCARD_CS_PIN))) {
      // stop here, but print a message repetitively
      while (1) {
        Serial.println("Unable to access the SD card");
        delay(500);
      }
    }

    pinMode(buttonPin, INPUT_PULLUP); //Teensy pin for the Wayfinder Button

    delay(1000);
}

void loop() {

int wayfinderButton = digitalRead(buttonPin); //read the Wayfinder button.

    if(wayfinderButton == LOW) {
          playSdWav1.play("HOLE07.WAV"); //change the sound file here for each hole.
          delay(10); // wait for library to parse WAV info
    }
    
}
