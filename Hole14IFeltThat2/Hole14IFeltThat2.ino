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
  FastLED.setTemperature(TEMPERATURE_1);
  FastLED.show();

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
  }

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(forwards, OUTPUT);//set relay as an output
  pinMode(backwards, OUTPUT);//set relay as an output
  // int t = 0;
  //more pinMode here

  delay(1000);
}


// Flicker code
uint16_t flickerEnd = millis();
bool flickerOn = true;
void flicker() {
  if (millis() > flickerEnd) {
    flickerOn = !flickerOn;
    flickerEnd = millis() + random(50, 1000);
  }
  fill_solid(leds, NUM_LEDS_1, flickerOn ? CRGB::White : CRGB::Black);
}

void resetFlicker() {
  fill_solid(leds, NUM_LEDS_1, CRGB::White);
}

// Movement code
// 0 = stopped, 1 = forward, 2 = brake forward, 3 = backward, 4 = brake backward
int step = 0;
// The number of milliseconds in each step
// Note: 0 = stopped (we never use this)
int times[5] = {0, 2000, 200, 2000, 200};
// We're rotating through the steps 3 times
int maxRepetitions = 3;
int numberOfRepetitions = 0;
// By tracking the milliseconds since this step started, we can move on once it gets past the times[i]
uint16_t timeThisStepStarted = millis();

void loop() {
  int wayfinderButton = digitalRead(buttonPin);
  Serial.println(wayfinderButton);

  if(wayfinderButton == LOW && step == 0) {
    Serial.println("Start playing");
    playSdWav1.play("HOLE_14_WAYFINDER_EARTHQUAKE.WAV"); //change the sound file here for each hole.
    delay(10); // wait for library to parse WAV info
    step = 1;
    timeThisStepStarted = millis();
  }

  // If we're moving
  if (step > 0) {
    int timeToSpendInThisStep = times[step];
    int timeSpentInThisStep = millis() - timeThisStepStarted;

    // TODO: Write the flicker code for the LEDs.
    // Probably use random() and fadeToBlackBy()
    flicker();

    switch (step) {
      case 1:
        // Activate the relay one direction, they must be different to move the motor
        digitalWrite(forwards, LOW);
        digitalWrite(backwards, HIGH);
        Serial.println("down");
        break;
      case 2:
        // Deactivate both relays to brake the motor
        digitalWrite(forwards, HIGH);
        digitalWrite(backwards, HIGH);
        Serial.println("stop");
        break;
      case 3:
        // Activate the relay the other direction, they must be different to move the motor
        digitalWrite(forwards, HIGH);
        digitalWrite(backwards, LOW);
        Serial.println("up");
        break;
      case 4:
        // Deactivate both relays to brake the motor
        digitalWrite(forwards, HIGH);
        digitalWrite(backwards, HIGH);
        Serial.println("stop");
        break;
    }

    // We've been in this step long enough. Onward!
    if (timeSpentInThisStep > timeToSpendInThisStep) {
      // Next step
      step++;
      // Restart the timer
      timeThisStepStarted = millis();

      if (step == 5) {
        numberOfRepetitions++;
        if (numberOfRepetitions > maxRepetitions) {
          // Stop!
          step = 0;
        } else {
          // Do it again!
          step = 1;
        }
      }
    }
  } else {
    resetFlicker();
  }
}
