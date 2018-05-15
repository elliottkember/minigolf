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


//Here is where you define which actions go with which pins.
#define SDCARD_CS_PIN    BUILTIN_SDCARD

#define IR_Pin 19

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

    pinMode(IR_Pin, INPUT_PULLUP);

    delay(1000);
}

void loop() {

int sense_motion = digitalRead(IR_Pin);

    if(sense_motion == LOW) {
          Serial.println("Start playing");
          playSdWav1.play("DAZZLINGGOLD.WAV"); //this file is in the "Fixed Audio" folder
          delay(10);
    }
}
