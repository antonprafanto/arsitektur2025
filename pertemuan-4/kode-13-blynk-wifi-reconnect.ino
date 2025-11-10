/*
  ===================================================================
  PRAKTIKUM 13: WIFI & BLYNK RECONNECT - Best Practice Error Handling
  ===================================================================

  Deskripsi:
  Program ini mendemonstrasikan cara yang BENAR untuk handle
  koneksi WiFi dan Blynk yang sering disconnect. Sangat penting
  untuk sistem yang harus reliable (handal).

  Fitur:
  - Auto-reconnect WiFi jika disconnect
  - Auto-reconnect Blynk jika disconnect
  - LED indikator status koneksi (visual feedback)
  - Sistem tetap jalan offline (failsafe)
  - Tidak hang saat koneksi bermasalah

  Komponen yang Dibutuhkan:
  - 1x ESP32 Development Board
  - 2x LED (Merah & Hijau)
  - 2x Resistor 220Ω
  - Kabel jumper

  Koneksi Rangkaian:
  LED Hijau (WiFi):
  - Anode (+)  → Resistor 220Ω → ESP32 GPIO2
  - Cathode (-) → ESP32 GND

  LED Merah (Blynk):
  - Anode (+)  → Resistor 220Ω → ESP32 GPIO4
  - Cathode (-) → ESP32 GND

  Interpretasi LED:
  - LED Hijau ON  = WiFi Connected
  - LED Hijau OFF = WiFi Disconnected
  - LED Merah ON  = Blynk Connected
  - LED Merah OFF = Blynk Disconnected

  Library yang Diperlukan:
  - WiFi (built-in ESP32)
  - Blynk (by Volodymyr Shymanskyy)

  Setup Blynk (PENTING!):
  ⚠️  Setup HARUS via Blynk Console (web): https://blynk.cloud
      Bukan hanya via app! App hanya untuk monitoring.

  1. Download app "Blynk IoT" → Buat akun
  2. [Via WEB] Buka browser → https://blynk.cloud → Login
  3. [Via WEB] Buat Template baru:
     - Klik "Templates" → "+ New Template"
     - Name: "Reconnect Demo"
     - Hardware: ESP32
     - Connection: WiFi
     - Klik "Done"

  4. [Via WEB] Buat Datastream (Tab "Datastreams" → "+ New Datastream"):
     - Virtual Pin: V0
     - Name: "Status"
     - Data Type: String

  5. [Via WEB] Tambah Widget ke Dashboard (Tab "Mobile Dashboard"):
     - Label widget → Datastream: V0 (Status)

  6. [Via WEB] Buat Device:
     - Klik "Devices" → "+ New Device" → "From Template"
     - Pilih "Reconnect Demo"
     - Device Name: "ESP32_Reconnect"
     - Klik "Create"
  7. [Via WEB] Copy Auth Token:
     - Device Info → Copy BLYNK_AUTH_TOKEN (klik icon ⎘)
     - Paste ke line 69 di bawah!

  💡 TIP: Auth Token lebih mudah di-copy via web console!
  📖 Panduan lengkap: Lihat MATERI-PERTEMUAN-4.md Bagian 2B

  Cara Menggunakan:
  1. Ubah credentials Blynk
  2. Ubah ssid dan pass WiFi
  3. Upload kode
  4. Buka Serial Monitor
  5. Coba matikan WiFi router → Lihat reconnect otomatis!
  6. Nyalakan WiFi lagi → Akan connect kembali

  Dibuat untuk: Mata Kuliah Bangunan Cerdas
  Instruktur: Anton Prafanto
  ===================================================================
*/

// ===== INCLUDE LIBRARY =====
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// ===== BLYNK CREDENTIALS =====
#define BLYNK_TEMPLATE_ID "TMPL4xxxxxxxxx"
#define BLYNK_TEMPLATE_NAME "Reconnect Demo"
#define BLYNK_AUTH_TOKEN "abcdefgh123456789ijklmnopqrstuv"
#define BLYNK_PRINT Serial

// ===== WIFI CREDENTIALS =====
char ssid[] = "NAMA_WIFI_ANDA";
char pass[] = "PASSWORD_WIFI_ANDA";

// ===== PIN DEFINITIONS =====
#define LED_WIFI 2      // LED Hijau (WiFi status)
#define LED_BLYNK 4     // LED Merah (Blynk status)

// ===== VARIABEL TIMER =====
unsigned long lastCheckTime = 0;
const long checkInterval = 10000;  // Cek koneksi setiap 10 detik

unsigned long lastSendTime = 0;
const long sendInterval = 5000;    // Kirim status setiap 5 detik

// ===== VARIABEL RECONNECT =====
unsigned long wifiReconnectTime = 0;
unsigned long blynkReconnectTime = 0;
const long reconnectDelay = 30000;  // Tunggu 30 detik sebelum reconnect lagi

bool wifiWasConnected = false;
bool blynkWasConnected = false;

// ===== FUNGSI SETUP =====
void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.println();
  Serial.println("================================================");
  Serial.println("  WIFI & BLYNK RECONNECT - PRAKTIKUM 13");
  Serial.println("================================================");
  Serial.println();

  // Setup LED
  pinMode(LED_WIFI, OUTPUT);
  pinMode(LED_BLYNK, OUTPUT);
  digitalWrite(LED_WIFI, LOW);
  digitalWrite(LED_BLYNK, LOW);

  // Koneksi pertama kali
  connectToWiFi();

  if (WiFi.status() == WL_CONNECTED) {
    connectToBlynk();
  }

  Serial.println();
  Serial.println("Setup selesai!");
  Serial.println("Monitoring koneksi dimulai...");
  Serial.println("================================================");
}

