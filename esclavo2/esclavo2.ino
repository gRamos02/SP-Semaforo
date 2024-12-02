#include <Wire.h>

// Traffic Light 1 (first set of 4 LEDs)
int straightGreen1 = 2; // Pin for straight green LED
int leftBlue1 = 3;      // Pin for left blue LED
int yellow1 = 4;        // Pin for yellow LED
int red1 = 5;           // Pin for red LED

// Traffic Light 2 (second set of 4 LEDs)
int straightGreen2 = 8; // Pin for straight green LED
int leftBlue2 = 9;      // Pin for left blue LED
int yellow2 = 10;        // Pin for yellow LED
int red2 = 11;           // Pin for red LED

void setup() {
  Wire.begin(3); // Set this Arduino as slave #3
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);

  pinMode(straightGreen1, OUTPUT);
  pinMode(leftBlue1, OUTPUT);
  pinMode(yellow1, OUTPUT);
  pinMode(red1, OUTPUT);

  pinMode(straightGreen2, OUTPUT);
  pinMode(leftBlue2, OUTPUT);
  pinMode(yellow2, OUTPUT);
  pinMode(red2, OUTPUT);
}

void loop() {
  // The loop is empty; communication is handled through events
}

void receiveEvent(int bytes) {
  char command = Wire.read(); // Read the command sent by the master

  switch (command) {
    // Traffic Light 1 Commands
    case 'A': // Left turn (blue LED) for Traffic Light 1
      setTrafficLight1(LOW, HIGH, LOW, LOW);
      setTrafficLight2(LOW, HIGH, LOW, LOW);
      break;

    case 'B': // Blink left turn (blue LED) for Traffic Light 1
      setTrafficLight1(LOW, HIGH, LOW, LOW);
      setTrafficLight2(LOW, HIGH, LOW, LOW);
      break;
    case 'b': // Blink left turn (blue LED) for Traffic Light 1
      setTrafficLight1(LOW, LOW, LOW, LOW);
      setTrafficLight2(LOW, LOW, LOW, LOW);
      break;

    case 'C': // VERDE en ambos
      setTrafficLight1(HIGH, LOW, LOW, LOW);
      setTrafficLight2(HIGH, LOW, LOW, LOW);
      break;

    case 'c': // VERDE en ambos
      setTrafficLight1(LOW, LOW, LOW, LOW);
      setTrafficLight2(LOW, LOW, LOW, LOW);
      break;

    case 'D': // Amarillo en ambos
      setTrafficLight1(LOW, LOW, HIGH, LOW);
      setTrafficLight2(LOW, LOW, HIGH, LOW);
      break;

    // Traffic Light 2 Commands
    case 'R': // Straight green light for Traffic Light 2
      setTrafficLight1(LOW, LOW, LOW, HIGH);
      setTrafficLight2(LOW, LOW, LOW, HIGH);
      break;

    case 'F': // Blink straight green light for Traffic Light 2
      blinkLED(straightGreen2);
      break;

    case 'G': // Yellow light for Traffic Light 2
      setTrafficLight2(LOW, LOW, HIGH, LOW);
      break;

    case 'H': // Red light for Traffic Light 2
      setTrafficLight2(LOW, LOW, LOW, HIGH);
      break;

    case 'O':
      setTrafficLight1(LOW, LOW, LOW, LOW);
      setTrafficLight2(LOW, LOW, LOW, LOW);
      break;
    case '|':
      digitalWrite(straightGreen1, LOW);
      digitalWrite(yellow1, LOW);
      digitalWrite(leftBlue1, LOW);
      digitalWrite(straightGreen2, LOW);
      digitalWrite(yellow2, LOW);
      digitalWrite(leftBlue2, LOW);

      digitalWrite(red1, HIGH);
      digitalWrite(red2, HIGH);
      break;
  }
}

// Function to set the state of Traffic Light 1
void setTrafficLight1(int green, int blue, int yellow, int red) {
  digitalWrite(straightGreen1, green);
  digitalWrite(leftBlue1, blue);
  digitalWrite(yellow1, yellow);
  digitalWrite(red1, red);
}

// Function to set the state of Traffic Light 2
void setTrafficLight2(int green, int blue, int yellow, int red) {
  digitalWrite(straightGreen2, green);
  digitalWrite(leftBlue2, blue);
  digitalWrite(yellow2, yellow);
  digitalWrite(red2, red);
}

// Function to blink the specified LED
void blinkLED(int ledPin) {
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin, LOW);
    delay(500); // On for 500ms
    digitalWrite(ledPin, HIGH);
    delay(500); // Off for 500ms
  }
}

void blinkBlueLeds(){
  for (int i = 0; i < 3; i++) {
    digitalWrite(leftBlue1, LOW);
    digitalWrite(leftBlue2, LOW);
    delay(500); // On for 500ms
    digitalWrite(leftBlue1, HIGH);
    digitalWrite(leftBlue2, HIGH);
    delay(500); // Off for 500ms
  }
}