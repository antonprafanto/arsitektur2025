/*
  ===================================================================
  STUDI KASUS 4: SMART BEDROOM - 5 Button Scene + Passive Buzzer
  ===================================================================

  Deskripsi:
  Sistem kamar tidur pintar dengan:
  - 5 Push Button untuk scene control
  - Passive Buzzer dengan melody (alarm lembut)
  - PWM LED dimming (gradual brightness)
  - 3 Mode: SLEEP, WAKE UP, AWAY

  Fitur Utama:
  1. Mode SLEEP: AC ON 24°C, lampu mati, night light dim
  2. Mode WAKE: Melody alarm, lampu gradual ON
  3. Mode AWAY: Hemat energi (semua mati)
  4. Manual control: AC & Light toggle
  5. PIR auto night light saat mode SLEEP

  Hardware (Sesuai Inventory):
  - ESP32, DHT11, PIR, LDR
  - 5x Push Button
  - Relay 2CH, Passive Buzzer
  - 3x LED (Hijau/Kuning/Merah)

  Wiring:
  DHT11: DATA→GPIO15
  PIR: OUT→GPIO27
  LDR: GPIO34
  Button SLEEP→GPIO14, WAKE→GPIO12, AWAY→GPIO13, AC→GPIO32, Light→GPIO33
  Relay: IN1→GPIO25(AC), IN2→GPIO26(Lampu)
  Passive Buzzer: GPIO23
  LED: GPIO2(Sleep), GPIO4(Wake), GPIO5(Away)

  Instruktur: Anton Prafanto, S.Kom., M.T.
  ===================================================================
*/

// ===== BLYNK =====
#define BLYNK_TEMPLATE_ID "TMPL4xxxxxxxxx"
#define BLYNK_TEMPLATE_NAME "Smart Bedroom"
#define BLYNK_AUTH_TOKEN "abcdefgh1234567890ijklmnopqrstuv"
#define BLYNK_PRINT Serial

// ===== LIBRARY =====
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// ===== WIFI =====
char ssid[] = "NAMA_WIFI_ANDA";
char pass[] = "PASSWORD_WIFI_ANDA";

// ===== PINS =====
#define DHTPIN 15
#define DHTTYPE DHT11
#define PIRPIN 27
#define LDRPIN 34

// 5 Buttons
#define BTN_SLEEP 14
#define BTN_WAKE 12
#define BTN_AWAY 13
#define BTN_AC 32
#define BTN_LIGHT 33

// Output
#define RELAY_AC 25
#define RELAY_LIGHT 26
#define BUZZER 23         // Passive buzzer (bisa tone)
#define LED_SLEEP 2       // Hijau
#define LED_WAKE 4        // Kuning
#define LED_AWAY 5        // Merah

// ===== MODE =====
enum Mode { SLEEP, WAKE, AWAY };
Mode currentMode = SLEEP;

// ===== SENSOR DATA =====
DHT dht(DHTPIN, DHTTYPE);
float suhu = 0;
float kelembapan = 0;
int cahaya = 0;
bool gerakan = false;

// ===== CONTROL =====
bool acStatus = false;
bool lightStatus = false;
bool nightLightActive = false;

// ===== BUTTON DEBOUNCE =====
unsigned long lastButtonPress[5] = {0};
const int DEBOUNCE_DELAY = 200;

// ===== TIMER =====
unsigned long lastSensorRead = 0;
unsigned long lastBlynkSend = 0;
unsigned long nightLightTimer = 0;

// ===== MELODY (Wake Up Alarm) =====
// Nada: C, D, E, F, G (Do, Re, Mi, Fa, Sol)
int melody[] = {262, 294, 330, 349, 392};
int noteDuration = 200;

