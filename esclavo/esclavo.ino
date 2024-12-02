#include <Wire.h>

int green1 = 2; // Pines para los LEDs del semáforo 1
int yellow1 = 3;
int red1 = 4;

int green2 = 8; // Pines para los LEDs del semáforo 2
int yellow2 = 9;
int red2 = 10;

void setup() {
  Wire.begin(2);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);

  pinMode(green1, OUTPUT);
  pinMode(yellow1, OUTPUT);
  pinMode(red1, OUTPUT);

  pinMode(green2, OUTPUT);
  pinMode(yellow2, OUTPUT);
  pinMode(red2, OUTPUT);
 
}

void loop() {
  // El loop se mantiene vacío, la comunicación es a través de eventos
}

void receiveEvent(int bytes) {
  char comando = Wire.read(); // Lee el comando enviado por el maestro
  Serial.println(comando);
  switch (comando) {
    case '1': // Semáforo 1 en verde, Semáforo 2 en rojo
      setTrafficLight1(HIGH, LOW, LOW);
      setTrafficLight2(LOW, LOW, HIGH);
      break;

    case 'g': // Parpadeo verde en semáforo 1
      blinkLED(green1);
      break;

    case 'y': // Semáforo 1 en amarillo
      setTrafficLight1(LOW, HIGH, LOW);
      break;

    case 'r': // Semáforo 1 en rojo, Semáforo 2 en verde
      setTrafficLight1(LOW, LOW, HIGH);
      setTrafficLight2(HIGH, LOW, LOW);
      break;

    case 't':
      blinkLED(green2);
      break;
    case 'Y':
      //Semaforo 2 en amarillo
      setTrafficLight2(LOW, HIGH, LOW); 
      break;
    case 'u':
      //Sewaforo 2 en rojo 
      setTrafficLight2(LOW, LOW, HIGH); 
      break;
    case 'o': // Apagar todas las luces en semáforo 1 (para parpadeo)
      setTrafficLight1(LOW, LOW, LOW);
      break;
    case 'O': // Apagar todas las luces en semáforo 1 (para parpadeo)
      setTrafficLight2(LOW, LOW, LOW);
      break;
    case '|':
      setTrafficLight1(LOW, LOW, HIGH);
      setTrafficLight2(LOW, LOW, HIGH);
      break;
  }
}
void setTrafficLight1(int green, int yellow, int red) {
  digitalWrite(green1, green);
  digitalWrite(yellow1, yellow);
  digitalWrite(red1, red);
}


void setTrafficLight2(int green, int yellow, int red) {
  digitalWrite(green2, green);
  digitalWrite(yellow2, yellow);
  digitalWrite(red2, red);
}

void blinkLED(int ledPin) {
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin, LOW);
    delay(500); // On for 500ms
    digitalWrite(ledPin, HIGH);
    delay(500); // Off for 500ms
  }
}
// Función para parpadear la luz verde
void parpadearVerde(int greenPin) {
  for (int i = 0; i < 3; i++) {
    digitalWrite(greenPin, LOW);
    delay(500);                // Apagado 500ms
    digitalWrite(greenPin, HIGH);
    delay(500);                // Encendido 500ms
  }
}
