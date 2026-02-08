#include <Servo.h>

Servo servo1;   // D3 wala (har 5 sec)
Servo servo2;   // D6 wala (same jaise pehle)

unsigned long lastMove1 = 0;
unsigned long lastMove2 = 0;

void setup() {
  servo1.attach(3);   // Servo 1 → D3
  servo2.attach(6);   // Servo 2 → D6 (same as before)

  servo1.write(0);
  servo2.write(0);
}

void loop() {

  // ------------ Servo 1 (D3) → har 5 second move karega ------------
  if (millis() - lastMove1 >= 5000) {
    servo1.write(90);
    delay(1000);
    servo1.write(0);
    lastMove1 = millis();
  }

  // ------------ Servo 2 (D6) → har 3 second move karega ------------
  if (millis() - lastMove2 >= 3000) {
    servo2.write(90);
    delay(1000);
    servo2.write(0);
    lastMove2 = millis();
  }
}

