/*
  ===================================================================
  STUDI KASUS 3: SMART HOME DASHBOARD - OLED + Blynk IoT
  ===================================================================

  Deskripsi:
  Sistem smart home dengan dual interface (OLED lokal + Blynk remote):
  - OLED Display 0.96" dengan 3 halaman menu
  - Button navigation (Next & Select)
  - Dual control: Lokal (button) + Remote (Blynk app)
  - Auto mode dengan grafik real-time

  Fitur Utama:
  1. OLED Menu: Home, Graph, Control (3 pages)
  2. Button Next: Navigate pages
  3. Button Select: Toggle controls
  4. Auto/Manual mode switchable
  5. Bar chart suhu di OLED
  6. LED indikator status (Hijau/Kuning/Merah)
  7. Sinkronisasi OLED ↔ Blynk

  Hardware:
  - ESP32, OLED 0.96" I2C, DHT11, PIR, LDR
  - 2x Button, Relay 2CH, Buzzer, 3x LED

  Wiring:
  OLED: SDA→GPIO21, SCL→GPIO22
  DHT11: DATA→GPIO15
  PIR: OUT→GPIO27
  LDR: GPIO34 + R10k
  Button Next: GPIO14 (pull-up)
  Button Select: GPIO12 (pull-up)
  Relay: IN1→GPIO25(AC), IN2→GPIO26(Lampu)
  LED: GPIO2(Hijau), GPIO4(Kuning), GPIO5(Merah)
  Buzzer: GPIO33

  Instruktur: Anton Prafanto, S.Kom., M.T.
  ===================================================================
*/

// ===== BLYNK =====
#define BLYNK_TEMPLATE_ID "TMPL4xxxxxxxxx"
#define BLYNK_TEMPLATE_NAME "Smart Home Dashboard"
#define BLYNK_AUTH_TOKEN "abcdefgh1234567890ijklmnopqrstuv"
#define BLYNK_PRINT Serial

// ===== LIBRARY =====
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ===== WIFI =====
char ssid[] = "NAMA_WIFI_ANDA";
char pass[] = "PASSWORD_WIFI_ANDA";

// ===== PINS =====
#define DHTPIN 15
#define DHTTYPE DHT11
#define PIRPIN 27
#define LDRPIN 34
#define BTN_NEXT 14
#define BTN_SELECT 12
#define RELAY_AC 25
#define RELAY_LAMPU 26
#define BUZZER 33
#define LED_GREEN 2
#define LED_YELLOW 4
#define LED_RED 5

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

// ===== OBJECTS =====
DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ===== SENSOR DATA =====
float suhu = 0;
float kelembapan = 0;
int cahaya = 0;
bool gerakan = false;

// ===== CONTROL =====
bool acStatus = false;
bool lampuStatus = false;
bool modeAuto = true;       // true=AUTO, false=MANUAL

// ===== OLED =====
int currentPage = 1;        // 1=Home, 2=Graph, 3=Control
int cursorPos = 0;          // Posisi cursor di Page 3
float suhuHistory[10] = {0}; // Untuk graph

// ===== BUTTON =====
bool lastNext = HIGH;
bool lastSelect = HIGH;
unsigned long lastDebounce = 0;

// ===== THRESHOLD =====
const float SUHU_TINGGI = 28.0;
const float SUHU_BAHAYA = 35.0;
const int CAHAYA_GELAP = 2500;

// ===== TIMER =====
unsigned long lastSensorRead = 0;
unsigned long lastBlynkSend = 0;
unsigned long lastOLEDUpdate = 0;

