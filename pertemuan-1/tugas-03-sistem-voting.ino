/*
  ===================================================================
  TUGAS RUMAH 3: SISTEM VOTING SEDERHANA
  ===================================================================

  Deskripsi:
  Membuat sistem voting dengan 2 pilihan menggunakan 2 tombol dan 2 LED.
  Setiap tombol mewakili 1 kandidat, dan LED menunjukkan pemenang.

  Fitur:
  - Button A (kandidat merah)
  - Button B (kandidat hijau)
  - LED merah nyala jika kandidat A unggul
  - LED hijau nyala jika kandidat B unggul
  - Kedua LED nyala jika seri
  - Serial Monitor menampilkan hasil vote real-time
  - Button Reset untuk mulai voting baru

  Komponen yang Dibutuhkan:
  - 1x ESP32 Development Board
  - 2x Push Button (vote A dan B)
  - 1x Push Button (reset)
  - 1x LED Merah
  - 1x LED Hijau
  - 2x Resistor 220 ohm
  - Kabel jumper
  - Breadboard

  Koneksi Rangkaian:
  Button A (Vote Merah): GPIO15 ---> Button ---> GND
  Button B (Vote Hijau): GPIO16 ---> Button ---> GND
  Button Reset: GPIO17 ---> Button ---> GND
  LED Merah: GPIO2 ---> LED ---> Resistor 220Ω ---> GND
  LED Hijau: GPIO4 ---> LED ---> Resistor 220Ω ---> GND

  Aplikasi:
  - Voting kelas/organisasi
  - Polling pendapat
  - Game quiz
  - Feedback sistem (puas/tidak puas)

  Dibuat untuk: Mata Kuliah Bangunan Cerdas
  Instruktur: Anton Prafanto
  ===================================================================
*/

// ===== DEKLARASI PIN =====
const int pinButtonA = 15;     // Button vote A (merah)
const int pinButtonB = 16;     // Button vote B (hijau)
const int pinButtonReset = 17; // Button reset
const int pinLEDMerah = 2;     // LED merah (kandidat A)
const int pinLEDHijau = 4;     // LED hijau (kandidat B)

// ===== VARIABEL VOTING =====
int voteA = 0;  // Jumlah vote kandidat A
int voteB = 0;  // Jumlah vote kandidat B

// ===== VARIABEL BUTTON STATE =====
bool buttonA_sebelumnya = false;
bool buttonB_sebelumnya = false;
bool buttonReset_sebelumnya = false;

// ===== FUNGSI SETUP =====
void setup() {
  // Inisialisasi Serial Monitor
  Serial.begin(115200);
  delay(1000);

  Serial.println("========================================");
  Serial.println("     SISTEM VOTING SEDERHANA");
  Serial.println("========================================");
  Serial.println();
  Serial.println("Tekan Button A untuk vote MERAH");
  Serial.println("Tekan Button B untuk vote HIJAU");
  Serial.println("Tekan Button Reset untuk mulai lagi");
  Serial.println("========================================");
  Serial.println();

  // Set pin button sebagai INPUT dengan PULL-UP
  pinMode(pinButtonA, INPUT_PULLUP);
  pinMode(pinButtonB, INPUT_PULLUP);
  pinMode(pinButtonReset, INPUT_PULLUP);

  // Set pin LED sebagai OUTPUT
  pinMode(pinLEDMerah, OUTPUT);
  pinMode(pinLEDHijau, OUTPUT);

  // Matikan LED di awal
  digitalWrite(pinLEDMerah, LOW);
  digitalWrite(pinLEDHijau, LOW);

  // Tampilkan hasil awal (0-0)
  tampilkanHasil();
}

