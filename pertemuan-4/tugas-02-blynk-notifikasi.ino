/*
  ===================================================================
  TUGAS 2: BLYNK PUSH NOTIFICATION - Temperature Alert System
  ===================================================================

  Deskripsi Tugas:
  Buatlah sistem alert yang mengirim push notification ke smartphone
  ketika suhu ruangan melebihi batas yang ditentukan. Batas suhu bisa
  diatur langsung dari aplikasi Blynk menggunakan Slider widget.

  Target Pembelajaran:
  - Memahami cara kerja Blynk.logEvent() untuk notifikasi
  - Menggunakan Slider widget untuk input dari user
  - Implementasi logic threshold (ambang batas)
  - Mencegah spam notification dengan cooldown timer

  Komponen yang Dibutuhkan:
  - 1x ESP32 Development Board
  - 1x Sensor DHT11 (Suhu & Kelembapan)
  - 1x LED Merah (indikator alert)
  - 1x Resistor 220Ω
  - Kabel jumper

  Koneksi Rangkaian:
  DHT11:
  - VCC   → ESP32 3.3V
  - DATA  → ESP32 GPIO15
  - GND   → ESP32 GND

  LED Alert (Merah):
  - Anode (+)  → Resistor 220Ω → ESP32 GPIO2
  - Cathode (-) → ESP32 GND

  Library yang Diperlukan:
  - WiFi (built-in ESP32)
  - Blynk (by Volodymyr Shymanskyy)
  - DHT sensor library (by Adafruit)
  - Adafruit Unified Sensor (dependency)

  Setup Blynk (PENTING!):
  ⚠️  Setup HARUS via Blynk Console (web): https://blynk.cloud
      Bukan hanya via app! App hanya untuk monitoring.

  1. Download app "Blynk IoT" → Buat akun
  2. [Via WEB] Buka browser → https://blynk.cloud → Login
  3. [Via WEB] Buat Template baru:
     - Klik "Templates" → "+ New Template"
     - Name: "Temperature Alert"
     - Hardware: ESP32
     - Connection: WiFi
     - Klik "Done"

  4. [Via WEB] Buat Event untuk Notifikasi (Tab "Events" → "+ New Event"):
     - Event Code: high_temp
     - Name: "High Temperature Alert"
     - Description: "Temperature exceeded threshold!"
     - Type: Warning (kuning) atau Critical (merah)
     - Enable Notification: ON
     - Klik "Create"

  5. [Via WEB] Buat Datastream (Tab "Datastreams" → "+ New Datastream"):
     a. Datastream 1:
        - Virtual Pin: V0
        - Name: "Suhu"
        - Data Type: Double
        - Min: 0, Max: 50
        - Units: °C
     b. Datastream 2:
        - Virtual Pin: V1
        - Name: "Threshold"
        - Data Type: Integer
        - Min: 25, Max: 35
        - Default: 30
        - Units: °C
     c. Datastream 3:
        - Virtual Pin: V2
        - Name: "Status"
        - Data Type: String

  6. [Via WEB] Tambah Widget ke Dashboard (Tab "Mobile Dashboard"):
     - Gauge widget → Datastream: V0 (Suhu real-time)
     - Slider widget → Datastream: V1 (Atur threshold, 25-35)
     - Label widget → Datastream: V2 (Status alert)

  7. [Via WEB] Buat Device:
     - Klik "Devices" → "+ New Device" → "From Template"
     - Pilih "Temperature Alert"
     - Device Name: "ESP32_Temp_Alert"
     - Klik "Create"
  8. [Via WEB] Copy Auth Token:
     - Device Info → Copy BLYNK_AUTH_TOKEN (klik icon ⎘)
     - Paste ke line 112 di bawah (ganti "TMPL4xxxxxxxxx")!

  💡 TIP: Auth Token lebih mudah di-copy via web console!
  📖 Panduan lengkap: Lihat MATERI-PERTEMUAN-4.md Bagian 2B

  Kriteria Penilaian:
  ✓ Notification terkirim saat suhu > threshold (35%)
  ✓ Threshold bisa diatur via Slider (25%)
  ✓ LED alert nyala saat suhu tinggi (15%)
  ✓ Tidak ada spam notification (cooldown) (15%)
  ✓ Kode rapi dengan komentar jelas (10%)

  Dibuat untuk: Mata Kuliah Bangunan Cerdas
  Instruktur: Anton Prafanto
  ===================================================================
*/

// ===== BLYNK CREDENTIALS =====
// PENTING: Harus di PALING ATAS sebelum #include!
// GANTI dengan credentials Anda!
#define BLYNK_TEMPLATE_ID "TMPL4xxxxxxxxx"
#define BLYNK_TEMPLATE_NAME "Temperature Alert"
#define BLYNK_AUTH_TOKEN "abcdefgh123456789ijklmnopqrstuv"
#define BLYNK_PRINT Serial

