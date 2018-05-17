#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <FastLED.h>

#define COLOR_ORDER BGR  //if your colors look incorrect, change the color order here
#define NUM_LEDS_1    120  //change this number for the final LED count
#define NUM_LEDS_2    50

#define LEDdata 3
#define LEDclock 4

#define buttonPin 19

#define forwards 11
#define backwards 12 //assign relay INx pins to arduino pins

CRGB leds[NUM_LEDS_1];

void setup() {
  delay(3000); // sanity delay
  FastLED.addLeds<SK9822, LEDdata, LEDclock, COLOR_ORDER, DATA_RATE_MHZ(1)>(leds, NUM_LEDS_1);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 3000);
  FastLED.setBrightness(255);
  fill_solid(leds, NUM_LEDS_1, CRGB(255,147,41)); //fill with warm white
  FastLED.show();

  Serial.begin(9600);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(forwards, OUTPUT);//set relay as an output
  pinMode(backwards, OUTPUT);//set relay as an output

  //this section should rock the house to each extent, then
  digitalWrite(forwards, LOW);
  digitalWrite(backwards, HIGH);//moves the house down to limit
  delay(4500);
  digitalWrite(forwards, HIGH);
  digitalWrite(backwards, LOW);//moves the house up to limit
  delay(4500);
  digitalWrite(forwards, LOW);
  digitalWrite(backwards, HIGH);//moves the house down to center
  delay(2000);
  digitalWrite(forwards,HIGH);
  digitalWrite(backwards,HIGH); //stop moving the house
  delay(1000);
}


// Flicker code
unsigned long flickerEnd = millis();
bool flickerOn = true;
void flicker() {
  if (millis() > flickerEnd) {
    flickerOn = !flickerOn;
    flickerEnd = millis() + random(20, 1000);
  }
  fill_solid(leds, NUM_LEDS_1, flickerOn ? CRGB(255,147,41) : CRGB::Black);
  FastLED.show();
}

void resetFlicker() {
  fill_solid(leds, NUM_LEDS_1, CRGB(255,147,41));
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
unsigned long timeThisStepStarted = millis();

void loop() {
  int wayfinderButton = digitalRead(buttonPin);

  if(wayfinderButton == HIGH && step == 0) {
    delay(7000); //delay to match shaking with the wayfinder audio
    step = 1;
    timeThisStepStarted = millis();
  }

  // If we're moving
  if (step > 0) {
    int timeToSpendInThisStep = times[step];
    int timeSpentInThisStep = millis() - timeThisStepStarted;

    flicker();

    switch (step) {
      case 1:
        // Activate the relay one direction, they must be different to move the motor
        digitalWrite(forwards, LOW);
        digitalWrite(backwards, HIGH);
        //Serial.println("down");
        break;
      case 2:
        // Deactivate both relays to brake the motor
        digitalWrite(forwards, HIGH);
        digitalWrite(backwards, HIGH);
        //Serial.println("stop");
        break;
      case 3:
        // Activate the relay the other direction, they must be different to move the motor
        digitalWrite(forwards, HIGH);
        digitalWrite(backwards, LOW);
        //Serial.println("up");
        break;
      case 4:
        // Deactivate both relays to brake the motor
        digitalWrite(forwards, HIGH);
        digitalWrite(backwards, HIGH);
        //Serial.println("stop");
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
          numberOfRepetitions = 0;
          resetFlicker();
          //digitalWrite(forwards, HIGH);
          //digitalWrite(backwards, LOW);
          //delay(2000);
          //digitalWrite(forwards, HIGH);
          //digitalWrite(backwards, HIGH);
        }

        else {
          // Do it again!
          step = 1;
        }
      }
    }
  } else {

  }
}
