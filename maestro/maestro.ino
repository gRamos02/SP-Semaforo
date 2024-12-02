#include <Wire.h>

void setup() {
  Wire.begin();        // Connect to the I2C bus
  Serial.begin(9600);  // Initialize serial communication
  inicializar();
  delay(1000);
}

void loop() {
  //Control de semaforo 3 y 4

  controlTrafficLight4LEDs();
  encenderVerdeSemaforo1_RojoSemaforo2();
  parpadearVerdeSemaforo1();
  encenderAmarilloSemaforo1();
  encenderRojoSemaforo1_VerdeSemaforo2();

}

void encenderVerdeSemaforo1_RojoSemaforo2() {
  // Semáforo 1 en verde, 2 en rojo
  sendMsg(2, '1');
  Serial.println("Semáforo 1: Verde, Semáforo 2: Rojo");
  delay(5000);  // Wait for 5 seconds
}

void parpadearVerdeSemaforo1() {
  for (int i = 0; i < 3; i++) {  // Blink 3 times
    Wire.beginTransmission(2);
    Wire.write('g');  // Turn on green
    Wire.endTransmission();
    delay(500);

    Wire.beginTransmission(2);
    Wire.write('o');  // Turn off green
    Wire.endTransmission();
    delay(500);
  }
}

void parpadearVerdeSemaforo2() {
  for (int i = 0; i < 3; i++) {  // Blink 3 times
    Wire.beginTransmission(2);
    Wire.write('t');  // Turn on green
    Wire.endTransmission();
    delay(500);

    Wire.beginTransmission(2);
    Wire.write('O');  // Turn off green
    Wire.endTransmission();
    delay(500);
  }
}

void encenderAmarilloSemaforo1() {
  Wire.beginTransmission(2);
  Wire.write('y');  // Semáforo 1 en amarillo
  Wire.endTransmission();

  Serial.println("Semáforo 1: Amarillo");
  delay(2000);
}

void encenderRojoSemaforo1_VerdeSemaforo2() {
  Wire.beginTransmission(2);
  Wire.write('r');  // Semáforo 1 en rojo, Semáforo 2 en verde
  Wire.endTransmission();

  Serial.println("Semáforo 1: Rojo, Semáforo 2: Verde");
  delay(5000);  // Wait for 5 seconds


  parpadearVerdeSemaforo2();

  //Semaforo 2 amarillo
  sendMsg(2, 'Y');
  delay(2000);

  sendMsg(2, 'u');
}

void controlTrafficLight4LEDs() {
  // Left turn blue LED
  sendMsg(3, 'A');
  delay(5000);

  sendParpadeo(3, 'B', 'b');

  //Prender el verde en semaforo 3 y 4
  // Yellow LED
  sendMsg(3, 'C');
  delay(5000);


  //Parpadear VERDE EN 3 Y 4
  sendParpadeo(3, 'C', 'c');

  //Prender amarillo en 3 y 4
  sendMsg(3, 'D');
  delay(2000);

  //Apagar amarillo, prender rojo en 3 y 4
  sendMsg(3,'R');

}

void inicializar(){
  sendMsg(2, '|');
  sendMsg(3, '|');
}


void sendParpadeo(int slave, char msgA, char msgB){
  for (int i = 0; i < 3; i++) {  // Blink 3 times
    Wire.beginTransmission(slave);
    Wire.write(msgA);  // Turn on green
    Wire.endTransmission();
    delay(500);

    Wire.beginTransmission(3);
    Wire.write(msgB);  // Turn off green
    Wire.endTransmission();
    delay(500);
  }
}


void sendMsg(int slave, char msg){
  Wire.beginTransmission(slave);
  Wire.write(msg);  // Red LED
  Wire.endTransmission();
}