void setup() {
  Serial.begin(115200);
  delay(100);
  
  Serial.println("\n========================================");
  Serial.println("  SMART HOME OLED DASHBOARD");
  Serial.println("========================================\n");

  // Pins
  pinMode(PIRPIN, INPUT);
  pinMode(BTN_NEXT, INPUT_PULLUP);
  pinMode(BTN_SELECT, INPUT_PULLUP);
  pinMode(RELAY_AC, OUTPUT);
  pinMode(RELAY_LAMPU, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  
  digitalWrite(RELAY_AC, LOW);
  digitalWrite(RELAY_LAMPU, LOW);
  digitalWrite(BUZZER, LOW);
  setStatusLED(0);  // Green

  // DHT
  dht.begin();
  Serial.println("[DHT11] OK");

  // OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("[OLED] ERROR!");
    while (1);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Smart Home");
  display.println("Initializing...");
  display.display();
  delay(2000);

  // Blynk
  Serial.println("Connecting WiFi & Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  Serial.println("\n✓ Setup complete!");
  Serial.println("Button NEXT = Change page");
  Serial.println("Button SELECT = Action");
  Serial.println("========================================\n");
}

void loop() {
  Blynk.run();

  // Button handling
  handleButtons();

  // Sensor setiap 2 detik
  if (millis() - lastSensorRead >= 2000) {
    lastSensorRead = millis();
    bacaSensor();
    kontrolOtomatis();
    updateHistory();
  }

  // Blynk setiap 2 detik
  if (millis() - lastBlynkSend >= 2000) {
    lastBlynkSend = millis();
    if (Blynk.connected()) {
      kirimKeBlynk();
    }
  }

  // OLED setiap 500ms
  if (millis() - lastOLEDUpdate >= 500) {
    lastOLEDUpdate = millis();
    updateOLED();
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

// ===== FUNGSI: KONTROL OTOMATIS =====
void kontrolOtomatis() {
  if (modeAuto) {
    // AC
    if (suhu > SUHU_TINGGI && !acStatus) {
      digitalWrite(RELAY_AC, HIGH);
      acStatus = true;
      Serial.println("[AC] AUTO ON");
    } else if (suhu <= (SUHU_TINGGI - 2) && acStatus) {
      digitalWrite(RELAY_AC, LOW);
      acStatus = false;
      Serial.println("[AC] AUTO OFF");
    }

    // Lampu
    if (cahaya > CAHAYA_GELAP && gerakan && !lampuStatus) {
      digitalWrite(RELAY_LAMPU, HIGH);
      lampuStatus = true;
      Serial.println("[LAMPU] AUTO ON");
    } else if ((cahaya <= CAHAYA_GELAP || !gerakan) && lampuStatus) {
      digitalWrite(RELAY_LAMPU, LOW);
      lampuStatus = false;
      Serial.println("[LAMPU] AUTO OFF");
    }
  }

  // Alarm & LED Status
  if (suhu > SUHU_BAHAYA) {
    digitalWrite(BUZZER, HIGH);
    setStatusLED(2);  // Red
    delay(1000);
  } else if (suhu > SUHU_TINGGI) {
    digitalWrite(BUZZER, LOW);
    setStatusLED(1);  // Yellow
    delay(1000);
  } else {
    digitalWrite(BUZZER, LOW);
    setStatusLED(0);  // Green
    delay(1000);
  }

  //Buzzer & PIR
  if (gerakan == HIGH){
    digitalWrite(BUZZER, HIGH);
    delay(1000);
  }else{
    digitalWrite(BUZZER, HIGH);
  }
}

// ===== FUNGSI: BUTTON HANDLER =====
void handleButtons() {
  bool currentNext = digitalRead(BTN_NEXT);
  bool currentSelect = digitalRead(BTN_SELECT);

  // Button NEXT (change page)
  if (currentNext == LOW && lastNext == HIGH) {
    if (millis() - lastDebounce > 200) {
      currentPage++;
      if (currentPage > 3) currentPage = 1;
      Serial.printf("[OLED] Page %d\n", currentPage);
      lastDebounce = millis();
    }
  }
  lastNext = currentNext;

  // Button SELECT (action)
  if (currentSelect == LOW && lastSelect == HIGH) {
    if (millis() - lastDebounce > 200) {
      handleSelect();
      lastDebounce = millis();
    }
  }
  lastSelect = currentSelect;
}

// ===== FUNGSI: SELECT ACTION =====
void handleSelect() {
  if (currentPage == 1) {
    // Toggle Auto/Manual
    modeAuto = !modeAuto;
    Serial.printf("[MODE] %s\n", modeAuto ? "AUTO" : "MANUAL");
    Blynk.virtualWrite(V6, modeAuto ? 1 : 0);
  } 
  else if (currentPage == 3) {
    // Toggle selected item
    if (cursorPos == 0) {
      acStatus = !acStatus;
      digitalWrite(RELAY_AC, acStatus);
      Serial.printf("[AC] %s\n", acStatus ? "ON" : "OFF");
      Blynk.virtualWrite(V4, acStatus ? 1 : 0);
    } else if (cursorPos == 1) {
      lampuStatus = !lampuStatus;
      digitalWrite(RELAY_LAMPU, lampuStatus);
      Serial.printf("[LAMPU] %s\n", lampuStatus ? "ON" : "OFF");
      Blynk.virtualWrite(V5, lampuStatus ? 1 : 0);
    }
    cursorPos = (cursorPos + 1) % 2;
  }
}

// ===== FUNGSI: UPDATE OLED =====
void updateOLED() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  if (currentPage == 1) {
    // HOME PAGE
    display.setCursor(0, 0);
    display.println("SMART HOME");
    display.println("---Dashboard---");
    display.printf("T: %.1f C\n", suhu);
    display.printf("RH: %.0f %%\n", kelembapan);
    display.printf("Cahaya: %s\n", cahaya > CAHAYA_GELAP ? "GELAP" : "TERANG");
    display.printf("PIR: %s\n", gerakan ? "ADA" : "---");
    display.printf("Mode: %s [1/3]", modeAuto ? "AUTO" : "MANUAL");
  }
  else if (currentPage == 2) {
    // GRAPH PAGE
    display.setCursor(0, 0);
    display.println("SUHU 24H");
    drawBarChart();
    display.setCursor(0, 57);
    display.println("       [2/3]");
  }
  else if (currentPage == 3) {
    // CONTROL PAGE
    display.setCursor(0, 0);
    display.println("KONTROL MANUAL");
    display.println("---------------");
    display.printf("%c AC:    %s\n", cursorPos == 0 ? '>' : ' ', acStatus ? "ON " : "OFF");
    display.printf("%c Lampu: %s\n", cursorPos == 1 ? '>' : ' ', lampuStatus ? "ON " : "OFF");
    display.println("");
    display.println("SELECT=Toggle");
    display.println("       [3/3]");
  }

  display.display();
}

// ===== FUNGSI: DRAW BAR CHART =====
void drawBarChart() {
  int barWidth = 10;
  int maxHeight = 40;
  int baseY = 55;
  
  for (int i = 0; i < 10; i++) {
    int barHeight = map((int)suhuHistory[i], 20, 40, 0, maxHeight);
    barHeight = constrain(barHeight, 0, maxHeight);
    
    int x = 5 + i * (barWidth + 2);
    int y = baseY - barHeight;
    
    display.fillRect(x, y, barWidth, barHeight, SSD1306_WHITE);
  }
}

// ===== FUNGSI: UPDATE HISTORY =====
void updateHistory() {
  // Shift array
  for (int i = 9; i > 0; i--) {
    suhuHistory[i] = suhuHistory[i - 1];
  }
  suhuHistory[0] = suhu;
}

// ===== FUNGSI: STATUS LED =====
void setStatusLED(int status) {
  digitalWrite(LED_GREEN, status == 0 ? HIGH : LOW);
  digitalWrite(LED_YELLOW, status == 1 ? HIGH : LOW);
  digitalWrite(LED_RED, status == 2 ? HIGH : LOW);
}

// ===== FUNGSI: KIRIM KE BLYNK =====
void kirimKeBlynk() {
  Blynk.virtualWrite(V0, suhu);
  Blynk.virtualWrite(V1, kelembapan);
  Blynk.virtualWrite(V2, cahaya);
  Blynk.virtualWrite(V3, gerakan ? 1 : 0);
  Blynk.virtualWrite(V4, acStatus ? 1 : 0);
  Blynk.virtualWrite(V5, lampuStatus ? 1 : 0);
  Blynk.virtualWrite(V6, modeAuto ? 1 : 0);
  
  String status = "Normal";
  if (suhu > SUHU_BAHAYA) status = "⚠️ ALARM!";
  else if (suhu > SUHU_TINGGI) status = "Warning";
  Blynk.virtualWrite(V7, status);
  Blynk.virtualWrite(V8, currentPage);
}

// ===== BLYNK: KONTROL AC (V4) =====
BLYNK_WRITE(V4) {
  int value = param.asInt();
  acStatus = (value == 1);
  digitalWrite(RELAY_AC, acStatus);
  Serial.printf("[Blynk] AC %s\n", acStatus ? "ON" : "OFF");
}

// ===== BLYNK: KONTROL LAMPU (V5) =====
BLYNK_WRITE(V5) {
  int value = param.asInt();
  lampuStatus = (value == 1);
  digitalWrite(RELAY_LAMPU, lampuStatus);
  Serial.printf("[Blynk] Lampu %s\n", lampuStatus ? "ON" : "OFF");
}

// ===== BLYNK: MODE AUTO (V6) =====
BLYNK_WRITE(V6) {
  int value = param.asInt();
  modeAuto = (value == 1);
  Serial.printf("[Blynk] Mode %s\n", modeAuto ? "AUTO" : "MANUAL");
}

// ===== BLYNK: PAGE SELECTOR (V8) =====
BLYNK_WRITE(V8) {
  int value = param.asInt();
  if (value >= 1 && value <= 3) {
    currentPage = value;
    Serial.printf("[Blynk] Page %d\n", currentPage);
  }
}

// ===== BLYNK: CONNECTED =====
BLYNK_CONNECTED() {
  Serial.println("\n✓ BLYNK CONNECTED!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  
  // Sync
  Blynk.syncVirtual(V4, V5, V6, V8);
  
  // OLED update
  display.clearDisplay();
  display.setCursor(0, 20);
  display.setTextSize(2);
  display.println("BLYNK");
  display.println("  OK!");
  display.display();
  delay(1000);
}

