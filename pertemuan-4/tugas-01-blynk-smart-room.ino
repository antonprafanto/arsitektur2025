/*
  ===================================================================
  TUGAS 1: BLYNK SMART ROOM DASHBOARD - Room Monitoring System
  ===================================================================

  Deskripsi Tugas:
  Buatlah sistem monitoring ruangan pintar yang menampilkan data
  dari 3 sensor (DHT11, LDR, PIR) ke dalam dashboard Blynk di
  smartphone. Dashboard harus menampilkan data secara real-time
  dan mudah dibaca.

  Target Pembelajaran:
  - Memahami cara integrasi multiple sensor dengan Blynk
  - Membuat dashboard monitoring yang informatif
  - Menggunakan berbagai jenis widget Blynk
  - Implementasi rate limiting untuk efisiensi data

  Komponen yang Dibutuhkan:
  - 1x ESP32 Development Board
  - 1x Sensor DHT11 (Suhu & Kelembapan)
  - 1x Sensor LDR (Cahaya)
  - 1x Sensor PIR HC-SR501 (Gerakan)
  - 1x Resistor 10kΩ (untuk LDR)
  - Kabel jumper

  Koneksi Rangkaian:
  DHT11:
  - VCC   → ESP32 3.3V
  - DATA  → ESP32 GPIO15
  - GND   → ESP32 GND

  LDR (Light Dependent Resistor):
  - Satu kaki → ESP32 3.3V
  - Kaki lain → ESP32 GPIO34 + Resistor 10kΩ ke GND
  (Voltage Divider Circuit)

  PIR HC-SR501:
  - VCC   → ESP32 5V
  - OUT   → ESP32 GPIO25
  - GND   → ESP32 GND

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
     - Name: "Smart Room Monitor"
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
        - Name: "Cahaya"
        - Data Type: Integer
        - Min: 0, Max: 4095
        - Units: Lux
     d. Datastream 4:
        - Virtual Pin: V3
        - Name: "Gerakan"
        - Data Type: Integer
        - Min: 0, Max: 1
     e. Datastream 5:
        - Virtual Pin: V4
        - Name: "Status"
        - Data Type: String

  5. [Via WEB] Tambah Widget ke Dashboard (Tab "Mobile Dashboard"):
     - Gauge widget → Datastream: V0 (Suhu)
     - Value Display widget → Datastream: V1 (Kelembapan)
     - Value Display widget → Datastream: V2 (Cahaya)
     - LED widget → Datastream: V3 (Gerakan)
     - Label widget → Datastream: V4 (Status)

  6. [Via WEB] Buat Device:
     - Klik "Devices" → "+ New Device" → "From Template"
     - Pilih "Smart Room Monitor"
     - Device Name: "ESP32_Smart_Room"
     - Klik "Create"
  7. [Via WEB] Copy Auth Token:
     - Device Info → Copy BLYNK_AUTH_TOKEN (klik icon ⎘)
     - Paste ke line 124 di bawah (ganti "TMPL4xxxxxxxxx")!

  💡 TIP: Auth Token lebih mudah di-copy via web console!
  📖 Panduan lengkap: Lihat MATERI-PERTEMUAN-4.md Bagian 2B

  Kriteria Penilaian:
  ✓ Semua sensor terbaca dengan benar (30%)
  ✓ Data terkirim ke Blynk secara real-time (25%)
  ✓ Dashboard informatif dan mudah dibaca (20%)
  ✓ Kode rapi dengan komentar yang jelas (15%)
  ✓ Error handling yang baik (10%)

  Dibuat untuk: Mata Kuliah Bangunan Cerdas
  Instruktur: Anton Prafanto
  ===================================================================
*/

// ===== BLYNK CREDENTIALS =====
// PENTING: Harus di PALING ATAS sebelum #include!
// GANTI dengan credentials Anda!
#define BLYNK_TEMPLATE_ID "TMPL4xxxxxxxxx"
#define BLYNK_TEMPLATE_NAME "Smart Room Monitor"
#define BLYNK_AUTH_TOKEN "abcdefgh123456789ijklmnopqrstuv"
#define BLYNK_PRINT Serial

// ===== INCLUDE LIBRARY =====
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// ===== WIFI CREDENTIALS =====
char ssid[] = "NAMA_WIFI_ANDA";
char pass[] = "PASSWORD_WIFI_ANDA";

// ===== PIN DEFINITIONS =====
#define DHTPIN 15       // DHT11 DATA pin
#define DHTTYPE DHT11   // Tipe sensor DHT11
#define LDR_PIN 34      // LDR Analog pin (ADC1_CH6)
#define PIR_PIN 25      // PIR Digital pin

