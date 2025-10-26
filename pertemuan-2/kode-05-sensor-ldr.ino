/*
  ===================================================================
  PRAKTIKUM 2: SENSOR LDR - Lampu Otomatis
  ===================================================================

  Deskripsi:
  Program ini membuat lampu otomatis yang menyala saat gelap dan
  mati saat terang menggunakan sensor LDR (Light Dependent Resistor).

  Konsep:
  - LDR adalah resistor yang resistansinya berubah sesuai cahaya
  - Gelap → resistansi tinggi → nilai ADC tinggi
  - Terang → resistansi rendah → nilai ADC rendah

  Komponen yang Dibutuhkan:
  - 1x ESP32 Development Board
  - 1x LDR (Light Dependent Resistor)
  - 1x Resistor 10K ohm (untuk voltage divider)
  - 1x LED
  - 1x Resistor 220 ohm (untuk LED)
  - Kabel jumper
  - Breadboard

  Koneksi Rangkaian:

  Voltage Divider untuk LDR:
  3.3V
    │
    ├── LDR ────┬──── GPIO34 (Analog Input)
    │           │
    └── 10KΩ ───┴──── GND

  LED Indikator:
  GPIO2 ---> LED (+) ---> Resistor 220Ω ---> GND

  Catatan:
  - GPIO34-39 adalah input only (hanya bisa analogRead)
  - ADC ESP32: 12-bit (0-4095)

  Dibuat untuk: Mata Kuliah Bangunan Cerdas
  Instruktur: Anton Prafanto
  ===================================================================
*/

// ===== KONFIGURASI PIN =====
const int pinLDR = 34;       // Pin analog untuk membaca LDR (harus GPIO 34-39)
const int pinLED = 2;        // Pin digital untuk LED

// ===== KONFIGURASI THRESHOLD =====
// Nilai threshold menentukan kapan lampu nyala/mati
// Sesuaikan nilai ini berdasarkan kondisi ruangan Anda!
// Cara kalibrasi:
// 1. Upload kode ini dengan mode DEBUG
// 2. Lihat nilai LDR saat gelap dan terang di Serial Monitor
// 3. Tentukan nilai tengah sebagai threshold
const int threshold = 2500;  // Ganti nilai ini sesuai kalibrasi

// Hysteresis (dead band) untuk mencegah flicker
// Lampu nyala jika nilai > thresholdNyala
// Lampu mati jika nilai < thresholdMati
const int thresholdNyala = threshold + 200;  // 2700
const int thresholdMati = threshold - 200;   // 2300

// ===== VARIABEL STATUS =====
bool lampuNyala = false;  // Status lampu saat ini

// ===== MODE DEBUG =====
// Set true untuk melihat nilai LDR mentah
// Set false untuk mode operasional normal
const bool DEBUG_MODE = true;

// ===== FUNGSI SETUP =====
void setup() {
  // Inisialisasi Serial Monitor
  Serial.begin(115200);
  delay(1000);

  Serial.println("========================================");
  Serial.println("    SISTEM PENCAHAYAAN OTOMATIS        ");
  Serial.println("       Menggunakan Sensor LDR          ");
  Serial.println("========================================");
  Serial.println();

  // Konfigurasi pin
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, LOW);  // Pastikan LED mati di awal

  // Pin ADC tidak perlu pinMode (otomatis input)

  Serial.println("Sistem siap!");
  Serial.print("Threshold: ");
  Serial.println(threshold);
  Serial.print("Threshold Nyala: ");
  Serial.println(thresholdNyala);
  Serial.print("Threshold Mati: ");
  Serial.println(thresholdMati);
  Serial.println();

  if (DEBUG_MODE) {
    Serial.println("MODE DEBUG: Aktif");
    Serial.println("Amati nilai LDR dan sesuaikan threshold");
    Serial.println("Format: Nilai LDR | Status Cahaya | Status Lampu");
    Serial.println("--------------------------------------------------");
  }
}

// ===== FUNGSI LOOP =====
void loop() {

  // LANGKAH 1: Baca nilai sensor LDR
  // analogRead() mengembalikan nilai 0-4095 (12-bit ADC)
  int nilaiLDR = analogRead(pinLDR);

  // LANGKAH 2: Logika kontrol lampu dengan HYSTERESIS
  // Hysteresis mencegah lampu flicker (nyala-mati cepat)
  // saat nilai LDR berada di sekitar threshold

  if (nilaiLDR > thresholdNyala && !lampuNyala) {
    // Kondisi: Gelap DAN lampu belum nyala
    digitalWrite(pinLED, HIGH);
    lampuNyala = true;

    if (!DEBUG_MODE) {
      Serial.println("💡 LAMPU NYALA (Gelap terdeteksi)");
    }
  }
  else if (nilaiLDR < thresholdMati && lampuNyala) {
    // Kondisi: Terang DAN lampu masih nyala
    digitalWrite(pinLED, LOW);
    lampuNyala = false;

    if (!DEBUG_MODE) {
      Serial.println("🌙 LAMPU MATI (Terang terdeteksi)");
    }
  }

  // LANGKAH 3: Tampilkan info di Serial Monitor
  if (DEBUG_MODE) {
    // Mode debug: tampilkan nilai mentah setiap 500ms
    Serial.print("Nilai LDR: ");
    Serial.print(nilaiLDR);
    Serial.print("\t| ");

    // Status cahaya
    if (nilaiLDR > thresholdNyala) {
      Serial.print("GELAP      ");
    } else if (nilaiLDR < thresholdMati) {
      Serial.print("TERANG     ");
    } else {
      Serial.print("REDUP      ");
    }

    Serial.print("\t| Lampu: ");
    Serial.println(lampuNyala ? "NYALA 💡" : "MATI 🌙");

    delay(500);  // Update setiap 500ms
  } else {
    // Mode normal: hanya tampilkan saat perubahan status
    delay(100);  // Cek setiap 100ms
  }
}

