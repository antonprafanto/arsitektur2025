/*
  ===================================================================
  PRAKTIKUM 3: SISTEM SMART ROOM TERINTEGRASI
  ===================================================================

  Deskripsi:
  Program ini mengintegrasikan semua sensor dan aktuator menjadi
  sistem "Smart Room" otomatis yang lengkap.

  Komponen yang Digunakan:
  INPUT (Sensor):
  - DHT11: Suhu & kelembapan
  - LDR: Intensitas cahaya
  - PIR: Deteksi kehadiran/gerakan

  OUTPUT (Aktuator):
  - Relay 1: Lampu (LED simulasi)
  - Relay 2: AC/Kipas (LED simulasi)
  - OLED Display: Tampilkan status
  - Buzzer: Alarm suhu ekstrem

  Logika Sistem Smart Room:
  1. LAMPU (Relay 1): Nyala jika GELAP + ADA ORANG
  2. AC (Relay 2): Nyala jika PANAS (>28°C) + ADA ORANG
  3. BUZZER: Bunyi jika suhu ekstrem (>35°C)
  4. OLED: Tampilkan semua data sensor + status aktuator
  5. Hemat energi: Semua mati jika tidak ada orang

  Koneksi Rangkaian:
  DHT11: VCC(3.3V), DATA(GPIO15), GND
  LDR: 3.3V - LDR - GPIO34 - 10KΩ - GND
  PIR: VCC(5V), OUT(GPIO13), GND
  Relay 1 (Lampu): VCC(5V), GND, IN1(GPIO25)
  Relay 2 (AC): VCC(5V), GND, IN2(GPIO26)
  OLED: VCC(3.3V), GND, SDA(GPIO21), SCL(GPIO22)
  Buzzer: GPIO12, GND

  Library yang Diperlukan:
  - DHT sensor library
  - Adafruit SSD1306
  - Adafruit GFX Library

  Dibuat untuk: Mata Kuliah Bangunan Cerdas
  Instruktur: Anton Prafanto
  ===================================================================
*/

// ===== INCLUDE LIBRARY =====
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// ===== KONFIGURASI OLED =====
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ===== KONFIGURASI DHT11 =====
#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ===== KONFIGURASI PIN =====
const int pinLDR = 34;        // Sensor cahaya
const int pinPIR = 13;        // Sensor gerak
const int pinRelayLampu = 25; // Relay 1 - Lampu
const int pinRelayAC = 26;    // Relay 2 - AC
const int pinBuzzer = 12;     // Buzzer alarm

// ===== THRESHOLD & PARAMETER =====
// Suhu
const float SUHU_AC_NYALA = 28.0;
const float SUHU_AC_MATI = 26.0;
const float SUHU_EKSTREM = 35.0;  // Alarm

// Cahaya
const int CAHAYA_GELAP = 2500;

// Kelembapan (untuk informasi saja)
const float KELEMBAPAN_TINGGI = 70.0;

// ===== VARIABEL STATUS =====
bool statusLampu = false;
bool statusAC = false;
bool statusBuzzer = false;
bool adaOrang = false;

// Statistik
unsigned long waktuMulai = 0;
int jumlahDeteksiOrang = 0;

// ===== FUNGSI SETUP =====
void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("========================================");
  Serial.println("     SISTEM SMART ROOM OTOMATIS        ");
  Serial.println("========================================");
  Serial.println();

  // Konfigurasi pin
  pinMode(pinPIR, INPUT);
  pinMode(pinRelayLampu, OUTPUT);
  pinMode(pinRelayAC, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);

  // Matikan semua aktuator di awal
  digitalWrite(pinRelayLampu, LOW);
  digitalWrite(pinRelayAC, LOW);
  digitalWrite(pinBuzzer, LOW);

  // Inisialisasi OLED
  Serial.print("Inisialisasi OLED...");
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(" GAGAL!");
    while (1);
  }
  Serial.println(" OK!");

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Splash screen
  tampilSplash();
  delay(2000);

  // Inisialisasi DHT11
  Serial.print("Inisialisasi DHT11...");
  dht.begin();
  Serial.println(" OK!");

  // Kalibrasi PIR
  Serial.println("Kalibrasi sensor PIR (30 detik)...");
  Serial.println("Jangan bergerak!");

  for (int i = 30; i > 0; i--) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("KALIBRASI PIR");
    display.println();
    display.setTextSize(2);
    display.setCursor(50, 25);
    display.println(i);
    display.setTextSize(1);
    display.setCursor(10, 50);
    display.println("Jangan bergerak!");
    display.display();
    delay(1000);
  }

  Serial.println("Kalibrasi selesai!");
  Serial.println("========================================");
  Serial.println("Sistem AKTIF!");
  Serial.println();

  waktuMulai = millis();
}

