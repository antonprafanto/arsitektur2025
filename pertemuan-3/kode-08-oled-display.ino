/*
  ===================================================================
  PRAKTIKUM 2: MENAMPILKAN DATA SENSOR KE OLED DISPLAY
  ===================================================================

  Deskripsi:
  Program ini menampilkan data dari sensor DHT11 (suhu & kelembapan)
  dan sensor LDR (intensitas cahaya) ke layar OLED 0.96 inch.

  Fitur Tampilan:
  - Header "SMART ROOM"
  - Suhu dalam °C dengan grafik bar
  - Kelembapan dalam % dengan grafik bar
  - Status cahaya (Terang/Gelap)
  - Update setiap 2 detik

  Komponen yang Dibutuhkan:
  - 1x ESP32 Development Board
  - 1x OLED Display 0.96" (SSD1306, I2C)
  - 1x Sensor DHT11
  - 1x LDR + Resistor 10K (voltage divider)
  - Kabel jumper
  - Breadboard

  Koneksi Rangkaian:

  OLED Display (I2C):
  VCC  --->  ESP32 3.3V
  GND  --->  ESP32 GND
  SDA  --->  ESP32 GPIO21 (default I2C SDA)
  SCL  --->  ESP32 GPIO22 (default I2C SCL)

  DHT11:
  VCC  --->  ESP32 3.3V
  DATA --->  ESP32 GPIO15
  GND  --->  ESP32 GND

  LDR (Voltage Divider):
  3.3V --->  LDR --->  GPIO34  --->  10KΩ --->  GND

  Library yang Diperlukan:
  - DHT sensor library (by Adafruit)
  - Adafruit SSD1306
  - Adafruit GFX Library

  Cara Install Library:
  1. Sketch > Include Library > Manage Libraries
  2. Cari "Adafruit SSD1306" → Install
  3. Cari "Adafruit GFX" → Install (dependency)
  4. Cari "DHT sensor library" → Install

  Dibuat untuk: Mata Kuliah Bangunan Cerdas
  Instruktur: Anton Prafanto
  ===================================================================
*/

// ===== INCLUDE LIBRARY =====
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// ===== KONFIGURASI OLED =====
#define SCREEN_WIDTH 128    // Lebar layar OLED (pixel)
#define SCREEN_HEIGHT 64    // Tinggi layar OLED (pixel)
#define OLED_RESET -1       // Reset pin (-1 jika sharing dengan ESP32 reset)
#define SCREEN_ADDRESS 0x3C // Alamat I2C OLED (bisa 0x3C atau 0x3D)

// Membuat objek display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ===== KONFIGURASI DHT =====
#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ===== KONFIGURASI LDR =====
const int pinLDR = 34;
const int thresholdGelap = 2500;  // Sesuaikan dengan kalibrasi

// ===== FUNGSI SETUP =====
void setup() {
  // Inisialisasi Serial Monitor
  Serial.begin(115200);
  delay(1000);

  Serial.println("========================================");
  Serial.println("  SISTEM MONITORING DENGAN OLED        ");
  Serial.println("========================================");
  Serial.println();

  // Inisialisasi OLED
  Serial.print("Inisialisasi OLED...");
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(" GAGAL!");
    Serial.println("Cek koneksi OLED atau alamat I2C");
    Serial.println("Gunakan I2C Scanner untuk cek alamat");
    while (1);  // Hang jika OLED tidak terdeteksi
  }
  Serial.println(" OK!");

  // Konfigurasi display
  display.clearDisplay();           // Bersihkan buffer
  display.setTextColor(SSD1306_WHITE);  // Set warna teks putih
  display.setTextSize(1);           // Set ukuran font (1 = kecil)

  // Tampilkan splash screen
  tampilSplashScreen();
  delay(2000);

  // Inisialisasi DHT11
  Serial.print("Inisialisasi DHT11...");
  dht.begin();
  Serial.println(" OK!");

  Serial.println("Sistem siap!");
  Serial.println("========================================");
  Serial.println();

  delay(1000);
}

