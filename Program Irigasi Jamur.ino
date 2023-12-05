#include <ModbusRtu.h>    // Library protokol modbus.
#define ID 1              // Mendifinisikan ID modbus 1. 
Modbus slave (ID, 0, 0);  // Port serial (0), dan kontrol transmisi (0).

int8_t state = 0;         
uint16_t data [3];        // Array untuk menyimpan data Modbus.
int sensorValue = A0;     // Inisialisasi kaki PIN analog sensor kelembapan. 

float kelembapantanah;    // Variabel untuk menyimpan data kelembapan.
int ledred = 3;           // Inisialisasi kaki PIN digital LED merah.
int ledgreen = 5;         // Inisialisasi kaki PIN digital LED hijau.
int Relay = 6;            // Inisialisasi kaki PIN digital relay.
int thresholdValue = 50;  // Nilai ambang batas non/aktif pompa air berdasarkan kelembaban.

void setup(){
  Serial.begin(9600);     // Memulai komunikasi serial.
  slave.begin(9600);      // Inisialisasi Komunikasi Modbus.
  pinMode (A0, INPUT);    // Mengatur kaki A0 sebagai INPUT.
  pinMode (3, OUTPUT);    // Mengatur kaki 3 sebagai OUTPUT.
  pinMode (5, OUTPUT);    // Mengatur kaki 5 sebagai OUTPUT.
  pinMode (6, OUTPUT);    // Mengatur kaki 6 sebagai OUTPUT. 
}

void loop(){
  state = slave.poll(data,3);
  data[2]= kelembapantanah;
  
  kelembapantanah;
   int baca = analogRead(sensorValue);
   kelembapantanah = (100-((baca/1023.00)*100));
  Serial.print(kelembapantanah);
  
  if(kelembapantanah < thresholdValue){
    Serial.println("Aktifkan pompa air");
    digitalWrite(ledred, LOW);
    digitalWrite(ledgreen, HIGH);
    digitalWrite(Relay, HIGH);
  }
  else {
    Serial.println("Matikan pompa air");
    digitalWrite(ledred, HIGH);
    digitalWrite(ledgreen, LOW);
    digitalWrite(Relay, LOW);
  }
  delay(100);
}
