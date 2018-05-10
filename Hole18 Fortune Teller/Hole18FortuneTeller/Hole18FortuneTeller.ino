//Here is where you define which actions go with which pins.
#define special_Fortune 12
#define hole_In_One 13
#define stop_Button_Pin 14
#define PIR_PIN 18

void setup() {
    Serial.begin(115200);
    Serial1.begin(9600);
    
    pinMode(special_Fortune, OUTPUT);
    pinMode(hole_In_One, OUTPUT);
    pinMode(PIR_PIN, INPUT_PULLUP);

    delay(5000);
}

void loop() {

    // Test play sound 
//    if(sense_motion()) {
//        play_sound();
//        delay(10000);
//    }
//    else {
//        delay(25);
//    }

    //Test Light
    
//    play_sound();
//    delay(10000);


//  *******************
//  *****MAIN CODE*****
//  *******************

    if(sense_motion()) { //sense_motion is a programmed command defined at the bottom of the code.
        boothLight();
        giveFortune();
    }

    delay(10);

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

void boothLight() {
  bool stop_Button = digitalRead(stop_Button_Pin)
  while(stop_Button == LOW) {
    digitalWrite(hole_In_One, HIGH);
    delay(1000);
    digitalWrite(hole_In_One, LOW);
    delay(1000);
  }
  if(stop_Button == HIGH){
    digitalWrite(hole_In_One, LOW);
  }
}

void giveFortune() {
    digitalWrite(special_Fortune, HIGH);
    delay(10);
    digitalWrite(special_Fortune, LOW);
}

bool sense_motion() {
    Serial.println(digitalRead(PIR_PIN));
    if (digitalRead(PIR_PIN) == HIGH) {
        Serial.println("motion");
        return true;
    }
    Serial.println(".");
    return false;
}

void play_sound() {
    Serial1.write((byte)0x7e);
    Serial1.write((byte)0xff);
    Serial1.write((byte)0x06);
    Serial1.write((byte)0x22);
    Serial1.write((byte)0x00);
    Serial1.write((byte)0x0f);
    Serial1.write((byte)0x01);
    Serial1.write((byte)0xef);
}

