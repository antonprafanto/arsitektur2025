/*
  ===================================================================
  PRAKTIKUM 10: BLYNK LED CONTROL - Kontrol LED via Smartphone
  ===================================================================

  Deskripsi:
  Program ini mendemonstrasikan kontrol LED melalui smartphone
  menggunakan platform Blynk IoT. LED bisa dikendalikan dari mana
  saja (selama ESP32 dan smartphone terkoneksi internet).

  Fitur:
  - Kontrol LED ON/OFF via Blynk app
  - LED indikator status WiFi
  - Status koneksi di Serial Monitor
  - Auto-reconnect WiFi & Blynk

  Komponen yang Dibutuhkan:
  - 1x ESP32 Development Board
  - 1x LED (warna bebas)
  - 1x Resistor 220Ω
  - Kabel jumper

  Koneksi Rangkaian:
  LED Anode (+)  --->  Resistor 220Ω  --->  ESP32 GPIO4
  LED Cathode (-) --->  ESP32 GND

  (LED built-in ESP32 ada di GPIO2, jadi bisa langsung
   pakai LED built-in tanpa LED eksternal)

  Library yang Diperlukan:
  - WiFi (built-in ESP32)
  - Blynk (by Volodymyr Shymanskyy)
    Install via: Sketch > Include Library > Manage Libraries
    Cari "Blynk" dan install yang by Volodymyr Shymanskyy

  Setup Blynk (PENTING!):
  ⚠️  Setup HARUS via Blynk Console (web): https://blynk.cloud
      Bukan hanya via app! App hanya untuk monitoring.

  1. Download app "Blynk IoT" (bukan "Blynk Legacy")
  2. Buat akun baru di app
  3. [Via WEB] Buka browser → https://blynk.cloud → Login
  4. [Via WEB] Buat Template baru:
     - Klik "Templates" (sidebar kiri) → "+ New Template"
     - Name: "LED Control"
     - Hardware: ESP32
     - Connection: WiFi
     - Klik "Done"
  5. [Via WEB] Buat Datastream:
     - Masuk ke Template "LED Control"
     - Tab "Datastreams" → "+ New Datastream" → "Virtual Pin"
     - Name: "LED Status"
     - Pin: V0
     - Data Type: Integer
     - Min: 0, Max: 1
     - Klik "Create"
  6. [Via WEB] Tambah Button Widget:
     - Tab "Web Dashboard" atau "Mobile Dashboard"
     - Drag "Button" widget ke canvas
     - Linked to: V0 (LED Status)
     - Mode: Switch (bukan Push)
     - ON Label: "LED ON"
     - OFF Label: "LED OFF"
     - Klik "Save"
  7. [Via WEB] Buat Device dari template:
     - Klik "Devices" (sidebar kiri) → "+ New Device" → "From Template"
     - Pilih template "LED Control"
     - Device Name: "ESP32_LED"
     - Klik "Create"
  8. [Via WEB] COPY Auth Token:
     - Klik device yang baru dibuat
     - Tab "Device Info"
     - Klik icon copy (⎘) di samping BLYNK_AUTH_TOKEN
     - Paste ke line 96 di bawah (ganti "TMPL4xxxxxxxxx")!

  💡 TIP: Auth Token lebih mudah di-copy via web console!
  📖 Panduan lengkap: Lihat MATERI-PERTEMUAN-4.md Bagian 2B

  Cara Menggunakan:
  1. Ubah BLYNK_TEMPLATE_ID, BLYNK_TEMPLATE_NAME, BLYNK_AUTH_TOKEN
  2. Ubah ssid dan pass sesuai WiFi Anda
  3. Upload kode ke ESP32
  4. Buka Serial Monitor (115200 baud)
  5. Tunggu hingga "Blynk Connected"
  6. Buka Blynk app, tekan button
  7. LED akan nyala/mati sesuai button!

  Dibuat untuk: Mata Kuliah Bangunan Cerdas
  Instruktur: Anton Prafanto
  ===================================================================
*/

// ===== BLYNK CREDENTIALS =====
// PENTING: Harus di PALING ATAS sebelum #include!
// GANTI dengan credentials dari Blynk Console Anda!
#define BLYNK_TEMPLATE_ID "TMPL4xxxxxxxxx"
#define BLYNK_TEMPLATE_NAME "LED Control"
#define BLYNK_AUTH_TOKEN "abcdefgh123456789ijklmnopqrstuv"

// Print debug ke Serial Monitor (opsional, bisa di-comment jika tidak perlu)
#define BLYNK_PRINT Serial

