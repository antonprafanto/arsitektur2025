# CHEAT SHEET ARDUINO/ESP32
## Panduan Cepat untuk Mahasiswa

---

## 📌 STRUKTUR PROGRAM DASAR

```cpp
// Deklarasi variabel global
int pinLED = 2;

void setup() {
  // Dijalankan SEKALI saat ESP32 dinyalakan
  Serial.begin(115200);      // Inisialisasi Serial Monitor
  pinMode(pinLED, OUTPUT);   // Set pin sebagai output
}

void loop() {
  // Dijalankan BERULANG selamanya
  digitalWrite(pinLED, HIGH);
  delay(1000);
  digitalWrite(pinLED, LOW);
  delay(1000);
}
```

---

## 🔧 FUNGSI PIN

### Set Mode Pin
```cpp
pinMode(pin, OUTPUT);      // Pin sebagai output (LED, Relay)
pinMode(pin, INPUT);       // Pin sebagai input
pinMode(pin, INPUT_PULLUP); // Input dengan pull-up internal
```

### Digital Output
```cpp
digitalWrite(pin, HIGH);   // Kirim 3.3V (nyala)
digitalWrite(pin, LOW);    // Kirim 0V (mati)
```

### Digital Input
```cpp
int nilai = digitalRead(pin);  // Baca HIGH atau LOW
```

### Analog Input (ADC)
```cpp
int nilai = analogRead(pin);   // Baca 0-4095 (12-bit)
// Pin ADC ESP32: GPIO32-39
```

### Analog Output (PWM)
```cpp
analogWrite(pin, 128);  // Output PWM 0-255 (0=mati, 255=max)
// Untuk kontrol kecerahan LED atau kecepatan motor
```

---

## ⏱️ FUNGSI WAKTU

```cpp
delay(1000);              // Tunggu 1000 ms (1 detik)
delayMicroseconds(100);   // Tunggu 100 mikrodetik

unsigned long waktu = millis();  // Waktu sejak boot (ms)
unsigned long waktu = micros();  // Waktu sejak boot (μs)

// Contoh timer tanpa delay:
unsigned long previousMillis = 0;
const long interval = 1000;

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    // Lakukan sesuatu setiap 1 detik
  }
}
```

---

## 💬 SERIAL MONITOR

```cpp
Serial.begin(115200);       // Inisialisasi (di setup)

Serial.print("Suhu: ");     // Print tanpa newline
Serial.println(suhu);       // Print dengan newline

Serial.print(suhu, 2);      // Print 2 angka desimal
Serial.println();           // Print newline saja

// Format printf (lebih rapi):
Serial.printf("Suhu: %.1f °C\n", suhu);
```

---

## 🔢 VARIABEL & TIPE DATA

```cpp
// Integer (bilangan bulat)
int angka = 10;           // -32768 sampai 32767
unsigned int angka = 10;  // 0 sampai 65535
long angka = 100000;      // Bilangan besar

// Floating point (desimal)
float suhu = 28.5;        // 4 byte, presisi 6-7 digit
double suhu = 28.5;       // 8 byte (sama dengan float di ESP32)

// Boolean
bool lampuNyala = true;   // true atau false
bool pintu = false;

// Character & String
char huruf = 'A';         // Satu karakter
String teks = "Hello";    // String (banyak karakter)

// Array
int data[5] = {1, 2, 3, 4, 5};  // Array 5 elemen
data[0] = 10;  // Akses elemen pertama (index 0)

// Konstanta (tidak bisa diubah)
const int THRESHOLD = 100;
#define LED_PIN 2
```

---

## 🔀 KONTROL FLOW

### If - Else
```cpp
if (suhu > 30) {
  // Jika suhu lebih dari 30
  Serial.println("Panas");
} else if (suhu > 20) {
  // Jika suhu 20-30
  Serial.println("Normal");
} else {
  // Jika suhu kurang dari 20
  Serial.println("Dingin");
}
```

### Switch - Case
```cpp
switch (mode) {
  case 0:
    Serial.println("Mode 0");
    break;
  case 1:
    Serial.println("Mode 1");
    break;
  default:
    Serial.println("Mode lain");
}
```

### For Loop
```cpp
for (int i = 0; i < 10; i++) {
  Serial.println(i);  // Print 0 sampai 9
}
```

### While Loop
```cpp
int i = 0;
while (i < 10) {
  Serial.println(i);
  i++;
}
```

---

## 🧮 OPERATOR

### Aritmatika
```cpp
int a = 10 + 5;   // Tambah = 15
int b = 10 - 5;   // Kurang = 5
int c = 10 * 5;   // Kali = 50
int d = 10 / 5;   // Bagi = 2
int e = 10 % 3;   // Modulo (sisa bagi) = 1
```

### Perbandingan
```cpp
a == b   // Sama dengan
a != b   // Tidak sama dengan
a > b    // Lebih besar
a < b    // Lebih kecil
a >= b   // Lebih besar atau sama dengan
a <= b   // Lebih kecil atau sama dengan
```

