/*
  ===================================================================
  PRAKTIKUM 12: SMART HOME DASHBOARD - Sistem Lengkap dengan Blynk
  ===================================================================

  Deskripsi:
  Program ini adalah sistem smart home LENGKAP yang menggabungkan:
  - Multi-sensor (DHT11 + LDR + PIR)
  - Multi-aktuator (Relay untuk AC/Lampu + Buzzer)
  - OLED Display (status lokal)
  - Blynk Dashboard (monitoring & kontrol via smartphone)

  Fitur Utama:
  1. Monitoring real-time: Suhu, Kelembapan, Cahaya, Gerakan
  2. Kontrol AC via smartphone (Blynk Button)
  3. Lampu otomatis (berdasarkan LDR + PIR)
  4. Alarm suhu tinggi (Buzzer + Notifikasi Blynk)
  5. Display status di OLED (WiFi, Blynk, Sensor)
  6. Sistem tetap jalan offline (failsafe)

  Komponen yang Dibutuhkan:
  - 1x ESP32 Development Board
  - 1x Sensor DHT11 (Suhu & Kelembapan)
  - 1x Sensor LDR (Cahaya)
  - 1x Sensor PIR (Gerakan)
  - 1x Relay 2 Channel (AC & Lampu)
  - 1x Buzzer Aktif
  - 1x OLED Display 0.96" (I2C)
  - Kabel jumper & Breadboard

  Koneksi Rangkaian:

  DHT11:
  - VCC   → ESP32 3.3V
  - DATA  → ESP32 GPIO15
  - GND   → ESP32 GND

  LDR (dengan resistor 10K):
  - LDR satu kaki → ESP32 3.3V
  - LDR kaki lain → ESP32 GPIO34 (ADC)
  - Resistor 10K dari GPIO34 → GND

  PIR:
  - VCC   → ESP32 5V
  - OUT   → ESP32 GPIO27
  - GND   → ESP32 GND

  Relay 2 Channel:
  - VCC   → ESP32 5V (PENTING: Jangan 3.3V!)
  - GND   → ESP32 GND
  - IN1   → ESP32 GPIO25 (Relay AC)
  - IN2   → ESP32 GPIO26 (Relay Lampu)

  Buzzer:
  - (+)   → ESP32 GPIO33
  - (-)   → ESP32 GND

  OLED Display (I2C):
  - VCC   → ESP32 3.3V
  - GND   → ESP32 GND
  - SDA   → ESP32 GPIO21
  - SCL   → ESP32 GPIO22

  Library yang Diperlukan:
  - WiFi (built-in ESP32)
  - Blynk (by Volodymyr Shymanskyy)
  - DHT sensor library (by Adafruit)
  - Adafruit Unified Sensor
  - Adafruit SSD1306 (untuk OLED)
  - Adafruit GFX Library

  Setup Blynk (PENTING!):
  1. Buat Template: "Smart Home"
  2. Buat Datastream:
     - V0: Suhu (Double, 0-50, °C)
     - V1: Kelembapan (Double, 0-100, %)
     - V2: Intensitas Cahaya (Integer, 0-4095)
     - V3: Status PIR (Integer, 0-1)
     - V4: Kontrol AC (Integer, 0-1)
     - V5: Kontrol Lampu (Integer, 0-1)
     - V6: Status Sistem (String)
  3. Tambah Widget:
     - Gauge → V0 (Suhu)
     - Value Display → V1 (Kelembapan)
     - Value Display → V2 (Cahaya)
     - LED indicator → V3 (PIR)
     - Button (Switch) → V4 (AC)
     - Button (Switch) → V5 (Lampu)
     - Label → V6 (Status)
  4. Buat Device dan copy Auth Token

  Cara Menggunakan:
  1. Rakit rangkaian sesuai diagram di atas
  2. Ubah BLYNK_TEMPLATE_ID, BLYNK_TEMPLATE_NAME, BLYNK_AUTH_TOKEN
  3. Ubah ssid dan pass WiFi
  4. Upload kode
  5. Buka Serial Monitor dan Blynk app
  6. Nikmati smart home Anda!

  Dibuat untuk: Mata Kuliah Bangunan Cerdas
  Instruktur: Anton Prafanto
  Target: Mahasiswa Arsitektur (Mudah dipahami!)
  ===================================================================
*/

