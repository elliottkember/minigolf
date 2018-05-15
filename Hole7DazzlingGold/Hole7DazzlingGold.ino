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

#define buttonPin 18
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

    pinMode(buttonPin, INPUT_PULLUP);

    int wayfinderButton = digitalRead(buttonPin);
    int sense_motion = digitalRead(IR_Pin);

    delay(1000);
}

void loop() {

wayfinderButton = digitalRead(buttonPin);
sense_motion = digitalRead(IR_Pin);

    if(wayfinderButton == LOW) {
          Serial.println("Start playing");
          playSdWav1.play("HOLE07.WAV"); //change the sound file here for each hole.
          delay(10); // wait for library to parse WAV info
    }

    if(sense_motion == LOW) {
          Serial.println("Start playing");
          playSdWav1.play("DAZZLINGGOLD.WAV");
          delay(10);
    }
}


void loop() {

int wayfinderButton = digitalRead(buttonPin);
int sense_motion = digitalRead(triggerPin);
Serial.println(wayfinderButton); //for testing purposes
Serial.println(sense_motion); //for testing purposes

    if(wayfinderButton == LOW) {
          Serial.println("Start playing");
          playSdWav1.play("HOLE_07_WAYFINDER_DAZZLING_GOLD.WAV"); //change the sound file here for each hole.
          delay(10); // wait for library to parse WAV info
    }

    if(sense_motion == LOW) {
          Serial.println("Start playing");
          playSdWav1.play("HOLE_07_ BALL_TRIGGERED_DAZZLING_GOLD.WAV");
          delay(10);
    }
}
