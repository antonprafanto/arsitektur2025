/*
  ===================================================================
  PRAKTIKUM 3: SENSOR PIR - Sistem Deteksi Gerak
  ===================================================================

  Deskripsi:
  Program ini membuat sistem keamanan sederhana menggunakan sensor
  PIR (Passive Infrared) yang mendeteksi gerakan manusia.
  Ketika gerakan terdeteksi, LED dan buzzer akan aktif.

  Konsep:
  - PIR mendeteksi radiasi infrared dari tubuh manusia
  - Output: Digital (HIGH = ada gerakan, LOW = tidak ada)
  - Jangkauan: 3-7 meter (tergantung setting)
  - Sudut: 100-120 derajat

  Komponen yang Dibutuhkan:
  - 1x ESP32 Development Board
  - 1x Sensor PIR (HC-SR501)
  - 1x LED merah (indikator)
  - 1x Active Buzzer (alarm)
  - 1x Resistor 220 ohm
  - Kabel jumper
  - Breadboard

  Koneksi Rangkaian:
  PIR Sensor:
  VCC  --->  ESP32 5V (atau 3.3V, cek datasheet sensor)
  OUT  --->  ESP32 GPIO13
  GND  --->  ESP32 GND

  LED Indikator:
  GPIO2  --->  LED (+)  --->  Resistor 220Ω  --->  GND

  Buzzer Alarm:
  GPIO12  --->  Active Buzzer (+)
  GND     --->  Active Buzzer (-)

  Pengaturan PIR:
  - Potensiometer Sensitivity (S): Atur jarak deteksi
  - Potensiometer Time Delay (T): Atur durasi output HIGH

  Dibuat untuk: Mata Kuliah Bangunan Cerdas
  Instruktur: Anton Prafanto
  ===================================================================
*/

// ===== KONFIGURASI PIN =====
const int pinPIR = 13;      // Pin digital untuk membaca sensor PIR
const int pinLED = 2;       // LED indikator (merah)
const int pinBuzzer = 12;   // Active buzzer untuk alarm

// ===== KONFIGURASI SISTEM =====
const int WAKTU_KALIBRASI = 30;  // Waktu kalibrasi sensor (detik)
const int DURASI_ALARM = 3;      // Durasi alarm saat deteksi (detik)

// ===== VARIABEL STATUS =====
bool sistemAktif = false;         // Status sistem (sudah kalibrasi?)
bool gerakanTerdeteksi = false;   // Status deteksi gerakan
unsigned long waktuDeteksiTerakhir = 0;  // Timestamp deteksi terakhir

// ===== STATISTIK =====
int jumlahDeteksi = 0;  // Counter berapa kali terdeteksi gerakan

// ===== FUNGSI SETUP =====
void setup() {
  // Inisialisasi Serial Monitor
  Serial.begin(115200);
  delay(1000);

  Serial.println("========================================");
  Serial.println("   SISTEM DETEKSI GERAKAN (PIR)        ");
  Serial.println("========================================");
  Serial.println();

  // Konfigurasi pin
  pinMode(pinPIR, INPUT);        // PIR sebagai input
  pinMode(pinLED, OUTPUT);       // LED sebagai output
  pinMode(pinBuzzer, OUTPUT);    // Buzzer sebagai output

  // Pastikan LED dan buzzer mati di awal
  digitalWrite(pinLED, LOW);
  digitalWrite(pinBuzzer, LOW);

  // FASE KALIBRASI SENSOR PIR
  // PIR butuh waktu 30-60 detik untuk kalibrasi setelah power on
  Serial.println("⏳ FASE KALIBRASI SENSOR PIR");
  Serial.print("Mohon tunggu ");
  Serial.print(WAKTU_KALIBRASI);
  Serial.println(" detik...");
  Serial.println("Jangan bergerak di depan sensor!");
  Serial.println();

  // Countdown dengan animasi
  for (int i = WAKTU_KALIBRASI; i > 0; i--) {
    Serial.print("Kalibrasi: ");
    Serial.print(i);
    Serial.println(" detik");

    // LED berkedip selama kalibrasi
    digitalWrite(pinLED, HIGH);
    delay(200);
    digitalWrite(pinLED, LOW);
    delay(800);
  }

  // Buzzer beep 2x menandakan kalibrasi selesai
  digitalWrite(pinBuzzer, HIGH);
  delay(200);
  digitalWrite(pinBuzzer, LOW);
  delay(200);
  digitalWrite(pinBuzzer, HIGH);
  delay(200);
  digitalWrite(pinBuzzer, LOW);

  sistemAktif = true;

  Serial.println();
  Serial.println("✅ Kalibrasi selesai!");
  Serial.println("🚨 Sistem keamanan AKTIF!");
  Serial.println("Monitoring dimulai...");
  Serial.println("========================================");
  Serial.println();
}

