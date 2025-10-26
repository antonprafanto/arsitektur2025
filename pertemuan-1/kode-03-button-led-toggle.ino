/*
  ===================================================================
  PRAKTIKUM 2B: BUTTON TOGGLE LED (ON/OFF)
  ===================================================================

  Deskripsi:
  Setiap kali tombol ditekan, LED akan berganti status (toggle).
  - Tekan 1x: LED nyala
  - Tekan lagi: LED mati
  - Tekan lagi: LED nyala
  - Dan seterusnya...

  Ini mirip saklar lampu rumah biasa (on/off).

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

  Dibuat untuk: Mata Kuliah Bangunan Cerdas
  Instruktur: Anton Prafanto
  ===================================================================
*/

// ===== DEKLARASI PIN =====
int pinLED = 2;
int pinButton = 4;

// ===== VARIABEL STATUS =====
// Variabel untuk menyimpan kondisi LED saat ini
bool statusLED = false;  // false = mati, true = nyala

// Variabel untuk deteksi perubahan button (edge detection)
bool buttonSebelumnya = false;  // Status button di loop sebelumnya

// ===== FUNGSI SETUP =====
void setup() {
  // Set pin mode
  pinMode(pinLED, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Pastikan LED mati di awal
  digitalWrite(pinLED, LOW);

  // (Opsional) Aktifkan Serial Monitor untuk debugging
  Serial.begin(115200);
  Serial.println("Program Toggle LED siap!");
  Serial.println("Tekan button untuk toggle LED ON/OFF");
}

// ===== FUNGSI LOOP =====
void loop() {

  // LANGKAH 1: Baca status button saat ini
  // INPUT_PULLUP: LOW = ditekan, HIGH = tidak ditekan
  bool buttonSekarang = (digitalRead(pinButton) == LOW);
  // Hasil: true jika ditekan, false jika tidak

  // LANGKAH 2: Deteksi PERUBAHAN dari tidak ditekan → ditekan
  // Ini disebut "edge detection" atau "rising edge"
  if (buttonSekarang == true && buttonSebelumnya == false) {
    // Button BARU SAJA ditekan (perubahan dari false ke true)

    // LANGKAH 3: Toggle (balik) status LED
    statusLED = !statusLED;
    // Operator ! = NOT (membalik boolean)
    // Jika statusLED = false → jadi true
    // Jika statusLED = true → jadi false

    // LANGKAH 4: Update LED sesuai status baru
    if (statusLED == true) {
      digitalWrite(pinLED, HIGH);  // Nyalakan LED
      Serial.println("LED: NYALA");
    } else {
      digitalWrite(pinLED, LOW);   // Matikan LED
      Serial.println("LED: MATI");
    }

    // LANGKAH 5: Debouncing
    // Tunggu sebentar untuk mencegah deteksi ganda
    delay(50);
  }

  // LANGKAH 6: Simpan status button untuk loop berikutnya
  buttonSebelumnya = buttonSekarang;

  // Delay kecil untuk stabilitas
  delay(10);
}

/*
  ===================================================================
  PENJELASAN KONSEP:
  ===================================================================

  1. VARIABEL BOOLEAN:
     - Tipe data yang hanya punya 2 nilai: true atau false
     - Cocok untuk status on/off, nyala/mati, aktif/non-aktif
     - Contoh: bool lampu = true; bool kipas = false;

  2. TOGGLE (Pembalikan Status):
     - Toggle = membalik nilai boolean
     - Menggunakan operator NOT (!)
     - statusLED = !statusLED;
       → false jadi true
       → true jadi false
     - Alternatif: statusLED = (statusLED == false) ? true : false;

  3. EDGE DETECTION (Deteksi Perubahan):
     - Tidak cukup hanya cek "button ditekan?"
     - Harus cek "button BARU ditekan?" (perubahan status)
     - Cara: bandingkan status sekarang vs sebelumnya
     - Pola: (sekarang == true) && (sebelumnya == false)
     - Ini mencegah toggle berkali-kali saat button ditahan

  4. DEBOUNCING:
     - Button mekanis mengalami "bouncing" (getaran)
     - Satu tekanan bisa terbaca sebagai beberapa tekanan
     - Solusi: delay kecil (50ms) setelah deteksi
     - Atau gunakan kapasitor untuk hardware debouncing

  5. PENYIMPANAN STATUS:
     - Berbeda dengan kode sebelumnya (kontrol langsung)
     - Di sini kita SIMPAN status LED dalam variabel
     - Status tetap ada meskipun button sudah dilepas
     - Ini disebut "stateful programming"

  ===================================================================
  DIAGRAM ALIR (FLOWCHART):
  ===================================================================

  START
    ↓
  Setup: statusLED = false, buttonSebelumnya = false
    ↓
  ┌─────────────────────────┐
  │      LOOP FOREVER       │
  └───────────┬─────────────┘
              ↓
  Baca buttonSekarang
              ↓
  buttonSekarang==true && buttonSebelumnya==false?
              │
         NO───┴───YES
         │         │
         │    Toggle statusLED (balik nilai)
         │         │
         │    Update LED sesuai statusLED
         │         │
         │    Delay 50ms (debouncing)
         │         │
         └─────────┘
              ↓
  buttonSebelumnya = buttonSekarang
              ↓
  Delay 10ms
              ↓
  (kembali ke loop)

  ===================================================================
  TABEL LOGIKA (Truth Table):
  ===================================================================

  buttonSekarang | buttonSebelumnya | Deteksi | Aksi
  ---------------|------------------|---------|------------------
  false          | false            | -       | Tidak ada
  false          | true             | -       | Tidak ada
  true           | false            | YA!     | Toggle LED
  true           | true             | -       | Tidak ada (ditahan)

  Hanya baris ke-3 yang akan trigger toggle!

  ===================================================================
  EKSPERIMEN YANG BISA DICOBA:
  ===================================================================

  1. Hitung jumlah tekanan button:
     int counter = 0;
     // Di dalam if edge detection:
     counter++;
     Serial.print("Ditekan: ");
     Serial.println(counter);

  2. Buat 3 mode dengan 1 button:
     int mode = 0;
     // Di dalam if edge detection:
     mode++;
     if (mode > 2) mode = 0;  // Reset ke 0 setelah 2

     if (mode == 0) {
       digitalWrite(pinLED, LOW);   // Mati
     } else if (mode == 1) {
       digitalWrite(pinLED, HIGH);  // Nyala terang
     } else if (mode == 2) {
       // Blink mode (perlu kode tambahan)
     }

  3. Long press detection (tekan lama vs pendek):
     unsigned long waktutombolDitekan = 0;

     // Saat button ditekan:
     if (buttonSekarang && !buttonSebelumnya) {
       waktutombolDitekan = millis();
     }

     // Saat button dilepas:
     if (!buttonSekarang && buttonSebelumnya) {
       unsigned long durasi = millis() - waktutombolDitekan;
       if (durasi > 2000) {
         Serial.println("Long press!");
       } else {
         Serial.println("Short press!");
       }
     }

  4. Kombinasi 2 button untuk 2 LED:
     // LED1: toggle dengan button1
     // LED2: toggle dengan button2
     // Bisa buat mode: red only, green only, both, none

  ===================================================================
  TROUBLESHOOTING:
  ===================================================================

  Masalah: LED toggle beberapa kali dalam 1 tekanan
  Solusi:
  - Bouncing! Tambah delay(50) setelah toggle
  - Atau tambah delay(100) untuk button yang lebih bouncy
  - Hardware solution: tambah kapasitor 0.1uF paralel button

  Masalah: LED tidak toggle saat ditekan
  Solusi:
  - Cek Serial Monitor untuk lihat nilai button
  - Pastikan edge detection bekerja dengan print:
    Serial.print("Sekarang: "); Serial.print(buttonSekarang);
    Serial.print(" Sebelumnya: "); Serial.println(buttonSebelumnya);
  - Cek variabel buttonSebelumnya sudah di-update

  Masalah: LED toggle saat tidak ada tekanan
  Solusi:
  - Koneksi button longgar
  - Interferensi elektromagnetik (jauhkan dari motor/relay)
  - Tambah kapasitor filter di button

  Masalah: Serial Monitor tidak muncul tulisan
  Solusi:
  - Pastikan Serial.begin(115200) ada di setup
  - Pilih baud rate 115200 di Serial Monitor
  - Tunggu 2 detik setelah upload baru buka Serial Monitor

  ===================================================================
  APLIKASI DALAM BANGUNAN CERDAS:
  ===================================================================

  Konsep toggle ini digunakan dalam:

  1. Saklar Lampu Digital:
     - 1 tombol untuk on/off
     - Status tersimpan meskipun listrik mati (dengan EEPROM)

  2. Mode Switching:
     - Mode hemat energi / mode normal
     - Mode manual / mode otomatis
     - Siang / malam

  3. Pengunci Pintu Digital:
     - Tekan untuk kunci
     - Tekan lagi untuk buka
     - Status kunci tersimpan

  4. Sistem Ventilasi:
     - ON: kipas nyala
     - OFF: kipas mati
     - Status tetap meskipun button dilepas

  5. Kontrol Scene Pencahayaan:
     - Tekan 1x: scene romantis
     - Tekan 2x: scene kerja
     - Tekan 3x: scene santai
     - Tekan 4x: mati

  ===================================================================
  PENGEMBANGAN LANJUTAN:
  ===================================================================

  Dari kode ini bisa dikembangkan menjadi:

  1. Multi-button Input:
     - Kombinasi button untuk berbagai fungsi
     - Contoh: button1+button2 = reset

  2. Long Press vs Short Press:
     - Tekan singkat: toggle
     - Tekan lama (>2 detik): mode khusus

  3. Double Click Detection:
     - Deteksi 2 tekanan dalam waktu singkat
     - Untuk fungsi khusus (seperti mouse double click)

  4. State Machine:
     - Banyak mode dengan transisi tertentu
     - Diagram state: idle → active → standby → idle

  5. Simpan Status ke EEPROM:
     - Status tetap ada meskipun mati listrik
     - Bermanfaat untuk sistem keamanan

  ===================================================================
*/
