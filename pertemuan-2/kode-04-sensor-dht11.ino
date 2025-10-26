/*
  ===================================================================
  PRAKTIKUM 1: SENSOR DHT11 - Suhu & Kelembapan
  ===================================================================

  Deskripsi:
  Program ini membaca data suhu dan kelembapan dari sensor DHT11
  dan menampilkannya di Serial Monitor setiap 2 detik.

  Komponen yang Dibutuhkan:
  - 1x ESP32 Development Board
  - 1x Sensor DHT11
  - 3x Kabel jumper

  Koneksi Rangkaian:
  DHT11 VCC   --->  ESP32 3.3V
  DHT11 DATA  --->  ESP32 GPIO15
  DHT11 GND   --->  ESP32 GND

  Library yang Diperlukan:
  - DHT sensor library (by Adafruit)
  - Adafruit Unified Sensor

  Cara Install Library:
  1. Sketch > Include Library > Manage Libraries
  2. Cari "DHT sensor library"
  3. Install yang dari Adafruit
  4. Install dependencies jika diminta

  Dibuat untuk: Mata Kuliah Bangunan Cerdas
  Instruktur: Anton Prafanto
  ===================================================================
*/

// ===== INCLUDE LIBRARY =====
#include <DHT.h>
// Library DHT untuk berkomunikasi dengan sensor DHT11/DHT22

// ===== KONFIGURASI DHT =====
#define DHTPIN 15        // Pin GPIO yang terhubung ke sensor DHT
#define DHTTYPE DHT11    // Tipe sensor: DHT11 (ada juga DHT22/DHT21)

// Membuat objek DHT
DHT dht(DHTPIN, DHTTYPE);
// Sintaks: DHT nama(pin, tipe)

// ===== FUNGSI SETUP =====
void setup() {
  // Inisialisasi Serial Monitor
  Serial.begin(115200);
  delay(1000);  // Tunggu Serial Monitor siap

  Serial.println("========================================");
  Serial.println("  SISTEM MONITORING SUHU & KELEMBAPAN  ");
  Serial.println("        Menggunakan DHT11              ");
  Serial.println("========================================");
  Serial.println();

  // Inisialisasi sensor DHT
  dht.begin();
  Serial.println("Sensor DHT11 diinisialisasi...");
  Serial.println("Tunggu 2 detik untuk pembacaan pertama...");
  Serial.println();

  delay(2000);  // DHT butuh waktu settling
}

// ===== FUNGSI LOOP =====
void loop() {

  // LANGKAH 1: Baca data dari sensor DHT11
  // readTemperature() mengembalikan suhu dalam Celcius
  // readHumidity() mengembalikan kelembapan dalam %

  float kelembapan = dht.readHumidity();
  float suhu = dht.readTemperature();  // Dalam Celcius
  // Jika ingin Fahrenheit: dht.readTemperature(true)

  // LANGKAH 2: Cek apakah pembacaan berhasil
  // Jika gagal, fungsi akan return NaN (Not a Number)
  if (isnan(kelembapan) || isnan(suhu)) {
    Serial.println("❌ Gagal membaca sensor DHT11!");
    Serial.println("   Cek koneksi sensor...");
    Serial.println();
    delay(2000);
    return;  // Keluar dari loop() dan coba lagi
  }

  // LANGKAH 3: Hitung Heat Index (Indeks Kenyamanan)
  // Heat index = bagaimana suhu "terasa" oleh tubuh manusia
  // Dipengaruhi oleh suhu dan kelembapan
  float heatIndex = dht.computeHeatIndex(suhu, kelembapan, false);
  // Parameter: (suhu, kelembapan, isFahrenheit)

  // LANGKAH 4: Tampilkan data di Serial Monitor
  Serial.println("===== SENSOR DHT11 =====");

  Serial.print("Suhu         : ");
  Serial.print(suhu, 1);  // 1 = 1 angka di belakang koma
  Serial.println(" °C");

  Serial.print("Kelembapan   : ");
  Serial.print(kelembapan, 1);
  Serial.println(" %");

  Serial.print("Heat Index   : ");
  Serial.print(heatIndex, 1);
  Serial.println(" °C");

  // LANGKAH 5: Interpretasi kondisi
  Serial.print("Kondisi      : ");
  if (suhu < 20) {
    Serial.println("Dingin ❄️");
  } else if (suhu >= 20 && suhu <= 26) {
    Serial.println("Nyaman ✅");
  } else if (suhu > 26 && suhu <= 30) {
    Serial.println("Hangat 🌤️");
  } else {
    Serial.println("Panas 🔥");
  }

  Serial.print("Kelembapan   : ");
  if (kelembapan < 30) {
    Serial.println("Kering");
  } else if (kelembapan >= 30 && kelembapan <= 60) {
    Serial.println("Ideal");
  } else {
    Serial.println("Lembap");
  }

  Serial.println("========================");
  Serial.println();

  // LANGKAH 6: Tunggu 2 detik sebelum pembacaan berikutnya
  // DHT11 max sampling rate: 1 Hz (1 kali per detik)
  // Tapi lebih baik 2 detik untuk stabilitas
  delay(2000);
}

