/*
  ===================================================================
  PRAKTIKUM 1: KONTROL RELAY BERDASARKAN SENSOR DHT11
  ===================================================================

  Deskripsi:
  Program ini mensimulasikan sistem HVAC (Heating, Ventilation, Air
  Conditioning) otomatis menggunakan relay yang dikontrol berdasarkan
  data suhu dan kelembapan dari sensor DHT11.

  Logika Sistem:
  - Relay 1 (simulasi AC): Nyala jika suhu > 28°C
  - Relay 2 (simulasi Exhaust Fan): Nyala jika kelembapan > 70%
  - Menggunakan hysteresis untuk mencegah relay flicker

  Komponen yang Dibutuhkan:
  - 1x ESP32 Development Board
  - 1x Sensor DHT11
  - 1x Relay Module 2 Channel
  - 2x LED (sebagai simulasi perangkat AC)
  - 2x Resistor 220 ohm
  - Kabel jumper
  - Breadboard

  Koneksi Rangkaian:
  DHT11:
  VCC  --->  ESP32 3.3V
  DATA --->  ESP32 GPIO15
  GND  --->  ESP32 GND

  Relay Module:
  VCC  --->  ESP32 5V
  GND  --->  ESP32 GND
  IN1  --->  ESP32 GPIO25 (kontrol Relay 1 - AC)
  IN2  --->  ESP32 GPIO26 (kontrol Relay 2 - Fan)

  LED Simulasi (opsional, untuk testing tanpa beban AC):
  Relay 1 COM --->  LED1 (+) --->  Resistor 220Ω --->  GND
  Relay 2 COM --->  LED2 (+) --->  Resistor 220Ω --->  GND

  PERINGATAN KEAMANAN:
  ⚠️ Untuk praktikum, gunakan LED sebagai simulasi!
  ⚠️ Jangan hubungkan perangkat AC 220V tanpa supervisi!
  ⚠️ Relay module bisa menangani 220V, tapi berbahaya!

  Library yang Diperlukan:
  - DHT sensor library (by Adafruit)

  Dibuat untuk: Mata Kuliah Bangunan Cerdas
  Instruktur: Anton Prafanto
  ===================================================================
*/

// ===== INCLUDE LIBRARY =====
#include <DHT.h>

// ===== KONFIGURASI PIN =====
#define DHTPIN 15         // Pin DHT11
#define DHTTYPE DHT11     // Tipe sensor

const int pinRelay1 = 25; // Relay 1 - AC/Cooler
const int pinRelay2 = 26; // Relay 2 - Exhaust Fan

// ===== KONFIGURASI THRESHOLD =====
// Threshold dengan hysteresis untuk mencegah relay flicker

// SUHU (untuk AC):
const float SUHU_NYALA = 28.0;   // AC nyala jika suhu >= 28°C
const float SUHU_MATI = 26.0;    // AC mati jika suhu <= 26°C
// Hysteresis = 2°C (gap antara nyala dan mati)

// KELEMBAPAN (untuk Exhaust Fan):
const float KELEMBAPAN_NYALA = 70.0;  // Fan nyala jika RH >= 70%
const float KELEMBAPAN_MATI = 65.0;   // Fan mati jika RH <= 65%
// Hysteresis = 5% (gap antara nyala dan mati)

// ===== OBJEK DHT =====
DHT dht(DHTPIN, DHTTYPE);

// ===== VARIABEL STATUS =====
bool statusRelay1 = false;  // Status AC (false = mati, true = nyala)
bool statusRelay2 = false;  // Status Fan (false = mati, true = nyala)

// ===== FUNGSI SETUP =====
void setup() {
  // Inisialisasi Serial Monitor
  Serial.begin(115200);
  delay(1000);

  Serial.println("========================================");
  Serial.println("  SISTEM HVAC OTOMATIS BERBASIS IoT    ");
  Serial.println("========================================");
  Serial.println();

  // Konfigurasi pin relay sebagai OUTPUT
  pinMode(pinRelay1, OUTPUT);
  pinMode(pinRelay2, OUTPUT);

  // Matikan relay di awal (relay aktif LOW pada kebanyakan module)
  // Catatan: Beberapa relay module aktif HIGH, sesuaikan jika perlu
  digitalWrite(pinRelay1, LOW);
  digitalWrite(pinRelay2, LOW);

  // Inisialisasi sensor DHT
  dht.begin();

  Serial.println("✅ Sistem diinisialisasi");
  Serial.println();
  Serial.println("Konfigurasi Threshold:");
  Serial.println("----------------------");
  Serial.print("AC nyala    : Suhu >= ");
  Serial.print(SUHU_NYALA);
  Serial.println(" °C");
  Serial.print("AC mati     : Suhu <= ");
  Serial.print(SUHU_MATI);
  Serial.println(" °C");
  Serial.println();
  Serial.print("Fan nyala   : RH >= ");
  Serial.print(KELEMBAPAN_NYALA);
  Serial.println(" %");
  Serial.print("Fan mati    : RH <= ");
  Serial.print(KELEMBAPAN_MATI);
  Serial.println(" %");
  Serial.println("========================================");
  Serial.println();
  Serial.println("Monitoring dimulai...");
  Serial.println();

  delay(2000);  // Settling time untuk DHT11
}