// ===== FUNGSI LOOP =====
void loop() {

  // ===== STEP 1: BACA SEMUA SENSOR =====
  float suhu = dht.readTemperature();
  float kelembapan = dht.readHumidity();
  int nilaiLDR = analogRead(pinLDR);
  int statusPIR = digitalRead(pinPIR);

  // Validasi DHT11
  if (isnan(suhu) || isnan(kelembapan)) {
    tampilError("Sensor DHT11 Error!");
    delay(2000);
    return;
  }

  // ===== STEP 2: DETEKSI KEHADIRAN =====
  if (statusPIR == HIGH && !adaOrang) {
    adaOrang = true;
    jumlahDeteksiOrang++;
    Serial.println("👤 ADA ORANG TERDETEKSI!");
  } else if (statusPIR == LOW && adaOrang) {
    adaOrang = false;
    Serial.println("🚶 ORANG PERGI");
  }

  // ===== STEP 3: ANALISIS KONDISI =====
  bool gelap = (nilaiLDR > CAHAYA_GELAP);
  bool panas = (suhu >= SUHU_AC_NYALA);
  bool panasEkstrem = (suhu >= SUHU_EKSTREM);

  // ===== STEP 4: KONTROL LAMPU =====
  // Logika: Nyala jika GELAP + ADA ORANG
  bool lampuSeharusnya = (gelap && adaOrang);

  if (lampuSeharusnya && !statusLampu) {
    digitalWrite(pinRelayLampu, HIGH);
    statusLampu = true;
    Serial.println("💡 LAMPU DINYALAKAN");
  } else if (!lampuSeharusnya && statusLampu) {
    digitalWrite(pinRelayLampu, LOW);
    statusLampu = false;
    Serial.println("💡 LAMPU DIMATIKAN");
  }

  // ===== STEP 5: KONTROL AC =====
  // Logika: Nyala jika PANAS + ADA ORANG
  bool acSeharusnya = false;

  if (panas && adaOrang) {
    acSeharusnya = true;
  } else if (suhu <= SUHU_AC_MATI) {
    acSeharusnya = false;
  }
  // Jika tidak ada orang, AC selalu mati
  if (!adaOrang) {
    acSeharusnya = false;
  }

  if (acSeharusnya && !statusAC) {
    digitalWrite(pinRelayAC, HIGH);
    statusAC = true;
    Serial.println("❄️ AC DINYALAKAN");
  } else if (!acSeharusnya && statusAC) {
    digitalWrite(pinRelayAC, LOW);
    statusAC = false;
    Serial.println("❄️ AC DIMATIKAN");
  }

  // ===== STEP 6: ALARM SUHU EKSTREM =====
  if (panasEkstrem && !statusBuzzer) {
    statusBuzzer = true;
    Serial.println("🚨 ALARM! SUHU EKSTREM!");
  } else if (!panasEkstrem && statusBuzzer) {
    statusBuzzer = false;
    digitalWrite(pinBuzzer, LOW);
  }

  // Kontrol buzzer beep
  if (statusBuzzer) {
    static unsigned long lastBeep = 0;
    static bool beepState = false;

    if (millis() - lastBeep > 500) {
      beepState = !beepState;
      digitalWrite(pinBuzzer, beepState ? HIGH : LOW);
      lastBeep = millis();
    }
  }

  // ===== STEP 7: TAMPILKAN KE OLED =====
  tampilDashboard(suhu, kelembapan, nilaiLDR, adaOrang);

  // ===== STEP 8: LOG KE SERIAL MONITOR =====
  Serial.print("Suhu: ");
  Serial.print(suhu, 1);
  Serial.print("°C | RH: ");
  Serial.print(kelembapan, 1);
  Serial.print("% | Cahaya: ");
  Serial.print(gelap ? "GELAP" : "TERANG");
  Serial.print(" | Orang: ");
  Serial.print(adaOrang ? "ADA" : "TIDAK");
  Serial.print(" | Lampu: ");
  Serial.print(statusLampu ? "ON" : "OFF");
  Serial.print(" | AC: ");
  Serial.println(statusAC ? "ON" : "OFF");

  delay(1000);  // Update setiap 1 detik
}