// ===== FUNGSI LOOP =====
void loop() {

  // LANGKAH 1: Baca data sensor
  float suhu = dht.readTemperature();
  float kelembapan = dht.readHumidity();
  int nilaiLDR = analogRead(pinLDR);

  // LANGKAH 2: Validasi data DHT11
  if (isnan(suhu) || isnan(kelembapan)) {
    tampilError("Sensor DHT11 Error!");
    delay(2000);
    return;
  }

  // LANGKAH 3: Tampilkan ke OLED
  tampilDataSensor(suhu, kelembapan, nilaiLDR);

  // LANGKAH 4: Tampilkan juga ke Serial Monitor (untuk debugging)
  Serial.print("Suhu: ");
  Serial.print(suhu, 1);
  Serial.print(" °C | Kelembapan: ");
  Serial.print(kelembapan, 1);
  Serial.print(" % | LDR: ");
  Serial.print(nilaiLDR);
  Serial.print(" (");
  Serial.print(nilaiLDR > thresholdGelap ? "GELAP" : "TERANG");
  Serial.println(")");

  // LANGKAH 5: Update setiap 2 detik
  delay(2000);
}

// ===== FUNGSI TAMPIL SPLASH SCREEN =====
void tampilSplashScreen() {
  display.clearDisplay();

  // Judul besar
  display.setTextSize(2);
  display.setCursor(10, 10);
  display.println("SMART");
  display.setCursor(15, 30);
  display.println("ROOM");

  // Subtitle kecil
  display.setTextSize(1);
  display.setCursor(5, 55);
  display.println("Monitoring System");

  display.display();  // Kirim buffer ke layar
}

// ===== FUNGSI TAMPIL DATA SENSOR =====
void tampilDataSensor(float suhu, float kelembapan, int nilaiLDR) {
  display.clearDisplay();  // Bersihkan layar

  // ===== HEADER =====
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("==== SMART ROOM ====");

  // ===== SUHU =====
  display.setCursor(0, 12);
  display.print("Suhu: ");
  display.print(suhu, 1);  // 1 angka desimal
  display.print(" ");
  display.print((char)247);  // Simbol derajat °
  display.println("C");

  // Bar graph untuk suhu (range 0-50°C)
  int barSuhu = map(suhu, 0, 50, 0, 100);  // Convert ke persen
  if (barSuhu > 100) barSuhu = 100;
  if (barSuhu < 0) barSuhu = 0;
  gambarBarGraph(0, 22, barSuhu);

  // ===== KELEMBAPAN =====
  display.setCursor(0, 32);
  display.print("RH  : ");
  display.print(kelembapan, 1);
  display.println(" %");

  // Bar graph untuk kelembapan (range 0-100%)
  int barRH = kelembapan;
  if (barRH > 100) barRH = 100;
  if (barRH < 0) barRH = 0;
  gambarBarGraph(0, 42, barRH);

  // ===== STATUS CAHAYA =====
  display.setCursor(0, 54);
  display.print("Cahaya: ");
  if (nilaiLDR > thresholdGelap) {
    display.println("GELAP");
  } else {
    display.println("TERANG");
  }

  // Kirim buffer ke layar
  display.display();
}

// ===== FUNGSI GAMBAR BAR GRAPH =====
// x, y = koordinat kiri atas
// persen = nilai 0-100
void gambarBarGraph(int x, int y, int persen) {
  int lebar = 128;  // Lebar penuh layar
  int tinggi = 8;   // Tinggi bar

  // Frame (border)
  display.drawRect(x, y, lebar, tinggi, SSD1306_WHITE);

  // Fill bar sesuai persen
  int lebarFill = map(persen, 0, 100, 0, lebar - 2);  // -2 untuk border
  display.fillRect(x + 1, y + 1, lebarFill, tinggi - 2, SSD1306_WHITE);
}

// ===== FUNGSI TAMPIL ERROR =====
void tampilError(String pesan) {
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("==== ERROR ====");
  display.println();

  display.setTextSize(1);
  display.setCursor(0, 20);
  display.println(pesan);

  display.setCursor(0, 50);
  display.println("Cek koneksi sensor");

  display.display();

  Serial.print("ERROR: ");
  Serial.println(pesan);
}

