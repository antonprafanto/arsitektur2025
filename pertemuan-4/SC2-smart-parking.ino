/*
  ===================================================================
  STUDI KASUS 2: SMART PARKING - Multi Sensor + LED RGB + Blynk
  ===================================================================

  Deskripsi:
  Sistem parkir basement cerdas dengan:
  - 4 Sensor: PIR (Slot A), Button (Slot B), DHT11, LDR
  - 4 Output: LED RGB, Relay Fan, Relay Lampu, Buzzer
  - Platform: Blynk IoT

  Fitur Utama:
  1. Deteksi ketersediaan 2 slot parkir
  2. LED RGB indikator (Hijau=Kosong, Merah=Terisi)
  3. Exhaust fan otomatis (suhu > 30°C)
  4. Auto lighting (gelap → lampu ON)
  5. Alarm suhu bahaya (CO tinggi)
  6. Dashboard Blynk monitoring

  Hardware (Sesuai Inventory):
  - ESP32, DHT11, PIR, LDR, Button
  - LED RGB (atau 3x LED: R+G+B)
  - Relay 2CH, Buzzer

  Wiring:
  DHT11: DATA→GPIO15
  PIR (Slot A): OUT→GPIO27
  Button (Slot B): GPIO14 (pull-up internal)
  LDR: GPIO34 + R10k to GND
  LED RGB: R→GPIO2, G→GPIO4, B→GPIO5 (+ R220Ω)
  Relay: IN1→GPIO25(Fan), IN2→GPIO26(Lampu)
  Buzzer: GPIO33

  Instruktur: Anton Prafanto, S.Kom., M.T.
  ===================================================================
*/

// ===== BLYNK CREDENTIALS =====
#define BLYNK_TEMPLATE_ID "TMPL4xxxxxxxxx"
#define BLYNK_TEMPLATE_NAME "Smart Parking"
#define BLYNK_AUTH_TOKEN "abcdefgh1234567890ijklmnopqrstuv"
#define BLYNK_PRINT Serial

// ===== LIBRARY =====
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

//  ===== WIFI =====
char ssid[] = "NAMA_WIFI_ANDA";
char pass[] = "PASSWORD_WIFI_ANDA";

// ===== PINS =====
#define DHTPIN 15
#define DHTTYPE DHT11
#define PIR_SLOT_A 27
#define BTN_SLOT_B 14     // Button simulasi slot B
#define LDR_PIN 34
#define LED_R 2
#define LED_G 4
#define LED_B 5
#define RELAY_FAN 25
#define RELAY_LAMPU 26
#define BUZZER 33

// ===== THRESHOLD =====
const float SUHU_TINGGI = 30.0;    // Fan ON
const float SUHU_BAHAYA = 35.0;    // Alarm
const int CAHAYA_GELAP = 2500;

// ===== SENSOR DATA =====
DHT dht(DHTPIN, DHTTYPE);
float suhu = 0;
float kelembapan = 0;
int cahaya = 0;
bool slotA_occupied = false;       // PIR
bool slotB_occupied = false;       // Button
int totalTerisi = 0;

// ===== STATUS AKTUATOR =====
bool fanStatus = false;
bool lampuStatus = false;
bool alarmActive = false;

// ===== MODE MANUAL =====
bool fanManual = false;
bool lampuManual = false;

// ===== TIMER =====
unsigned long lastSensorRead = 0;
unsigned long lastBlynkSend = 0;
unsigned long lastCheck = 0;
unsigned long lastDebounce = 0;
bool lastButtonState = HIGH;