// ===== FUNGSI LOOP =====
void loop() {

  // LANGKAH 1: Baca status sensor PIR
  // HIGH = gerakan terdeteksi
  // LOW = tidak ada gerakan
  int statusPIR = digitalRead(pinPIR);

  // LANGKAH 2: Cek apakah ada gerakan BARU
  if (statusPIR == HIGH) {
    // Gerakan terdeteksi!

    if (!gerakanTerdeteksi) {
      // Ini adalah deteksi BARU (edge detection)
      gerakanTerdeteksi = true;
      jumlahDeteksi++;
      waktuDeteksiTerakhir = millis();

      // Tampilkan peringatan
      Serial.println("🚨🚨🚨 PERINGATAN! 🚨🚨🚨");
      Serial.println("GERAKAN TERDETEKSI!");
      Serial.print("Deteksi ke-");
      Serial.println(jumlahDeteksi);
      Serial.print("Waktu: ");
      Serial.print(millis() / 1000);
      Serial.println(" detik sejak boot");
      Serial.println("========================================");

      // Aktifkan alarm
      aktivasiAlarm();
    }

    // Update timestamp setiap kali ada gerakan
    waktuDeteksiTerakhir = millis();

  } else {
    // Tidak ada gerakan

    // Cek apakah sudah melewati durasi alarm
    if (gerakanTerdeteksi && (millis() - waktuDeteksiTerakhir > DURASI_ALARM * 1000)) {
      // Nonaktifkan alarm
      gerakanTerdeteksi = false;
      nonaktivasiAlarm();

      Serial.println("✅ Sistem kembali normal");
      Serial.println("Monitoring...");
      Serial.println();
    }
  }

  // Delay kecil untuk stabilitas
  delay(100);
}

// ===== FUNGSI AKTIVASI ALARM =====
void aktivasiAlarm() {
  // Nyalakan LED
  digitalWrite(pinLED, HIGH);

  // Buzzer bunyi beep-beep (3 kali)
  for (int i = 0; i < 3; i++) {
    digitalWrite(pinBuzzer, HIGH);
    delay(150);
    digitalWrite(pinBuzzer, LOW);
    delay(150);
  }

  // Buzzer tetap bunyi selama alarm aktif
  digitalWrite(pinBuzzer, HIGH);
}

// ===== FUNGSI NONAKTIVASI ALARM =====
void nonaktivasiAlarm() {
  // Matikan LED dan buzzer
  digitalWrite(pinLED, LOW);
  digitalWrite(pinBuzzer, LOW);
}