// ===== INCLUDE LIBRARY =====
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// ===== WIFI CREDENTIALS =====
char ssid[] = "NAMA_WIFI_ANDA";
char pass[] = "PASSWORD_WIFI_ANDA";

// ===== PIN DEFINITIONS =====
#define DHTPIN 15       // DHT11 DATA pin
#define DHTTYPE DHT11   // Tipe sensor DHT11
#define LED_ALERT 2     // LED indikator alert

// ===== INISIALISASI SENSOR =====
DHT dht(DHTPIN, DHTTYPE);

// ===== VIRTUAL PIN BLYNK =====
// V0 = Suhu (°C)
// V1 = Threshold Suhu (°C) - Input dari Slider
// V2 = Status Alert (String)

// ===== VARIABEL SENSOR =====
float suhu = 0;
float kelembapan = 0;

// ===== VARIABEL THRESHOLD =====
int suhuThreshold = 30;  // Default 30°C (bisa diubah via Slider)

// ===== VARIABEL TIMER =====
unsigned long lastSendTime = 0;
const long sendInterval = 3000;  // Baca sensor setiap 3 detik

unsigned long lastNotificationTime = 0;
const long notificationCooldown = 60000;  // Cooldown 60 detik (1 menit)
// Mencegah spam notification

// ===== VARIABEL STATUS =====
bool alertActive = false;
bool lastAlertState = false;

// ===== FUNGSI SETUP =====
void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.println();
  Serial.println("================================================");
  Serial.println("  TUGAS 2: TEMPERATURE ALERT SYSTEM");
  Serial.println("================================================");
  Serial.println();

  // Setup pin LED
  pinMode(LED_ALERT, OUTPUT);
  digitalWrite(LED_ALERT, LOW);

  // Inisialisasi sensor DHT11
  dht.begin();
  Serial.println("[DHT11] Sensor initialized");
  delay(2000);

  // Koneksi ke Blynk
  Serial.println("Menghubungkan ke WiFi dan Blynk...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println();
  Serial.println("Setup selesai!");
  Serial.println("Temperature monitoring dimulai...");
  Serial.println("================================================");
}

// ===== FUNGSI LOOP =====
void loop() {
  // Handle komunikasi Blynk
  Blynk.run();

  // Baca sensor dan proses alert setiap 3 detik
  if (millis() - lastSendTime >= sendInterval) {
    lastSendTime = millis();

    bacaSensor();
    cekAlert();
    kirimKeBlynk();
  }
}

// ===== FUNGSI: BACA SENSOR DHT11 =====
void bacaSensor() {
  suhu = dht.readTemperature();
  kelembapan = dht.readHumidity();

  // Cek validitas pembacaan
  if (isnan(suhu) || isnan(kelembapan)) {
    Serial.println("[DHT11] ERROR: Gagal membaca sensor!");
    return;
  }

  // Tampilkan di Serial Monitor
  Serial.println("========================================");
  Serial.print("[DHT11] Suhu: ");
  Serial.print(suhu);
  Serial.print(" °C  (Threshold: ");
  Serial.print(suhuThreshold);
  Serial.println(" °C)");

  Serial.print("[DHT11] Kelembapan: ");
  Serial.print(kelembapan);
  Serial.println(" %");
}

// ===== FUNGSI: CEK ALERT =====
void cekAlert() {
  if (isnan(suhu)) return;  // Skip jika sensor error

  // Cek apakah suhu melebihi threshold
  if (suhu > suhuThreshold) {
    alertActive = true;
    digitalWrite(LED_ALERT, HIGH);  // Nyalakan LED alert

    // Kirim notification HANYA jika:
    // 1. Blynk connected
    // 2. Sudah lewat cooldown period
    // 3. Status berubah dari normal ke alert (untuk menghindari spam)
    if (Blynk.connected() &&
        (millis() - lastNotificationTime >= notificationCooldown) &&
        !lastAlertState) {

      kirimNotifikasi();
      lastNotificationTime = millis();
    }

    lastAlertState = true;

    Serial.println("[ALERT] ⚠️  SUHU TINGGI! Melebihi threshold!");
    Serial.println("========================================");

  } else {
    alertActive = false;
    digitalWrite(LED_ALERT, LOW);  // Matikan LED alert
    lastAlertState = false;

    Serial.println("[Status] ✓ Suhu normal");
    Serial.println("========================================");
  }
}

