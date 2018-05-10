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

#define special_Fortune 11
#define hole_In_One 12
#define free_Game_Buzz 15
#define stop_Button_Pin 16
#define PIR_PIN 18

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
      
    //pinMode(special_Fortune, OUTPUT);
    //pinMode(hole_In_One, OUTPUT);
    pinMode(PIR_PIN, INPUT_PULLUP);

    delay(1000);
}
}

void loop() {

//Test play sound 
  //if (playSdWav1.isPlaying() == false) {
  //  Serial.println("Start playing");
  //  playSdWav1.play("001test.WAV");
  //  delay(10); // wait for library to parse WAV info
  //}
//  }
//    else {
//        delay(25);
//    }

    //Test Light
    
//    delay(10000);


//  *******************
//  *****MAIN CODE*****
//  *******************
int sense_motion = digitalRead(PIR_PIN);
Serial.println(sense_motion);

    if(sense_motion == LOW) {
          Serial.println("Start playing");
          playSdWav1.play("001test.WAV");
          delay(10); // wait for library to parse WAV info
       }
   //    boothLight();
   //   giveFortune();

    //delay(10);

    // Test motion sensing
//    if(sense_motion()) {
//        Serial.println("Motion!");
//	delay(1000);
//    }
//    else {
//    	Serial.println("No Motion...");
//    }
//    delay(10);

    // Test motion activated actuator triggering
//    if(sense_motion()) {
//        Serial.println("Motion");
//    	push(1, 1000);
//	delay(50);
//	pull(1, 1000);
//	delay(5000);
//    }
//    else {
//        Serial.println("No Motion");
//        delay(100);
//    }
}

//void boothLight() {
//  bool stop_Button = digitalRead(stop_Button_Pin);
//  while(stop_Button == LOW) {
//    digitalWrite(hole_In_One, HIGH);
//    delay(1000);
//    digitalWrite(hole_In_One, LOW);
//    delay(1000);
//  }
//  if(stop_Button == HIGH){
//    digitalWrite(hole_In_One, LOW);
//  }
//}

//void giveFortune() {
//    digitalWrite(special_Fortune, HIGH);
//    delay(10);
//    digitalWrite(special_Fortune, LOW);
//}

//bool sense_motion() {
//    Serial.println(digitalRead(PIR_PIN));
//    if (digitalRead(PIR_PIN) == LOW) {
//        Serial.println("motion");
//        return true;
//    }
//    Serial.println("NOPE.");
//    return false;
//}

