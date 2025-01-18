#include <Servo.h>

#define ldr A0
#define led 9
#define servoPin 10  // Pin untuk servo motor
#define irPin1 2     // Pin InfraRed sensor pertama
#define irPin2 4     // Pin InfraRed sensor kedua
#define servoOpenPosition 0  // Posisi servo terbuka
#define servoClosePosition 90   // Posisi servo tertutup

Servo myServo;  // Servo object

int ldrValue;

void setup() {
  // pinMode setup Sensor InfraRed pertama
  pinMode(irPin1, INPUT);
  pinMode(irPin2, INPUT);
  pinMode(3, OUTPUT);

  // pinMode setup Sensor LDR
  pinMode(ldr, INPUT);
  pinMode(led, OUTPUT);  

  // Pin servo setup
  myServo.attach(servoPin);  // Attach servo ke pin 10
  
  Serial.begin(9600);
}

void loop() {
  bool irValue1 = digitalRead(irPin1); // baca nilai dari sensor InfraRed pertama
  bool irValue2 = digitalRead(irPin2); // baca nilai dari sensor InfraRed kedua
  ldrValue = analogRead(ldr);         // baca nilai dari sensor LDR
  Serial.println(ldrValue);           // print nilai ldrValue (nilai sensor LDR) di Serial Monitor

  // Cek Sensor InfraRed pertama
  if(irValue1 == 0) {
    Serial.println("ON1");            // print "ON1" di serial Monitor jika ada Objek
    digitalWrite(3, HIGH);
    myServo.write(servoOpenPosition);
    delay(500); // Buka servo
  } 
  else if(irValue2 == 0) {
    Serial.println("ON2");            // print "ON2" di serial Monitor jika ada Objek
    myServo.write(servoOpenPosition);
    delay(2000); // Buka servo
  } 
  else {
    Serial.println("OFF");           // print "OFF" jika tidak ada Objek
    digitalWrite(3, LOW);
    myServo.write(servoClosePosition); // Tutup servo
  }

  // Cek Sensor LDR
  if (ldrValue > 800) {
    digitalWrite(led, HIGH);    // LED nyala jika ldrValue > 800 (jika tidak kedeteksi cahaya)
  } else {
    digitalWrite(led, LOW);     // LED mati jika kedeteksi cahaya
  }
  
  delay(100);
}
