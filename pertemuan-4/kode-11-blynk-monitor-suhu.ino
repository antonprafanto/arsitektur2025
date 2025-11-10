/*
  ===================================================================
  PRAKTIKUM 11: BLYNK MONITOR SUHU - Monitoring DHT11 via Smartphone
  ===================================================================

  Deskripsi:
  Program ini mengirim data suhu dan kelembapan dari sensor DHT11
  ke smartphone secara real-time menggunakan Blynk IoT. Data
  ditampilkan dalam bentuk Gauge, Value Display, dan Chart (grafik).

  Fitur:
  - Monitoring suhu real-time di Gauge widget
  - Monitoring kelembapan di Value Display widget
  - Grafik historis suhu & kelembapan (Chart widget)
  - Status sensor di Label widget
  - Rate limiting (kirim data setiap 2 detik)

  Komponen yang Dibutuhkan:
  - 1x ESP32 Development Board
  - 1x Sensor DHT11
  - Kabel jumper

  Koneksi Rangkaian:
  DHT11 VCC   --->  ESP32 3.3V
  DHT11 DATA  --->  ESP32 GPIO15
  DHT11 GND   --->  ESP32 GND

  Library yang Diperlukan:
  - WiFi (built-in ESP32)
  - Blynk (by Volodymyr Shymanskyy)
  - DHT sensor library (by Adafruit)
  - Adafruit Unified Sensor (dependency)

  Setup Blynk (PENTING!):
  ⚠️  Setup HARUS via Blynk Console (web): https://blynk.cloud
      Bukan hanya via app! App hanya untuk monitoring.

  1. Download app "Blynk IoT" → Buat akun
  2. [Via WEB] Buka browser → https://blynk.cloud → Login
  3. [Via WEB] Buat Template baru:
     - Klik "Templates" → "+ New Template"
     - Name: "Room Monitor"
     - Hardware: ESP32
     - Connection: WiFi
     - Klik "Done"

  4. [Via WEB] Buat Datastream (Tab "Datastreams" → "+ New Datastream"):
     a. Datastream 1:
        - Virtual Pin: V0
        - Name: "Suhu"
        - Data Type: Double
        - Min: 0, Max: 50
        - Units: °C
     b. Datastream 2:
        - Virtual Pin: V1
        - Name: "Kelembapan"
        - Data Type: Double
        - Min: 0, Max: 100
        - Units: %
     c. Datastream 3:
        - Virtual Pin: V2
        - Name: "Status Sensor"
        - Data Type: String

  5. [Via WEB] Tambah Widget ke Dashboard (Tab "Mobile Dashboard"):
     a. Gauge widget → Datastream: V0 (Suhu)
     b. Value Display widget → Datastream: V1 (Kelembapan)
     c. Chart widget → Datastream: V0 dan V1 (grafik)
     d. Label widget → Datastream: V2 (Status)

  6. [Via WEB] Buat Device:
     - Klik "Devices" → "+ New Device" → "From Template"
     - Pilih "Room Monitor"
     - Device Name: "ESP32_Monitor"
     - Klik "Create"
  7. [Via WEB] Copy Auth Token:
     - Device Info → Copy BLYNK_AUTH_TOKEN (klik icon ⎘)
     - Paste ke line 90 di bawah!

  💡 TIP: Auth Token lebih mudah di-copy via web console!
  📖 Panduan lengkap: Lihat MATERI-PERTEMUAN-4.md Bagian 2B

  Cara Menggunakan:
  1. Ubah BLYNK_TEMPLATE_ID, BLYNK_TEMPLATE_NAME, BLYNK_AUTH_TOKEN
  2. Ubah ssid dan pass sesuai WiFi Anda
  3. Upload kode ke ESP32
  4. Buka Serial Monitor (115200 baud)
  5. Buka Blynk app, lihat data real-time!

  Dibuat untuk: Mata Kuliah Bangunan Cerdas
  Instruktur: Anton Prafanto
  ===================================================================
*/

// ===== INCLUDE LIBRARY =====
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
// Library WiFi untuk koneksi internet
// Library Blynk untuk komunikasi dengan Blynk cloud
// Library DHT untuk sensor DHT11

// ===== BLYNK CREDENTIALS =====
// GANTI dengan credentials dari Blynk app Anda!
#define BLYNK_TEMPLATE_ID "TMPL4xxxxxxxxx"
#define BLYNK_TEMPLATE_NAME "Room Monitor"
#define BLYNK_AUTH_TOKEN "abcdefgh123456789ijklmnopqrstuv"

// Print debug ke Serial Monitor
#define BLYNK_PRINT Serial