/*
  ===================================================================
  PENJELASAN KONSEP:
  ===================================================================

  1. LIBRARY DHT:
     - Menyederhanakan komunikasi dengan sensor DHT
     - Protokol komunikasi DHT11: 1-wire (kompleks)
     - Library menghandle timing dan checksum
     - Alternatif: bisa pakai library DHTesp (khusus ESP32)

  2. PEMBACAAN DATA:
     - dht.readTemperature() → float (suhu dalam °C)
     - dht.readHumidity() → float (kelembapan dalam %)
     - Jika gagal → return NaN (Not a Number)
     - Gunakan isnan() untuk cek validitas data

  3. HEAT INDEX (Indeks Panas):
     - Kombinasi suhu dan kelembapan
     - Menunjukkan bagaimana suhu "terasa"
     - Kelembapan tinggi → terasa lebih panas
     - Rumus: HI = c1 + c2T + c3R + c4TR + ... (kompleks)
     - Standar: NOAA Heat Index

  4. DELAY 2 DETIK:
     - DHT11 lambat (max 1 Hz)
     - Pembacaan terlalu cepat → data tidak valid
     - 2 detik = aman dan hemat resource

  5. ERROR HANDLING:
     - Selalu cek hasil pembacaan dengan isnan()
     - Jika error, beri pesan ke user
     - return; untuk skip loop dan coba lagi

  ===================================================================
  TABEL REFERENSI KENYAMANAN:
  ===================================================================

  SUHU (°C)     | KONDISI         | AKSI
  --------------|-----------------|---------------------------
  < 18          | Sangat Dingin   | Nyalakan pemanas
  18 - 20       | Dingin          | Pertimbangkan pemanas
  20 - 26       | Nyaman          | Ideal, tidak perlu aksi
  26 - 30       | Hangat          | Pertimbangkan AC/kipas
  > 30          | Panas           | Nyalakan AC

  KELEMBAPAN (%)| KONDISI         | AKSI
  --------------|-----------------|---------------------------
  < 30          | Terlalu Kering  | Humidifier (pelembap)
  30 - 60       | Ideal           | Tidak perlu aksi
  60 - 70       | Agak Lembap     | Pertimbangkan dehumidifier
  > 70          | Terlalu Lembap  | Dehumidifier/exhaust fan

  HEAT INDEX    | RISIKO          | PERINGATAN
  --------------|-----------------|---------------------------
  < 27          | Normal          | Aman
  27 - 32       | Caution         | Kelelahan jika aktif lama
  32 - 41       | Extreme Caution | Heat cramps, heat exhaustion
  41 - 54       | Danger          | Heat stroke probable
  > 54          | Extreme Danger  | Heat stroke imminent

  ===================================================================
  EKSPERIMEN YANG BISA DICOBA:
  ===================================================================

  1. Tambahkan LED Indikator Suhu:
     int pinLED_merah = 2;   // Panas
     int pinLED_hijau = 4;   // Nyaman
     int pinLED_biru = 5;    // Dingin

     // Di loop, setelah baca suhu:
     digitalWrite(pinLED_merah, suhu > 30 ? HIGH : LOW);
     digitalWrite(pinLED_hijau, (suhu >= 20 && suhu <= 30) ? HIGH : LOW);
     digitalWrite(pinLED_biru, suhu < 20 ? HIGH : LOW);

  2. Kontrol Relay (Simulasi AC):
     int pinRelay = 25;
     pinMode(pinRelay, OUTPUT);

     // Di loop:
     if (suhu > 28) {
       digitalWrite(pinRelay, HIGH);  // Nyalakan AC
       Serial.println("AC: NYALA");
     } else if (suhu < 24) {
       digitalWrite(pinRelay, LOW);   // Matikan AC
       Serial.println("AC: MATI");
     }
     // Ini pakai hysteresis: nyala di 28°C, mati di 24°C

  3. Data Logger (Simpan ke Array):
     float dataSuhu[10];
     int index = 0;

     // Di loop:
     dataSuhu[index] = suhu;
     index++;
     if (index >= 10) index = 0;  // Circular buffer

     // Hitung rata-rata:
     float total = 0;
     for (int i = 0; i < 10; i++) {
       total += dataSuhu[i];
     }
     float rataRata = total / 10.0;
     Serial.print("Rata-rata 10 data: ");
     Serial.println(rataRata);

  4. Alarm Suhu Ekstrem:
     int pinBuzzer = 12;
     pinMode(pinBuzzer, OUTPUT);

     // Di loop:
     if (suhu > 35 || suhu < 15) {
       // Buzzer bunyi beep
       digitalWrite(pinBuzzer, HIGH);
       delay(200);
       digitalWrite(pinBuzzer, LOW);
       delay(200);
     }

  5. Format Output JSON (untuk IoT):
     Serial.println("{");
     Serial.print("  \"temperature\": ");
     Serial.print(suhu);
     Serial.println(",");
     Serial.print("  \"humidity\": ");
     Serial.print(kelembapan);
     Serial.println(",");
     Serial.print("  \"heatIndex\": ");
     Serial.println(heatIndex);
     Serial.println("}");

  ===================================================================
  TROUBLESHOOTING:
  ===================================================================

  Masalah: "Failed to read from DHT sensor!"
  Solusi:
  - Cek koneksi VCC, DATA, GND
  - Pastikan pin DATA ke GPIO15 (atau sesuaikan #define DHTPIN)
  - VCC ke 3.3V (bukan 5V untuk ESP32)
  - Coba tambah pull-up resistor 10K antara DATA dan VCC
  - Ganti sensor DHT11 (mungkin rusak)

  Masalah: Data tidak berubah/freeze
  Solusi:
  - Sensor butuh waktu response (~2 detik)
  - Jangan baca terlalu cepat (min delay 2000ms)
  - Reset ESP32 (tekan tombol RST)

  Masalah: Suhu tidak akurat (selisih >5°C)
  Solusi:
  - DHT11 akurasi ±2°C (bukan sensor presisi)
  - Jauhkan dari sumber panas (resistor, LED, board ESP32)
  - Bandingkan dengan termometer akurat
  - Beri kalibrasi offset:
    float suhuTerkalibrasi = suhu + OFFSET;  // OFFSET = -2.0 misalnya

  Masalah: Library tidak ditemukan (error compile)
  Solusi:
  - Install DHT sensor library via Library Manager
  - Restart Arduino IDE
  - Cek path library: Documents/Arduino/libraries/DHT-sensor-library

  Masalah: Serial Monitor tidak tampil angka
  Solusi:
  - Pastikan baud rate 115200
  - Tambah delay(1000) di awal setup()
  - Cek kabel USB (harus bisa data transfer)

  ===================================================================
  APLIKASI DALAM BANGUNAN CERDAS:
  ===================================================================

  1. HVAC Control:
     - Monitor suhu ruangan
     - Nyalakan AC jika > threshold
     - Matikan jika sudah mencapai setpoint
     - Hemat energi dengan hysteresis

  2. Server Room Monitoring:
     - Suhu harus stabil 18-24°C
     - Alarm jika keluar range
     - Log data untuk analisis
     - Deteksi dini overheating

  3. Greenhouse/Indoor Farming:
     - Kontrol suhu dan kelembapan optimal
     - Sesuai jenis tanaman
     - Otomasi misting (kabut air)
     - Monitoring 24/7

  4. Museum/Galeri Seni:
     - Preservasi artefak butuh kelembapan stabil
     - Ideal: 40-60% RH
     - Suhu: 18-24°C
     - Alarm jika keluar range

  5. Comfort Monitoring:
     - Pastikan ruangan nyaman untuk penghuni
     - Sesuaikan HVAC berdasarkan occupancy (jumlah orang)
     - Hemat energi saat tidak ada orang (gabung dengan PIR)

  ===================================================================
*/
