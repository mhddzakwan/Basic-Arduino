#include <Servo.h>

Servo myservo;

#define servopin 9  
#define trigpin 2
#define echopin 3

#DEFINE LED_RED 7
#DEFINE LED_YELLOW 8
#DEFINE LED_GREEN 10

long durasi;
int jarak;
int pos = 0;

void setup() {
  //inisiasi LED
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, HIGH);
  digitalWrite(LED_GREEN, LOW);
  
  //inisialisasi servo pin
  myservo.attach(servopin);

  Serial.begin(9600);

  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);

  //set posisi awal servo ke 0
  myservo.write(pos);

}

void loop() {
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

  durasi = pulseIn(echopin, HIGH);

  jarak = durasi * 0.034 / 2;

  Serial.print("Jarak: ");
  Serial.print(jarak);
  Serial.println(" cm");

  //variable untuk jarak mentrigger servo
  int trigger_pos = 20;

  if (jarak < trigger_pos){
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREENN, LOW);

    //Membuka tong sampah
    for(pos=0; pos <=90; pos++){
      myservo.write(pos);
      delay(20);
    }
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREENN, HIGH);
    delay(2000);
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREENN, LOW);
    //Menutup tong sampah
    for(pos=90; pos >=0; pos--){
      myservo.write(pos);
      delay(20);
    }

    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_GREENN, LOW);
  } else{
    pos = 0;
    myservo.write(pos);
  }

  delay(500);

}
