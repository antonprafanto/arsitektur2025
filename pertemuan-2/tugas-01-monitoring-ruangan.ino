/*
  ===================================================================
  TUGAS RUMAH 1: SISTEM MONITORING RUANGAN LENGKAP
  ===================================================================

  Deskripsi:
  Membuat sistem monitoring lengkap yang menampilkan semua parameter
  ruangan di Serial Monitor secara real-time dengan format rapi.

  Data yang Ditampilkan:
  - Suhu dan Kelembapan (DHT11)
  - Tingkat Cahaya (LDR)
  - Status Kehadiran (PIR)
  - Uptime sistem

  Format Output:
  =================================
  MONITORING RUANGAN
  =================================
  Suhu         : 28.5 °C
  Kelembapan   : 65 %
  Cahaya       : Terang (nilai: 1200)
  Kehadiran    : Ada Orang
  Uptime       : 00:12:45
  =================================

  Komponen yang Dibutuhkan:
  - 1x ESP32
  - 1x DHT11 (Suhu & Kelembapan)
  - 1x LDR + Resistor 10K
  - 1x PIR (Sensor Gerak)
  - Kabel jumper
  - Breadboard

  Koneksi Rangkaian:
  DHT11: VCC(3.3V), DATA(GPIO15), GND
  LDR: 3.3V ---> LDR ---> GPIO34 ---> 10KΩ ---> GND
  PIR: VCC(5V), OUT(GPIO13), GND

  Library yang Diperlukan:
  - DHT sensor library (by Adafruit)

  Dibuat untuk: Mata Kuliah Bangunan Cerdas
  Instruktur: Anton Prafanto
  ===================================================================
*/

// ===== INCLUDE LIBRARY =====
#include <DHT.h>

// ===== KONFIGURASI DHT11 =====
#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ===== KONFIGURASI PIN =====
const int pinLDR = 34;
const int pinPIR = 13;

// ===== THRESHOLD =====
const int thresholdGelap = 2500;

// ===== VARIABEL WAKTU =====
unsigned long waktuMulai = 0;

// ===== FUNGSI SETUP =====
void setup() {
  // Inisialisasi Serial Monitor
  Serial.begin(115200);
  delay(1000);

  Serial.println("========================================");
  Serial.println("  SISTEM MONITORING RUANGAN LENGKAP    ");
  Serial.println("========================================");
  Serial.println();

  // Inisialisasi sensor
  dht.begin();
  pinMode(pinPIR, INPUT);

  Serial.println("Sensor diinisialisasi...");
  Serial.println("Kalibrasi PIR (30 detik)...");
  Serial.println("Jangan bergerak!");
  Serial.println();

  // Kalibrasi PIR
  for (int i = 30; i > 0; i--) {
    Serial.print("Countdown: ");
    Serial.print(i);
    Serial.println(" detik");
    delay(1000);
  }

  Serial.println();
  Serial.println("✅ Kalibrasi selesai!");
  Serial.println("Monitoring dimulai...");
  Serial.println();

  // Catat waktu mulai
  waktuMulai = millis();

  delay(2000);
}