// ===== FUNGSI LOOP =====
void loop() {
  // Update status LED
  updateLEDStatus();

  // Cek dan reconnect jika perlu (setiap 10 detik)
  if (millis() - lastCheckTime >= checkInterval) {
    lastCheckTime = millis();
    checkAndReconnect();
  }

  // Jalankan Blynk HANYA jika connected
  if (Blynk.connected()) {
    Blynk.run();

    // Kirim status ke Blynk setiap 5 detik
    if (millis() - lastSendTime >= sendInterval) {
      lastSendTime = millis();
      sendStatusToBlynk();
    }
  }

  // Sistem tetap jalan (contoh: baca sensor, kontrol aktuator)
  // Meskipun WiFi/Blynk disconnect!
  // ... kode sistem di sini ...
}

// ===== FUNGSI: CONNECT KE WIFI =====
void connectToWiFi() {
  Serial.println();
  Serial.println("--- Connecting to WiFi ---");
  Serial.print("SSID: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  int attempts = 0;
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("✓ WiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Signal Strength: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
    wifiWasConnected = true;
  } else {
    Serial.println("✗ WiFi Connection FAILED!");
    Serial.println("Cek SSID dan password!");
    wifiWasConnected = false;
  }
}

// ===== FUNGSI: CONNECT KE BLYNK =====
void connectToBlynk() {
  Serial.println();
  Serial.println("--- Connecting to Blynk ---");

  Blynk.config(BLYNK_AUTH_TOKEN);

  Serial.print("Connecting");
  int attempts = 0;

  while (!Blynk.connect() && attempts < 10) {
    Serial.print(".");
    delay(500);
    attempts++;
  }

  Serial.println();

  if (Blynk.connected()) {
    Serial.println("✓ Blynk Connected!");
    blynkWasConnected = true;
  } else {
    Serial.println("✗ Blynk Connection FAILED!");
    Serial.println("Cek Auth Token dan koneksi internet!");
    blynkWasConnected = false;
  }
}

// ===== FUNGSI: CEK & RECONNECT =====
void checkAndReconnect() {
  Serial.println();
  Serial.println("========== Status Check ==========");

  // Cek WiFi
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("WiFi: ✓ Connected (");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm)");

    if (!wifiWasConnected) {
      Serial.println("→ WiFi RECONNECTED!");
      wifiWasConnected = true;

      // WiFi baru connect, coba connect Blynk
      if (!Blynk.connected()) {
        connectToBlynk();
      }
    }
  } else {
    Serial.println("WiFi: ✗ Disconnected");

    if (wifiWasConnected) {
      Serial.println("→ WiFi CONNECTION LOST!");
      wifiWasConnected = false;
      blynkWasConnected = false;  // Blynk pasti disconnect juga
    }

    // Coba reconnect WiFi (dengan delay)
    if (millis() - wifiReconnectTime >= reconnectDelay) {
      wifiReconnectTime = millis();
      Serial.println("→ Attempting WiFi reconnect...");
      connectToWiFi();
    } else {
      long waitTime = (reconnectDelay - (millis() - wifiReconnectTime)) / 1000;
      Serial.print("→ Reconnect in ");
      Serial.print(waitTime);
      Serial.println(" seconds...");
    }
  }

  // Cek Blynk (hanya jika WiFi connected)
  if (WiFi.status() == WL_CONNECTED) {
    if (Blynk.connected()) {
      Serial.println("Blynk: ✓ Connected");

      if (!blynkWasConnected) {
        Serial.println("→ Blynk RECONNECTED!");
        blynkWasConnected = true;
      }
    } else {
      Serial.println("Blynk: ✗ Disconnected");

      if (blynkWasConnected) {
        Serial.println("→ Blynk CONNECTION LOST!");
        blynkWasConnected = false;
      }

      // Coba reconnect Blynk (dengan delay)
      if (millis() - blynkReconnectTime >= reconnectDelay) {
        blynkReconnectTime = millis();
        Serial.println("→ Attempting Blynk reconnect...");
        connectToBlynk();
      } else {
        long waitTime = (reconnectDelay - (millis() - blynkReconnectTime)) / 1000;
        Serial.print("→ Reconnect in ");
        Serial.print(waitTime);
        Serial.println(" seconds...");
      }
    }
  }

  Serial.println("==================================");
}

// ===== FUNGSI: UPDATE LED STATUS =====
void updateLEDStatus() {
  // LED Hijau = WiFi
  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(LED_WIFI, HIGH);
  } else {
    digitalWrite(LED_WIFI, LOW);
  }

  // LED Merah = Blynk
  if (Blynk.connected()) {
    digitalWrite(LED_BLYNK, HIGH);
  } else {
    digitalWrite(LED_BLYNK, LOW);
  }
}

// ===== FUNGSI: KIRIM STATUS KE BLYNK =====
void sendStatusToBlynk() {
  if (!Blynk.connected()) return;

  String status = "";

  if (WiFi.status() == WL_CONNECTED && Blynk.connected()) {
    status = "✓ All Systems Online";
  } else if (WiFi.status() == WL_CONNECTED) {
    status = "WiFi OK, Blynk Offline";
  } else {
    status = "WiFi Offline";
  }

  Blynk.virtualWrite(V0, status);
  Serial.print("[Blynk] Status sent: ");
  Serial.println(status);
}

// ===== FUNGSI BLYNK: CONNECTED EVENT =====
BLYNK_CONNECTED() {
  Serial.println();
  Serial.println("================================================");
  Serial.println("   ✓ BLYNK CONNECTED!");
  Serial.println("================================================");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("Monitoring aktif di Blynk app!");
  Serial.println("================================================");

  // Kirim status segera
  sendStatusToBlynk();
}