// ===== FUNGSI LOOP =====
void loop() {

  // LANGKAH 1: Baca data dari sensor DHT11
  float kelembapan = dht.readHumidity();
  float suhu = dht.readTemperature();

  // LANGKAH 2: Validasi data sensor
  if (isnan(kelembapan) || isnan(suhu)) {
    Serial.println("❌ Error: Gagal membaca sensor DHT11!");
    Serial.println("   Cek koneksi sensor...");
    Serial.println();
    delay(2000);
    return;  // Skip loop ini dan coba lagi
  }

  // LANGKAH 3: Logika kontrol Relay 1 (AC) dengan HYSTERESIS
  if (suhu >= SUHU_NYALA && !statusRelay1) {
    // Kondisi: Suhu panas DAN AC belum nyala
    digitalWrite(pinRelay1, HIGH);  // Nyalakan relay
    statusRelay1 = true;

    Serial.println("🔴 AC DINYALAKAN (Suhu tinggi)");
  }
  else if (suhu <= SUHU_MATI && statusRelay1) {
    // Kondisi: Suhu sudah turun DAN AC masih nyala
    digitalWrite(pinRelay1, LOW);   // Matikan relay
    statusRelay1 = false;

    Serial.println("🔵 AC DIMATIKAN (Suhu normal)");
  }

  // LANGKAH 4: Logika kontrol Relay 2 (Exhaust Fan) dengan HYSTERESIS
  if (kelembapan >= KELEMBAPAN_NYALA && !statusRelay2) {
    // Kondisi: Kelembapan tinggi DAN fan belum nyala
    digitalWrite(pinRelay2, HIGH);  // Nyalakan relay
    statusRelay2 = true;

    Serial.println("💨 EXHAUST FAN DINYALAKAN (Kelembapan tinggi)");
  }
  else if (kelembapan <= KELEMBAPAN_MATI && statusRelay2) {
    // Kondisi: Kelembapan sudah turun DAN fan masih nyala
    digitalWrite(pinRelay2, LOW);   // Matikan relay
    statusRelay2 = false;

    Serial.println("💨 EXHAUST FAN DIMATIKAN (Kelembapan normal)");
  }

  // LANGKAH 5: Tampilkan data sensor dan status sistem
  tampilkanStatus(suhu, kelembapan);

  // LANGKAH 6: Tunggu 3 detik sebelum pembacaan berikutnya
  delay(3000);
}

// ===== FUNGSI TAMPILKAN STATUS =====
void tampilkanStatus(float suhu, float kelembapan) {
  Serial.println("┌─────────────────────────────────────┐");
  Serial.println("│     STATUS SISTEM HVAC OTOMATIS     │");
  Serial.println("├─────────────────────────────────────┤");

  // Data Sensor
  Serial.print("│ Suhu          : ");
  Serial.print(suhu, 1);
  Serial.print(" °C");
  if (suhu >= SUHU_NYALA) {
    Serial.println("  🔥 PANAS     │");
  } else if (suhu <= SUHU_MATI) {
    Serial.println("  ❄️  DINGIN    │");
  } else {
    Serial.println("  ✅ NORMAL    │");
  }

  Serial.print("│ Kelembapan    : ");
  Serial.print(kelembapan, 1);
  Serial.print(" %");
  if (kelembapan >= KELEMBAPAN_NYALA) {
    Serial.println("   💧 LEMBAP    │");
  } else if (kelembapan <= KELEMBAPAN_MATI) {
    Serial.println("   ☀️  KERING    │");
  } else {
    Serial.println("   ✅ NORMAL    │");
  }

  Serial.println("├─────────────────────────────────────┤");

  // Status Aktuator
  Serial.print("│ AC (Relay 1)  : ");
  Serial.println(statusRelay1 ? "🟢 NYALA          │" : "⚫ MATI            │");

  Serial.print("│ Fan (Relay 2) : ");
  Serial.println(statusRelay2 ? "🟢 NYALA          │" : "⚫ MATI            │");

  Serial.println("└─────────────────────────────────────┘");
  Serial.println();
}

