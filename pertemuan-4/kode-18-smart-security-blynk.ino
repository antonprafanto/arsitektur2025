/*
  ===================================================================
  STUDI KASUS 5: SMART SECURITY - Multi-Zone + Dual Buzzer
  ===================================================================

  Deskripsi:
  Sistem keamanan rumah dengan:
  - Multi-zone detection (3 zone: Pintu/Jendela/Belakang)
  - Active + Passive Buzzer (dual alarm)
  - LED blinking patterns (non-blocking)
  - ARM/DISARM system dengan grace period

  Fitur Utama:
  1. Mode DISARMED: Normal, semua aman
  2. Mode ARMED: System aktif, LED blink
  3. Mode TRIGGERED: Intrusion! Siren + notification
  4. Multi-zone: 3 sensor simulasi (button)
  5. Auto ARM saat malam + tidak ada gerakan

  Hardware (Sesuai Inventory):
  - ESP32, DHT11, PIR, LDR
  - 4x Push Button (3 zone + 1 arm/disarm)
  - Relay 2CH, Active + Passive Buzzer
  - 5x LED (Hijau/Merah/3 Kuning)

  Wiring:
  DHT11: DATA→GPIO15
  PIR: OUT→GPIO27
  LDR: GPIO34
  Button ARM→GPIO14, Zone1→GPIO12, Zone2→GPIO13, Zone3→GPIO32
  Relay: IN1→GPIO25(Lampu), IN2→GPIO26(Lock)
  Active Buzzer: GPIO33
  Passive Buzzer: GPIO23
  LED: Hijau→GPIO2, Merah→GPIO4, Kuning1→GPIO5, Kuning2→GPIO18, Kuning3→GPIO19

  Instruktur: Anton Prafanto, S.Kom., M.T.
  ===================================================================
*/

// ===== BLYNK =====
#define BLYNK_TEMPLATE_ID "TMPL4xxxxxxxxx"
#define BLYNK_TEMPLATE_NAME "Smart Security"
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
#define PIR PIN 27
#define LDRPIN 34

// Buttons
#define BTN_ARM 14
#define BTN_ZONE1 12   // Main Door
#define BTN_ZONE2 13   // Window
#define BTN_ZONE3 32   // Back Door

// Output
#define RELAY_LIGHT 25
#define RELAY_LOCK 26
#define ACTIVE_BUZZER 33
#define PASSIVE_BUZZER 23
#define LED_DISARMED 2    // Hijau
#define LED_ARMED 4       // Merah
#define LED_ZONE1 5       // Kuning
#define LED_ZONE2 18      // Kuning
#define LED_ZONE3 19      // Kuning

// ===== STATUS =====
enum SecurityStatus { DISARMED, ARMED, TRIGGERED };
SecurityStatus currentStatus = DISARMED;

// ===== SENSOR DATA =====
DHT dht(DHTPIN, DHTTYPE);
float suhu = 0;
float kelembapan = 0;
int cahaya = 0;
bool gerakan = false;

// ===== ZONE STATUS =====
bool zoneTriggered[3] = {false, false, false};
int triggeredZone = -1;  // -1 = none, 0-2 = zone number

// ===== TIMING =====
unsigned long lastSensorRead = 0;
unsigned long lastBlynkSend = 0;
unsigned long lastButtonPress[4] = {0};
unsigned long gracePeriodStart = 0;
unsigned long triggeredStart = 0;
unsigned long lastBlink = 0;
bool ledState = false;

const int DEBOUNCE_DELAY = 200;
const int GRACE_PERIOD = 10000;      // 10 detik untuk disarm
const int TRIGGERED_DURATION = 30000; // 30 detik siren

