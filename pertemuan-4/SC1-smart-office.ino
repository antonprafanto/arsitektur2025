/*
  ===================================================================
  STUDI KASUS: SMART OFFICE - 3 Sensor + 3 Output + Blynk IoT
  ===================================================================

  Deskripsi:
  Program studi kasus lengkap untuk sistem smart office menggunakan:
  - 3 Sensor: DHT11 (Suhu/Kelembapan), LDR (Cahaya), PIR (Gerakan)
  - 3 Output: Relay AC, Relay Lampu, Buzzer
  - 3 LED Indikator: WiFi, Blynk, Error
  - Platform Cloud: Blynk IoT (monitoring & kontrol via smartphone)

  Fitur Lengkap:
  1. Monitoring real-time suhu, kelembapan, cahaya, gerakan
  2. AC otomatis: Nyala jika suhu > 28°C
  3. Lampu otomatis: Nyala jika gelap DAN ada orang (hemat energi!)
  4. Buzzer warning: Bunyi jika suhu > 32°C
  5. LED indikator status WiFi & Blynk
  6. Kontrol manual via Blynk app (override otomatis)
  7. Dashboard Blynk lengkap dengan 7 widget
  8. Auto-reconnect WiFi & Blynk
  9. Error handling untuk semua sensor

  Hardware (Sesuai Inventory):
  - 1x ESP32
  - 1x DHT11
  - 1x LDR + Resistor 10kΩ
  - 1x PIR HC-SR501
  - 1x Relay Module 2 Channel
  - 1x Buzzer
  - 3x LED (Hijau, Kuning, Merah)

  Wiring:
  DHT11: VCC→3.3V, DATA→GPIO15, GND→GND
  LDR: Pin1→3.3V, Pin2→GPIO34, R10k dari GPIO34→GND
  PIR: VCC→5V, OUT→GPIO27, GND→GND
  Relay: VCC→5V, IN1→GPIO25(AC), IN2→GPIO26(Lampu)
  Buzzer: (+)→GPIO33, (-)→GND
  LED Hijau (WiFi): GPIO2 + R220Ω → GND
  LED Kuning (Blynk): GPIO4 + R220Ω → GND
  LED Merah (Error): GPIO5 + R220Ω → GND

  Library:
  - WiFi (built-in)
  - Blynk (by Volodymyr Shymanskyy)
  - DHT sensor library (by Adafruit)

  Setup Blynk:
  📖 Lihat SC1-SMART-OFFICE.md untuk panduan lengkap!

  Instruktur: Anton Prafanto, S.Kom., M.T.
  ===================================================================
*/

// ===== BLYNK CREDENTIALS =====
// ⚠️ WAJIB DIISI! Copy dari https://blynk.cloud
#define BLYNK_TEMPLATE_ID "TMPL4xxxxxxxxx"
#define BLYNK_TEMPLATE_NAME "Smart Office"
#define BLYNK_AUTH_TOKEN "abcdefgh1234567890ijklmnopqrstuv"
#define BLYNK_PRINT Serial

// ===== INCLUDE LIBRARY =====
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// ===== WIFI CREDENTIALS =====
char ssid[] = "NAMA_WIFI_ANDA";
char pass[] = "PASSWORD_WIFI_ANDA";

// ===== PIN DEFINITIONS =====
#define DHTPIN 15
#define DHTTYPE DHT11
#define LDRPIN 34
#define PIRPIN 27
#define RELAY_AC 25
#define RELAY_LAMPU 26
#define BUZZER 33

// LED Indikator
#define LED_WIFI 2      // Hijau = WiFi Connected
#define LED_BLYNK 4     // Kuning = Blynk Connected
#define LED_ERROR 5     // Merah = Error

// ===== THRESHOLD =====
const float SUHU_TINGGI = 28.0;      // AC ON jika > 28°C
const float SUHU_BAHAYA = 32.0;      // Buzzer ON jika > 32°C
const int CAHAYA_GELAP = 2500;       // Cahaya > 2500 = gelap

// ===== VARIABEL SENSOR =====
DHT dht(DHTPIN, DHTTYPE);
float suhu = 0;
float kelembapan = 0;
int cahaya = 0;
bool gerakan = false;