### Logika
```cpp
(a > 5) && (b < 10)  // AND (DAN)
(a > 5) || (b < 10)  // OR (ATAU)
!(a > 5)             // NOT (TIDAK)
```

### Increment/Decrement
```cpp
i++;    // i = i + 1
i--;    // i = i - 1
i += 5; // i = i + 5
i *= 2; // i = i * 2
```

---

## 📊 FUNGSI MATEMATIKA

```cpp
int hasil = abs(-5);          // Nilai absolut = 5
int hasil = constrain(x, 0, 100);  // Batasi x antara 0-100
int hasil = map(x, 0, 1023, 0, 255); // Konversi range

float hasil = sqrt(16);       // Akar kuadrat = 4
float hasil = pow(2, 3);      // Pangkat (2^3) = 8

float hasil = sin(radians(90));   // Sinus
float hasil = cos(radians(0));    // Cosinus
float hasil = tan(radians(45));   // Tangen

int hasil = random(10);       // Random 0-9
int hasil = random(5, 10);    // Random 5-9

float hasil = round(3.7);     // Pembulatan = 4
float hasil = ceil(3.2);      // Pembulatan ke atas = 4
float hasil = floor(3.7);     // Pembulatan ke bawah = 3
```

---

## 📦 LIBRARY SENSOR UMUM

### DHT11/DHT22 (Suhu & Kelembapan)
```cpp
#include <DHT.h>

#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  dht.begin();
}

void loop() {
  float suhu = dht.readTemperature();       // °C
  float kelembapan = dht.readHumidity();    // %
  float heatIndex = dht.computeHeatIndex(suhu, kelembapan, false);
}
```

### OLED Display (SSD1306)
```cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Hello!");
  display.display();
}
```

---

## 📍 PIN ESP32

### Pin Digital (GPIO)
- Bisa digunakan: 0, 2, 4, 5, 12-19, 21-23, 25-27, 32-33
- **Hindari:** 6-11 (flash memory), 34-39 (input only)

### Pin Analog Input (ADC)
- **ADC1:** GPIO32-39 (bisa pakai bersamaan WiFi)
- **ADC2:** GPIO0, 2, 4, 12-15, 25-27 (tidak bisa pakai saat WiFi aktif)

### Pin I2C (untuk OLED, sensor I2C)
- **SDA:** GPIO21 (default)
- **SCL:** GPIO22 (default)

### Pin PWM
- Semua GPIO bisa PWM (kecuali 34-39)

---

## ☁️ BLYNK IoT PLATFORM

### Setup Blynk
```cpp
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Credentials (dari Blynk Console)
#define BLYNK_TEMPLATE_ID "TMPL4xxxxxxxxx"
#define BLYNK_TEMPLATE_NAME "Project Name"
#define BLYNK_AUTH_TOKEN "your-auth-token-32-chars"
#define BLYNK_PRINT Serial  // Debug ke Serial Monitor

char ssid[] = "WIFI_NAME";
char pass[] = "WIFI_PASSWORD";

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();  // WAJIB! Di awal loop()
}
```

### Kirim Data ke App (ESP32 → Blynk)
```cpp
// Kirim nilai ke Virtual Pin
Blynk.virtualWrite(V0, suhu);        // Kirim float/int
Blynk.virtualWrite(V1, "Status OK"); // Kirim string

// Rate limiting (max 10 writes/second)
unsigned long lastSend = 0;
void loop() {
  Blynk.run();

  if (millis() - lastSend >= 2000) {  // Setiap 2 detik
    lastSend = millis();
    Blynk.virtualWrite(V0, suhu);
  }
}
```

### Terima Data dari App (Blynk → ESP32)
```cpp
// Terima data dari Button/Slider widget
BLYNK_WRITE(V0) {
  int value = param.asInt();    // Ambil nilai integer
  // String str = param.asStr(); // Atau string

  digitalWrite(LED_PIN, value); // Kontrol LED
  Serial.print("Received: ");
  Serial.println(value);
}

// Terima beberapa nilai sekaligus (Joystick)
BLYNK_WRITE(V1) {
  int x = param[0].asInt();  // Nilai pertama
  int y = param[1].asInt();  // Nilai kedua
}
```

### Event Saat Connected
```cpp
BLYNK_CONNECTED() {
  // Dipanggil otomatis saat connect ke Blynk
  Serial.println("Blynk connected!");

  // Sync nilai dari server
  Blynk.syncVirtual(V0);  // Sync V0
  Blynk.syncAll();        // Sync semua virtual pin
}
```

