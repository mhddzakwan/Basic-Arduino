# Tutorial Basic Arduino/ESP

Pada tutorial ini, kita akan mempelajari dasar-dasar Arduino dan ESP, yang meliputi:
- Pengenalan hardware
- Software dan dasar pemrograman
- Cara penggunaan sensor (sensor jarak HC-SR04)
- Pengendalian motor (motor servo) serta 3 LED

## Introduction Arduino dan Basic Programming

### Overview Singkat Arduino dan Kemampuannya
- Arduino adalah platform elektronik open-source yang terdiri dari hardware dan software yang mudah digunakan, sering dimanfaatkan dalam pembelajaran mikrokontroler dan embedded system karena kesederhanaan dan fleksibilitasnya. Platform ini terdiri dari papan sirkuit yang dapat diprogram (mikrokontroler) dan lingkungan pengembangan (development environment) yang memungkinkan pengguna menulis dan mengunggah kode ke papan tersebut.

- **Kemampuannya**
dapat berinterface dengan banyak jenis sensor, display, dan comunnication modules. sehingga sering digunakan untuk robotik, IoT (home automation), dll.

### Pinout Arduino Uno
![Alt text](images/pinout_uno.png)

1. **Pinout power:**
![Alt text](images/power.png)
- **Power Jack**
sebagai adapter power supply 7-12V
- **Vin**
pin untuk external power source ke arduino
- **USB jack**
konek ke komputer, menyediakan 5v 500mA
- **5V dan 3v3**
menyediakan 5v dan 3,3V untuk memberi daya komponen external
- **GND**
pin GND digunakan untuk menutup rangkaian listrik


2. **Pinout Analog:**
<br><br>
![Alt text](images/pinout_analog.png)
 - Dapat digunakan sebagai input dan output
 - Pin analog bisa digunakan untuk membaca data sensor analog seperti sensor suhu, sensor cahaya, pontensiometer, dll.


3. **Pinout Digital:**
<br><br>
   ![Alt text](images/pinout_digital.png)
- Pin digital dapat digunakan sebagai input dan output (pin 0 - 13)
- **Sebagai INPUT** membaca signal digital HIGH = 5V dan LOW = 0V
- **Sebagai OUTPUT** memberikan signal digital HIGH dan LOW untuk mengontrol LED, relay, motor, dan digital device lainnya
- pin PWM (~), digunakan untuk men-generate sinyal seperti analog dengan menggunakan sinyal. biasa digunakan untuk mengontrol kecepatan motor, kecerahan LED, dll

## Basic Konsep Pemrogramman Arduino C

### Structure
```c
#include <Servo.h>
#include <LiquidCrystal.h>
#include "CMPS12.h"

#define LED_BUILTIN 13

int loop_count = 0;

void setup(){
     //inisialisasi serial komunikasi
     Serial.begin(9600);

     //set pin mode
     pinMode(LED_BUILTIN, OUTPUT);
     
}

void loop(){
     //blink LED
     digitalWrite(LED_BUILTIN, HIGH);
     delay(1000);
     digitalWrite(LED_BUILTIN, LOW);
     delay(1000);
}
```

1. **setup()**
```c
void setup(){
     //inisialisasi serial komunikasi
     Serial.begin(9600);

     //set pin mode
     pinMode(LED_BUILTIN, OUTPUT);
     
}
```
- dijalankan hanya sekali saat Arduino board diberikan daya atau saat reset button ditekan
- untuk inisialisasi variable
- setting pin mode
- menjalankan "one-time setup" yang lainnya

2. **loop()**
```c
void loop(){
     //blink LED
     digitalWrite(LED_BUILTIN, HIGH);
     delay(1000);
     digitalWrite(LED_BUILTIN, LOW);
     delay(1000);
}
```
- dijalankan secara kontiniu setelah setup().
- berisi code utama yang berjalan secara berulang selama arduino masih dalam keadaan hidup
3. **bagian Opsional**
- Inklusi library
```c
#include <Servo.h>
#include <LiquidCrystal.h>
#include "CMPS12.h"
```

- Constant definition
```c
#define LED_BUILTIN 13
```

- Global variable declaration
```c
int loop_count = 0;
```

## Cara menggunakan sensor (sensor jarak HC-SR04 ultrasonic sensor)
Sensor Ultrasonic HC-SR04 adalah sensor jarak. Menggunakan prinsip kecepatan suara. **Akurasi** dari sensor ini adalah **2-400cm**

### Wiring HC-SR04 ke Arduino
![Alt text](images/hcsr_arduino.png)

### Wiring HC-SR04 menggunakan breadboard
![Alt text](images/hcsr_arduino_bb.png)

- Vcc -> 5V
- GND -> GND
- Trig -> 2
- Echo -> 3

[click disini untuk melihat code](https://github.com/mhddzakwan/Basic-Arduino/blob/main/hcsr/baca_hcsr.ino)

## Cara mengendalikan 3 Buah LED

### Wiring LED menggunakan breadboard
![Alt text](images/led3_arduino.png)

- Negatif -> GND
- Positif merah -> 7
- Positif merah -> 8
- Positif merah -> 9

[click disini untuk melihat code](https://github.com/mhddzakwan/Basic-Arduino/blob/main/led/led_arduino.ino)

## Cara mengendalikan motor servo
- Motor servo adalah perangkat yang dapat berputar ke lokasi spesifik atau ke angle spesifik berdasarkan input sinyal yang diterima
![Alt text](images/servo_arduino.png)
![Alt text](images/servo_arduino_bb.png)


- Vcc -> 5V
- GND -> GND
- Data -> 9~

[click disini untuk melihat code](https://github.com/mhddzakwan/Basic-Arduino/blob/main/servo/kontrol_servo.ino)

## Simulasi Tong Sampah Otomastis menggunakan HC-SR04, motor servo dan LED
![Alt text](images/gabungan_led.png)

[click disini untuk melihat code](https://github.com/mhddzakwan/Basic-Arduino/blob/main/gabungan/gabungan.ino)