// ===== VARIABEL KONTROL =====
bool acStatus = false;
bool lampuStatus = false;
bool acManual = false;           // true = kontrol dari app
bool lampuManual = false;

// ===== TIMER =====
unsigned long lastSensorRead = 0;
unsigned long lastBlynkSend = 0;
unsigned long lastCheck = 0;
bool warningActive = false;      // Flag untuk buzzer

void setup() {
  Serial.begin(115200);
  delay(100);
  
  Serial.println("\n========================================");
  Serial.println("  SMART OFFICE - STUDI KASUS BLYNK");
  Serial.println("========================================\n");

  // Setup pin
  pinMode(PIRPIN, INPUT);
  pinMode(RELAY_AC, OUTPUT);
  pinMode(RELAY_LAMPU, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_WIFI, OUTPUT);
  pinMode(LED_BLYNK, OUTPUT);
  pinMode(LED_ERROR, OUTPUT);
  
  digitalWrite(RELAY_AC, LOW);
  digitalWrite(RELAY_LAMPU, LOW);
  digitalWrite(BUZZER, LOW);
  digitalWrite(LED_WIFI, LOW);
  digitalWrite(LED_BLYNK, LOW);
  digitalWrite(LED_ERROR, LOW);

  // Inisialisasi sensor
  dht.begin();
  Serial.println("[DHT11] Sensor siap");
  Serial.println("[PIR] Kalibrasi 30 detik... Jangan gerak!\n");
  delay(2000);

  // Koneksi Blynk
  Serial.println("Menghubungkan ke WiFi dan Blynk...");
  Serial.print("SSID: ");
  Serial.println(ssid);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  Serial.println("\n✓ Setup selesai!");
  Serial.println("========================================\n");
}

void loop() {
  Blynk.run();

  // Update LED status
  updateLEDStatus();

  // Baca sensor setiap 2 detik
  if (millis() - lastSensorRead >= 2000) {
    lastSensorRead = millis();
    bacaSensor();
    kontrolOtomatis();
  }

  // Kirim ke Blynk setiap 2 detik
  if (millis() - lastBlynkSend >= 2000) {
    lastBlynkSend = millis();
    if (Blynk.connected()) {
      kirimKeBlynk();
    }
  }

  // Cek koneksi setiap 10 detik
  if (millis() - lastCheck >= 10000) {
    lastCheck = millis();
    cekKoneksi();
  }
}

// ===== FUNGSI: UPDATE LED STATUS =====
void updateLEDStatus() {
  // LED WiFi (Hijau)
  digitalWrite(LED_WIFI, WiFi.status() == WL_CONNECTED ? HIGH : LOW);
  
  // LED Blynk (Kuning)
  digitalWrite(LED_BLYNK, Blynk.connected() ? HIGH : LOW);
  
  // LED Error (Merah) - nyala jika ada error sensor
  if (suhu == 0 && kelembapan == 0) {
    digitalWrite(LED_ERROR, HIGH);
  } else {
    digitalWrite(LED_ERROR, LOW);
  }
}

// ===== FUNGSI: BACA SEMUA SENSOR =====
void bacaSensor() {
  // Baca DHT11
  suhu = dht.readTemperature();
  kelembapan = dht.readHumidity();
  
  if (isnan(suhu) || isnan(kelembapan)) {
    Serial.println("[DHT11] ERROR: Gagal baca!");
    suhu = 0;
    kelembapan = 0;
  }

  // Baca LDR (0=terang, 4095=gelap)
  cahaya = analogRead(LDRPIN);

  // Baca PIR
  gerakan = digitalRead(PIRPIN);

  // Log ke Serial
  Serial.println("─── Sensor Reading ───");
  Serial.printf("Suhu: %.1f°C | RH: %.0f%% | Cahaya: %d | PIR: %s\n",
                suhu, kelembapan, cahaya, gerakan ? "ADA" : "Kosong");
}

