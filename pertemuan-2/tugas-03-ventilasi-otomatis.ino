/*
  TUGAS 3: SISTEM VENTILASI OTOMATIS
  
  Logika:
  - LED Hijau (kipas exhaust): Nyala jika kelembapan > 70%
  - LED Biru (AC): Nyala jika suhu > 30°C  
  - LED Merah (alarm): Nyala jika suhu > 35°C DAN kelembapan > 80%
  
  Komponen: ESP32, DHT11, 3x LED (merah,hijau,biru), 3x resistor 220Ω
  
  Koneksi:
  - DHT11: 3.3V-DATA(GPIO15)-GND
  - LED Hijau (exhaust): GPIO2
  - LED Biru (AC): GPIO4
  - LED Merah (alarm): GPIO5
*/

#include <DHT.h>

#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int pinExhaust = 2;   // LED hijau
const int pinAC = 4;        // LED biru
const int pinAlarm = 5;     // LED merah

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  pinMode(pinExhaust, OUTPUT);
  pinMode(pinAC, OUTPUT);
  pinMode(pinAlarm, OUTPUT);
  
  Serial.println("=== SISTEM VENTILASI OTOMATIS ===");
  Serial.println("Exhaust Fan: Kelembapan > 70%");
  Serial.println("AC: Suhu > 30°C");
  Serial.println("Alarm: Suhu>35°C DAN RH>80%");
  Serial.println();
  
  delay(2000);
}

void loop() {
  float suhu = dht.readTemperature();
  float rh = dht.readHumidity();
  
  if (isnan(suhu) || isnan(rh)) {
    Serial.println("Error DHT11!");
    delay(2000);
    return;
  }
  
  // Kontrol Exhaust Fan (hijau)
  bool exhaustOn = (rh > 70);
  digitalWrite(pinExhaust, exhaustOn ? HIGH : LOW);
  
  // Kontrol AC (biru)
  bool acOn = (suhu > 30);
  digitalWrite(pinAC, acOn ? HIGH : LOW);
  
  // Alarm (merah) - kondisi ekstrem
  bool alarmOn = (suhu > 35 && rh > 80);
  digitalWrite(pinAlarm, alarmOn ? HIGH : LOW);
  
  // Display
  Serial.println("┌─────────────────────────────┐");
  Serial.print("│ Suhu: ");
  Serial.print(suhu, 1);
  Serial.println(" °C              │");
  Serial.print("│ Kelembapan: ");
  Serial.print(rh, 1);
  Serial.println(" %       │");
  Serial.println("├─────────────────────────────┤");
  Serial.print("│ 🌀 Exhaust Fan: ");
  Serial.println(exhaustOn ? "NYALA   │" : "MATI    │");
  Serial.print("│ ❄️  AC: ");
  Serial.println(acOn ? "NYALA            │" : "MATI             │");
  Serial.print("│ 🚨 Alarm: ");
  Serial.println(alarmOn ? "AKTIF          │" : "NORMAL         │");
  Serial.println("└─────────────────────────────┘\n");
  
  delay(3000);
}

/*
  APLIKASI:
  - Kamar mandi: Exhaust auto saat lembap
  - Dapur: Exhaust saat memasak (lembap + panas)
  - Server room: AC + alarm jika overheating
  - Gudang: Ventilasi untuk cegah jamur
  
  PENGEMBANGAN:
  1. Tambah dehumidifier kontrol
  2. Integrasi dengan window actuator (buka jendela)
  3. Smart scheduling (ventilasi malam hari)
  4. Data logging untuk maintenance prediction
*/
