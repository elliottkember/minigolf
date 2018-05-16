#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <FastLED.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=105,182
AudioOutputAnalogStereo  dacs1;          //xy=321,188
AudioConnection          patchCord1(playSdWav1, 0, dacs1, 0);
AudioConnection          patchCord2(playSdWav1, 1, dacs1, 1);
// GUItool: end automatically generated code

#define SDCARD_CS_PIN     BUILTIN_SDCARD
#define COLOR_ORDER       BGR  //if your colors look incorrect, change the color order here
#define NUM_LEDS          300  //change this number for the final LED count
#define BRIGHTNESS        180
#define FRAMES_PER_SECOND 20

#define LEDdata  3
#define LEDclock 4


CRGB leds[NUM_LEDS];

void setup() {
    //delay(3000); // sanity delay
    FastLED.addLeds<SK9822, LEDdata, LEDclock, COLOR_ORDER, DATA_RATE_MHZ(1)>(leds, NUM_LEDS);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 3000);
    FastLED.setBrightness(255);

    Serial.begin(9600);
    AudioMemory(20);
    if (!(SD.begin(SDCARD_CS_PIN))) {
      // stop here, but print a message repetitively
      while (1) {
        Serial.println("Unable to access the SD card");
        delay(500);
      }
    }
    delay(1000);

}

//  *******************
//  *****MAIN CODE*****
//  *******************
void loop() {
   random16_add_entropy(random());

  if (playSdWav1.isPlaying() == false) {
    playSdWav1.play("SNAP15.WAV");
    delay(1000); // wait for library to parse WAV info
  }
     Fire2012();
     FastLED.show();
     FastLED.delay(44);
  }


  // Fire2012 by Mark Kriegsman, July 2012
  // as part of "Five Elements" shown here: http://youtu.be/knWiGsmgycY
  ////
  // This basic one-dimensional 'fire' simulation works roughly as follows:
  // There's a underlying array of 'heat' cells, that model the temperature
  // at each point along the line.  Every cycle through the simulation,
  // four steps are performed:
  //  1) All cells cool down a little bit, losing heat to the air
  //  2) The heat from each cell drifts 'up' and diffuses a little
  //  3) Sometimes randomly new 'sparks' of heat are added at the bottom
  //  4) The heat from each cell is rendered as a color into the leds array
  //     The heat-to-color mapping uses a black-body radiation approximation.
  //
  // Temperature is in arbitrary units from 0 (cold black) to 255 (white hot).
  //
  // This simulation scales it self a bit depending on NUM_LEDS; it should look
  // "OK" on anywhere from 20 to 100 LEDs without too much tweaking.
  //
  // I recommend running this simulation at anywhere from 30-100 frames per second,
  // meaning an interframe delay of about 10-35 milliseconds.
  //
  // Looks best on a high-density LED setup (60+ pixels/meter).
  //
  //
  // There are two main parameters you can play with to control the look and
  // feel of your fire: COOLING (used in step 1 above), and SPARKING (used
  // in step 3 above).
  //
  // COOLING: How much does the air cool as it rises?
  // Less cooling = taller flames.  More cooling = shorter flames.
  // Default 50, suggested range 20-100
  #define COOLING  55

  // SPARKING: What chance (out of 255) is there that a new spark will be lit?
  // Higher chance = more roaring fire.  Lower chance = more flickery fire.
  // Default 120, suggested range 50-200.
  #define SPARKING 120

  #define BRIGHTNESS  200
  #define FRAMES_PER_SECOND 60

  bool gReverseDirection = false;

  void Fire2012() {
  // Array of temperature readings at each simulation cell
    static byte heat[NUM_LEDS];

    // Step 1.  Cool down every cell a little
    for (int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }

    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for (int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }

    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if (random8() < SPARKING) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for (int j = 0; j < NUM_LEDS; j++) {
      CRGB color = HeatColor(heat[j]);
      int pixelnumber;
      if (gReverseDirection ) {
        pixelnumber = (NUM_LEDS-1) - j;
      } else {
        pixelnumber = j;
      }
      leds[pixelnumber] = color;
    }
  }