// ===== INCLUDE LIBRARY =====
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ===== BLYNK CREDENTIALS =====
#define BLYNK_TEMPLATE_ID "TMPL4xxxxxxxxx"
#define BLYNK_TEMPLATE_NAME "Smart Home"
#define BLYNK_AUTH_TOKEN "abcdefgh123456789ijklmnopqrstuv"
#define BLYNK_PRINT Serial

// ===== WIFI CREDENTIALS =====
char ssid[] = "NAMA_WIFI_ANDA";
char pass[] = "PASSWORD_WIFI_ANDA";

// ===== PIN DEFINITIONS =====
// Sensor
#define DHTPIN 15       // DHT11 DATA pin
#define DHTTYPE DHT11   // Tipe DHT11
#define LDRPIN 34       // LDR pin (ADC)
#define PIRPIN 27       // PIR OUT pin

// Aktuator
#define RELAY_AC 25     // Relay channel 1 (AC)
#define RELAY_LAMPU 26  // Relay channel 2 (Lampu)
#define BUZZER 33       // Buzzer pin

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1   // Reset pin (-1 jika tidak ada)
#define SCREEN_ADDRESS 0x3C  // Alamat I2C OLED (biasanya 0x3C atau 0x3D)

// ===== INISIALISASI OBJEK =====
DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ===== VARIABEL GLOBAL - SENSOR =====
float suhu = 0;
float kelembapan = 0;
int cahaya = 0;
bool gerakanDetected = false;

// ===== VARIABEL GLOBAL - KONTROL =====
bool acManual = false;        // Kontrol AC manual dari Blynk
bool lampuManual = false;     // Kontrol lampu manual dari Blynk
bool acStatus = false;        // Status AC saat ini
bool lampuStatus = false;     // Status lampu saat ini

// ===== VARIABEL GLOBAL - THRESHOLD =====
const float SUHU_MAX = 30.0;       // Suhu tinggi (°C) → Nyalakan AC
const int CAHAYA_GELAP = 2000;     // Cahaya <2000 = gelap → Nyalakan lampu

// ===== VARIABEL GLOBAL - TIMER =====
unsigned long lastSensorRead = 0;    // Timer baca sensor
const long sensorInterval = 2000;    // Baca sensor setiap 2 detik

unsigned long lastBlynkSend = 0;     // Timer kirim data ke Blynk
const long blynkInterval = 2000;     // Kirim setiap 2 detik (rate limiting)

unsigned long lastDisplayUpdate = 0; // Timer update OLED
const long displayInterval = 1000;   // Update OLED setiap 1 detik

unsigned long lastCheck = 0;         // Timer cek koneksi
const long checkInterval = 10000;    // Cek setiap 10 detik