// ===== FUNGSI TAMPIL SPLASH =====
void tampilSplash() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(10, 5);
  display.println("SMART");
  display.setCursor(20, 25);
  display.println("ROOM");
  display.setTextSize(1);
  display.setCursor(15, 50);
  display.println("Initializing...");
  display.display();
}

// ===== FUNGSI TAMPIL DASHBOARD =====
void tampilDashboard(float suhu, float kelembapan, int cahaya, bool orang) {
  display.clearDisplay();

  // Header
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("== SMART ROOM ==");

  // Baris 1: Suhu
  display.setCursor(0, 10);
  display.print("T:");
  display.print(suhu, 1);
  display.print((char)247);
  display.print("C");

  // Status AC
  display.setCursor(70, 10);
  display.print("AC:");
  display.print(statusAC ? "ON" : "OFF");

  // Baris 2: Kelembapan
  display.setCursor(0, 20);
  display.print("H:");
  display.print(kelembapan, 0);
  display.print("%");

  // Status Lampu
  display.setCursor(70, 20);
  display.print("LP:");
  display.print(statusLampu ? "ON" : "OFF");

  // Baris 3: Cahaya
  display.setCursor(0, 30);
  display.print("L:");
  display.print(cahaya > CAHAYA_GELAP ? "GELAP" : "TERANG");

  // Baris 4: Kehadiran
  display.setCursor(0, 40);
  display.print("Orang: ");
  if (orang) {
    display.println("ADA");
  } else {
    display.println("TIDAK");
  }

  // Baris 5: Alarm jika ada
  if (statusBuzzer) {
    display.setTextSize(1);
    display.setCursor(0, 52);
    display.println("!!! SUHU EKSTREM !!!");
  }

  // Statistik
  display.setCursor(0, 56);
  display.print("Det:");
  display.print(jumlahDeteksiOrang);

  // Uptime
  unsigned long uptime = (millis() - waktuMulai) / 1000;
  display.setCursor(60, 56);
  display.print("T:");
  display.print(uptime / 60);
  display.print("m");

  display.display();
}

// ===== FUNGSI TAMPIL ERROR =====
void tampilError(String pesan) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("ERROR!");
  display.println();
  display.println(pesan);
  display.display();

  Serial.println("ERROR: " + pesan);
}