// ===== FUNGSI: KIRIM NOTIFIKASI =====
void kirimNotifikasi() {
  Serial.println();
  Serial.println("================================================");
  Serial.println("   📱 MENGIRIM PUSH NOTIFICATION...");
  Serial.println("================================================");

  // Format pesan notifikasi
  String message = "Suhu: " + String(suhu, 1) + "°C (Threshold: " +
                   String(suhuThreshold) + "°C)";

  // Kirim event notification ke Blynk
  // "high_temp" harus sesuai dengan Event Code yang dibuat di Blynk
  Blynk.logEvent("high_temp", message);

  Serial.println("[Blynk] ✓ Notification sent!");
  Serial.print("[Message] ");
  Serial.println(message);
  Serial.println("================================================");
  Serial.println();
}

// ===== FUNGSI: KIRIM DATA KE BLYNK =====
void kirimKeBlynk() {
  if (!Blynk.connected()) {
    Serial.println("[Blynk] Disconnected, data tidak terkirim");
    return;
  }

  if (isnan(suhu)) {
    Blynk.virtualWrite(V2, "⚠️ Sensor ERROR!");
    return;
  }

  // Kirim suhu ke V0 (Gauge widget)
  Blynk.virtualWrite(V0, suhu);

  // Kirim status ke V2 (Label widget)
  String status = "";
  if (alertActive) {
    status = "🔥 ALERT: Suhu Tinggi! (" + String(suhu, 1) + "°C)";
  } else {
    status = "✅ Normal (" + String(suhu, 1) + "°C)";
  }
  Blynk.virtualWrite(V2, status);
}

// ===== FUNGSI BLYNK: TERIMA THRESHOLD DARI SLIDER =====
// Fungsi ini dipanggil otomatis saat Slider V1 digeser
BLYNK_WRITE(V1) {
  // Ambil nilai dari Slider (25-35)
  int newThreshold = param.asInt();

  // Update threshold
  suhuThreshold = newThreshold;

  Serial.println();
  Serial.println("========================================");
  Serial.print("[Blynk] Threshold diubah: ");
  Serial.print(suhuThreshold);
  Serial.println(" °C");
  Serial.println("========================================");
  Serial.println();
}

// ===== FUNGSI BLYNK: EVENT SAAT TERKONEKSI =====
BLYNK_CONNECTED() {
  Serial.println();
  Serial.println("================================================");
  Serial.println("   ✓ BLYNK CONNECTED!");
  Serial.println("================================================");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Serial.println("Temperature Alert System aktif!");
  Serial.println("Atur threshold via Slider di Blynk app.");
  Serial.println("================================================");

  // Sync threshold dari server (ambil nilai terakhir)
  Blynk.syncVirtual(V1);

  // Kirim threshold saat ini ke Slider
  Blynk.virtualWrite(V1, suhuThreshold);
}

/*
  ===================================================================
  CATATAN UNTUK MAHASISWA:
  ===================================================================

  1. CARA KERJA NOTIFICATION:
     - Blynk.logEvent("event_code", "message") mengirim push notification
     - Event Code "high_temp" harus dibuat terlebih dahulu di Blynk Console
     - Notification akan muncul di smartphone meskipun app tidak dibuka
     - Pastikan izin notification di HP sudah diaktifkan!

  2. COOLDOWN MECHANISM:
     - Cooldown = jeda waktu minimum antar notification
     - Dalam kode ini: 60 detik (1 menit)
     - Mencegah spam notification yang mengganggu
     - Notification hanya dikirim saat status berubah dari normal ke alert

  3. INTERPRETASI LED:
     - LED OFF = Suhu normal (< threshold)
     - LED ON  = Suhu tinggi (> threshold) - ALERT!

  4. TROUBLESHOOTING:
     a. Notification tidak muncul:
        - Cek Event Code di Blynk Console (harus "high_temp")
        - Pastikan Enable Notification: ON
        - Cek izin notification di HP
        - Lihat Serial Monitor untuk konfirmasi pengiriman

     b. Spam notification:
        - Seharusnya tidak terjadi karena ada cooldown
        - Jika tetap terjadi, perbesar notificationCooldown

     c. Threshold tidak berubah:
        - Pastikan Slider widget linked ke V1
        - Cek Serial Monitor apakah terima nilai baru
        - Pastikan range Slider 25-35

  5. PENGEMBANGAN LEBIH LANJUT:
     - Tambahkan notification untuk suhu terlalu rendah
     - Kirim data ke database (Blynk Table atau Google Sheets)
     - Tambahkan buzzer untuk alarm lokal
     - Grafik suhu dengan Chart widget untuk analisis trend

  6. BLYNK FREE PLAN LIMIT:
     - Max 1 notification per menit per device
     - Total 100 notifications per hari
     - Cooldown 60 detik memastikan tidak melebihi limit

  ===================================================================
*/