/*
  ===================================================================
  PENJELASAN KONSEP:
  ===================================================================

  1. LDR (Light Dependent Resistor):
     - Material: Cadmium Sulfide (CdS)
     - Resistansi berubah sesuai cahaya
     - Gelap: ~1MΩ (1.000.000 ohm)
     - Terang: ~1KΩ (1.000 ohm)
     - Tidak linear (non-linear response)

  2. VOLTAGE DIVIDER:
     Rangkaian pembagi tegangan untuk membaca LDR:

     Vout = Vin × (R2 / (R1 + R2))

     Dimana:
     - Vin = 3.3V
     - R1 = LDR (berubah sesuai cahaya)
     - R2 = 10KΩ (tetap)
     - Vout = tegangan yang dibaca ESP32

     Contoh perhitungan:
     - Gelap (LDR = 1MΩ):
       Vout = 3.3 × (10K / (1000K + 10K)) = 0.033V
       ADC = 0.033/3.3 × 4095 ≈ 40 (nilai rendah)

     - Terang (LDR = 1KΩ):
       Vout = 3.3 × (10K / (1K + 10K)) = 3.0V
       ADC = 3.0/3.3 × 4095 ≈ 3723 (nilai tinggi)

     CATATAN: Pada rangkaian ini, gelap = nilai rendah
     Jika ingin gelap = nilai tinggi, balik posisi LDR dan resistor

  3. ADC (Analog to Digital Converter):
     - ESP32 punya ADC 12-bit
     - Range: 0 - 4095 (2^12 - 1)
     - 0 = 0V, 4095 = 3.3V
     - Resolusi: 3.3V / 4095 ≈ 0.8 mV
     - Pin ADC1: GPIO32-39 (bisa pakai WiFi)
     - Pin ADC2: GPIO0,2,4,12-15,25-27 (tidak bisa pakai WiFi)

  4. HYSTERESIS (Dead Band):
     Teknik untuk mencegah flicker (nyala-mati cepat)

     Tanpa hysteresis:
     Threshold = 2500
     Nilai LDR naik-turun di sekitar 2500 → lampu flicker

     Dengan hysteresis:
     Threshold nyala = 2700
     Threshold mati = 2300
     Gap 400 = dead band

     Logika:
     - Lampu nyala jika nilai > 2700
     - Lampu tetap nyala sampai nilai < 2300
     - Range 2300-2700 = zona aman (tidak ada perubahan)

  5. THRESHOLD:
     Nilai ambang batas untuk pengambilan keputusan
     Cara menentukan:
     - Ukur nilai LDR saat gelap (misal: 3500)
     - Ukur nilai LDR saat terang (misal: 1500)
     - Threshold = (3500 + 1500) / 2 = 2500
     - Sesuaikan berdasarkan preferensi

  ===================================================================
  DIAGRAM ALIR (FLOWCHART):
  ===================================================================

  START
    ↓
  Baca nilai LDR
    ↓
  nilaiLDR > thresholdNyala && !lampuNyala?
    │
    YES → Nyalakan LED, lampuNyala = true
    │
    NO
    ↓
  nilaiLDR < thresholdMati && lampuNyala?
    │
    YES → Matikan LED, lampuNyala = false
    │
    NO
    ↓
  Tampilkan status (jika DEBUG_MODE)
    ↓
  Delay
    ↓
  (kembali ke loop)

  ===================================================================
  EKSPERIMEN YANG BISA DICOBA:
  ===================================================================

  1. Tambah 3 Level Kecerahan (PWM):
     // Ganti digitalWrite dengan analogWrite (PWM)
     if (nilaiLDR > 3500) {
       analogWrite(pinLED, 255);  // 100% terang
     } else if (nilaiLDR > 2500) {
       analogWrite(pinLED, 128);  // 50% terang
     } else if (nilaiLDR > 1500) {
       analogWrite(pinLED, 64);   // 25% terang
     } else {
       analogWrite(pinLED, 0);    // Mati
     }

  2. Mode Manual Override dengan Button:
     int pinButton = 4;
     bool modeManual = false;

     // Di setup:
     pinMode(pinButton, INPUT_PULLUP);

     // Di loop:
     if (digitalRead(pinButton) == LOW) {
       modeManual = !modeManual;  // Toggle mode
       delay(300);  // Debounce
     }

     if (modeManual) {
       // Kontrol manual (button lagi untuk toggle LED)
     } else {
       // Kontrol otomatis (pakai LDR)
     }

  3. Kalibrasi Otomatis:
     // Saat startup, rekam nilai min dan max
     int nilaiMin = 4095;
     int nilaiMax = 0;

     // Selama 10 detik pertama:
     for (int i = 0; i < 100; i++) {
       int nilai = analogRead(pinLDR);
       if (nilai < nilaiMin) nilaiMin = nilai;
       if (nilai > nilaiMax) nilaiMax = nilai;
       delay(100);
     }

     // Hitung threshold otomatis:
     int threshold = (nilaiMin + nilaiMax) / 2;

  4. Data Logging ke SD Card:
     // Simpan data LDR setiap 1 menit
     // Format: timestamp, nilai_ldr, status_lampu
     // Untuk analisis pola pencahayaan

  5. Kontrol via Bluetooth:
     // Kirim nilai LDR ke smartphone
     // Terima perintah on/off manual
     // Sesuaikan threshold dari app

  ===================================================================
  TROUBLESHOOTING:
  ===================================================================

  Masalah: Nilai LDR tidak berubah saat ditutup/dibuka
  Solusi:
  - Cek rangkaian voltage divider (LDR + 10K)
  - Pastikan pakai pin ADC (GPIO34-39)
  - Test LDR dengan multimeter (ukur resistansi)
  - Pastikan LDR tidak rusak (coba LDR lain)

  Masalah: Nilai LDR selalu 0 atau 4095
  Solusi:
  - Koneksi putus atau short
  - Cek breadboard dan jumper wire
  - Pastikan 3.3V dan GND terhubung benar

  Masalah: Lampu flicker (nyala-mati cepat)
  Solusi:
  - Tambah hysteresis (perbesar gap threshold)
  - Tambah delay di loop (misal 200ms)
  - Tambah kapasitor 10uF paralel dengan LDR
  - Gunakan moving average (filter software)

  Masalah: Threshold tidak tepat
  Solusi:
  - Nyalakan DEBUG_MODE
  - Amati nilai LDR di berbagai kondisi
  - Sesuaikan threshold secara manual
  - Atau gunakan potensiometer untuk adjust realtime

  Masalah: LED tidak menyala sama sekali
  Solusi:
  - Cek koneksi LED (polaritas benar?)
  - Cek resistor 220Ω terpasang
  - Test LED dengan upload kode blink sederhana
  - Pastikan pin LED ke GPIO2 (atau sesuai kode)

  ===================================================================
  KALIBRASI:
  ===================================================================

  Prosedur kalibrasi untuk menentukan threshold optimal:

  1. Upload kode dengan DEBUG_MODE = true
  2. Buka Serial Monitor (115200 baud)
  3. Catat nilai LDR dalam berbagai kondisi:

     Kondisi           | Nilai LDR | Catatan
     ------------------|-----------|------------------
     Ruangan gelap     |           |
     Redup             |           |
     Cahaya normal     |           |
     Terang (jendela)  |           |
     Senter langsung   |           |

  4. Tentukan threshold:
     - Jika ingin lampu nyala saat redup:
       threshold = (nilai_gelap + nilai_redup) / 2
     - Jika ingin lampu nyala hanya saat sangat gelap:
       threshold = nilai_gelap - 500

  5. Update nilai threshold di kode
  6. Set DEBUG_MODE = false untuk operasi normal

  ===================================================================
  APLIKASI DALAM BANGUNAN CERDAS:
  ===================================================================

  1. Street Lighting (Lampu Jalan):
     - Nyala otomatis saat senja
     - Mati otomatis saat pagi
     - Hemat energi (tidak perlu timer)
     - Adaptif (sesuai cuaca mendung/cerah)

  2. Office Lighting (Lampu Kantor):
     - Sesuaikan dengan cahaya alami
     - Dekat jendela: redup/mati saat siang
     - Jauh dari jendela: tetap nyala
     - Hemat energi 30-50%

  3. Parking Lot:
     - Lampu parkir nyala saat gelap
     - Dimmer saat tidak ada kendaraan (+ PIR)
     - Terang penuh saat ada aktivitas

  4. Billboard/Digital Signage:
     - Kecerahan layar menyesuaikan ambient
     - Terang di siang hari (agar terlihat)
     - Redup di malam (hemat energi + tidak silau)

  5. Automated Blinds (Tirai/Blind Otomatis):
     - Tutup saat matahari terik (AC hemat energi)
     - Buka saat mendung (manfaatkan cahaya alami)

  6. Greenhouse:
     - Monitor intensitas cahaya untuk tanaman
     - Nyalakan grow light jika kurang cahaya
     - Buka shade jika terlalu terang

  ===================================================================
*/