/*
  ===================================================================
  PENJELASAN SISTEM INTEGRASI:
  ===================================================================

  1. ARSITEKTUR SISTEM:

     LAYER INPUT (Sensing):
     ├── DHT11 → Suhu & Kelembapan
     ├── LDR → Intensitas Cahaya
     └── PIR → Kehadiran Manusia

     LAYER PROCESSING (Decision):
     ├── ESP32 → Algoritma kontrol
     ├── Threshold & Hysteresis
     └── Logika berbasis kondisi

     LAYER OUTPUT (Actuation):
     ├── Relay 1 → Lampu
     ├── Relay 2 → AC
     ├── OLED → Display
     └── Buzzer → Alarm

  2. LOGIKA HEMAT ENERGI:
     - Prinsip: Perangkat hanya nyala saat DIBUTUHKAN
     - Lampu: Hanya saat gelap + ada orang
     - AC: Hanya saat panas + ada orang
     - Jika ruangan kosong (tidak ada orang) → semua mati
     - Potensi penghematan: 30-50% konsumsi energi

  3. PRIORITAS KEAMANAN:
     - Alarm suhu ekstrem (>35°C) → risiko kebakaran
     - Buzzer bunyi kontinyu hingga suhu turun
     - Bisa dikembangkan: kirim notifikasi ke smartphone
     - Log event untuk analisis

  4. USER EXPERIENCE:
     - OLED display menunjukkan status real-time
     - User bisa monitor tanpa buka app
     - Otomatis tapi tetap transparan
     - Statistik: jumlah deteksi, uptime

  5. SKALABILITAS:
     - Mudah tambah sensor baru (gas, suara, dll)
     - Mudah tambah aktuator (motor, solenoid)
     - Modular: setiap fungsi terpisah
     - Bisa integrasikan dengan cloud (IoT platform)

  ===================================================================
  FLOW CHART SISTEM:
  ===================================================================

  [START]
     ↓
  Inisialisasi semua sensor & aktuator
     ↓
  Kalibrasi PIR (30 detik)
     ↓
  ┌─────── LOOP ───────┐
  │                    │
  │ Baca DHT11         │
  │ Baca LDR           │
  │ Baca PIR           │
  │                    │
  │ Analisis kondisi:  │
  │ - Gelap?           │
  │ - Panas?           │
  │ - Ada orang?       │
  │                    │
  │ Kontrol Lampu:     │
  │ IF gelap + orang   │
  │ THEN nyala         │
  │                    │
  │ Kontrol AC:        │
  │ IF panas + orang   │
  │ THEN nyala         │
  │                    │
  │ Cek Alarm:         │
  │ IF suhu > 35°C     │
  │ THEN buzzer ON     │
  │                    │
  │ Update OLED        │
  │ Log Serial         │
  │                    │
  │ Delay 1 detik      │
  │                    │
  └────────────────────┘

  ===================================================================
  PENGEMBANGAN LEBIH LANJUT:
  ===================================================================

  1. KONEKTIVITAS IoT:
     - WiFi: Kirim data ke server/cloud
     - MQTT: Protokol IoT standar
     - Blynk/Telegram: Notifikasi smartphone
     - Web dashboard: Monitor dari browser

  2. MACHINE LEARNING:
     - Pola penggunaan ruangan
     - Prediksi kapan ruangan akan terisi
     - Pre-cooling: AC nyala sebelum orang datang
     - Optimasi threshold otomatis

  3. INTEGRASI DENGAN SMART HOME:
     - Google Home / Alexa voice control
     - Scene/Routine: "Good morning", "Good night"
     - Geofencing: AC nyala otomatis saat hampir sampai rumah
     - Integrasi dengan kalender (meeting room)

  4. FITUR TAMBAHAN:
     - Sensor kualitas udara (CO2, VOC)
     - Kontrol tirai/blind otomatis
     - Sistem audio (speaker)
     - Kamera keamanan + face recognition

  5. ENERGY MONITORING:
     - Sensor arus (ACS712) untuk ukur konsumsi
     - Hitung biaya listrik real-time
     - Laporan harian/bulanan
     - Tips hemat energi

  ===================================================================
  APLIKASI REAL-WORLD:
  ===================================================================

  1. RUMAH TINGGAL:
     - Kamar tidur: AC otomatis saat tidur
     - Ruang tamu: Lampu + AC saat ada tamu
     - Kamar mandi: Exhaust fan otomatis

  2. KANTOR:
     - Meeting room: Sistem booking + auto AC/lampu
     - Open space: Zone control (area terpakai saja)
     - Pantry: Lampu otomatis

  3. HOTEL:
     - Kamar tamu: Auto saat check-in
     - Mati semua saat checkout/keluar
     - Hemat energi masif (ratusan kamar)

  4. RUMAH SAKIT:
     - ICU: Monitor suhu ketat
     - Ruang operasi: Kontrol suhu presisi
     - Ruang isolasi: Tekanan udara negatif

  5. SEKOLAH/KAMPUS:
     - Ruang kelas: Hemat saat kosong
     - Laboratorium: Kontrol suhu/kelembapan
     - Perpustakaan: Kenyamanan optimal

  ===================================================================
  TIPS DEPLOYMENT:
  ===================================================================

  1. TESTING MENYELURUH:
     - Test setiap sensor individual
     - Test setiap aktuator individual
     - Test kombinasi sensor
     - Test edge case (kondisi ekstrem)

  2. KALIBRASI:
     - Sesuaikan threshold dengan lokasi
     - Test di kondisi real (siang, malam)
     - Libatkan user untuk feedback

  3. DOKUMENTASI:
     - Wiring diagram jelas
     - Panduan troubleshooting
     - Manual user sederhana
     - Kontak support

  4. MAINTENANCE:
     - Bersihkan sensor berkala (debu)
     - Cek koneksi (longgar?)
     - Update firmware jika ada bug
     - Monitoring log error

  5. SAFETY:
     - Isolasi kabel AC dengan baik
     - Pasang MCB untuk proteksi
     - Grounding yang proper
     - Fire extinguisher siap

  ===================================================================
*/