// ===== WIFI CREDENTIALS =====
char ssid[] = "NAMA_WIFI_ANDA";
char pass[] = "PASSWORD_WIFI_ANDA";

// ===== PIN DEFINITIONS =====
#define DHTPIN 15       // Pin DATA DHT11 (GPIO15)
#define DHTTYPE DHT11   // Tipe sensor DHT11

// ===== INISIALISASI SENSOR =====
DHT dht(DHTPIN, DHTTYPE);
// Buat objek DHT dengan pin dan tipe sensor

// ===== VIRTUAL PIN BLYNK =====
// V0 = Suhu (°C)
// V1 = Kelembapan (%)
// V2 = Status sensor (String)

// ===== VARIABEL GLOBAL =====
unsigned long lastSend = 0;          // Timer untuk kirim data
const long sendInterval = 2000;      // Kirim data setiap 2 detik (rate limiting)
unsigned long lastCheck = 0;         // Timer untuk cek koneksi
const long checkInterval = 10000;    // Cek koneksi setiap 10 detik

float suhu = 0;          // Menyimpan nilai suhu
float kelembapan = 0;    // Menyimpan nilai kelembapan

// ===== FUNGSI SETUP =====
void setup() {
  // Inisialisasi Serial Monitor
  Serial.begin(115200);
  delay(100);

  Serial.println();
  Serial.println("========================================");
  Serial.println("  BLYNK MONITOR SUHU - PRAKTIKUM 11");
  Serial.println("========================================");
  Serial.println();

  // Inisialisasi sensor DHT11
  dht.begin();
  Serial.println("[DHT11] Sensor initialized");
  delay(2000);  // Tunggu sensor stabil

  // Koneksi ke Blynk
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

  // Kirim data sensor setiap 2 detik (rate limiting)
  if (millis() - lastSend >= sendInterval) {
    lastSend = millis();
    sendSensorData();  // Baca dan kirim data sensor
  }

  // Cek status koneksi setiap 10 detik
  if (millis() - lastCheck >= checkInterval) {
    lastCheck = millis();
    checkConnection();
  }
}

// ===== FUNGSI: BACA DAN KIRIM DATA SENSOR =====
void sendSensorData() {
  // Baca sensor DHT11
  suhu = dht.readTemperature();
  kelembapan = dht.readHumidity();

  // Cek apakah pembacaan berhasil
  if (isnan(suhu) || isnan(kelembapan)) {
    // Sensor error atau tidak terdeteksi
    Serial.println("[DHT11] ERROR: Gagal membaca sensor!");
    Serial.println("        Cek koneksi: VCC, DATA, GND");

    // Kirim status error ke Blynk (V2)
    if (Blynk.connected()) {
      Blynk.virtualWrite(V2, "Sensor ERROR!");
    }

    return;  // Skip pengiriman data
  }

  // Pembacaan berhasil, tampilkan di Serial Monitor
  Serial.println("----------------------------------------");
  Serial.print("[DHT11] Suhu: ");
  Serial.print(suhu);
  Serial.println(" °C");

  Serial.print("[DHT11] Kelembapan: ");
  Serial.print(kelembapan);
  Serial.println(" %");

  // Kirim data ke Blynk (jika terkoneksi)
  if (Blynk.connected()) {
    // Kirim suhu ke V0
    Blynk.virtualWrite(V0, suhu);

    // Kirim kelembapan ke V1
    Blynk.virtualWrite(V1, kelembapan);

    // Kirim status OK ke V2
    Blynk.virtualWrite(V2, "Sensor OK");

    Serial.println("[Blynk] Data terkirim ke app");
  } else {
    Serial.println("[Blynk] Disconnected, data tidak terkirim");
  }

  Serial.println("----------------------------------------");
}

// ===== FUNGSI: CEK STATUS KONEKSI =====
void checkConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[WiFi] Disconnected!");
    return;
  }

  if (!Blynk.connected()) {
    Serial.println("[Blynk] Disconnected! Mencoba reconnect...");
  } else {
    Serial.println("[Status] WiFi OK, Blynk OK");
    Serial.print("[WiFi] IP: ");
    Serial.println(WiFi.localIP());
  }
}

// ===== FUNGSI BLYNK: EVENT SAAT TERKONEKSI =====
BLYNK_CONNECTED() {
  Serial.println();
  Serial.println("========================================");
  Serial.println("   ✓ BLYNK CONNECTED!");
  Serial.println("========================================");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Serial.println("Monitoring dimulai...");
  Serial.println("Buka Blynk app untuk melihat data real-time!");
  Serial.println("========================================");
}
