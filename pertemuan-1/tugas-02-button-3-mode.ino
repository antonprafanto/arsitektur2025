/*
  ===================================================================
  TUGAS RUMAH 2: TOMBOL DENGAN 3 MODE (LED RGB)
  ===================================================================

  Deskripsi:
  Membuat sistem dengan 1 tombol dan 1 LED RGB yang memiliki 3 mode
  warna. Setiap kali tombol ditekan, mode berganti ke warna berikutnya.

  Logika:
  - Tekan 1x: LED Merah
  - Tekan 2x: LED Hijau
  - Tekan 3x: LED Biru
  - Tekan 4x: Kembali ke Merah (cycle repeat)

  Komponen yang Dibutuhkan:
  - 1x ESP32 Development Board
  - 1x LED RGB (Common Cathode)
  - 1x Push Button
  - 3x Resistor 220 ohm (untuk RGB)
  - Kabel jumper
  - Breadboard

  Koneksi Rangkaian:
  LED RGB (Common Cathode):
  GPIO2 ---> R (Red pin) ---> Resistor 220Ω --->
  GPIO4 ---> G (Green pin) ---> Resistor 220Ω --->
  GPIO5 ---> B (Blue pin) ---> Resistor 220Ω --->
  Common Cathode (kaki paling panjang) ---> GND

  Push Button:
  GPIO15 ---> Button ---> GND (dengan INPUT_PULLUP)

  Catatan LED RGB:
  - Common Cathode: GND bersama, RGB ke GPIO (HIGH = nyala)
  - Common Anode: VCC bersama, RGB ke GPIO (LOW = nyala)
  - Kode ini untuk Common Cathode

  Dibuat untuk: Mata Kuliah Bangunan Cerdas
  Instruktur: Anton Prafanto
  ===================================================================
*/

// ===== DEKLARASI PIN =====
const int pinRed = 2;      // Pin merah LED RGB
const int pinGreen = 4;    // Pin hijau LED RGB
const int pinBlue = 5;     // Pin biru LED RGB
const int pinButton = 15;  // Pin push button

// ===== VARIABEL MODE =====
int mode = 0;  // Mode saat ini (0=merah, 1=hijau, 2=biru)

// ===== VARIABEL BUTTON =====
bool buttonSebelumnya = false;  // Status button di loop sebelumnya

// ===== FUNGSI SETUP =====
void setup() {
  // Inisialisasi Serial Monitor
  Serial.begin(115200);
  delay(1000);

  Serial.println("========================================");
  Serial.println("  TOMBOL 3 MODE - LED RGB");
  Serial.println("========================================");
  Serial.println();

  // Set pin LED sebagai OUTPUT
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);

  // Set pin button sebagai INPUT dengan PULL-UP
  pinMode(pinButton, INPUT_PULLUP);

  // Matikan semua LED di awal
  digitalWrite(pinRed, LOW);
  digitalWrite(pinGreen, LOW);
  digitalWrite(pinBlue, LOW);

  Serial.println("Sistem siap!");
  Serial.println("Tekan tombol untuk ganti mode warna");
  Serial.println();

  // Mulai dengan mode 0 (merah)
  tampilkanMode();
}

// ===== FUNGSI LOOP =====
void loop() {

  // Baca status button saat ini
  // INPUT_PULLUP: LOW = ditekan, HIGH = tidak ditekan
  bool buttonSekarang = (digitalRead(pinButton) == LOW);

  // Deteksi edge (button baru saja ditekan)
  if (buttonSekarang == true && buttonSebelumnya == false) {
    // Button BARU DITEKAN!

    // Tambah mode (cycle: 0 → 1 → 2 → 0)
    mode++;
    if (mode > 2) {
      mode = 0;  // Reset ke merah
    }

    // Tampilkan mode baru
    tampilkanMode();

    // Debouncing delay
    delay(50);
  }

  // Simpan status button untuk deteksi berikutnya
  buttonSebelumnya = buttonSekarang;

  delay(10);
}