/*
  ===================================================================
  PENJELASAN KONSEP:
  ===================================================================

  1. OLED DISPLAY:
     - OLED = Organic Light Emitting Diode
     - Setiap pixel memancarkan cahaya sendiri (tidak perlu backlight)
     - Keunggulan: kontras tinggi, hemat daya, viewing angle lebar
     - Driver: SSD1306 (standar untuk OLED 128x64)

  2. I2C (Inter-Integrated Circuit):
     - Protokol komunikasi serial 2-wire: SDA (data) dan SCL (clock)
     - Master-Slave: ESP32 = master, OLED = slave
     - Alamat I2C: setiap device punya alamat unik (0x3C atau 0x3D)
     - Keuntungan: hemat pin (hanya 2 pin untuk banyak device)

     Pin I2C ESP32:
     - SDA = GPIO21 (default)
     - SCL = GPIO22 (default)
     - Bisa diubah dengan: Wire.begin(SDA_PIN, SCL_PIN);

  3. ADAFRUIT GFX LIBRARY:
     - Library standar untuk grafik (teks, garis, shape)
     - Mendukung banyak jenis display (OLED, LCD, TFT)
     - Fungsi-fungsi grafik:
       * drawPixel(x, y, color) - gambar 1 pixel
       * drawLine(x0, y0, x1, y1, color) - garis
       * drawRect(x, y, w, h, color) - persegi
       * fillRect(x, y, w, h, color) - persegi terisi
       * drawCircle(x, y, r, color) - lingkaran
       * setCursor(x, y) - set posisi teks
       * print() / println() - tulis teks

  4. SISTEM KOORDINAT OLED:
     Koordinat dimulai dari kiri atas (0, 0)

     (0,0) -------- X ---------> (127, 0)
       |
       |
       Y
       |
       |
       v
     (0,63) --------------------> (127, 63)

     Contoh:
     display.setCursor(10, 20) → 10 pixel dari kiri, 20 dari atas

  5. BUFFER DISPLAY:
     - OLED bekerja dengan sistem buffer
     - Semua perintah gambar masuk ke buffer (RAM)
     - display.display() → kirim buffer ke layar fisik
     - display.clearDisplay() → bersihkan buffer (bukan layar!)
     - Ini membuat rendering lebih cepat (batch update)

  6. UKURAN FONT:
     - setTextSize(1) = 6x8 pixel per karakter (default, kecil)
     - setTextSize(2) = 12x16 pixel (2x lebih besar)
     - setTextSize(3) = 18x24 pixel (besar)
     - Semakin besar, semakin sedikit karakter yang muat

     Kapasitas layar 128x64 dengan font size 1:
     - Lebar: 128 / 6 = 21 karakter per baris
     - Tinggi: 64 / 8 = 8 baris

  ===================================================================
  FUNGSI-FUNGSI PENTING ADAFRUIT GFX:
  ===================================================================

  SETUP & DISPLAY:
  - display.begin(mode, address) → Inisialisasi OLED
  - display.clearDisplay() → Bersihkan buffer
  - display.display() → Update layar dari buffer
  - display.invertDisplay(true/false) → Invert warna

  TEKS:
  - display.setTextSize(n) → Set ukuran font (1-3)
  - display.setTextColor(color) → Set warna teks
  - display.setCursor(x, y) → Set posisi teks
  - display.print(data) → Print tanpa newline
  - display.println(data) → Print dengan newline

  GRAFIK DASAR:
  - display.drawPixel(x, y, color)
  - display.drawLine(x0, y0, x1, y1, color)
  - display.drawRect(x, y, w, h, color)
  - display.fillRect(x, y, w, h, color)
  - display.drawCircle(x, y, r, color)
  - display.fillCircle(x, y, r, color)

  WARNA:
  - SSD1306_WHITE → Putih (pixel nyala)
  - SSD1306_BLACK → Hitam (pixel mati)
  - Untuk OLED monochrome, hanya 2 warna

  ===================================================================
  EKSPERIMEN YANG BISA DICOBA:
  ===================================================================

  1. Animasi Loading Bar:
     void tampilLoading() {
       display.clearDisplay();
       display.setCursor(30, 20);
       display.println("Loading...");

       for (int i = 0; i <= 100; i += 5) {
         display.fillRect(14, 35, i, 10, SSD1306_WHITE);
         display.display();
         delay(100);
       }
     }

  2. Grafik Real-time (Scrolling Graph):
     int dataSuhu[128];  // Array untuk 128 pixel
     int index = 0;

     // Di loop:
     dataSuhu[index] = suhu;
     index++;
     if (index >= 128) index = 0;

     // Gambar grafik:
     for (int i = 0; i < 127; i++) {
       int y1 = map(dataSuhu[i], 0, 50, 64, 0);
       int y2 = map(dataSuhu[i+1], 0, 50, 64, 0);
       display.drawLine(i, y1, i+1, y2, SSD1306_WHITE);
     }

  3. Multi-halaman dengan Button:
     int halaman = 0;
     int pinButton = 4;

     // Di loop:
     if (digitalRead(pinButton) == LOW) {
       halaman++;
       if (halaman > 2) halaman = 0;
       delay(300);
     }

     switch(halaman) {
       case 0: tampilSuhu(); break;
       case 1: tampilKelembapan(); break;
       case 2: tampilStatistik(); break;
     }

  4. Icon/Logo Custom (Bitmap):
     // Buat bitmap 16x16
     const unsigned char logo[] PROGMEM = {
       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
       // ... data bitmap ...
     };

     display.drawBitmap(x, y, logo, 16, 16, SSD1306_WHITE);

  5. Alarm Visual (Blink):
     if (suhu > 35) {
       // Kedipkan display
       for (int i = 0; i < 3; i++) {
         display.invertDisplay(true);
         delay(200);
         display.invertDisplay(false);
         delay(200);
       }
     }

  ===================================================================
  TROUBLESHOOTING:
  ===================================================================

  Masalah: OLED tidak menampilkan apa-apa (blank)
  Solusi:
  - Cek koneksi VCC, GND, SDA, SCL
  - Cek alamat I2C (0x3C atau 0x3D)
  - Gunakan I2C Scanner untuk deteksi alamat:
    https://playground.arduino.cc/Main/I2cScanner/
  - Pastikan library Adafruit SSD1306 terinstall
  - Coba ganti OLED (mungkin rusak)

  Masalah: Tampilan buram atau tidak jelas
  Solusi:
  - Layar OLED mungkin kotor (bersihkan dengan kain lembut)
  - Kontras kurang (tidak bisa diatur di SSD1306)
  - OLED rusak (burn-in jika terlalu lama tampil statis)

  Masalah: Alamat I2C tidak ditemukan
  Solusi:
  - Upload I2C Scanner sketch
  - Lihat alamat yang terdeteksi (0x3C atau 0x3D)
  - Ganti SCREEN_ADDRESS di kode

  Masalah: Teks terpotong atau keluar layar
  Solusi:
  - Hitung lebar teks: jumlah_karakter × (6 × textSize)
  - Sesuaikan posisi setCursor
  - Gunakan textSize lebih kecil
  - Singkat teksnya

  Masalah: Display lambat/lag
  Solusi:
  - Jangan terlalu sering panggil display.display()
  - Update hanya saat data berubah
  - Hindari clearDisplay() di setiap loop
  - Gunakan partial update (update area tertentu saja)

  Masalah: Compile error "SSD1306 not found"
  Solusi:
  - Install library: Adafruit SSD1306
  - Install dependency: Adafruit GFX Library
  - Restart Arduino IDE
  - Cek #include <Adafruit_SSD1306.h> ada di kode

  ===================================================================
  APLIKASI DALAM BANGUNAN CERDAS:
  ===================================================================

  1. DASHBOARD RUANGAN:
     - Tampilkan suhu, kelembapan, kualitas udara
     - Status AC, lampu, kipas
     - Hemat energi (tidak perlu selalu buka app)
     - Real-time monitoring

  2. SMART THERMOSTAT:
     - Tampilan setpoint suhu
     - Mode (auto, manual, eco)
     - Grafik suhu 24 jam
     - Estimasi biaya listrik

  3. MEETING ROOM PANEL:
     - Status ruangan (Available/Occupied)
     - Jadwal meeting hari ini
     - Nama meeting & durasi
     - Countdown waktu tersisa

  4. PARKING GUIDANCE:
     - Jumlah slot tersedia
     - Arah ke slot kosong
     - Tarif parkir
     - QR code untuk pembayaran

  5. ENERGY MONITOR:
     - Konsumsi daya real-time (Watt)
     - Total kWh hari ini
     - Biaya listrik
     - Perbandingan dengan hari kemarin

  6. SECURITY PANEL:
     - Status alarm (armed/disarmed)
     - Sensor yang aktif
     - Log aktivitas terakhir
     - Kode akses keypad

  ===================================================================
*/