/*
  ===================================================================
  PENJELASAN KONSEP:
  ===================================================================

  1. RELAY MODULE:
     - Relay adalah saklar elektronik
     - Input: Sinyal LOW/HIGH dari ESP32 (3.3V atau 5V)
     - Output: Buka/tutup kontak untuk beban (sampai 220V AC)

     Jenis Relay Module:
     - Active HIGH: Relay nyala saat diberi sinyal HIGH
     - Active LOW: Relay nyala saat diberi sinyal LOW
     - Kebanyakan module relay = Active HIGH

     Kenapa perlu relay?
     - ESP32 hanya bisa output 3.3V, max ~40mA
     - Tidak cukup untuk nyalakan perangkat AC (220V, ampere tinggi)
     - Relay = "perantara" antara ESP32 dan perangkat AC

  2. HYSTERESIS (Dead Band):
     Mencegah relay "flicker" (nyala-mati cepat)

     Tanpa Hysteresis:
     Threshold = 28°C
     Suhu naik-turun di sekitar 28°C → relay flicker
     Contoh: 27.9 → 28.1 → 27.9 → 28.1 (relay on-off-on-off)

     Dengan Hysteresis:
     Nyala = 28°C, Mati = 26°C (gap 2°C)
     Suhu 27.9°C → AC tetap mati
     Suhu 28.1°C → AC nyala
     Suhu 27.5°C → AC tetap nyala
     Suhu 25.9°C → AC mati

     Keuntungan:
     - Relay lebih awet (lifecycle ~100.000 switching)
     - Hemat energi (tidak sering on-off)
     - Sistem lebih stabil

  3. RELAY LIFETIME:
     - Relay mekanis: ~100.000 switching
     - Jika on-off 10x per hari = ~27 tahun
     - Jika on-off 100x per hari = ~2.7 tahun
     - Untuk aplikasi sering on-off: gunakan SSR (Solid State Relay)

  4. KONEKSI RELAY MODULE:
     Terminal Input (dari ESP32):
     - VCC: 5V (relay module butuh 5V untuk coil)
     - GND: Ground
     - IN1, IN2: Sinyal kontrol dari GPIO

     Terminal Output (untuk beban):
     - COM (Common): Input dari sumber listrik
     - NO (Normally Open): Kontak terbuka saat relay OFF
     - NC (Normally Closed): Kontak tertutup saat relay OFF

     Untuk kontrol perangkat:
     Sumber Listrik → COM
     NO → Perangkat → Kembali ke Sumber (netral)

     Saat relay ON: COM terhubung ke NO → Arus mengalir → Perangkat nyala
     Saat relay OFF: COM terputus dari NO → Perangkat mati

  5. ISOLASI OPTIK (Optocoupler):
     - Relay module biasanya punya optocoupler
     - Memisahkan sirkuit ESP32 dari sirkuit beban
     - Melindungi ESP32 dari tegangan tinggi
     - Mencegah ground loop dan noise

  ===================================================================
  DIAGRAM SISTEM:
  ===================================================================

  [DHT11] ---> [ESP32] ---> [Relay Module] ---> [Perangkat AC]
                  |              |
                  v              v
            [Algoritma]    [Isolasi Optik]
            [Hysteresis]   [Kontak Mekanis]

  Flow Data:
  1. DHT11 ukur suhu & kelembapan
  2. ESP32 terima data via protokol 1-wire
  3. ESP32 proses dengan algoritma hysteresis
  4. ESP32 kirim sinyal HIGH/LOW ke relay
  5. Optocoupler isolasi sinyal
  6. Coil relay aktif → kontak tertutup
  7. Arus mengalir → perangkat nyala

  ===================================================================
  EKSPERIMEN YANG BISA DICOBA:
  ===================================================================

  1. Tambah Mode Manual Override:
     bool modeManual = false;
     int pinButton = 4;

     // Di setup:
     pinMode(pinButton, INPUT_PULLUP);

     // Di loop (sebelum logika auto):
     if (digitalRead(pinButton) == LOW) {
       modeManual = !modeManual;
       Serial.println(modeManual ? "Mode: MANUAL" : "Mode: AUTO");
       delay(300);
     }

     if (!modeManual) {
       // Logika otomatis di sini
     } else {
       // Kontrol manual dengan button lain
     }

  2. Tambah Timer (AC mati otomatis setelah 2 jam):
     unsigned long waktuNyala = 0;
     const unsigned long DURASI_MAX = 2 * 60 * 60 * 1000;  // 2 jam

     // Saat AC nyala:
     if (!statusRelay1) {
       waktuNyala = millis();
     }

     // Cek durasi:
     if (statusRelay1 && (millis() - waktuNyala > DURASI_MAX)) {
       digitalWrite(pinRelay1, LOW);
       statusRelay1 = false;
       Serial.println("⏰ AC mati otomatis (timeout 2 jam)");
     }

  3. Tambah Setpoint yang Bisa Diatur:
     // Gunakan potensiometer untuk adjust threshold
     int pinPot = 34;

     // Di loop:
     int nilaiPot = analogRead(pinPot);
     float suhuSetpoint = map(nilaiPot, 0, 4095, 20, 32);  // Range 20-32°C

     Serial.print("Setpoint: ");
     Serial.print(suhuSetpoint);
     Serial.println(" °C");

  4. Statistik Penggunaan Energi:
     unsigned long totalWaktuAC = 0;
     unsigned long waktuMulaiAC = 0;

     // Saat AC nyala:
     waktuMulaiAC = millis();

     // Saat AC mati:
     totalWaktuAC += (millis() - waktuMulaiAC);

     // Tampilkan:
     Serial.print("Total AC ON: ");
     Serial.print(totalWaktuAC / 1000 / 60);
     Serial.println(" menit");

  5. Integrasi dengan Sensor PIR (Hemat Energi):
     // AC hanya nyala jika: PANAS + ADA ORANG
     int pinPIR = 13;

     if (suhu >= SUHU_NYALA && digitalRead(pinPIR) == HIGH) {
       // Nyalakan AC
     }

  ===================================================================
  TROUBLESHOOTING:
  ===================================================================

  Masalah: Relay tidak klik (tidak ada bunyi)
  Solusi:
  - Cek koneksi VCC relay ke 5V (bukan 3.3V)
  - Cek GND terhubung
  - Cek sinyal IN1/IN2 dari GPIO
  - Ukur tegangan di pin IN1 saat HIGH (harus ~3.3V)
  - Coba relay lain (mungkin rusak)

  Masalah: Relay klik tapi LED tidak nyala
  Solusi:
  - Cek koneksi COM dan NO pada terminal output
  - Pastikan LED dipasang di jalur yang benar
  - Test LED dengan multimeter
  - Cek polaritas LED

  Masalah: Relay flicker (nyala-mati cepat)
  Solusi:
  - Hysteresis terlalu kecil, perbesar gap
  - Tambah delay di loop (misal 5 detik)
  - Cek sensor DHT11 (data tidak stabil)
  - Gunakan moving average untuk smooth data

  Masalah: Data DHT11 tidak akurat
  Solusi:
  - DHT11 akurasi ±2°C (normal)
  - Jauhkan sensor dari sumber panas
  - Tunggu settling time 2-5 detik
  - Kalibrasi dengan termometer akurat

  Masalah: ESP32 restart sendiri saat relay nyala
  Solusi:
  - Power supply tidak cukup arus
  - Gunakan power supply 5V 2A minimum
  - Pisahkan power ESP32 dan relay module
  - Tambah kapasitor 1000uF di VCC relay

  ===================================================================
  APLIKASI DALAM BANGUNAN CERDAS:
  ===================================================================

  1. SISTEM HVAC OTOMATIS:
     - Kontrol AC, pemanas, ventilasi
     - Hemat energi (on hanya saat perlu)
     - Kenyamanan penghuni
     - Monitoring konsumsi listrik

  2. GREENHOUSE AUTOMATION:
     - Kontrol suhu dan kelembapan optimal
     - Pompa misting (kabut air)
     - Kipas exhaust
     - Grow light otomatis

  3. SERVER ROOM COOLING:
     - Suhu server harus stabil 18-24°C
     - AC redundan (2 unit bergantian)
     - Alarm jika suhu >30°C
     - Log untuk maintenance

  4. SMART HOME:
     - AC nyala otomatis saat tiba di rumah (GPS)
     - Matikan AC jika tidak ada orang >30 menit
     - Jadwal on/off harian
     - Kontrol via smartphone

  5. HOTEL ROOM AUTOMATION:
     - AC nyala saat tamu check-in
     - Mati saat tamu keluar (keycard sensor)
     - Hemat energi signifikan
     - Guest comfort terjaga

  ===================================================================
  KEAMANAN LISTRIK:
  ===================================================================

  ⚠️ PENTING! Bekerja dengan AC 220V berbahaya!

  Safety Guidelines:
  1. Jangan sentuh terminal saat listrik ON
  2. Gunakan kabel dengan isolasi baik
  3. Pasang dalam box tertutup (tidak terbuka)
  4. Tambahkan MCB (Miniature Circuit Breaker)
  5. Grounding yang baik
  6. Test dengan multimeter sebelum power on
  7. Untuk praktikum: gunakan LED simulasi (aman)

  Untuk Implementasi Real:
  - Konsultasi dengan teknisi listrik bersertifikat
  - Ikuti standar kelistrikan (SNI, PUIL)
  - Gunakan relay module berkualitas
  - Pertimbangkan fire safety

  ===================================================================
*/