// ===== FUNGSI TAMPILKAN MODE =====
void tampilkanMode() {
  // Matikan semua LED dulu
  digitalWrite(pinRed, LOW);
  digitalWrite(pinGreen, LOW);
  digitalWrite(pinBlue, LOW);

  // Nyalakan LED sesuai mode
  switch (mode) {
    case 0:
      // Mode 0: Merah
      digitalWrite(pinRed, HIGH);
      Serial.println("Mode 0: 🔴 MERAH");
      break;

    case 1:
      // Mode 1: Hijau
      digitalWrite(pinGreen, HIGH);
      Serial.println("Mode 1: 🟢 HIJAU");
      break;

    case 2:
      // Mode 2: Biru
      digitalWrite(pinBlue, HIGH);
      Serial.println("Mode 2: 🔵 BIRU");
      break;
  }
}

/*
  ===================================================================
  PENJELASAN KONSEP:
  ===================================================================

  1. LED RGB:
     - RGB = Red, Green, Blue
     - 3 LED dalam 1 package
     - Bisa menghasilkan banyak warna dengan kombinasi

     Jenis:
     - Common Cathode: GND bersama, HIGH = nyala
     - Common Anode: VCC bersama, LOW = nyala

     Warna yang bisa dibuat:
     - Merah: R=HIGH, G=LOW, B=LOW
     - Hijau: R=LOW, G=HIGH, B=LOW
     - Biru: R=LOW, G=LOW, B=HIGH
     - Kuning: R=HIGH, G=HIGH, B=LOW
     - Cyan: R=LOW, G=HIGH, B=HIGH
     - Magenta: R=HIGH, G=LOW, B=HIGH
     - Putih: R=HIGH, G=HIGH, B=HIGH
     - Mati: R=LOW, G=LOW, B=LOW

  2. MODE SYSTEM:
     - Variabel 'mode' menyimpan state saat ini
     - Setiap tekan button → mode++
     - Gunakan modulo (%) atau if untuk cycle

     Alternatif dengan modulo:
     mode = (mode + 1) % 3;
     // 0 → 1 → 2 → 0 → 1 → ...

  3. EDGE DETECTION:
     - Deteksi perubahan LOW → HIGH (button ditekan)
     - Mencegah multiple trigger saat button ditahan
     - Penting untuk counter/mode switcher

  4. SWITCH-CASE:
     - Alternatif if-else untuk banyak kondisi
     - Lebih rapi untuk multiple mode
     - Setiap case harus ada break

  ===================================================================
  VARIASI & PENGEMBANGAN:
  ===================================================================

  1. TAMBAH MODE LEBIH BANYAK (7 warna):
     case 3: // Kuning
       digitalWrite(pinRed, HIGH);
       digitalWrite(pinGreen, HIGH);
       digitalWrite(pinBlue, LOW);
       break;

     case 4: // Cyan
       digitalWrite(pinRed, LOW);
       digitalWrite(pinGreen, HIGH);
       digitalWrite(pinBlue, HIGH);
       break;

     case 5: // Magenta
       digitalWrite(pinRed, HIGH);
       digitalWrite(pinGreen, LOW);
       digitalWrite(pinBlue, HIGH);
       break;

     case 6: // Putih
       digitalWrite(pinRed, HIGH);
       digitalWrite(pinGreen, HIGH);
       digitalWrite(pinBlue, HIGH);
       break;

  2. MODE FADE (Transisi Smooth):
     // Gunakan PWM analogWrite()
     void fadeToColor(int r, int g, int b) {
       for (int i = 0; i <= 255; i++) {
         analogWrite(pinRed, (r * i) / 255);
         analogWrite(pinGreen, (g * i) / 255);
         analogWrite(pinBlue, (b * i) / 255);
         delay(5);
       }
     }

  3. MODE RAINBOW (Pelangi Otomatis):
     void rainbow() {
       // Merah → Kuning → Hijau → Cyan → Biru → Magenta → Merah
       for (int hue = 0; hue < 360; hue++) {
         setHSV(hue, 100, 100);  // Fungsi HSV to RGB
         delay(10);
       }
     }

  4. MODE BERKEDIP:
     case 3: // Merah Kedip
       for (int i = 0; i < 5; i++) {
         digitalWrite(pinRed, HIGH);
         delay(200);
         digitalWrite(pinRed, LOW);
         delay(200);
       }
       break;

  5. BRIGHTNESS CONTROL:
     int brightness = 128;  // 0-255

     // Gunakan analogWrite untuk PWM
     analogWrite(pinRed, brightness);
     analogWrite(pinGreen, brightness);
     analogWrite(pinBlue, brightness);

  6. DOUBLE-CLICK DETECTION:
     // Tekan 2x cepat untuk fungsi khusus
     unsigned long lastPress = 0;
     const int doubleClickTime = 300;  // 300ms

     if (millis() - lastPress < doubleClickTime) {
       // Double click terdeteksi!
       modeKhusus();
     }
     lastPress = millis();

  ===================================================================
  APLIKASI DALAM BANGUNAN CERDAS:
  ===================================================================

  1. AMBIENT LIGHTING:
     - Mode 1: Cahaya hangat (kuning) untuk santai
     - Mode 2: Cahaya putih untuk kerja
     - Mode 3: Cahaya biru untuk fokus
     - Mode 4: Rainbow untuk pesta

  2. STATUS INDICATOR:
     - Hijau: Sistem normal
     - Kuning: Warning/maintenance
     - Merah: Error/alarm
     - Biru: Standby/night mode

  3. MOOD LIGHTING:
     - Sesuaikan warna ruangan dengan aktivitas
     - Meeting: Putih terang
     - Relax: Biru lembut
     - Makan: Kuning hangat

  4. SMART BULB:
     - Kontrol warna lampu
     - Jadwal otomatis (pagi=putih, malam=kuning)
     - Integrasi dengan sensor (suhu, waktu)

  5. THEATER MODE:
     - Cinema: Redup + biru
     - Gaming: RGB cycling
     - Reading: Putih terang

  ===================================================================
  TROUBLESHOOTING:
  ===================================================================

  Masalah: LED tidak nyala sama sekali
  Solusi:
  - Cek jenis LED RGB (Common Cathode vs Anode)
  - Untuk Common Anode: balik logika (LOW = nyala)
  - Cek koneksi common ke GND (cathode) atau VCC (anode)

  Masalah: Warna tidak sesuai (misal merah jadi hijau)
  Solusi:
  - Pin RGB mungkin ketukar
  - Test satu-satu: nyalakan hanya R, lalu G, lalu B
  - Sesuaikan pin di kode

  Masalah: Button tidak responsif
  Solusi:
  - Pastikan pakai INPUT_PULLUP
  - Cek koneksi button ke GPIO dan GND
  - Tambah delay debouncing (50-100ms)

  Masalah: Mode loncat-loncat (skip)
  Solusi:
  - Bouncing! Button tertekan multiple kali
  - Tambah delay(50) setelah mode++
  - Atau gunakan library Bounce2

  Masalah: LED RGB redup/tidak terang
  Solusi:
  - Resistor terlalu besar (pakai 220Ω)
  - Cek tegangan dengan multimeter
  - Gunakan transistor untuk arus lebih besar

  ===================================================================
  TIPS LANJUTAN:
  ===================================================================

  1. Simpan mode ke EEPROM (tetap saat mati listrik):
     #include <EEPROM.h>

     void setup() {
       EEPROM.begin(1);
       mode = EEPROM.read(0);  // Baca mode terakhir
     }

     void tampilkanMode() {
       // ... kode tampil mode
       EEPROM.write(0, mode);  // Simpan mode
       EEPROM.commit();
     }

  2. Kontrol via Serial (debugging):
     if (Serial.available()) {
       char cmd = Serial.read();
       if (cmd == '0') mode = 0;
       if (cmd == '1') mode = 1;
       if (cmd == '2') mode = 2;
       tampilkanMode();
     }

  3. Animasi transisi:
     void transisiKeMode(int modeBaru) {
       // Fade out dulu
       for (int i = 255; i >= 0; i--) {
         // ... fade out
       }
       mode = modeBaru;
       // Fade in ke warna baru
       for (int i = 0; i <= 255; i++) {
         // ... fade in
       }
     }

  ===================================================================
*/