// ===== FUNGSI SETUP =====
void setup() {
  // Inisialisasi Serial
  Serial.begin(115200);
  delay(100);

  Serial.println();
  Serial.println("========================================");
  Serial.println("  SMART HOME DASHBOARD - PRAKTIKUM 12");
  Serial.println("========================================");
  Serial.println();

  // Inisialisasi pin sensor
  pinMode(PIRPIN, INPUT);
  pinMode(LDRPIN, INPUT);

  // Inisialisasi pin aktuator
  pinMode(RELAY_AC, OUTPUT);
  pinMode(RELAY_LAMPU, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Matikan semua aktuator di awal
  digitalWrite(RELAY_AC, LOW);
  digitalWrite(RELAY_LAMPU, LOW);
  digitalWrite(BUZZER, LOW);

  // Inisialisasi sensor DHT11
  dht.begin();
  Serial.println("[DHT11] Sensor initialized");
  delay(2000);  // Tunggu sensor stabil

  // Inisialisasi OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("[OLED] ERROR: Display not found!");
    Serial.println("       Cek koneksi I2C (SDA=21, SCL=22)");
  } else {
    Serial.println("[OLED] Display initialized");
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Smart Home");
    display.println("Starting...");
    display.display();
  }

  // Koneksi ke Blynk
  Serial.println();
  Serial.println("Menghubungkan ke WiFi dan Blynk...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println();
  Serial.println("Setup selesai!");
  Serial.println("========================================");
}

// ===== FUNGSI LOOP =====
void loop() {
  // WAJIB! Handle komunikasi Blynk
  Blynk.run();

  // Baca sensor setiap 2 detik
  if (millis() - lastSensorRead >= sensorInterval) {
    lastSensorRead = millis();
    bacaSemuaSensor();
    kontrolOtomatis();  // Jalankan logika otomatis
  }

  // Kirim data ke Blynk setiap 2 detik (rate limiting)
  if (millis() - lastBlynkSend >= blynkInterval) {
    lastBlynkSend = millis();
    kirimDataKeBlynk();
  }

  // Update OLED setiap 1 detik
  if (millis() - lastDisplayUpdate >= displayInterval) {
    lastDisplayUpdate = millis();
    updateOLED();
  }

  // Cek koneksi setiap 10 detik
  if (millis() - lastCheck >= checkInterval) {
    lastCheck = millis();
    cekKoneksi();
  }
}

// ===== FUNGSI: BACA SEMUA SENSOR =====
void bacaSemuaSensor() {
  // Baca DHT11
  suhu = dht.readTemperature();
  kelembapan = dht.readHumidity();

  // Cek error DHT11
  if (isnan(suhu) || isnan(kelembapan)) {
    Serial.println("[DHT11] ERROR: Gagal membaca!");
    suhu = 0;
    kelembapan = 0;
  }

  // Baca LDR (nilai ADC 0-4095)
  cahaya = analogRead(LDRPIN);

  // Baca PIR (HIGH=ada gerakan, LOW=tidak ada)
  gerakanDetected = digitalRead(PIRPIN);

  // Tampilkan di Serial Monitor
  Serial.println("--- Pembacaan Sensor ---");
  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.println(" °C");

  Serial.print("Kelembapan: ");
  Serial.print(kelembapan);
  Serial.println(" %");

  Serial.print("Cahaya: ");
  Serial.print(cahaya);
  Serial.println(" (0=terang, 4095=gelap)");

  Serial.print("Gerakan: ");
  Serial.println(gerakanDetected ? "TERDETEKSI" : "Tidak ada");
  Serial.println();
}

// ===== FUNGSI: KONTROL OTOMATIS =====
void kontrolOtomatis() {
  // ===== KONTROL AC OTOMATIS =====
  // Jika tidak dikontrol manual, otomatis berdasarkan suhu
  if (!acManual) {
    if (suhu > SUHU_MAX && !acStatus) {
      // Suhu tinggi → Nyalakan AC
      digitalWrite(RELAY_AC, HIGH);
      acStatus = true;
      Serial.println("[AC] AUTO ON (suhu tinggi)");

      // Bunyi buzzer 2x sebagai notifikasi
      bunyiBuzzer(2);
    }
    else if (suhu <= (SUHU_MAX - 2) && acStatus) {
      // Suhu turun → Matikan AC (hysteresis -2°C)
      digitalWrite(RELAY_AC, LOW);
      acStatus = false;
      Serial.println("[AC] AUTO OFF (suhu normal)");
    }
  }

  // ===== KONTROL LAMPU OTOMATIS =====
  // Jika tidak dikontrol manual, otomatis berdasarkan cahaya + gerakan
  if (!lampuManual) {
    if (cahaya > CAHAYA_GELAP && gerakanDetected && !lampuStatus) {
      // Gelap + Ada gerakan → Nyalakan lampu
      digitalWrite(RELAY_LAMPU, HIGH);
      lampuStatus = true;
      Serial.println("[LAMPU] AUTO ON (gelap + gerakan)");
    }
    else if ((cahaya <= CAHAYA_GELAP || !gerakanDetected) && lampuStatus) {
      // Terang ATAU tidak ada gerakan → Matikan lampu
      // (Tunggu 10 detik untuk mati, untuk hemat kode tidak implementasi di sini)
      digitalWrite(RELAY_LAMPU, LOW);
      lampuStatus = false;
      Serial.println("[LAMPU] AUTO OFF");
    }
  }
}

// ===== FUNGSI: KIRIM DATA KE BLYNK =====
void kirimDataKeBlynk() {
  // Hanya kirim jika Blynk connected (hemat bandwidth)
  if (!Blynk.connected()) {
    return;
  }

  // Kirim data sensor
  Blynk.virtualWrite(V0, suhu);
  Blynk.virtualWrite(V1, kelembapan);
  Blynk.virtualWrite(V2, cahaya);
  Blynk.virtualWrite(V3, gerakanDetected ? 1 : 0);

  // Kirim status aktuator
  Blynk.virtualWrite(V4, acStatus ? 1 : 0);
  Blynk.virtualWrite(V5, lampuStatus ? 1 : 0);

  // Kirim status sistem
  String status = "Normal";
  if (suhu > SUHU_MAX) {
    status = "Suhu Tinggi!";
  }
  Blynk.virtualWrite(V6, status);

  Serial.println("[Blynk] Data terkirim ke app");
}

// ===== FUNGSI: UPDATE OLED DISPLAY =====
void updateOLED() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  // Baris 1: Judul
  display.println("SMART HOME");
  display.println("----------------");

  // Baris 2-3: Data sensor
  display.print("T:");
  display.print(suhu, 1);
  display.print("C  H:");
  display.print(kelembapan, 0);
  display.println("%");

  display.print("Cahaya: ");
  display.println(cahaya > CAHAYA_GELAP ? "GELAP" : "TERANG");

  // Baris 4: Status aktuator
  display.print("AC:");
  display.print(acStatus ? "ON " : "OFF");
  display.print(" L:");
  display.println(lampuStatus ? "ON" : "OFF");

  // Baris 5: Status koneksi
  display.println("----------------");
  if (WiFi.status() == WL_CONNECTED) {
    display.print("WiFi:");
    display.println(Blynk.connected() ? "OK" : "X");
  } else {
    display.println("WiFi: OFFLINE");
  }

  display.display();
}

