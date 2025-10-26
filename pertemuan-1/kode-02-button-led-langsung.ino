/*
  ===================================================================
  PRAKTIKUM 2A: BUTTON KONTROL LED (Kontrol Langsung)
  ===================================================================

  Deskripsi:
  LED akan menyala selama tombol ditekan, dan mati saat tombol
  dilepas. Ini adalah kontrol langsung/realtime.

  Komponen yang Dibutuhkan:
  - 1x ESP32 Development Board
  - 1x LED (warna bebas)
  - 1x Push Button
  - 1x Resistor 220 ohm (untuk LED)
  - Kabel jumper
  - 1x Breadboard

  Koneksi Rangkaian:
  ESP32 GPIO2 ---> LED (+) ---> Resistor 220Ω ---> ESP32 GND
  ESP32 GPIO4 ---> Push Button ---> ESP32 GND

  Catatan: Kita menggunakan INTERNAL PULL-UP resistor ESP32,
  jadi tidak perlu resistor eksternal untuk button.

  Dibuat untuk: Mata Kuliah Bangunan Cerdas
  Instruktur: Anton Prafanto
  ===================================================================
*/

// ===== DEKLARASI PIN =====
int pinLED = 2;      // Pin untuk LED
int pinButton = 4;   // Pin untuk Push Button

// ===== FUNGSI SETUP =====
void setup() {
  // Set LED sebagai OUTPUT (kita kontrol LED)
  pinMode(pinLED, OUTPUT);

  // Set Button sebagai INPUT dengan PULL-UP internal
  pinMode(pinButton, INPUT_PULLUP);
  // INPUT_PULLUP artinya:
  // - Pin akan HIGH (3.3V) secara default (tidak ditekan)
  // - Pin akan LOW (0V) saat button ditekan (terhubung ke GND)

  // Matikan LED di awal program
  digitalWrite(pinLED, LOW);
}

// ===== FUNGSI LOOP =====
void loop() {

  // LANGKAH 1: Baca status button
  int statusButton = digitalRead(pinButton);
  // digitalRead() membaca sinyal digital dari pin
  // Hasilnya: HIGH (tidak ditekan) atau LOW (ditekan)

  // LANGKAH 2: Cek kondisi button dan kontrol LED
  if (statusButton == LOW) {
    // Kondisi: Button DITEKAN (LOW karena terhubung ke GND)
    digitalWrite(pinLED, HIGH);  // Nyalakan LED
  }
  else {
    // Kondisi: Button TIDAK DITEKAN (HIGH karena pull-up)
    digitalWrite(pinLED, LOW);   // Matikan LED
  }

  // LANGKAH 3: Delay kecil untuk stabilitas pembacaan
  delay(10);
  // Delay kecil ini mencegah pembacaan yang terlalu cepat
  // dan membantu stabilitas sistem
}

/*
  ===================================================================
  PENJELASAN KONSEP:
  ===================================================================

  1. INPUT_PULLUP:
     - Mengaktifkan resistor pull-up internal ESP32 (biasanya 45kΩ)
     - Membuat pin bernilai HIGH secara default
     - Saat button ditekan, pin terhubung ke GND → jadi LOW
     - Keuntungan: Tidak perlu resistor eksternal

  2. LOGIKA TERBALIK:
     - Button ditekan = LOW (bukan HIGH)
     - Button tidak ditekan = HIGH (bukan LOW)
     - Ini karena kita pakai pull-up
     - Alternatif: pakai INPUT dengan pull-down (perlu resistor eksternal)

  3. digitalRead():
     - Membaca nilai digital dari pin INPUT
     - Mengembalikan HIGH atau LOW
     - Hasil bisa disimpan dalam variabel

  4. IF-ELSE:
     - Struktur kontrol untuk membuat keputusan
     - if (kondisi) { jalankan jika true }
     - else { jalankan jika false }

  5. KONTROL REALTIME:
     - Respon langsung: tekan → nyala, lepas → mati
     - Tidak ada penyimpanan status
     - Cocok untuk: lampu tangga, lampu kulkas, dll

  ===================================================================
  DIAGRAM ALIR (FLOWCHART):
  ===================================================================

  START
    ↓
  Setup pin LED dan Button
    ↓
  ┌─────────────────┐
  │  LOOP FOREVER   │
  └────────┬────────┘
           ↓
  Baca status button
           ↓
     Button ditekan? ──NO──→ Matikan LED
           │                      ↓
          YES                     │
           │                      │
     Nyalakan LED                 │
           │                      │
           └──────────────────────┘
                    ↓
               Delay 10ms
                    ↓
              (kembali ke loop)

  ===================================================================
  EKSPERIMEN YANG BISA DICOBA:
  ===================================================================

  1. Balik logika (button tekan = LED mati):
     if (statusButton == LOW) {
       digitalWrite(pinLED, LOW);   // Mati saat ditekan
     } else {
       digitalWrite(pinLED, HIGH);  // Nyala saat tidak ditekan
     }

  2. Tambah LED kedua yang logikanya berlawanan:
     int pinLED2 = 5;
     pinMode(pinLED2, OUTPUT);
     // Di loop:
     if (statusButton == LOW) {
       digitalWrite(pinLED, HIGH);
       digitalWrite(pinLED2, LOW);
     } else {
       digitalWrite(pinLED, LOW);
       digitalWrite(pinLED2, HIGH);
     }

  3. Gunakan Serial Monitor untuk debugging:
     // Tambah di setup():
     Serial.begin(115200);

     // Tambah di loop setelah digitalRead:
     Serial.print("Status Button: ");
     Serial.println(statusButton);

     // Buka Serial Monitor (Tools > Serial Monitor)
     // Lihat nilai button saat ditekan/dilepas

  4. Buat button dengan debouncing manual:
     if (statusButton == LOW) {
       delay(50);  // Tunggu bouncing selesai
       if (digitalRead(pinButton) == LOW) {  // Baca ulang
         digitalWrite(pinLED, HIGH);
       }
     }

  ===================================================================
  TROUBLESHOOTING:
  ===================================================================

  Masalah: LED selalu nyala/mati, tidak tergantung button
  Solusi:
  - Pastikan pinMode(pinButton, INPUT_PULLUP) ada di setup
  - Cek koneksi button ke GPIO4 dan GND
  - Test button dengan Serial Monitor
  - Coba ganti pin button

  Masalah: LED berkedip-kedip saat button ditekan
  Solusi:
  - Button mengalami bouncing (getaran mekanis)
  - Tambah delay(50) setelah digitalRead
  - Atau gunakan kapasitor 0.1uF paralel dengan button

  Masalah: Button tidak responsif
  Solusi:
  - Pastikan button terpasang dengan benar di breadboard
  - Button 4 kaki: pastikan pakai kaki yang benar
  - Test dengan multimeter (continuity test)

  Masalah: LED redup saat button ditekan
  Solusi:
  - Cek resistor (harus 220Ω, bukan 10KΩ)
  - Cek koneksi jumper (mungkin longgar)

  ===================================================================
  APLIKASI DALAM BANGUNAN CERDAS:
  ===================================================================

  Konsep ini digunakan dalam:
  1. Lampu tangga darurat (tekan saat listrik mati)
  2. Lampu lemari/kulkas (switch di engsel pintu)
  3. Panic button (tombol darurat)
  4. Manual override untuk sistem otomatis
  5. Switch mode manual/otomatis

  ===================================================================
*/