void setup() {
  Serial.begin(115200);
  delay(100);
  
  Serial.println("\n========================================");
  Serial.println("  SMART SECURITY - BLYNK IoT");
  Serial.println("========================================\n");

  // Setup pins
  pinMode(PIRPIN, INPUT);
  
  // Buttons (pull-up internal)
  pinMode(BTN_ARM, INPUT_PULLUP);
  pinMode(BTN_ZONE1, INPUT_PULLUP);
  pinMode(BTN_ZONE2, INPUT_PULLUP);
  pinMode(BTN_ZONE3, INPUT_PULLUP);
  
  // Output
  pinMode(RELAY_LIGHT, OUTPUT);
  pinMode(RELAY_LOCK, OUTPUT);
  pinMode(ACTIVE_BUZZER, OUTPUT);
  pinMode(PASSIVE_BUZZER, OUTPUT);
  pinMode(LED_DISARMED, OUTPUT);
  pinMode(LED_ARMED, OUTPUT);
  pinMode(LED_ZONE1, OUTPUT);
  pinMode(LED_ZONE2, OUTPUT);
  pinMode(LED_ZONE3, OUTPUT);
  
  digitalWrite(RELAY_LIGHT, LOW);
  digitalWrite(RELAY_LOCK, LOW);
  digitalWrite(ACTIVE_BUZZER, LOW);
  noTone(PASSIVE_BUZZER);
  
  // Init sensor
  dht.begin();
  Serial.println("[DHT11] Ready");
  
  // Default: DISARMED
  setStatus(DISARMED);
  
  // Connect Blynk
  Serial.println("Connecting WiFi & Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  Serial.println("\n✓ Setup complete!");
  Serial.println("Press ARM button or use Blynk to activate");
  Serial.println("========================================\n");
}

void loop() {
  Blynk.run();

  // Handle buttons
  handleButtons();
  
  // Check zones
  checkZones();
  
  // Handle blinking LED
  if (currentStatus == ARMED) {
    blinkLED(LED_ARMED, 1000);  // Slow blink
  } else if (currentStatus == TRIGGERED) {
    blinkLED(LED_ARMED, 200);   // Fast blink
  }

  // Baca sensor
  if (millis() - lastSensorRead >= 2000) {
    lastSensorRead = millis();
    bacaSensor();
    checkFireAlarm();
  }

  // Kirim ke Blynk
  if (millis() - lastBlynkSend >= 2000) {
    lastBlynkSend = millis();
    if (Blynk.connected()) {
      kirimKeBlynk();
    }
  }

  // Grace period handling
  if (currentStatus == ARMED && triggeredZone != -1) {
    if (millis() - gracePeriodStart >= GRACE_PERIOD) {
      // Grace period habis → TRIGGERED!
      setStatus(TRIGGERED);
    }
  }

  // Auto disarm triggered setelah 30 detik
  if (currentStatus == TRIGGERED) {
    if (millis() - triggeredStart >= TRIGGERED_DURATION) {
      setStatus(DISARMED);
      Serial.println("[Auto] Disarmed after 30s");
    }
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
}

// ===== FUNGSI: HANDLE BUTTONS =====
void handleButtons() {
  // Button ARM/DISARM
  if (digitalRead(BTN_ARM) == LOW) {
    if (millis() - lastButtonPress[0] > DEBOUNCE_DELAY) {
      lastButtonPress[0] = millis();
      toggleArm();
    }
  }

  // Zone buttons
  int zonePins[] = {BTN_ZONE1, BTN_ZONE2, BTN_ZONE3};
  for (int i = 0; i < 3; i++) {
    if (digitalRead(zonePins[i]) == LOW) {
      if (millis() - lastButtonPress[i + 1] > DEBOUNCE_DELAY) {
        lastButtonPress[i + 1] = millis();
        handleZoneTrigger(i);
      }
    }
  }
}

// ===== FUNGSI: TOGGLE ARM/DISARM =====
void toggleArm() {
  if (currentStatus == DISARMED) {
    setStatus(ARMED);
  } else {
    setStatus(DISARMED);
  }
}

// ===== FUNGSI: SET STATUS =====
void setStatus(SecurityStatus newStatus) {
  currentStatus = newStatus;
  
  // Reset zone LEDs
  digitalWrite(LED_ZONE1, LOW);
  digitalWrite(LED_ZONE2, LOW);
  digitalWrite(LED_ZONE3, LOW);
  
  switch(currentStatus) {
    case DISARMED:
      digitalWrite(LED_DISARMED, HIGH);
      digitalWrite(LED_ARMED, LOW);
      digitalWrite(ACTIVE_BUZZER, LOW);
      noTone(PASSIVE_BUZZER);
      digitalWrite(RELAY_LIGHT, LOW);
      digitalWrite(RELAY_LOCK, LOW);
      triggeredZone = -1;
      Serial.println("[Status] DISARMED");
      break;
      
    case ARMED:
      digitalWrite(LED_DISARMED, LOW);
      // LED_ARMED akan blink di loop
      digitalWrite(RELAY_LOCK, HIGH);  // Lock
      Serial.println("[Status] ARMED - System Active");
      Blynk.logEvent("armed", "Security System ARMED");
      break;
      
    case TRIGGERED:
      digitalWrite(ACTIVE_BUZZER, HIGH);  // SIREN!
      digitalWrite(RELAY_LIGHT, HIGH);
      triggeredStart = millis();
      Serial.printf("[INTRUSION!] Zone %d\n", triggeredZone + 1);
      
      // Blynk notification
      String msg = "INTRUSION! Zone: ";
      if (triggeredZone == 0) msg += "Main Door";
      else if (triggeredZone == 1) msg += "Window";
      else msg += "Back Door";
      Blynk.logEvent("intrusion", msg);
      
      // Nyalakan LED zone yang triggered
      if (triggeredZone == 0) digitalWrite(LED_ZONE1, HIGH);
      else if (triggeredZone == 1) digitalWrite(LED_ZONE2, HIGH);
      else digitalWrite(LED_ZONE3, HIGH);
      break;
  }
  
  Blynk.virtualWrite(V0, currentStatus);
}

// ===== FUNGSI: CHECK ZONES =====
void checkZones() {
  // Function ini sudah dihandle di handleButtons
  // Tapi bisa ditambah logic PIR untuk motion detection
  if (currentStatus == ARMED && gerakan) {
    Serial.println("[PIR] Motion detected while ARMED!");
    // Bisa trigger alarm atau log saja
  }
}

// ===== FUNGSI: HANDLE ZONE TRIGGER =====
void handleZoneTrigger(int zone) {
  Serial.printf("[Zone %d] Triggered\n", zone + 1);
  zoneTriggered[zone] = true;
  
  if (currentStatus == DISARMED) {
    // Hanya log
    Serial.println("  System DISARMED, no alarm");
  } else if (currentStatus == ARMED) {
    // Start grace period
    triggeredZone = zone;
    gracePeriodStart = millis();
    
    // Warning beep (passive buzzer)
    warningBeep();
    Serial.println("  Grace period 10s... Disarm to cancel!");
  }
  
  Blynk.virtualWrite(V1 + zone, 1);
}

// ===== FUNGSI: WARNING BEEP (Passive Buzzer) =====
void warningBeep() {
  for (int i = 0; i < 3; i++) {
    tone(PASSIVE_BUZZER, 1000);
    delay(100);
    noTone(PASSIVE_BUZZER);
    delay(100);
  }
}

// ===== FUNGSI: BLINK LED (Non-blocking) =====
void blinkLED(int pin, int interval) {
  if (millis() - lastBlink >= interval) {
    lastBlink = millis();
    ledState = !ledState;
    digitalWrite(pin, ledState);
  }
}

// ===== FUNGSI: CHECK FIRE ALARM =====
void checkFireAlarm() {
  if (suhu > 50.0) {
    digitalWrite(ACTIVE_BUZZER, HIGH);
    Serial.println("[FIRE ALARM!] Temperature > 50°C");
    Blynk.logEvent("fire", "FIRE DETECTED!");
  }
}

// ===== FUNGSI: KIRIM KE BLYNK =====
void kirimKeBlynk() {
  Blynk.virtualWrite(V0, currentStatus);
  Blynk.virtualWrite(V1, zoneTriggered[0] ? 1 : 0);
  Blynk.virtualWrite(V2, zoneTriggered[1] ? 1 : 0);
  Blynk.virtualWrite(V3, zoneTriggered[2] ? 1 : 0);
  Blynk.virtualWrite(V4, gerakan ? 1 : 0);
  Blynk.virtualWrite(V5, suhu);
  
  String status = "Normal";
  if (currentStatus == DISARMED) status = "DISARMED";
  else if (currentStatus == ARMED) status = "ARMED (Active)";
  else if (currentStatus == TRIGGERED) status = "⚠️ INTRUSION!";
  Blynk.virtualWrite(V7, status);
}

// ===== BLYNK: ARM/DISARM (V6) =====
BLYNK_WRITE(V6) {
  int value = param.asInt();
  if (value == 1) {
    setStatus(ARMED);
  } else {
    setStatus(DISARMED);
  }
}

// ===== BLYNK: CONNECTED =====
BLYNK_CONNECTED() {
  Serial.println("\n✓ BLYNK CONNECTED!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  
  Blynk.syncVirtual(V6);
}
