/*
  ===================================================================
  TUGAS RUMAH 1: SIMULASI LAMPU LALU LINTAS
  ===================================================================

  Deskripsi:
  Membuat simulasi lampu lalu lintas sederhana dengan 3 LED yang
  bergantian menyala sesuai urutan: Merah → Kuning → Hijau

  Logika:
  - LED Merah nyala 5 detik (berhenti)
  - LED Kuning nyala 2 detik (bersiap)
  - LED Hijau nyala 5 detik (jalan)
  - Ulangi terus

  Komponen yang Dibutuhkan:
  - 1x ESP32 Development Board
  - 1x LED Merah
  - 1x LED Kuning
  - 1x LED Hijau
  - 3x Resistor 220 ohm
  - Kabel jumper
  - Breadboard

  Koneksi Rangkaian:
  GPIO2 ---> LED Merah (+) ---> Resistor 220Ω ---> GND
  GPIO4 ---> LED Kuning (+) ---> Resistor 220Ω ---> GND
  GPIO5 ---> LED Hijau (+) ---> Resistor 220Ω ---> GND

  Catatan:
  - Kaki panjang LED = Anoda (+) ke GPIO
  - Kaki pendek LED = Katoda (-) ke Resistor → GND

  Dibuat untuk: Mata Kuliah Bangunan Cerdas
  Instruktur: Anton Prafanto
  ===================================================================
*/

// ===== DEKLARASI PIN =====
const int pinMerah = 2;   // LED Merah
const int pinKuning = 4;  // LED Kuning
const int pinHijau = 5;   // LED Hijau

// ===== DEKLARASI WAKTU (dalam milidetik) =====
const int waktuMerah = 5000;   // 5 detik
const int waktuKuning = 2000;  // 2 detik
const int waktuHijau = 5000;   // 5 detik

// ===== FUNGSI SETUP =====
void setup() {
  // Inisialisasi Serial Monitor untuk debugging
  Serial.begin(115200);
  delay(1000);

  Serial.println("========================================");
  Serial.println("  SIMULASI LAMPU LALU LINTAS");
  Serial.println("========================================");
  Serial.println();

  // Set semua pin LED sebagai OUTPUT
  pinMode(pinMerah, OUTPUT);
  pinMode(pinKuning, OUTPUT);
  pinMode(pinHijau, OUTPUT);

  // Matikan semua LED di awal
  digitalWrite(pinMerah, LOW);
  digitalWrite(pinKuning, LOW);
  digitalWrite(pinHijau, LOW);

  Serial.println("Sistem siap!");
  Serial.println("Lampu lalu lintas dimulai...");
  Serial.println();

  delay(1000);
}

// ===== FUNGSI LOOP =====
void loop() {

  // ===== FASE 1: LAMPU MERAH (BERHENTI) =====
  Serial.println("🔴 MERAH - BERHENTI");
  digitalWrite(pinMerah, HIGH);   // Nyalakan merah
  digitalWrite(pinKuning, LOW);   // Matikan kuning
  digitalWrite(pinHijau, LOW);    // Matikan hijau

  delay(waktuMerah);  // Tunggu 5 detik

  // ===== FASE 2: LAMPU KUNING (BERSIAP) =====
  Serial.println("🟡 KUNING - BERSIAP");
  digitalWrite(pinMerah, LOW);    // Matikan merah
  digitalWrite(pinKuning, HIGH);  // Nyalakan kuning
  digitalWrite(pinHijau, LOW);    // Matikan hijau

  delay(waktuKuning);  // Tunggu 2 detik

  // ===== FASE 3: LAMPU HIJAU (JALAN) =====
  Serial.println("🟢 HIJAU - JALAN");
  digitalWrite(pinMerah, LOW);    // Matikan merah
  digitalWrite(pinKuning, LOW);   // Matikan kuning
  digitalWrite(pinHijau, HIGH);   // Nyalakan hijau

  delay(waktuHijau);  // Tunggu 5 detik

  Serial.println("---");

  // Loop akan mengulang dari awal (kembali ke merah)
}