### Push Notification
```cpp
// 1. Buat Event di Blynk Console dulu!
//    Event Code: high_temp
//    Enable Notification: ON

// 2. Kirim notification dari kode:
Blynk.logEvent("high_temp", "Suhu: 35°C");

// Limit: 1 notification/minute, max 100/day
// Gunakan cooldown:
unsigned long lastNotif = 0;
if (millis() - lastNotif >= 60000) {  // 60 detik
  Blynk.logEvent("high_temp", "Alert!");
  lastNotif = millis();
}
```

### Cek Status Koneksi
```cpp
void loop() {
  Blynk.run();

  if (Blynk.connected()) {
    // Blynk online
    Blynk.virtualWrite(V0, data);
  } else {
    // Blynk offline
    Serial.println("Blynk disconnected!");
  }
}
```

### WiFi Reconnect Pattern
```cpp
void checkWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi lost, reconnecting...");
    WiFi.disconnect();
    WiFi.begin(ssid, pass);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
      delay(500);
      Serial.print(".");
      attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\nWiFi reconnected!");
    }
  }
}
```

### Template Kode Minimal Blynk
```cpp
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_TEMPLATE_ID "TMPLxxxxxxxxx"
#define BLYNK_TEMPLATE_NAME "MyProject"
#define BLYNK_AUTH_TOKEN "your-32-char-token"

char ssid[] = "WiFi_Name";
char pass[] = "WiFi_Pass";

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
}

BLYNK_WRITE(V0) {
  int value = param.asInt();
  Serial.println(value);
}

BLYNK_CONNECTED() {
  Serial.println("Blynk connected!");
}
```

### Virtual Pin Reference
- **V0-V255**: Virtual pins (tidak ada pin fisik di ESP32)
- Gunakan untuk komunikasi dengan app Blynk
- Harus buat Datastream dulu di Blynk Console
- Datastream types: Integer, Double, String

### Widget → Virtual Pin Mapping (Contoh)
```
Gauge (suhu)         → V0 (Double, 0-50)
Button (LED)         → V1 (Integer, 0-1)
Slider (threshold)   → V2 (Integer, 0-100)
Label (status)       → V3 (String)
LED Indicator (PIR)  → V4 (Integer, 0-1)
Value Display (hum)  → V5 (Double, 0-100)
```

---

## 🎨 TIPS & TRICKS

### 1. Debouncing Button (Software)
```cpp
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void loop() {
  int reading = digitalRead(pinButton);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      // Button stabil, lakukan aksi
    }
  }

  lastButtonState = reading;
}
```

### 2. Moving Average (Stabilkan Sensor)
```cpp
const int numReadings = 10;
int readings[numReadings];
int index = 0;
int total = 0;

int bacaSensorStabil() {
  total -= readings[index];
  readings[index] = analogRead(pinSensor);
  total += readings[index];
  index = (index + 1) % numReadings;
  return total / numReadings;
}
```

### 3. Hysteresis (Anti-Flicker)
```cpp
const int THRESHOLD_ATAS = 2700;
const int THRESHOLD_BAWAH = 2300;
bool lampuNyala = false;

void loop() {
  int nilai = analogRead(pinLDR);

  if (nilai > THRESHOLD_ATAS && !lampuNyala) {
    digitalWrite(pinLED, HIGH);
    lampuNyala = true;
  } else if (nilai < THRESHOLD_BAWAH && lampuNyala) {
    digitalWrite(pinLED, LOW);
    lampuNyala = false;
  }
}
```

### 4. Non-Blocking Delay
```cpp
unsigned long previousMillis = 0;
const long interval = 1000;

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    // Kode yang dijalankan setiap 1 detik
  }

  // Kode lain tetap berjalan
}
```

---

## 🐛 DEBUG TIPS

### 1. Print Debug
```cpp
Serial.println("DEBUG: Masuk fungsi X");
Serial.print("Nilai variabel: ");
Serial.println(variabel);
```

### 2. LED Debug (tanpa Serial)
```cpp
digitalWrite(LED_DEBUG, HIGH);
// Kode yang di-debug
digitalWrite(LED_DEBUG, LOW);
```

### 3. Cek Sensor NaN
```cpp
if (isnan(suhu)) {
  Serial.println("Sensor error!");
}
```

---

## ⚡ SHORTCUTS ARDUINO IDE

- **Ctrl + R** : Verify (compile)
- **Ctrl + U** : Upload
- **Ctrl + Shift + M** : Serial Monitor
- **Ctrl + T** : Auto format kode
- **Ctrl + /** : Comment/uncomment
- **Ctrl + F** : Find (cari teks)

---

## 📞 BANTUAN

**Error Compile:**
- Cek library sudah terinstall
- Cek tanda kurung {} dan ; (titik koma)
- Cek nama variabel (case sensitive)

**Error Upload:**
- Tekan tombol BOOT saat upload
- Cek kabel USB
- Cek driver CH340/CP2102

**Sensor Tidak Jalan:**
- Cek koneksi VCC, GND, Signal
- Cek pin GPIO yang benar
- Upload kode test sederhana

---

**Simpan cheat sheet ini dan gunakan saat coding!** 📖