// ===== INCLUDE LIBRARY =====
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
// Library WiFi untuk koneksi ke internet
// Library Blynk untuk komunikasi dengan Blynk cloud

// ===== WIFI CREDENTIALS =====
// GANTI dengan nama dan password WiFi Anda!
char ssid[] = "NAMA_WIFI_ANDA";        // Nama WiFi (case sensitive!)
char pass[] = "PASSWORD_WIFI_ANDA";    // Password WiFi

// ===== PIN DEFINITIONS =====
#define LED_PIN 2       // LED yang dikontrol (GPIO2 = LED built-in ESP32)
#define LED_STATUS 4    // LED indikator status koneksi (GPIO4)

// ===== VARIABEL GLOBAL =====
unsigned long lastReconnect = 0;  // Timer untuk cek reconnect
const long reconnectInterval = 10000;  // Cek setiap 10 detik

// ===== FUNGSI SETUP =====
void setup() {
  // Inisialisasi Serial Monitor
  Serial.begin(115200);
  delay(100);  // Tunggu Serial Monitor stabil

  Serial.println();
  Serial.println("========================================");
  Serial.println("   BLYNK LED CONTROL - PRAKTIKUM 10");
  Serial.println("========================================");
  Serial.println();

  // Setup pin LED sebagai output
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_STATUS, OUTPUT);

  // Matikan LED di awal
  digitalWrite(LED_PIN, LOW);
  digitalWrite(LED_STATUS, LOW);

  // Koneksi ke Blynk (otomatis connect WiFi & Blynk)
  Serial.println("Menghubungkan ke WiFi dan Blynk...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  // Blynk.begin() akan:
  // 1. Connect ke WiFi
  // 2. Connect ke Blynk server
  // 3. Setup auto-reconnect
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println();
  Serial.println("Setup selesai!");
  Serial.println("Cek status koneksi di bawah...");
  Serial.println("========================================");
}

// ===== FUNGSI LOOP =====
void loop() {
  // WAJIB! Blynk.run() handle komunikasi dengan Blynk server
  // Harus dipanggil sesering mungkin (jangan ada delay lama!)
  Blynk.run();

  // Cek status koneksi setiap 10 detik
  if (millis() - lastReconnect >= reconnectInterval) {
    lastReconnect = millis();
    checkConnection();
  }

  // Update LED status (indikator koneksi)
  if (Blynk.connected()) {
    digitalWrite(LED_STATUS, HIGH);  // LED status ON = terkoneksi
  } else {
    digitalWrite(LED_STATUS, LOW);   // LED status OFF = tidak terkoneksi
  }
}

// ===== FUNGSI BLYNK: TERIMA DATA DARI APP =====
// Fungsi ini dipanggil otomatis saat button V0 di-tap di app
BLYNK_WRITE(V0) {
  // Ambil nilai dari button (0=OFF, 1=ON)
  int buttonValue = param.asInt();

  // Kontrol LED sesuai nilai button
  if (buttonValue == 1) {
    // Button ON
    digitalWrite(LED_PIN, HIGH);  // Nyalakan LED
    Serial.println("[Blynk] LED ON (dari app)");
  } else {
    // Button OFF
    digitalWrite(LED_PIN, LOW);   // Matikan LED
    Serial.println("[Blynk] LED OFF (dari app)");
  }
}

// ===== FUNGSI BLYNK: EVENT SAAT TERKONEKSI =====
// Fungsi ini dipanggil otomatis saat ESP32 berhasil connect ke Blynk
BLYNK_CONNECTED() {
  Serial.println();
  Serial.println("========================================");
  Serial.println("   ✓ BLYNK CONNECTED!");
  Serial.println("========================================");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Serial.println("Sekarang Anda bisa kontrol LED dari app!");
  Serial.println("Buka Blynk app dan tekan button.");
  Serial.println("========================================");

  // Sync status button dari server (ambil nilai terakhir)
  // Berguna jika ESP32 restart tapi button di app masih ON
  Blynk.syncVirtual(V0);
}

// ===== FUNGSI: CEK STATUS KONEKSI =====
void checkConnection() {
  // Cek WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[WiFi] Disconnected!");
    return;
  }

  // Cek Blynk
  if (!Blynk.connected()) {
    Serial.println("[Blynk] Disconnected!");
    Serial.println("[Blynk] Mencoba reconnect...");
  } else {
    Serial.println("[Status] WiFi OK, Blynk OK");
  }
}
