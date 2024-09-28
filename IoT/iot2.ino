#include <Servo.h>
#include <ESP8266WiFi.h> // Library Wifi Wemos
#include <ESP8266HTTPClient.h> //Library Koneksi HTTP

// Password dan SSID dari wifi yg dikoneksi
#define WIFI_SSID "KelilingDunia1"
#define WIFI_PASSWORD "12julham12"

Servo myservo;

// Wemos
#define servopin D7
#define trigpin D5
#define echopin D6

#define LED_RED D1
#define LED_YELLOW D2
#define LED_GREEN D3

long durasi;
int jarak, pos = 0, line=0;
String status,payload;

void setup() {
  Serial.begin(9600);
  //Koneksikan ssid dan password
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  // Loading Menunggu wifi terkoneksi
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  //Menampilkan ip addres wemos
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  //inisiasi LED
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, HIGH);
  digitalWrite(LED_GREEN, LOW);
  
  //inisialisasi servo pin
  myservo.attach(servopin);


  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);

  //set posisi awal servo ke 0
  myservo.write(0);

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

//Deklarasi HTTP
    WiFiClient client;
    HTTPClient http;
    //ALamat server
    String address = "http://192.168.1.7/tong_sampah/code/api_esp.php?jarak="; //Alamat, tempat notif dibuat
    address += jarak;
    Serial.println("------------------KIRIM DATA------------------");
    // Mulai koneksi HTTP
    http.begin(client,address);  
    // Kirim request GET
    int httpCode = http.GET(); 

    if (httpCode > 0) { // Jika koneksi berhasil
        Serial.println("httpcode lebih dari 0");

        if (httpCode == HTTP_CODE_OK) { // Periksa apakah status adalah 200 (HTTP_CODE_OK)
          payload = http.getString(); // Dapatkan payload dari tanggapan
          Serial.println(payload); // Tampilkan payload jika diperlukan
          if (payload == "on")digitalWrite(LED_RED, HIGH);
          else digitalWrite(LED_RED, LOW);
          // // Memproses respons baris per baris
          // int lineCount = 0; // Variabel untuk melacak nomor baris
          // line= 0;
          //int previousPos = 0; // Variabel untuk melacak posisi awal baris
          // bool foundLine5 = false; // Menandai apakah baris ke-5 ditemukan

          // while ((line = payload.indexOf('\n', line)) != -1) {
          //   // lineCount++; // Tambahkan nomor baris
          //   status = payload.substring(previousPos, line);
          //   if (status == "ON")digitalWrite(LED_RED, LOW);
          //   else digitalWrite(LED_RED, HIGH);
            
          //     // if(lineCount == 14){
          //     //   kenaikan = payload.substring(previousPos, pos);
          //     //   lcd.setCursor(0, 0);
          //     //   lcd.print(kenaikan);
            
          //     // }else if(lineCount == 15 ){
          //     //   Serial.println("---------sampek15------");
          //     //   prediksi = payload.substring(previousPos, pos);
          //     //   lcd.setCursor(0, 1);
          //     //   lcd.print(prediksi);
          //     // }
            
          //   // Geser posisi ke karakter setelah baris baru
          //   previousPos = pos + 1;
          //   pos++;
          // }
          // Serial.println("Status : " + status);
        
        } else {
          // Tanggapan tidak berhasil, tampilkan kode status
          Serial.println("Gagal, kode status HTTP: " + String(httpCode));
        }
      } else if (httpCode == 0) {
        Serial.println("Gagal koneksi ke server.");
      } else {
        Serial.println("Gagal, kode status HTTP: " + String(httpCode));
      }

      http.end();   //Close connection

  //variable untuk jarak mentrigger servo
  int trigger_pos = 5;

  if (jarak < trigger_pos){
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, LOW);

    //Membuka tong sampah
    for(pos=0; pos <=180; pos++){
      myservo.write(pos);
      delay(20);
    }
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, HIGH);
    delay(2000);
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, LOW);
    //Menutup tong sampah
    for(pos=180; pos >=0; pos--){
      myservo.write(pos);
      delay(20);
    }

    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_GREEN, LOW);
  } else{
    pos = 0;
    myservo.write(pos);
  }

  delay(1000);

}
