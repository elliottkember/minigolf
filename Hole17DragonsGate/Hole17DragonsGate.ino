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
#define triggerPin 16

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
    pinMode(triggerPin, INPUT_PULLUP);

    delay(1000);
}
}

void loop() {

int wayfinderButton = digitalRead(buttonPin);
int senseMotion = digitalRead(triggerPin);
Serial.println(wayfinderButton); //for testing purposes
Serial.println(senseMotion); //for testing purposes

    if(wayfinderButton == LOW) {
          Serial.println("Start playing");
          playSdWav1.play("HOLE_17_WAYFINDER_DRAGON_S_GATE.WAV"); //change the sound file here for each hole.
          delay(10); // wait for library to parse WAV info
     }

     if(senseMotion == LOW) {
      Serial.println("Motion Detected");
      //still need to write the part of the sketch that flashes the eyes. Waiting on DA advice on the lights.
      playSdWav1.play("HOLE_17_BALL_TRIGGERED_DRAGON_S GATE.WAV");
      delay(10);
     }
}
