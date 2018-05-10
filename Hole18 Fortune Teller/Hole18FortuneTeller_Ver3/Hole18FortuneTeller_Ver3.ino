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

#define specialFortune 11
#define holeInOne 12
#define free_Game_Buzz 15
#define stop_Button_Pin 16
#define IR_PIN 18

void setup() {
    Serial.begin(9600);
    AudioMemory(8);
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.25);
    SPI.setMOSI(SDCARD_MOSI_PIN);
    SPI.setSCK(SDCARD_SCK_PIN);
    if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
      
    
    pinMode(IR_PIN, INPUT_PULLUP);
    pinMode(specialFortune, OUTPUT);
    pinMode(holeInOne, OUTPUT);

    delay(1000);
}
}

void loop() {
  
//  *******************
//  *****MAIN CODE*****
//  *******************
int sense_motion = digitalRead(IR_PIN);
Serial.println(sense_motion);

    if(sense_motion == LOW) {
          Serial.println("Start playing");
          playSdWav1.play("001test.WAV");
          delay(10); // wait for library to parse WAV info

          digitalWrite(specialFortune, HIGH);
          delay(10);
          digitalWrite(specialFortune, LOW); //these 3 lines give the special fortune trigger
          
          for(int i = 0; i < 3; i++) {
            digitalWrite(holeInOne, HIGH);
            delay(500);
            digitalWrite(holeInOne, LOW);
            delay(500);
          } //this for loop buzzes the booth light 3 times
       }
}


