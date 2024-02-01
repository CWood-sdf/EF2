
#include "yeet.h"
#include "Arduino.h"
#include <Servo.h>
#include "pitches.h"

int melody[] = {
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_C5, NOTE_B4, NOTE_B4, NOTE_D4,
  NOTE_E4, NOTE_F4, NOTE_D5, NOTE_B4, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_F4, 
  NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_A4, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_E5, 
  NOTE_D5, NOTE_G4, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_C5, REST, NOTE_C5, REST, NOTE_C5, NOTE_E5, 
  NOTE_C5, NOTE_D5, REST, NOTE_D5, NOTE_D5, NOTE_D5, REST, NOTE_D5, NOTE_F5, NOTE_D5, NOTE_E5, REST, NOTE_E5, 
  NOTE_E5, NOTE_E5, REST, NOTE_E5, NOTE_G5, NOTE_E5, NOTE_F5, REST, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_G4, 
  NOTE_B4, NOTE_C5, NOTE_C5, REST
};

int durations[] = {
  8, 8, 4, 4, 4, 8, 8, 4, 4, 4, 8, 8, 4, 4, 4, 8, 8, 4, 4, 4, 8, 8, 4, 8, 8, 4, 8, 8, 4, 
  8, 8, 4, 8, 8, 4, 4, 4, 4, 2, 4, 4, 4, 8, 8, 4, 4, 4, 8, 8, 2, 4, 8, 8, 4, 4, 4, 8, 8, 
  2, 4, 8, 8, 4, 4, 4, 8, 8, 4, 8, 8, 2, 2, 2, 4, 4
};

#define BUZZER_PIN 8
// void setup() {
  // iterate over the notes of the melody:
  // for (int thisNote = 0; thisNote < 44; thisNote++) {
  //
  //   // to calculate the note duration, take one second 
  //   // divided by the note type.
  //   //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
  //   int noteDuration = 1000/noteDurations[thisNote];
  //   tone(8, melody[thisNote],noteDuration);
  //
  //   // to distinguish the notes, set a minimum time between them.
  //   // the note's duration + 30% seems to work well:
  //   int pauseBetweenNotes = noteDuration * 1.30;
  //   delay(pauseBetweenNotes);
  //    while(pauseBetweenNotes != 0){
  //      pauseBetweenNotes--;
  //      analogWrite(9,pauseBetweenNotes);// LED is on PIN 9 to GND
  //    }
  //   // stop the tone playing:
  //   noTone(8);
  // }

// }
const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 11;
const int ledPin = 7;
Servo servo;
void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
    pinMode(ledPin, OUTPUT);
	Serial.begin(9600);
    servo.attach(servoPin);
}
int i = 0;
int direction = 1;
double speed = 1;
int musicI = 0;
int neededPause = 0;
int currentPause = 0;
int ledActive = 0;
void loop() {
    // do {
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // echoPin duration can be converted to distance
    float duration = pulseIn(echoPin, HIGH);  
    // Distance in cm
    float distance = (duration * 0.0343) / 2;  
    if (distance > 30) {
        digitalWrite(ledPin, LOW);
        delay(50);
        return;
    }
    // } while (distance < 10);

// int size = sizeof(durations) / sizeof(int);

  // for (int note = 0; note < size; note++) {
    //to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    if (currentPause >= neededPause){
        currentPause = 0;
        ledActive = 100;
        digitalWrite(ledPin, HIGH);
        int duration = 1000 / durations[musicI];
        noTone(BUZZER_PIN);
        delay(1);
        tone(BUZZER_PIN, melody[musicI], duration);

        //to distinguish the notes, set a minimum time between them.
        //the note's duration + 30% seems to work well:
        int pauseBetweenNotes = duration * 1.30;

        //stop the tone playing:
        musicI++;
        musicI %= sizeof(durations) / sizeof(int);
        neededPause = pauseBetweenNotes;
        // delay(pauseBetweenNotes);
    }
    if (ledActive < 0){
        ledActive = 0;
        digitalWrite(ledPin, LOW);
    }
    // if (currentPause + 20 >= neededPause){
    // }

    servo.write(i);
 //    delay(50);
	// // Set the pin to low, then high to trigger a reading 
 // //    delay(100);

 // //
    // Serial.print(distance);
    // Serial.println(" cm");
 // //    doYeet();
	//
 //    // analogWrite(0, i);
 //    //
 //    // // servo.write(0);
    int inc = direction * 3;
    i += inc;
    if(i > 90) {
        direction = -1;
    } else if(i < 0) {
        direction = 1;
    }
    delay(10);
    ledActive-=10;
    currentPause += 10;
 //    // Serial.println(i);
 //    // tone(8, 440 * 4);
 //    // delay(100);
}