// ===== FUNGSI LOOP =====
void loop() {

  // ===== CEK BUTTON A (VOTE MERAH) =====
  bool buttonA_sekarang = (digitalRead(pinButtonA) == LOW);

  if (buttonA_sekarang && !buttonA_sebelumnya) {
    // Button A baru ditekan
    voteA++;
    Serial.println("✅ Vote untuk KANDIDAT A (MERAH)");
    tampilkanHasil();
    updateLED();
    delay(50);  // Debouncing
  }

  buttonA_sebelumnya = buttonA_sekarang;

  // ===== CEK BUTTON B (VOTE HIJAU) =====
  bool buttonB_sekarang = (digitalRead(pinButtonB) == LOW);

  if (buttonB_sekarang && !buttonB_sebelumnya) {
    // Button B baru ditekan
    voteB++;
    Serial.println("✅ Vote untuk KANDIDAT B (HIJAU)");
    tampilkanHasil();
    updateLED();
    delay(50);  // Debouncing
  }

  buttonB_sebelumnya = buttonB_sekarang;

  // ===== CEK BUTTON RESET =====
  bool buttonReset_sekarang = (digitalRead(pinButtonReset) == LOW);

  if (buttonReset_sekarang && !buttonReset_sebelumnya) {
    // Button reset ditekan
    voteA = 0;
    voteB = 0;
    Serial.println();
    Serial.println("🔄 RESET! Voting dimulai dari 0");
    Serial.println("========================================");
    tampilkanHasil();
    updateLED();
    delay(50);  // Debouncing
  }

  buttonReset_sebelumnya = buttonReset_sekarang;

  delay(10);
}

// ===== FUNGSI TAMPILKAN HASIL =====
void tampilkanHasil() {
  Serial.println();
  Serial.println("┌─────────────────────────────┐");
  Serial.println("│     HASIL VOTING SAAT INI   │");
  Serial.println("├─────────────────────────────┤");

  Serial.print("│ 🔴 Kandidat A: ");
  Serial.print(voteA);
  Serial.print(" vote");
  if (voteA != 1) Serial.print("s");
  Serial.println("        │");

  Serial.print("│ 🟢 Kandidat B: ");
  Serial.print(voteB);
  Serial.print(" vote");
  if (voteB != 1) Serial.print("s");
  Serial.println("        │");

  Serial.println("├─────────────────────────────┤");

  // Tentukan pemenang
  if (voteA > voteB) {
    Serial.println("│ Pemenang: 🔴 KANDIDAT A     │");
  } else if (voteB > voteA) {
    Serial.println("│ Pemenang: 🟢 KANDIDAT B     │");
  } else {
    Serial.println("│ Status: 🤝 SERI             │");
  }

  Serial.println("└─────────────────────────────┘");
  Serial.println();
}

// ===== FUNGSI UPDATE LED =====
void updateLED() {
  if (voteA > voteB) {
    // A unggul: LED merah nyala, hijau mati
    digitalWrite(pinLEDMerah, HIGH);
    digitalWrite(pinLEDHijau, LOW);
  } else if (voteB > voteA) {
    // B unggul: LED hijau nyala, merah mati
    digitalWrite(pinLEDMerah, LOW);
    digitalWrite(pinLEDHijau, HIGH);
  } else {
    // Seri: kedua LED nyala
    digitalWrite(pinLEDMerah, HIGH);
    digitalWrite(pinLEDHijau, HIGH);
  }
}

