#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <FastLED.h>

AudioPlaySdWav           playSdWav1;
AudioOutputI2S           i2s1;
AudioConnection          patchCord1(playSdWav1, 0, i2s1, 0);
AudioConnection          patchCord2(playSdWav1, 1, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;

//Here is where you define which actions go with which pins.
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN 14

#define COLOR_ORDER BGR  //if your colors look incorrect, change the color order here
#define NUM_LEDS_1    120  //change this number for the final LED count
#define NUM_LEDS_2    50
#define BRIGHTNESS  180
#define FRAMES_PER_SECOND 20
#define TEMPERATURE_1 Tungsten100W //This is the basic temp without Hole in One

#define ONdata 3
#define ONclock 4
#define RainbowData 5
#define RainbowClock 6

#define specialFortune 11
#define holeInOne 12
#define free_Game_Buzz 15
#define stop_Button_Pin 16
#define IR_PIN 18
#define buttonPin 9

CRGB leds[NUM_LEDS_1];

void setup() {
  delay(3000); // sanity delay

  FastLED.addLeds<APA102, ONdata, ONclock, COLOR_ORDER>(leds, NUM_LEDS_1)
    .setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

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
  }

  pinMode(IR_PIN, INPUT_PULLUP);
  pinMode(specialFortune, OUTPUT);
  pinMode(holeInOne, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  delay(1000);
}

void loop() {
  int sense_motion = digitalRead(IR_PIN);
  int buttonPress = digitalRead(buttonPin);

  Serial.println(sense_motion);

  fill_rainbow(leds, NUM_LEDS_1)

  if(buttonPress == LOW) {
    Serial.println("Start Wayfinder Script");
    playSdWav1.play("HOLE_18_WAYFINDER_FORTUNE_TELLER.WAV");
    delay(10);
  }

  if(sense_motion == LOW) {
    Serial.println("Start playing");
    playSdWav1.play("HOLE_18_BALL_TRIGGERED_FORTUNE_TELLER.WAV");
    delay(10); // wait for library to parse WAV info

    digitalWrite(specialFortune, HIGH);
    delay(10);
    digitalWrite(specialFortune, LOW); //these 3 lines give the special fortune trigger

    for(int i = 0; i < 3; i++) {
      digitalWrite(holeInOne, HIGH);
      delay(500);
      digitalWrite(holeInOne, LOW);
      delay(500);
    } // this for loop buzzes the booth light 3 times
  }
}