/*
  ===================================================================
  PENJELASAN KONSEP:
  ===================================================================

  1. PIR (Passive Infrared) Sensor:
     - "Passive" = tidak memancarkan sinyal, hanya menerima
     - Mendeteksi radiasi infrared (panas) dari tubuh manusia
     - Tubuh manusia suhu ~37°C → memancarkan IR
     - Sensor pyroelectric mendeteksi perubahan radiasi

     Cara Kerja:
     - Sensor punya 2 elemen sensitif IR
     - Saat tidak ada gerakan → kedua elemen baca nilai sama
     - Saat ada gerakan → satu elemen baca lebih tinggi → trigger
     - Output HIGH selama time delay (atur dengan potensiometer)

  2. LENSA FRESNEL:
     - Lensa kubah putih di depan sensor
     - Membagi area deteksi jadi banyak zone (seperti peta)
     - Saat objek bergerak antar zone → perubahan radiasi → trigger
     - Jangkauan: 3-7 meter, sudut: 100-120°

  3. POTENSIOMETER PADA PIR:
     - **Sensitivity (S)**: Atur jarak deteksi
       * Putar CW (searah jarum jam) = lebih jauh (~7m)
       * Putar CCW (berlawanan) = lebih dekat (~3m)

     - **Time Delay (T)**: Atur durasi output HIGH
       * Minimum: ~2 detik
       * Maximum: ~5 menit
       * Setelah deteksi, output tetap HIGH selama time delay
       * Timer reset jika ada gerakan baru

  4. JUMPER PADA PIR (jika ada):
     - **Single Trigger**: Output HIGH hanya sekali, lalu LOW
       Cocok untuk counter atau alarm sekali bunyi

     - **Repeating Trigger**: Output HIGH terus selama ada gerakan
       Cocok untuk lampu koridor (tetap nyala selama ada orang)

  5. KALIBRASI AWAL:
     - PIR butuh waktu 30-60 detik settling setelah power on
     - Selama waktu ini, output tidak stabil
     - Jangan ada gerakan selama kalibrasi
     - Ini waktu untuk sensor belajar radiasi background ruangan

  6. FALSE POSITIVE (Deteksi Palsu):
     Penyebab:
     - Hewan peliharaan (kucing, anjing)
     - Tirai tertiup angin
     - Perubahan suhu mendadak (AC, heater)
     - Cahaya matahari langsung (panaskan sensor)
     - Objek panas bergerak (mobil, motor)

     Solusi:
     - Pasang PIR jauh dari jendela
     - Hindari arah AC/heater
     - Turunkan sensitivity
     - Gunakan pet-immune PIR (khusus untuk rumah dengan hewan)

  ===================================================================
  DIAGRAM ALIR (FLOWCHART):
  ===================================================================

  START
    ↓
  Setup: Kalibrasi PIR 30 detik
    ↓
  ┌────────────────────┐
  │   LOOP FOREVER     │
  └─────────┬──────────┘
            ↓
  Baca statusPIR
            ↓
  statusPIR == HIGH?
            │
       YES──┴──NO
       │        │
  Gerakan!    Tidak ada gerakan
       │        │
  gerakanTerdeteksi == false?
       │        │
      YES      │
       │       │
  Tampilkan peringatan
       │       │
  Aktivasi alarm (LED + Buzzer)
       │       │
  gerakanTerdeteksi = true
       │       │
       └───────┘
            ↓
  Cek waktu sejak deteksi terakhir
            ↓
  Lebih dari DURASI_ALARM?
            │
       YES──┴──NO
       │        │
  Nonaktivasi alarm
       │        │
  gerakanTerdeteksi = false
       │        │
       └────────┘
            ↓
  Delay 100ms
            ↓
  (kembali ke loop)

  ===================================================================
  EKSPERIMEN YANG BISA DICOBA:
  ===================================================================

  1. Lampu Koridor Otomatis (Stay On):
     // LED tetap nyala selama ada gerakan + 30 detik setelahnya
     unsigned long DURASI_NYALA = 30000;  // 30 detik

     if (statusPIR == HIGH) {
       waktuDeteksiTerakhir = millis();  // Update timer
       digitalWrite(pinLED, HIGH);
     }

     if (millis() - waktuDeteksiTerakhir > DURASI_NYALA) {
       digitalWrite(pinLED, LOW);  // Mati setelah 30 detik
     }

  2. Counter Orang Masuk (Sederhana):
     // Catatan: Tidak akurat untuk hitung orang real
     // Hanya hitung berapa kali PIR trigger
     int jumlahOrang = 0;

     if (statusPIR == HIGH && !gerakanTerdeteksi) {
       jumlahOrang++;
       Serial.print("Jumlah trigger: ");
       Serial.println(jumlahOrang);
       gerakanTerdeteksi = true;
     }

     if (statusPIR == LOW) {
       gerakanTerdeteksi = false;
     }

  3. Sistem Arming/Disarming dengan Button:
     int pinButton = 4;
     bool sistemAktif = false;

     // Di setup:
     pinMode(pinButton, INPUT_PULLUP);

     // Di loop:
     if (digitalRead(pinButton) == LOW) {
       sistemAktif = !sistemAktif;
       if (sistemAktif) {
         Serial.println("🔒 Sistem AKTIF");
       } else {
         Serial.println("🔓 Sistem NONAKTIF");
         nonaktivasiAlarm();
       }
       delay(500);  // Debounce
     }

     // Hanya cek PIR jika sistem aktif
     if (sistemAktif) {
       // Logika PIR di sini
     }

  4. Kombinasi PIR + LDR (Lampu hanya nyala saat gelap DAN ada orang):
     int pinLDR = 34;
     int thresholdGelap = 2500;

     if (statusPIR == HIGH && analogRead(pinLDR) > thresholdGelap) {
       digitalWrite(pinLED, HIGH);  // Gelap DAN ada orang
     } else {
       digitalWrite(pinLED, LOW);
     }

  5. Kirim Notifikasi ke Smartphone (via Blynk/MQTT):
     // Saat gerakan terdeteksi, kirim notifikasi push
     if (statusPIR == HIGH && !gerakanTerdeteksi) {
       Blynk.notify("⚠️ Gerakan terdeteksi di rumah!");
       gerakanTerdeteksi = true;
     }

  6. Data Logger ke SD Card:
     // Simpan log setiap deteksi
     // Format: timestamp, jumlah_deteksi
     File dataFile = SD.open("log.txt", FILE_WRITE);
     if (dataFile) {
       dataFile.print(millis());
       dataFile.print(",");
       dataFile.println(jumlahDeteksi);
       dataFile.close();
     }

  ===================================================================
  TROUBLESHOOTING:
  ===================================================================

  Masalah: PIR terus terdeteksi meskipun tidak ada gerakan
  Solusi:
  - Tunggu kalibrasi 60 detik (bukan 30)
  - Jauhkan dari sumber panas (AC, heater, jendela)
  - Turunkan sensitivity (putar pot S ke minimum)
  - Hindari objek bergerak (tirai, kipas)
  - Pastikan tidak ada sinar matahari langsung
  - Coba ganti sensor PIR (mungkin rusak)

  Masalah: PIR tidak pernah terdeteksi
  Solusi:
  - Cek koneksi VCC, OUT, GND
  - Pastikan VCC ke 5V (atau 3.3V, cek datasheet)
  - Putar pot Sensitivity ke maksimum
  - Gerakkan tangan dengan jelas di depan sensor (1-2m)
  - Cek jumper mode (harus di "repeating" atau "H")
  - Test output PIR dengan LED langsung (tanpa ESP32)

  Masalah: Output tidak stabil saat kalibrasi
  Solusi:
  - Normal! Tunggu sampai kalibrasi selesai
  - Perpanjang WAKTU_KALIBRASI jadi 60 detik
  - Jangan ada gerakan sama sekali selama kalibrasi

  Masalah: Jangkauan deteksi terlalu dekat/jauh
  Solusi:
  - Atur potensiometer Sensitivity
  - CW (putar kanan) = lebih jauh
  - CCW (putar kiri) = lebih dekat
  - Test dengan trial and error

  Masalah: Delay output terlalu lama
  Solusi:
  - Atur potensiometer Time Delay
  - Putar ke posisi minimum (paling kiri)
  - Delay minimum: ~2-3 detik (hardware limitation)

  Masalah: Buzzer tidak bunyi
  Solusi:
  - Cek polaritas buzzer (+ dan -)
  - Active buzzer: bunyi saat diberi tegangan HIGH
  - Passive buzzer: perlu sinyal PWM (gunakan tone())
  - Test dengan: digitalWrite(pinBuzzer, HIGH); delay(1000);

  ===================================================================
  APLIKASI DALAM BANGUNAN CERDAS:
  ===================================================================

  1. SISTEM KEAMANAN:
     - Alarm saat ada penyusup
     - Notifikasi ke smartphone
     - Rekam video saat terdeteksi
     - Log waktu deteksi

  2. LAMPU KORIDOR/TANGGA OTOMATIS:
     - Hemat energi (hanya nyala saat ada orang)
     - Nyaman (tidak perlu saklar)
     - Keamanan (tidak gelap saat jalan malam)
     - Timer: mati otomatis 30 detik setelah tidak ada gerakan

  3. TOILET/KAMAR MANDI OTOMATIS:
     - Lampu nyala otomatis saat masuk
     - Exhaust fan nyala saat ada orang
     - Flush otomatis (kombinasi dengan sensor lain)
     - Hand dryer otomatis

  4. MEETING ROOM OCCUPANCY:
     - Deteksi ruangan kosong/ada orang
     - Matikan AC/lampu jika kosong >30 menit
     - Sistem booking otomatis (available/occupied)
     - Hemat energi signifikan

  5. SISTEM HVAC CERDAS:
     - AC hanya nyala jika ada orang di ruangan
     - Sesuaikan temperature berdasarkan occupancy
     - Kombinasi dengan sensor suhu (DHT11)
     - Prediksi waktu ramai (machine learning)

  6. RETAIL ANALYTICS:
     - Hitung traffic pengunjung
     - Analisis area paling ramai
     - Heatmap pergerakan pelanggan
     - Optimasi layout toko

  7. ELDERLY CARE (Perawatan Lansia):
     - Monitor aktivitas lansia di rumah
     - Alert jika tidak ada gerakan lama (>12 jam)
     - Deteksi jatuh (kombinasi dengan accelerometer)
     - Keamanan dan ketenangan keluarga

  ===================================================================
  TIPS INSTALASI PIR:
  ===================================================================

  1. LOKASI PEMASANGAN:
     ✅ DO:
     - Pojok ruangan (jangkauan luas)
     - Ketinggian 2-2.5 meter
     - Area yang dilalui orang
     - Arah tegak lurus jalur gerakan

     ❌ DON'T:
     - Dekat jendela (sinar matahari)
     - Dekat AC/heater (perubahan suhu)
     - Mengarah ke jalan raya (mobil lewat)
     - Terlalu tinggi (>3m, jangkauan berkurang)

  2. PENGATURAN OPTIMAL:
     - Sensitivity: 50-70% (tidak terlalu sensitif)
     - Time Delay: 2-5 detik untuk alarm, 30-60 detik untuk lampu
     - Mode: Repeating trigger (untuk lampu stay on)

  3. TESTING:
     - Test siang dan malam (kondisi berbeda)
     - Test dengan orang berjalan pelan dan cepat
     - Test dari berbagai sudut
     - Catat false positive dan adjust

  ===================================================================
*/