/*
  ===================================================================
  PENJELASAN KONSEP:
  ===================================================================

  1. SISTEM VOTING:
     - Counter untuk setiap kandidat
     - Increment counter saat button ditekan
     - Perbandingan untuk tentukan pemenang

  2. EDGE DETECTION:
     - Deteksi button "baru ditekan"
     - Mencegah multiple count saat button ditahan
     - Pattern: (now && !before)

  3. INDIKATOR VISUAL:
     - LED menunjukkan pemenang real-time
     - Merah = A unggul
     - Hijau = B unggul
     - Kedua nyala = seri

  4. RESET FUNCTIONALITY:
     - Kembalikan counter ke 0
     - Mulai voting baru
     - Clear display

  ===================================================================
  VARIASI & PENGEMBANGAN:
  ===================================================================

  1. VOTING 3 KANDIDAT:
     int voteC = 0;
     int pinButtonC = 18;
     int pinLEDBiru = 5;

     // Logika LED lebih kompleks (pakai if-else)

  2. BATAS WAKTU VOTING:
     unsigned long waktuMulai = millis();
     const unsigned long durasiVoting = 60000;  // 60 detik

     if (millis() - waktuMulai > durasiVoting) {
       // Voting selesai
       tutupVoting();
     }

  3. BATAS JUMLAH VOTER:
     const int maxVoter = 10;
     int totalVote = voteA + voteB;

     if (totalVote >= maxVoter) {
       // Voting penuh
       Serial.println("Voting ditutup (kuota penuh)");
     }

  4. TAMPILKAN DI OLED:
     display.clearDisplay();
     display.setTextSize(1);
     display.setCursor(0, 0);
     display.println("VOTING");
     display.print("A: ");
     display.println(voteA);
     display.print("B: ");
     display.println(voteB);
     display.display();

  5. PERCENTAGE BAR:
     int totalVote = voteA + voteB;
     if (totalVote > 0) {
       int persenA = (voteA * 100) / totalVote;
       int persenB = (voteB * 100) / totalVote;

       Serial.print("A: ");
       Serial.print(persenA);
       Serial.println("%");
       Serial.print("B: ");
       Serial.print(persenB);
       Serial.println("%");
     }

  6. BUZZER SAAT VOTE:
     digitalWrite(pinBuzzer, HIGH);
     delay(100);
     digitalWrite(pinBuzzer, LOW);

  7. ANTI-CHEAT (1 ORANG 1 VOTE):
     // Gunakan RFID card atau fingerprint
     // Cek apakah user sudah vote
     bool sudahVote[100];  // Array untuk track user

  ===================================================================
  APLIKASI REAL-WORLD:
  ===================================================================

  1. VOTING ORGANISASI:
     - Pemilihan ketua/anggota
     - Real-time result display
     - Anonymous voting

  2. FEEDBACK SYSTEM:
     - Puas / Tidak Puas
     - Like / Dislike
     - Restoran, hotel, event

  3. QUIZ/GAME:
     - Pilihan A atau B
     - Fastest finger first
     - Audience poll

  4. SMART BUILDING:
     - Vote untuk suhu AC (naik/turun)
     - Vote untuk pencahayaan (terang/redup)
     - Democracy in office environment

  5. TRAINING/WORKSHOP:
     - Polling pendapat peserta
     - Quick survey
     - Yes/No questions

  6. TRAFFIC SURVEY:
     - Hitung kendaraan (motor/mobil)
     - Pedestrian counter
     - Direction counter (masuk/keluar)

  ===================================================================
  TROUBLESHOOTING:
  ===================================================================

  Masalah: Vote bertambah sendiri tanpa tekan button
  Solusi:
  - Bouncing atau interferensi
  - Tambah delay debouncing lebih besar (100ms)
  - Tambah kapasitor di button

  Masalah: Vote tidak bertambah saat button ditekan
  Solusi:
  - Cek edge detection logic
  - Print status button untuk debug:
    Serial.println(buttonA_sekarang);
  - Cek koneksi button

  Masalah: LED tidak update
  Solusi:
  - Pastikan fungsi updateLED() dipanggil setelah vote
  - Cek koneksi LED
  - Test LED dengan digitalWrite langsung

  Masalah: Reset tidak berfungsi
  Solusi:
  - Cek button reset terhubung dengan benar
  - Pastikan edge detection untuk reset sama seperti button lain

  ===================================================================
  TIPS LANJUTAN:
  ===================================================================

  1. Data Logging ke SD Card:
     File logFile = SD.open("voting.txt", FILE_WRITE);
     logFile.print(millis());
     logFile.print(",");
     logFile.print(voteA);
     logFile.print(",");
     logFile.println(voteB);
     logFile.close();

  2. WiFi Voting (Web Interface):
     // Buat web server
     // Tampilkan hasil di browser
     // Vote dari smartphone

  3. MQTT untuk IoT Platform:
     // Kirim data ke cloud
     // Dashboard real-time di web
     // Notifikasi ke admin

  4. Sound Effect:
     // Bunyi berbeda untuk setiap kandidat
     tone(pinBuzzer, 1000);  // A = 1000Hz
     tone(pinBuzzer, 2000);  // B = 2000Hz

  ===================================================================
*/