/*
  ===================================================================
  PENJELASAN KONSEP:
  ===================================================================

  1. SISTEM LAMPU LALU LINTAS:
     - Mengatur arus lalu lintas dengan sinyal warna
     - Merah = Berhenti
     - Kuning = Bersiap (transisi)
     - Hijau = Jalan

     Urutan standar Indonesia:
     Merah → Kuning → Hijau → (kembali ke Merah)

  2. TIMING:
     - Waktu disimpan dalam konstanta (mudah diubah)
     - Menggunakan delay() untuk timing sederhana
     - Dalam aplikasi nyata: gunakan millis() untuk non-blocking

  3. KONTROL MULTI-LED:
     - Hanya 1 LED yang nyala di setiap fase
     - Matikan LED lain untuk menghindari kebingungan
     - digitalWrite() untuk setiap LED

  ===================================================================
  VARIASI & PENGEMBANGAN:
  ===================================================================

  1. LAMPU LALU LINTAS 4 ARAH:
     // Tambah LED untuk arah lain
     int pinMerah2 = 16;
     int pinKuning2 = 17;
     int pinHijau2 = 18;

     // Fase: Utara hijau + Timur merah
     // Lalu: Utara merah + Timur hijau

  2. MODE MALAM (KUNING KEDIP):
     // Jam 00:00 - 05:00 hanya kuning kedip
     void modeMalam() {
       digitalWrite(pinKuning, HIGH);
       delay(500);
       digitalWrite(pinKuning, LOW);
       delay(500);
     }

  3. TOMBOL PEJALAN KAKI:
     int pinButton = 15;

     if (digitalRead(pinButton) == LOW) {
       // Langsung pindah ke merah
       // Nyalakan lampu pejalan kaki (hijau)
       delay(10000);  // 10 detik untuk menyeberang
     }

  4. COUNTDOWN TIMER di OLED:
     // Tampilkan countdown waktu tersisa
     display.print(waktuTersisa);
     display.print(" detik");

  5. SENSOR KENDARAAN:
     // Pakai PIR atau sensor ultrasonik
     // Perpanjang hijau jika ada kendaraan
     if (adaKendaraan) {
       delay(5000);  // Tambah 5 detik
     }

  ===================================================================
  APLIKASI REAL-WORLD:
  ===================================================================

  1. PERSIMPANGAN JALAN:
     - Atur arus 2 atau 4 arah
     - Sinkronisasi antar lampu
     - Prioritas ambulans (semua merah kecuali jalur ambulans)

  2. SMART TRAFFIC LIGHT:
     - Sensor deteksi kepadatan
     - Perpanjang hijau di jalur padat
     - Kurangi waktu di jalur sepi
     - Machine learning untuk prediksi pola

  3. PERLINTASAN KERETA:
     - Merah menyala saat kereta datang
     - Palang pintu turun
     - Buzzer/alarm bunyi

  4. PARKIRAN:
     - Merah = penuh
     - Hijau = tersedia
     - Display jumlah slot

  5. ZONA SEKOLAH:
     - Kuning kedip saat jam sekolah
     - Kecepatan maksimal turun
     - Peringatan "HATI-HATI ANAK SEKOLAH"

  ===================================================================
  TROUBLESHOOTING:
  ===================================================================

  Masalah: Semua LED menyala bersamaan
  Solusi:
  - Pastikan matikan LED lain saat satu LED nyala
  - Cek tidak ada koneksi short antar pin

  Masalah: LED tidak nyala
  Solusi:
  - Cek polaritas LED (panjang = +, pendek = -)
  - Cek resistor terpasang (220Ω)
  - Test LED dengan blink sederhana
  - Ukur tegangan pin dengan multimeter

  Masalah: Timing tidak akurat
  Solusi:
  - delay() sudah cukup akurat untuk aplikasi ini
  - Jika perlu presisi tinggi: gunakan millis()
  - Perhatikan delay() di Serial.println juga konsumsi waktu

  Masalah: Serial Monitor tidak muncul teks
  Solusi:
  - Pastikan Serial.begin(115200)
  - Set baud rate Serial Monitor ke 115200
  - Tunggu 1-2 detik setelah upload

  ===================================================================
  TIPS PENGEMBANGAN:
  ===================================================================

  1. Gunakan array untuk timing:
     int waktu[] = {5000, 2000, 5000};
     for (int i = 0; i < 3; i++) {
       // Nyalakan LED
       delay(waktu[i]);
     }

  2. Buat fungsi untuk setiap fase:
     void faseMerah() {
       digitalWrite(pinMerah, HIGH);
       digitalWrite(pinKuning, LOW);
       digitalWrite(pinHijau, LOW);
       delay(waktuMerah);
     }

  3. State machine untuk kontrol kompleks:
     enum State { MERAH, KUNING, HIJAU };
     State currentState = MERAH;

  4. Integrasikan dengan RTC (Real-Time Clock):
     // Timing berbeda untuk siang vs malam
     // Sinkronisasi dengan waktu real

  5. Wireless control via WiFi/Bluetooth:
     // Kontrol dari pusat (traffic management center)
     // Ubah timing secara remote
     // Data logging ke cloud

  ===================================================================
*/
