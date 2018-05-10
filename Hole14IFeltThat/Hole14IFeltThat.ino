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
#define TEMPERATURE_1 Tungsten100W //maybe try AntiqueWhite too

#define ONdata 3
#define ONclock 4
#define FlickerData 5
#define FlickerClock 6
#define Fortune 17

#define buttonPin 18

const int forwards = 8;
const int backwards = 9; //assign relay INx pins to arduino pins

CRGB leds[NUM_LEDS_1];

void setup() {
    delay(3000); // sanity delay
    FastLED.addLeds<APA102, ONdata, ONclock, COLOR_ORDER>(leds, NUM_LEDS_1).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(BRIGHTNESS);
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
    pinMode(forwards, OUTPUT);//set relay as an output
    pinMode(backwards, OUTPUT);//set relay as an output
    int t = 0;
    //more pinMode here
    FastLED.setTemperature(TEMPERATURE_1);
    FastLED.show();

    delay(1000);
}
}

void loop() {

int wayfinderButton = digitalRead(buttonPin);
int t = 3;
Serial.println(wayfinderButton);

    if(wayfinderButton == LOW) {
          Serial.println("Start playing");
          playSdWav1.play("HOLE_14_WAYFINDER_EARTHQUAKE.WAV"); //change the sound file here for each hole.
          delay(10); // wait for library to parse WAV info
          t = 0;
    }

          while(t < 3) {
                digitalWrite(forwards, LOW);
                digitalWrite(backwards, HIGH);//Activate the relay one direction, they must be different to move the motor
                Serial.println("down");
                delay(3250); // move 4 seconds

                digitalWrite(forwards, HIGH);
                digitalWrite(backwards, HIGH);//Deactivate both relays to brake the motor
                Serial.println("stop");
                delay(250);// wait 2 seconds

                digitalWrite(forwards, HIGH);
                digitalWrite(backwards, LOW);//Activate the relay the other direction, they must be different to move the motor
                Serial.println("up");
                delay(3750);// move 4 seconds

                digitalWrite(forwards, HIGH);
                digitalWrite(backwards, HIGH);//Deactivate both relays to brake the motor
                Serial.println("stop");
                delay(250);// wait 2 seconds
                ++t;
          }
}