// ===== FUNGSI LOOP =====
void loop() {

  // ===== BACA SEMUA SENSOR =====

  // 1. DHT11 (Suhu & Kelembapan)
  float suhu = dht.readTemperature();
  float kelembapan = dht.readHumidity();

  // 2. LDR (Cahaya)
  int nilaiLDR = analogRead(pinLDR);

  // 3. PIR (Kehadiran)
  int statusPIR = digitalRead(pinPIR);
  bool adaOrang = (statusPIR == HIGH);

  // ===== VALIDASI DATA DHT11 =====
  if (isnan(suhu) || isnan(kelembapan)) {
    Serial.println("❌ Error membaca sensor DHT11!");
    Serial.println("   Cek koneksi sensor...");
    Serial.println();
    delay(2000);
    return;
  }

  // ===== HITUNG UPTIME =====
  unsigned long uptimeSeconds = (millis() - waktuMulai) / 1000;
  int jam = uptimeSeconds / 3600;
  int menit = (uptimeSeconds % 3600) / 60;
  int detik = uptimeSeconds % 60;

  // ===== TAMPILKAN DATA =====
  Serial.println("=================================");
  Serial.println("       MONITORING RUANGAN        ");
  Serial.println("=================================");
  Serial.println();

  // Suhu
  Serial.print("Suhu         : ");
  Serial.print(suhu, 1);
  Serial.print(" ");
  Serial.print((char)247);  // Simbol derajat
  Serial.print("C");
  if (suhu > 30) {
    Serial.println("  🔥 PANAS");
  } else if (suhu < 20) {
    Serial.println("  ❄️  DINGIN");
  } else {
    Serial.println("  ✅ NORMAL");
  }

  // Kelembapan
  Serial.print("Kelembapan   : ");
  Serial.print(kelembapan, 1);
  Serial.print(" %");
  if (kelembapan > 70) {
    Serial.println("  💧 LEMBAP");
  } else if (kelembapan < 30) {
    Serial.println("  ☀️  KERING");
  } else {
    Serial.println("  ✅ NORMAL");
  }

  // Cahaya
  Serial.print("Cahaya       : ");
  if (nilaiLDR > thresholdGelap) {
    Serial.print("GELAP       ");
  } else {
    Serial.print("TERANG      ");
  }
  Serial.print(" (nilai: ");
  Serial.print(nilaiLDR);
  Serial.println(")");

  // Kehadiran
  Serial.print("Kehadiran    : ");
  if (adaOrang) {
    Serial.println("👤 ADA ORANG");
  } else {
    Serial.println("🚫 TIDAK ADA");
  }

  // Uptime
  Serial.print("Uptime       : ");
  if (jam < 10) Serial.print("0");
  Serial.print(jam);
  Serial.print(":");
  if (menit < 10) Serial.print("0");
  Serial.print(menit);
  Serial.print(":");
  if (detik < 10) Serial.print("0");
  Serial.println(detik);

  Serial.println();
  Serial.println("=================================");
  Serial.println();

  // Update setiap 3 detik
  delay(3000);
}

