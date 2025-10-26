/*
  ===================================================================
  PRAKTIKUM 1: LED BLINK (Berkedip)
  ===================================================================

  Deskripsi:
  Program ini membuat LED berkedip dengan pola nyala 1 detik,
  mati 1 detik, secara berulang.

  Komponen yang Dibutuhkan:
  - 1x ESP32 Development Board
  - 1x LED (warna bebas)
  - 1x Resistor 220 ohm
  - 2x Kabel jumper
  - 1x Breadboard

  Koneksi Rangkaian:
  ESP32 GPIO2 ---> LED (kaki panjang/+)
  LED (kaki pendek/-) ---> Resistor 220Ω ---> ESP32 GND

  Cara Upload:
  1. Hubungkan ESP32 ke komputer via USB
  2. Pilih Board: Tools > Board > ESP32 Dev Module
  3. Pilih Port: Tools > Port > (pilih COM yang tersedia)
  4. Klik tombol Upload (panah kanan)

  Dibuat untuk: Mata Kuliah Bangunan Cerdas
  Instruktur: Anton Prafanto
  ===================================================================
*/

// ===== DEKLARASI PIN =====
// Mendefinisikan pin yang akan digunakan untuk LED
// GPIO2 adalah pin internal LED pada kebanyakan board ESP32
int pinLED = 2;

// ===== FUNGSI SETUP =====
// Fungsi ini dijalankan SATU KALI saat ESP32 pertama kali dinyalakan
// Digunakan untuk konfigurasi awal
void setup() {
  // Mengatur pinLED sebagai OUTPUT
  // OUTPUT berarti pin ini akan MENGIRIM sinyal keluar (ke LED)
  pinMode(pinLED, OUTPUT);

  // Catatan: pinMode() harus dipanggil untuk setiap pin yang digunakan
  // Pilihan mode: OUTPUT (mengirim sinyal) atau INPUT (menerima sinyal)
}

// ===== FUNGSI LOOP =====
// Fungsi ini dijalankan BERULANG-ULANG selamanya setelah setup() selesai
// Seperti while(true) atau perulangan tak terbatas
void loop() {

  // LANGKAH 1: Nyalakan LED
  digitalWrite(pinLED, HIGH);
  // HIGH berarti mengirim tegangan 3.3V ke pin
  // Ini membuat LED menyala

  // LANGKAH 2: Tunggu 1 detik
  delay(1000);
  // delay() membuat program berhenti sementara
  // Satuan dalam milidetik (1000 ms = 1 detik)
  // Selama delay, LED tetap menyala

  // LANGKAH 3: Matikan LED
  digitalWrite(pinLED, LOW);
  // LOW berarti mengirim tegangan 0V ke pin
  // Ini membuat LED mati

  // LANGKAH 4: Tunggu 1 detik
  delay(1000);
  // LED tetap mati selama 1 detik

  // Setelah baris ini, loop() akan dijalankan lagi dari awal
  // Sehingga LED akan berkedip: nyala → mati → nyala → mati → ...
}

/*
  ===================================================================
  PENJELASAN KONSEP:
  ===================================================================

  1. DIGITAL OUTPUT:
     - digitalWrite() mengirim sinyal digital (hanya 2 nilai: HIGH atau LOW)
     - HIGH = 3.3V = 1 = nyala
     - LOW = 0V = 0 = mati

  2. DELAY:
     - delay(1000) = tunggu 1000 milidetik = 1 detik
     - Selama delay, program berhenti (tidak bisa melakukan hal lain)
     - Ini disebut "blocking delay"

  3. LOOP:
     - loop() berjalan terus menerus
     - Urutan: setup() → loop() → loop() → loop() → ...
     - Tidak ada kondisi berhenti

  ===================================================================
  EKSPERIMEN YANG BISA DICOBA:
  ===================================================================

  1. Ubah kecepatan kedip:
     - Ganti delay(1000) menjadi delay(500) → lebih cepat
     - Ganti delay(1000) menjadi delay(2000) → lebih lambat

  2. Buat pola kedip berbeda:
     - Nyala sebentar, mati lama: delay(200) dan delay(2000)
     - Nyala lama, mati sebentar: delay(2000) dan delay(200)

  3. Buat kedip SOS (morse code):
     - S = 3 kedip cepat
     - O = 3 kedip lambat
     - S = 3 kedip cepat

  4. Buat lampu fade (bonus):
     - Gunakan analogWrite() untuk mengatur kecerahan
     - Contoh: analogWrite(pinLED, 128) → setengah terang

  ===================================================================
  TROUBLESHOOTING:
  ===================================================================

  Masalah: LED tidak menyala
  Solusi:
  - Cek polaritas LED (kaki panjang ke GPIO, kaki pendek ke GND)
  - Pastikan resistor terpasang
  - Coba ganti pin (misalnya ke GPIO4)
  - Coba LED lain (mungkin rusak)

  Masalah: Error saat upload
  Solusi:
  - Tekan dan tahan tombol BOOT saat upload
  - Cek kabel USB (harus bisa transfer data)
  - Pilih port COM yang benar
  - Install ulang driver CH340/CP2102

  Masalah: LED redup sekali
  Solusi:
  - Resistor terlalu besar, coba pakai 220Ω
  - Cek tegangan pin dengan multimeter

  ===================================================================
*/
