#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11);   // RX, TX (HC-05)

// Pin setup
#define trigPin 7
#define echoPin 6
#define pumpPin 8
#define buzzerPin 9
#define soilPin A1

long duration;
int distance;

void setup() {
  Serial.begin(9600);
  BT.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pumpPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(pumpPin, LOW);
  digitalWrite(buzzerPin, LOW);
}

void loop() {

  // ---------- ULTRASONIC SENSOR ----------
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  // ---------- BUZZER IF OBJECT DETECTED ----------
  if (distance > 0 && distance < 15) {   // 15 cm ke andar koi bhi saman aaye
    digitalWrite(buzzerPin, HIGH);
  }
  else {
    digitalWrite(buzzerPin, LOW);
  }

  // ---------- SOIL MOISTURE ----------
  int soil = analogRead(soilPin);
  Serial.print("Soil: ");
  Serial.println(soil);

  // Dry soil → pump ON
  if (soil > 600) {         
    digitalWrite(pumpPin, HIGH);
  }
  else {
    digitalWrite(pumpPin, LOW);
  }

  // ---------- BLUETOOTH COMMANDS ----------
  if (BT.available()) {
    char cmd = BT.read();

    if (cmd == 'P') {        // Pump OFF
      digitalWrite(pumpPin, LOW);
    }

    if (cmd == 'B') {        // Buzzer ON
      digitalWrite(buzzerPin, HIGH);
    }

    if (cmd == 'b') {        // Buzzer OFF
      digitalWrite(buzzerPin, LOW);
    }
  }

  delay(200);
}