/*
  ===================================================================
  PENJELASAN KONSEP:
  ===================================================================

  1. MULTI-SENSOR INTEGRATION:
     - Baca data dari 3 sensor berbeda
     - DHT11 (digital serial), LDR (analog), PIR (digital)
     - Gabungkan semua data dalam satu dashboard

  2. DATA VALIDATION:
     - Selalu cek data sensor dengan isnan()
     - Skip loop jika data invalid
     - Beri pesan error yang jelas

  3. FORMATTED OUTPUT:
     - Gunakan printf atau print dengan format
     - Simbol khusus untuk visual (°, 🔥, 💧, dll)
     - Border dan spacing untuk keterbacaan

  4. UPTIME CALCULATION:
     - millis() = waktu sejak ESP32 boot (ms)
     - Convert ke jam:menit:detik
     - Berguna untuk monitoring stability

  5. THRESHOLD-BASED ANALYSIS:
     - Bukan hanya tampilkan angka
     - Beri interpretasi (panas, normal, dingin)
     - Memudahkan user memahami kondisi

  ===================================================================
  PENGEMBANGAN & VARIASI:
  ===================================================================

  1. TAMBAH STATISTIK:
     float suhuMin = 100, suhuMax = 0;
     float suhuTotal = 0;
     int jumlahPembacaan = 0;

     // Di loop:
     if (suhu < suhuMin) suhuMin = suhu;
     if (suhu > suhuMax) suhuMax = suhu;
     suhuTotal += suhu;
     jumlahPembacaan++;

     float suhuRataRata = suhuTotal / jumlahPembacaan;

     Serial.print("Suhu Min/Max/Avg: ");
     Serial.print(suhuMin);
     Serial.print(" / ");
     Serial.print(suhuMax);
     Serial.print(" / ");
     Serial.println(suhuRataRata);

  2. DATA LOGGING KE SD CARD:
     #include <SD.h>

     File dataFile = SD.open("log.csv", FILE_WRITE);
     if (dataFile) {
       dataFile.print(millis());
       dataFile.print(",");
       dataFile.print(suhu);
       dataFile.print(",");
       dataFile.print(kelembapan);
       dataFile.print(",");
       dataFile.print(nilaiLDR);
       dataFile.print(",");
       dataFile.println(adaOrang);
       dataFile.close();
     }

  3. GRAFIK REAL-TIME (Serial Plotter):
     // Bukan tampilkan teks, tapi angka saja
     Serial.print(suhu);
     Serial.print(",");
     Serial.print(kelembapan);
     Serial.print(",");
     Serial.println(nilaiLDR / 10);  // Scale down
     // Tools > Serial Plotter

  4. ALERT SYSTEM:
     if (suhu > 35) {
       Serial.println("⚠️  ALERT: SUHU SANGAT TINGGI!");
       digitalWrite(pinBuzzer, HIGH);
       delay(1000);
       digitalWrite(pinBuzzer, LOW);
     }

  5. KIRIM DATA KE CLOUD (Blynk/ThingSpeak):
     Blynk.virtualWrite(V0, suhu);
     Blynk.virtualWrite(V1, kelembapan);
     Blynk.virtualWrite(V2, nilaiLDR);
     Blynk.virtualWrite(V3, adaOrang);

  6. WEB DASHBOARD:
     // ESP32 sebagai web server
     // Tampilkan data di browser
     // Refresh otomatis setiap detik

  ===================================================================
  APLIKASI REAL-WORLD:
  ===================================================================

  1. BUILDING MANAGEMENT SYSTEM (BMS):
     - Monitor multiple ruangan
     - Database terpusat
     - Alert ke facility manager
     - Historical data untuk analisis

  2. DATA CENTER MONITORING:
     - Suhu harus stabil 18-24°C
     - Kelembapan 40-60%
     - Alert jika keluar range
     - Cooling efficiency analysis

  3. SMART HOME AUTOMATION:
     - Dashboard di smartphone
     - Kontrol AC/lampu berdasarkan data
     - Energy consumption tracking
     - Comfort optimization

  4. GREENHOUSE/VERTICAL FARMING:
     - Monitor suhu, kelembapan, cahaya
     - Optimal untuk pertumbuhan tanaman
     - Automated irrigation & lighting
     - Yield optimization

  5. MUSEUM/ART GALLERY:
     - Preservasi artefak
     - Kelembapan dan suhu stabil
     - Light exposure control
     - Climate logging untuk insurance

  6. OFFICE COMFORT MONITORING:
     - Ensure employee comfort
     - Adjust HVAC automatically
     - Occupancy-based control
     - Energy savings

  ===================================================================
  TROUBLESHOOTING:
  ===================================================================

  Masalah: Data DHT11 selalu NaN
  Solusi:
  - Cek koneksi VCC, DATA, GND
  - Tambah delay 2 detik di setup()
  - Pastikan library DHT terinstall
  - Coba sensor lain

  Masalah: Uptime tidak akurat
  Solusi:
  - millis() overflow setelah ~50 hari (normal)
  - Untuk aplikasi long-term, gunakan RTC
  - Atau reset counter secara berkala

  Masalah: Serial Monitor lambat/freeze
  Solusi:
  - Jangan print terlalu cepat
  - Delay minimal 1 detik antar print
  - Kurangi jumlah karakter yang di-print

  Masalah: PIR false positive terus
  Solusi:
  - Tunggu kalibrasi 60 detik
  - Jauhkan dari AC/heater
  - Turunkan sensitivity

  ===================================================================
  TIPS LANJUTAN:
  ===================================================================

  1. Moving Average untuk Smooth Data:
     const int numReadings = 10;
     float readingsSuhu[numReadings];
     int index = 0;

     float getAverageSuhu() {
       float total = 0;
       for (int i = 0; i < numReadings; i++) {
         total += readingsSuhu[i];
       }
       return total / numReadings;
     }

  2. Color Output (jika terminal support):
     #define RED "\033[31m"
     #define GREEN "\033[32m"
     #define RESET "\033[0m"

     Serial.print(RED);
     Serial.println("PANAS!");
     Serial.print(RESET);

  3. JSON Output (untuk IoT platform):
     Serial.println("{");
     Serial.print("  \"temperature\": ");
     Serial.print(suhu);
     Serial.println(",");
     Serial.print("  \"humidity\": ");
     Serial.print(kelembapan);
     Serial.println(",");
     Serial.print("  \"light\": ");
     Serial.print(nilaiLDR);
     Serial.println(",");
     Serial.print("  \"occupancy\": ");
     Serial.println(adaOrang);
     Serial.println("}");

  ===================================================================
*/