// ===== FUNGSI: KONTROL OTOMATIS =====
void kontrolOtomatis() {
  // === AC OTOMATIS ===
  if (!acManual) {
    if (suhu > SUHU_TINGGI && !acStatus) {
      digitalWrite(RELAY_AC, HIGH);
      acStatus = true;
      Serial.println("[AC] AUTO ON (suhu tinggi)");
      bunyiBuzzer(2);  // Notifikasi 2x beep
    } 
    else if (suhu <= (SUHU_TINGGI - 2) && acStatus) {
      digitalWrite(RELAY_AC, LOW);
      acStatus = false;
      Serial.println("[AC] AUTO OFF (suhu normal)");
    }
  }

  // === LAMPU OTOMATIS ===
  if (!lampuManual) {
    if (cahaya > CAHAYA_GELAP && gerakan && !lampuStatus) {
      digitalWrite(RELAY_LAMPU, HIGH);
      lampuStatus = true;
      Serial.println("[LAMPU] AUTO ON (gelap + ada orang)");
    }
    else if ((cahaya <= CAHAYA_GELAP || !gerakan) && lampuStatus) {
      digitalWrite(RELAY_LAMPU, LOW);
      lampuStatus = false;
      Serial.println("[LAMPU] AUTO OFF");
    }
  }

  // === BUZZER WARNING ===
  if (suhu > SUHU_BAHAYA && !warningActive) {
    Serial.println("[WARNING] Suhu bahaya! Buzzer aktif!");
    digitalWrite(BUZZER, HIGH);
    warningActive = true;
  }
  else if (suhu <= SUHU_BAHAYA && warningActive) {
    digitalWrite(BUZZER, LOW);
    warningActive = false;
  }
}

// ===== FUNGSI: KIRIM KE BLYNK =====
void kirimKeBlynk() {
  Blynk.virtualWrite(V0, suhu);
  Blynk.virtualWrite(V1, kelembapan);
  Blynk.virtualWrite(V2, cahaya);
  Blynk.virtualWrite(V3, gerakan ? 1 : 0);
  Blynk.virtualWrite(V4, acStatus ? 1 : 0);
  Blynk.virtualWrite(V5, lampuStatus ? 1 : 0);
  
  String status = "Normal";
  if (suhu > SUHU_BAHAYA) status = "⚠️ BAHAYA!";
  else if (suhu > SUHU_TINGGI) status = "Panas";
  Blynk.virtualWrite(V6, status);
  
  Serial.println("[Blynk] Data terkirim\n");
}

// ===== FUNGSI: CEK KONEKSI =====
void cekKoneksi() {
  Serial.println("─── Status Koneksi ───");
  Serial.print("WiFi: ");
  Serial.println(WiFi.status() == WL_CONNECTED ? "OK" : "DISCONNECTED");
  Serial.print("Blynk: ");
  Serial.println(Blynk.connected() ? "OK" : "DISCONNECTED");
  Serial.println();
}

// ===== FUNGSI: BUZZER =====
void bunyiBuzzer(int kali) {
  for (int i = 0; i < kali; i++) {
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
    delay(100);
  }
}

// ===== BLYNK: KONTROL AC (V4) =====
BLYNK_WRITE(V4) {
  int value = param.asInt();
  
  if (value == 1) {
    digitalWrite(RELAY_AC, HIGH);
    acStatus = true;
    acManual = true;
    Serial.println("[AC] MANUAL ON dari app");
  } else {
    digitalWrite(RELAY_AC, LOW);
    acStatus = false;
    acManual = false;
    Serial.println("[AC] OFF → kembali mode AUTO");
  }
}

// ===== BLYNK: KONTROL LAMPU (V5) =====
BLYNK_WRITE(V5) {
  int value = param.asInt();
  
  if (value == 1) {
    digitalWrite(RELAY_LAMPU, HIGH);
    lampuStatus = true;
    lampuManual = true;
    Serial.println("[LAMPU] MANUAL ON dari app");
  } else {
    digitalWrite(RELAY_LAMPU, LOW);
    lampuStatus = false;
    lampuManual = false;
    Serial.println("[LAMPU] OFF → kembali mode AUTO");
  }
}

// ===== BLYNK: EVENT CONNECTED =====
BLYNK_CONNECTED() {
  Serial.println("\n========================================");
  Serial.println("   ✓ BLYNK CONNECTED!");
  Serial.println("========================================");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Buka Blynk app untuk monitoring!");
  Serial.println("========================================\n");
  
  // Sync status dari server
  Blynk.syncVirtual(V4, V5);
}