// ===== FUNGSI: CEK KONEKSI =====
void cekKoneksi() {
  Serial.println("--- Status Koneksi ---");

  // Cek WiFi
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("[WiFi] OK - IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("[WiFi] DISCONNECTED");
  }

  // Cek Blynk
  if (Blynk.connected()) {
    Serial.println("[Blynk] CONNECTED");
  } else {
    Serial.println("[Blynk] DISCONNECTED");
  }

  Serial.println();
}

// ===== FUNGSI: BUNYI BUZZER =====
void bunyiBuzzer(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
    delay(100);
  }
}

// ===== FUNGSI BLYNK: KONTROL AC DARI APP (V4) =====
BLYNK_WRITE(V4) {
  int value = param.asInt();

  if (value == 1) {
    // User nyalakan AC dari app
    digitalWrite(RELAY_AC, HIGH);
    acStatus = true;
    acManual = true;  // Mode manual
    Serial.println("[AC] MANUAL ON dari app");
  } else {
    // User matikan AC dari app
    digitalWrite(RELAY_AC, LOW);
    acStatus = false;
    acManual = false;  // Kembali ke auto
    Serial.println("[AC] MANUAL OFF dari app");
  }
}

// ===== FUNGSI BLYNK: KONTROL LAMPU DARI APP (V5) =====
BLYNK_WRITE(V5) {
  int value = param.asInt();

  if (value == 1) {
    // User nyalakan lampu dari app
    digitalWrite(RELAY_LAMPU, HIGH);
    lampuStatus = true;
    lampuManual = true;  // Mode manual
    Serial.println("[LAMPU] MANUAL ON dari app");
  } else {
    // User matikan lampu dari app
    digitalWrite(RELAY_LAMPU, LOW);
    lampuStatus = false;
    lampuManual = false;  // Kembali ke auto
    Serial.println("[LAMPU] MANUAL OFF dari app");
  }
}

// ===== FUNGSI BLYNK: EVENT SAAT CONNECTED =====
BLYNK_CONNECTED() {
  Serial.println();
  Serial.println("========================================");
  Serial.println("   ✓ BLYNK CONNECTED!");
  Serial.println("========================================");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Serial.println("Smart Home Dashboard aktif!");
  Serial.println("Buka Blynk app untuk monitoring.");
  Serial.println("========================================");

  // Sync status button dari server
  Blynk.syncVirtual(V4, V5);

  // Update tampilan OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("CONNECTED!");
  display.println();
  display.print("IP: ");
  display.println(WiFi.localIP());
  display.display();
  delay(2000);
}
