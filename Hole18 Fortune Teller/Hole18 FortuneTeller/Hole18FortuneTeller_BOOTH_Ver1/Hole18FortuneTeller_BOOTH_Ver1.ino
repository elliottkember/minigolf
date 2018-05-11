//#include <Audio.h>
//#include <Wire.h>
//#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <FastLED.h>

//commenting out all audio stuff for the BOOTH sketch
//AudioPlaySdWav           playSdWav1;
//AudioOutputI2S           i2s1;
//AudioConnection          patchCord1(playSdWav1, 0, i2s1, 0);
//AudioConnection          patchCord2(playSdWav1, 1, i2s1, 1);
//AudioControlSGTL5000     sgtl5000_1;


//Here is where you define which actions go with which pins.
//#define SDCARD_CS_PIN    BUILTIN_SDCARD
//#define SDCARD_MOSI_PIN  11
//#define SDCARD_SCK_PIN 13

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
//#define buttonPin 9 //This was used when we had one teensy. This sketch is now for the Fortune Booth teensy which will not interact with the wayfinder.

CRGB leds[NUM_LEDS];

void setup() {
    //delay(3000); // sanity delay
    FastLED.addLeds<APA102, LEDdata, LEDclock, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.setTemperature(TEMPERATURE_1);
    //fill_solid(leds, NUM_LEDS, CRGB(150,120,120));
    FastLED.show();
    
    Serial.begin(9600);
    //AudioMemory(8);
    //sgtl5000_1.enable();
    //sgtl5000_1.volume(0.25);
    //SPI.setMOSI(SDCARD_MOSI_PIN);
    //SPI.setSCK(SDCARD_SCK_PIN);
    //if (!(SD.begin(SDCARD_CS_PIN))) {
    //while (1) {
    //  Serial.println("Unable to access the SD card");
    //  delay(500);
    //}
      
    
    pinMode(IR_PIN, INPUT_PULLUP);
    pinMode(specialFortune, OUTPUT);
    pinMode(kioskLight, OUTPUT);
    //pinMode(buttonPin, INPUT_PULLUP);

    delay(1000);
//}
}

void loop() {
  
//  *******************
//  *****MAIN CODE*****
//  *******************
int sense_motion = digitalRead(IR_PIN);
digitalWrite(specialFortune, HIGH);
digitalWrite(kioskLight, HIGH);
Serial.println(sense_motion);
//int buttonPress = digitalRead(buttonPin);

Serial.println(sense_motion);
    //if(buttonPress == LOW) {
      //Serial.println("Start Wayfinder Script");
      //playSdWav1.play("HOLE_18_WAYFINDER_FORTUNE_TELLER.WAV");
      //delay(10);
    //}
    if(sense_motion == LOW) {
          Serial.println("Motion Sensed");
          //playSdWav1.play("HOLE_18_BALL_TRIGGERED_FORTUNE_TELLER.WAV");
          //delay(10); // wait for library to parse WAV info
          
          digitalWrite(specialFortune, LOW);
          delay(10);
          digitalWrite(specialFortune, HIGH); //these 3 lines give the special fortune trigger

          fill_rainbow(leds, NUM_LEDS, 0, 7);
          FastLED.show();
          delay(22000); //this should be the duration of the message
          FastLED.setTemperature(TEMPERATURE_1);
          //fill_solid(leds, NUM_LEDS, CRGB(150,120,120));
          FastLED.show();
          
          digitalWrite(kioskLight, LOW);
          delay(3000);
          digitalWrite(kioskLight, HIGH);
          delay(10);
       }
}