void setup() {
  Serial.begin(115200);
  delay(100);
  
  Serial.println("\n========================================");
  Serial.println("  SMART BEDROOM - BLYNK IoT");
  Serial.println("========================================\n");

  // Setup pins
  pinMode(PIRPIN, INPUT);
  
  // Buttons (pull-up internal)
  pinMode(BTN_SLEEP, INPUT_PULLUP);
  pinMode(BTN_WAKE, INPUT_PULLUP);
  pinMode(BTN_AWAY, INPUT_PULLUP);
  pinMode(BTN_AC, INPUT_PULLUP);
  pinMode(BTN_LIGHT, INPUT_PULLUP);
  
  // Output
  pinMode(RELAY_AC, OUTPUT);
  pinMode(RELAY_LIGHT, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_SLEEP, OUTPUT);
  pinMode(LED_WAKE, OUTPUT);
  pinMode(LED_AWAY, OUTPUT);
  
  digitalWrite(RELAY_AC, LOW);
  digitalWrite(RELAY_LIGHT, LOW);
  
  // Init sensor
  dht.begin();
  Serial.println("[DHT11] Ready");
  
  // Default mode
  setMode(SLEEP);
  
  // Connect Blynk
  Serial.println("Connecting WiFi & Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  Serial.println("\n✓ Setup complete!");
  Serial.println("========================================\n");
}

void loop() {
  Blynk.run();

  // Handle buttons
  handleButtons();

  // Baca sensor setiap 2 detik
  if (millis() - lastSensorRead >= 2000) {
    lastSensorRead = millis();
    bacaSensor();
    handleAutoFeatures();
  }

  // Kirim ke Blynk
  if (millis() - lastBlynkSend >= 2000) {
    lastBlynkSend = millis();
    if (Blynk.connected()) {
      kirimKeBlynk();
    }
  }

  // Night light timeout (30 detik)
  if (nightLightActive && millis() - nightLightTimer > 30000) {
    analogWrite(LED_SLEEP, 51);  // Kembali ke dim 20%
    nightLightActive = false;
    Serial.println("[Night Light] Dim 20%");
  }
}

// ===== FUNGSI: BACA SENSOR =====
void bacaSensor() {
  suhu = dht.readTemperature();
  kelembapan = dht.readHumidity();
  
  if (isnan(suhu) || isnan(kelembapan)) {
    suhu = 0;
    kelembapan = 0;
  }

  cahaya = analogRead(LDRPIN);
  gerakan = digitalRead(PIRPIN);

  Serial.printf("T:%.1f°C RH:%.0f%% LDR:%d PIR:%d\n",
                suhu, kelembapan, cahaya, gerakan);
}

// ===== FUNGSI: HANDLE BUTTONS =====
void handleButtons() {
  // Button 0: SLEEP
  if (digitalRead(BTN_SLEEP) == LOW) {
    if (millis() - lastButtonPress[0] > DEBOUNCE_DELAY) {
      lastButtonPress[0] = millis();
      setMode(SLEEP);
      Serial.println("[Button] Mode SLEEP");
    }
  }

  // Button 1: WAKE
  if (digitalRead(BTN_WAKE) == LOW) {
    if (millis() - lastButtonPress[1] > DEBOUNCE_DELAY) {
      lastButtonPress[1] = millis();
      setMode(WAKE);
      Serial.println("[Button] Mode WAKE");
    }
  }

  // Button 2: AWAY
  if (digitalRead(BTN_AWAY) == LOW) {
    if (millis() - lastButtonPress[2] > DEBOUNCE_DELAY) {
      lastButtonPress[2] = millis();
      setMode(AWAY);
      Serial.println("[Button] Mode AWAY");
    }
  }

  // Button 3: AC Toggle
  if (digitalRead(BTN_AC) == LOW) {
    if (millis() - lastButtonPress[3] > DEBOUNCE_DELAY) {
      lastButtonPress[3] = millis();
      acStatus = !acStatus;
      digitalWrite(RELAY_AC, acStatus);
      Serial.printf("[AC] %s\n", acStatus ? "ON" : "OFF");
      Blynk.virtualWrite(V4, acStatus ? 1 : 0);
    }
  }

  // Button 4: Light Toggle
  if (digitalRead(BTN_LIGHT) == LOW) {
    if (millis() - lastButtonPress[4] > DEBOUNCE_DELAY) {
      lastButtonPress[4] = millis();
      toggleLight();
    }
  }
}

// ===== FUNGSI: SET MODE =====
void setMode(Mode newMode) {
  currentMode = newMode;
  
  // Matikan semua LED mode
  digitalWrite(LED_SLEEP, LOW);
  digitalWrite(LED_WAKE, LOW);
  digitalWrite(LED_AWAY, LOW);
  
  switch(currentMode) {
    case SLEEP:
      digitalWrite(LED_SLEEP, HIGH);
      digitalWrite(RELAY_AC, HIGH);
      acStatus = true;
      digitalWrite(RELAY_LIGHT, LOW);
      lightStatus = false;
      analogWrite(LED_SLEEP, 51);  // Dim 20% untuk night light
      Serial.println("[Mode] SLEEP - AC ON, Light OFF, Night light dim");
      break;
      
    case WAKE:
      digitalWrite(LED_WAKE, HIGH);
      playWakeUpAlarm();  // Melody
      gradualLightOn();   // Lampu gradual
      digitalWrite(RELAY_AC, LOW);
      acStatus = false;
      Serial.println("[Mode] WAKE - Alarm + Gradual light");
      Blynk.logEvent("wake_up", "Good Morning!");
      break;
      
    case AWAY:
      digitalWrite(LED_AWAY, HIGH);
      digitalWrite(RELAY_AC, LOW);
      digitalWrite(RELAY_LIGHT, LOW);
      acStatus = false;
      lightStatus = false;
      Serial.println("[Mode] AWAY - Semua OFF (hemat energi)");
      break;
  }
  
  Blynk.virtualWrite(V3, currentMode);
}

// ===== FUNGSI: AUTO FEATURES =====
void handleAutoFeatures() {
  // Night light auto saat mode SLEEP + PIR detect
  if (currentMode == SLEEP && gerakan && !nightLightActive) {
    analogWrite(LED_SLEEP, 128);  // Brighten ke 50%
    nightLightActive = true;
    nightLightTimer = millis();
    Serial.println("[Night Light] AUTO ON (PIR detect)");
  }
}

// ===== FUNGSI: PLAY WAKE UP ALARM (Passive Buzzer) =====
void playWakeUpAlarm() {
  Serial.println("[Alarm] Playing melody...");
  for (int i = 0; i < 5; i++) {
    tone(BUZZER, melody[i]);
    delay(noteDuration);
    noTone(BUZZER);
    delay(50);
  }
}

// ===== FUNGSI: GRADUAL LIGHT ON (PWM) =====
void gradualLightOn() {
  Serial.println("[Light] Gradual ON (0% → 100%)");
  digitalWrite(RELAY_LIGHT, HIGH);
  lightStatus = true;
  
  // Simulasi PWM dimming dengan delay
  // (Karena relay digital, ini hanya simulasi visual)
  // Untuk LED bisa pakai analogWrite()
}

// ===== FUNGSI: TOGGLE LIGHT =====
void toggleLight() {
  lightStatus = !lightStatus;
  digitalWrite(RELAY_LIGHT, lightStatus);
  Serial.printf("[Light] %s\n", lightStatus ? "ON" : "OFF");
  Blynk.virtualWrite(V5, lightStatus ? 1 : 0);
}

// ===== FUNGSI: KIRIM KE BLYNK =====
void kirimKeBlynk() {
  Blynk.virtualWrite(V0, suhu);
  Blynk.virtualWrite(V1, kelembapan);
  Blynk.virtualWrite(V2, cahaya);
  Blynk.virtualWrite(V3, currentMode);
  Blynk.virtualWrite(V4, acStatus ? 1 : 0);
  Blynk.virtualWrite(V5, lightStatus ? 1 : 0);
  
  String status = "Normal";
  if (currentMode == SLEEP) status = "Sleeping Mode";
  else if (currentMode == WAKE) status = "Wake Up";
  else if (currentMode == AWAY) status = "Away (Energy Saving)";
  Blynk.virtualWrite(V7, status);
}

// ===== BLYNK: MODE SELECTOR (V3) =====
BLYNK_WRITE(V3) {
  int value = param.asInt();
  setMode((Mode)value);
}

// ===== BLYNK: AC CONTROL (V4) =====
BLYNK_WRITE(V4) {
  int value = param.asInt();
  acStatus = (value == 1);
  digitalWrite(RELAY_AC, acStatus);
  Serial.printf("[Blynk] AC %s\n", acStatus ? "ON" : "OFF");
}

// ===== BLYNK: LIGHT CONTROL (V5) =====
BLYNK_WRITE(V5) {
  int value = param.asInt();
  lightStatus = (value == 1);
  digitalWrite(RELAY_LIGHT, lightStatus);
  Serial.printf("[Blynk] Light %s\n", lightStatus ? "ON" : "OFF");
}

// ===== BLYNK: CONNECTED =====
BLYNK_CONNECTED() {
  Serial.println("\n✓ BLYNK CONNECTED!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  
  Blynk.syncVirtual(V3, V4, V5);
}