// ===== INISIALISASI SENSOR =====
DHT dht(DHTPIN, DHTTYPE);

// ===== VIRTUAL PIN BLYNK =====
// V0 = Suhu (°C)
// V1 = Kelembapan (%)
// V2 = Cahaya (0-4095)
// V3 = Gerakan (0=Tidak Ada, 1=Terdeteksi)
// V4 = Status System (String)

// ===== VARIABEL SENSOR =====
float suhu = 0;
float kelembapan = 0;
int cahaya = 0;
bool gerakan = false;

// ===== VARIABEL TIMER =====
unsigned long lastSendTime = 0;
const long sendInterval = 2000;  // Kirim data setiap 2 detik

unsigned long lastCheckTime = 0;
const long checkInterval = 10000;  // Cek koneksi setiap 10 detik

unsigned long motionDetectedTime = 0;
const long motionDisplayTime = 3000;  // Tampilkan gerakan selama 3 detik

// ===== VARIABEL STATUS =====
bool lastMotionState = false;

// ===== FUNGSI SETUP =====
void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.println();
  Serial.println("================================================");
  Serial.println("  TUGAS 1: SMART ROOM DASHBOARD");
  Serial.println("================================================");
  Serial.println();

  // Setup pin sensor
  pinMode(PIR_PIN, INPUT);

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
  Serial.println("Monitoring ruangan dimulai...");
  Serial.println("================================================");
}

// ===== FUNGSI LOOP =====
void loop() {
  // Handle komunikasi Blynk
  Blynk.run();

  // Baca sensor dan kirim ke Blynk setiap 2 detik
  if (millis() - lastSendTime >= sendInterval) {
    lastSendTime = millis();

    bacaSemuaSensor();
    kirimKeBlynk();
    tampilkanSerial();
  }

  // Deteksi gerakan real-time (tidak menunggu interval)
  deteksiGerakan();

  // Cek koneksi setiap 10 detik
  if (millis() - lastCheckTime >= checkInterval) {
    lastCheckTime = millis();
    cekKoneksi();
  }
}

// ===== FUNGSI: BACA SEMUA SENSOR =====
void bacaSemuaSensor() {
  // Baca DHT11 (Suhu & Kelembapan)
  suhu = dht.readTemperature();
  kelembapan = dht.readHumidity();

  // Baca LDR (Cahaya)
  cahaya = analogRead(LDR_PIN);

  // Baca PIR (Gerakan)
  // PIR akan dibaca di fungsi deteksiGerakan() untuk real-time response
}

// ===== FUNGSI: DETEKSI GERAKAN REAL-TIME =====
void deteksiGerakan() {
  bool currentMotion = digitalRead(PIR_PIN);

  // Deteksi perubahan dari LOW ke HIGH (gerakan baru terdeteksi)
  if (currentMotion && !lastMotionState) {
    gerakan = true;
    motionDetectedTime = millis();
    lastMotionState = true;

    Serial.println();
    Serial.println("⚠️  GERAKAN TERDETEKSI!");
    Serial.println();

    // Langsung kirim ke Blynk (tidak menunggu interval)
    if (Blynk.connected()) {
      Blynk.virtualWrite(V3, 1);  // LED ON di app
    }
  }

  // Reset status gerakan setelah 3 detik
  if (gerakan && (millis() - motionDetectedTime >= motionDisplayTime)) {
    gerakan = false;

    if (Blynk.connected()) {
      Blynk.virtualWrite(V3, 0);  // LED OFF di app
    }
  }

  // Update lastMotionState
  if (!currentMotion && lastMotionState) {
    lastMotionState = false;
  }
}

// ===== FUNGSI: KIRIM DATA KE BLYNK =====
void kirimKeBlynk() {
  if (!Blynk.connected()) {
    Serial.println("[Blynk] Disconnected, data tidak terkirim");
    return;
  }

  // Cek apakah pembacaan DHT11 valid
  if (isnan(suhu) || isnan(kelembapan)) {
    Blynk.virtualWrite(V4, "⚠️ Sensor DHT11 ERROR!");
    Serial.println("[DHT11] ERROR: Gagal membaca sensor!");
    Serial.println("        Cek koneksi VCC, DATA, GND");
    return;
  }

  // Kirim Suhu ke V0
  Blynk.virtualWrite(V0, suhu);

  // Kirim Kelembapan ke V1
  Blynk.virtualWrite(V1, kelembapan);

  // Kirim Cahaya ke V2
  Blynk.virtualWrite(V2, cahaya);

  // Status gerakan sudah dikirim real-time di deteksiGerakan()

  // Kirim Status ke V4
  String status = generateStatus();
  Blynk.virtualWrite(V4, status);

  Serial.println("[Blynk] ✓ Data terkirim");
}