void setup() {
  Serial.begin(115200);
  delay(100);
  
  Serial.println("\n========================================");
  Serial.println("  SMART PARKING - BLYNK IoT");
  Serial.println("========================================\n");

  // Setup pins
  pinMode(PIR_SLOT_A, INPUT);
  pinMode(BTN_SLOT_B, INPUT_PULLUP);  // Pull-up internal
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(RELAY_FAN, OUTPUT);
  pinMode(RELAY_LAMPU, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  digitalWrite(RELAY_FAN, LOW);
  digitalWrite(RELAY_LAMPU, LOW);
  digitalWrite(BUZZER, LOW);
  setRGB(0, 255, 0);  // Hijau = Kosong

  // Init sensor
  dht.begin();
  Serial.println("[DHT11] Sensor ready");
  Serial.println("[PIR] Kalibrasi 30 detik...");
  delay(2000);

  // Connect Blynk
  Serial.println("\nConnecting to WiFi & Blynk...");
  Serial.print("SSID: ");
  Serial.println(ssid);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  Serial.println("\n✓ Setup complete!");
  Serial.println("========================================\n");
}

void loop() {
  Blynk.run();

  // Baca sensor setiap 2 detik
  if (millis() - lastSensorRead >= 2000) {
    lastSensorRead = millis();
    bacaSensor();
    kontrolOtomatis();
    updateRGBIndicator();
  }

  // Kirim ke Blynk setiap 2 detik
  if (millis() - lastBlynkSend >= 2000) {
    lastBlynkSend = millis();
    if (Blynk.connected()) {
      kirimKeBlynk();
    }
  }

  // Cek koneksi
  if (millis() - lastCheck >= 10000) {
    lastCheck = millis();
    cekKoneksi();
  }
}

// ===== FUNGSI: BACA SENSOR =====
void bacaSensor() {
  // DHT11
  suhu = dht.readTemperature();
  kelembapan = dht.readHumidity();
  
  if (isnan(suhu) || isnan(kelembapan)) {
    Serial.println("[DHT11] ERROR!");
    suhu = 0;
    kelembapan = 0;
  }

  // LDR
  cahaya = analogRead(LDR_PIN);

  // PIR Slot A
  slotA_occupied = digitalRead(PIR_SLOT_A);

  // Button Slot B (dengan debounce)
  bool currentButton = digitalRead(BTN_SLOT_B);
  if (currentButton != lastButtonState) {
    lastDebounce = millis();
  }
  if ((millis() - lastDebounce) > 50) {
    if (currentButton == LOW) {  // Button pressed
      slotB_occupied = !slotB_occupied;
      Serial.print("[SLOT B] ");
      Serial.println(slotB_occupied ? "TERISI (button)" : "KOSONG");
    }
  }
  lastButtonState = currentButton;

  // Hitung total
  totalTerisi = (slotA_occupied ? 1 : 0) + (slotB_occupied ? 1 : 0);

  // Debug log
  Serial.println("─── Parking Status ───");
  Serial.printf("Slot A: %s | Slot B: %s | Total: %d/2\n",
                slotA_occupied ? "TERISI" : "KOSONG",
                slotB_occupied ? "TERISI" : "KOSONG",
                totalTerisi);
  Serial.printf("Suhu: %.1f°C | RH: %.0f%% | Cahaya: %d\n",
                suhu, kelembapan, cahaya);
}

// ===== FUNGSI: KONTROL OTOMATIS =====
void kontrolOtomatis() {
  // === EXHAUST FAN ===
  if (!fanManual) {
    if (suhu > SUHU_TINGGI && !fanStatus) {
      digitalWrite(RELAY_FAN, HIGH);
      fanStatus = true;
      Serial.println("[FAN] AUTO ON (suhu tinggi)");
    }
    else if (suhu <= (SUHU_TINGGI - 2) && fanStatus) {
      digitalWrite(RELAY_FAN, LOW);
      fanStatus = false;
      Serial.println("[FAN] AUTO OFF");
    }
  }

  // === LAMPU PARKIR ===
  if (!lampuManual) {
    if (cahaya > CAHAYA_GELAP && !lampuStatus) {
      digitalWrite(RELAY_LAMPU, HIGH);
      lampuStatus = true;
      Serial.println("[LAMPU] AUTO ON (gelap)");
    }
    else if (cahaya <= CAHAYA_GELAP && lampuStatus) {
      digitalWrite(RELAY_LAMPU, LOW);
      lampuStatus = false;
      Serial.println("[LAMPU] AUTO OFF");
    }
  }

  // === BUZZER ALARM ===
  if (suhu > SUHU_BAHAYA && !alarmActive) {
    digitalWrite(BUZZER, HIGH);
    alarmActive = true;
    Serial.println("[ALARM] Suhu bahaya! (CO tinggi)");
  }
  else if (suhu <= SUHU_BAHAYA && alarmActive) {
    digitalWrite(BUZZER, LOW);
    alarmActive = false;
  }
}

// ===== FUNGSI: UPDATE LED RGB =====
void updateRGBIndicator() {
  if (totalTerisi == 0) {
    setRGB(0, 255, 0);  // Hijau = Semua kosong
  } else if (totalTerisi == 1) {
    setRGB(255, 255, 0);  // Kuning = 1 terisi
  } else {
    setRGB(255, 0, 0);  // Merah = Penuh
  }
}

// ===== FUNGSI: SET RGB =====
void setRGB(int r, int g, int b) {
  analogWrite(LED_R, r);
  analogWrite(LED_G, g);
  analogWrite(LED_B, b);
}

// ===== FUNGSI: KIRIM KE BLYNK =====
void kirimKeBlynk() {
  Blynk.virtualWrite(V0, slotA_occupied ? 1 : 0);
  Blynk.virtualWrite(V1, slotB_occupied ? 1 : 0);
  Blynk.virtualWrite(V2, totalTerisi);
  Blynk.virtualWrite(V3, suhu);
  Blynk.virtualWrite(V4, kelembapan);
  Blynk.virtualWrite(V5, cahaya);
  Blynk.virtualWrite(V6, fanStatus ? 1 : 0);
  Blynk.virtualWrite(V7, lampuStatus ? 1 : 0);
  
  String status = "Normal";
  if (suhu > SUHU_BAHAYA) status = "⚠️ CO TINGGI!";
  else if (totalTerisi == 2) status = "PENUH";
  else if (totalTerisi == 1) status = "1 Slot Tersedia";
  else status = "Semua Kosong";
  Blynk.virtualWrite(V8, status);
  
  Serial.println("[Blynk] Data sent\n");
}

// ===== FUNGSI: CEK KONEKSI =====
void cekKoneksi() {
  Serial.println("─── Status ───");
  Serial.print("WiFi: ");
  Serial.println(WiFi.status() == WL_CONNECTED ? "OK" : "DISCONNECTED");
  Serial.print("Blynk: ");
  Serial.println(Blynk.connected() ? "OK" : "DISCONNECTED");
  Serial.println();
}

// ===== BLYNK: KONTROL FAN (V6) =====
BLYNK_WRITE(V6) {
  int value = param.asInt();
  
  if (value == 1) {
    digitalWrite(RELAY_FAN, HIGH);
    fanStatus = true;
    fanManual = true;
    Serial.println("[FAN] MANUAL ON");
  } else {
    digitalWrite(RELAY_FAN, LOW);
    fanStatus = false;
    fanManual = false;
    Serial.println("[FAN] OFF → AUTO mode");
  }
}

// ===== BLYNK: KONTROL LAMPU (V7) =====
BLYNK_WRITE(V7) {
  int value = param.asInt();
  
  if (value == 1) {
    digitalWrite(RELAY_LAMPU, HIGH);
    lampuStatus = true;
    lampuManual = true;
    Serial.println("[LAMPU] MANUAL ON");
  } else {
    digitalWrite(RELAY_LAMPU, LOW);
    lampuStatus = false;
    lampuManual = false;
    Serial.println("[LAMPU] OFF → AUTO mode");
  }
}

// ===== BLYNK: EVENT CONNECTED =====
BLYNK_CONNECTED() {
  Serial.println("\n========================================");
  Serial.println("   ✓ BLYNK CONNECTED!");
  Serial.println("========================================");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("Smart Parking Online!");
  Serial.println("========================================\n");
  
  Blynk.syncVirtual(V6, V7);
}