// ===== FUNGSI: GENERATE STATUS =====
String generateStatus() {
  String status = "";

  // Status Suhu
  if (suhu < 24) {
    status += "❄️ Sejuk";
  } else if (suhu >= 24 && suhu <= 28) {
    status += "✅ Nyaman";
  } else {
    status += "🔥 Panas";
  }

  status += " | ";

  // Status Cahaya
  if (cahaya < 1000) {
    status += "🌙 Gelap";
  } else if (cahaya >= 1000 && cahaya < 2500) {
    status += "💡 Redup";
  } else {
    status += "☀️ Terang";
  }

  status += " | ";

  // Status Gerakan
  if (gerakan) {
    status += "👤 Ada Orang";
  } else {
    status += "✓ Kosong";
  }

  return status;
}

// ===== FUNGSI: TAMPILKAN DATA DI SERIAL =====
void tampilkanSerial() {
  Serial.println("========================================");
  Serial.print("[DHT11] Suhu: ");
  Serial.print(suhu);
  Serial.println(" °C");

  Serial.print("[DHT11] Kelembapan: ");
  Serial.print(kelembapan);
  Serial.println(" %");

  Serial.print("[LDR]   Cahaya: ");
  Serial.print(cahaya);
  Serial.print(" (");
  if (cahaya < 1000) {
    Serial.print("Gelap");
  } else if (cahaya >= 1000 && cahaya < 2500) {
    Serial.print("Redup");
  } else {
    Serial.print("Terang");
  }
  Serial.println(")");

  Serial.print("[PIR]   Gerakan: ");
  Serial.println(gerakan ? "TERDETEKSI" : "Tidak ada");

  Serial.println("========================================");
}

// ===== FUNGSI: CEK STATUS KONEKSI =====
void cekKoneksi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[WiFi] ⚠️  Disconnected!");
    return;
  }

  if (!Blynk.connected()) {
    Serial.println("[Blynk] ⚠️  Disconnected! Mencoba reconnect...");
  } else {
    Serial.println("[Status] ✓ WiFi OK, Blynk OK");
    Serial.print("[WiFi] IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("[WiFi] Signal: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
  }
}

// ===== FUNGSI BLYNK: EVENT SAAT TERKONEKSI =====
BLYNK_CONNECTED() {
  Serial.println();
  Serial.println("================================================");
  Serial.println("   ✓ BLYNK CONNECTED!");
  Serial.println("================================================");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Serial.println("Smart Room Monitoring aktif!");
  Serial.println("Buka Blynk app untuk melihat dashboard.");
  Serial.println("================================================");

  // Sync semua virtual pin dari server
  Blynk.syncAll();
}

/*
  ===================================================================
  CATATAN UNTUK MAHASISWA:
  ===================================================================

  1. CARA KERJA SISTEM:
     - DHT11 membaca suhu & kelembapan setiap 2 detik
     - LDR membaca intensitas cahaya (nilai 0-4095)
     - PIR mendeteksi gerakan secara real-time
     - Semua data dikirim ke Blynk untuk ditampilkan di dashboard

  2. INTERPRETASI DATA:
     Suhu:
     - < 24°C = Sejuk
     - 24-28°C = Nyaman
     - > 28°C = Panas

     Cahaya:
     - < 1000 = Gelap (lampu perlu dinyalakan)
     - 1000-2500 = Redup (cahaya cukup)
     - > 2500 = Terang (cahaya berlebih)

     Gerakan:
     - 0 = Tidak ada gerakan (ruangan kosong)
     - 1 = Gerakan terdeteksi (ada orang)

  3. TROUBLESHOOTING:
     - DHT11 ERROR → Cek koneksi VCC, DATA, GND
     - LDR selalu 0 → Cek resistor 10kΩ, pastikan tegangan 3.3V
     - PIR tidak deteksi → Cek jumper sensitivity & delay di modul
     - Blynk offline → Cek WiFi, Auth Token, koneksi internet

  4. PENGEMBANGAN LEBIH LANJUT:
     - Tambahkan notifikasi jika suhu > 30°C
     - Tambahkan kontrol lampu otomatis berdasarkan LDR
     - Tambahkan grafik historis di Blynk Chart widget
     - Integrasikan dengan relay untuk kontrol AC

  ===================================================================
*/
