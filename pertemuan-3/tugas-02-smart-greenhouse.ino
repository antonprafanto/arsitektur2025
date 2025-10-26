/*
  TUGAS 2 PERTEMUAN 3: SMART GREENHOUSE
  
  Sistem kontrol greenhouse otomatis:
  - Monitor suhu, kelembapan, cahaya
  - Relay 1 (pompa air): nyala jika kelembapan < 40%
  - Relay 2 (grow light): nyala jika cahaya kurang
  - OLED display semua parameter
  
  Komponen: ESP32, DHT11, LDR+10K, Relay 2CH, OLED
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int pinLDR = 34;
const int pinRelayPompa = 25;
const int pinRelayLampu = 26;

const int THRESHOLD_RH = 40;  // Pompa nyala jika < 40%
const int THRESHOLD_CAHAYA = 2000;  // Lampu nyala jika gelap

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(pinRelayPompa, OUTPUT);
  pinMode(pinRelayLampu, OUTPUT);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED error!");
    while(1);
  }
  
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  
  Serial.println("=== SMART GREENHOUSE ===");
  Serial.println("Pompa: RH < 40%");
  Serial.println("Lampu: Cahaya kurang\n");
  
  delay(2000);
}

void loop() {
  float suhu = dht.readTemperature();
  float rh = dht.readHumidity();
  int cahaya = analogRead(pinLDR);
  
  if (isnan(suhu) || isnan(rh)) {
    Serial.println("DHT Error!");
    delay(2000);
    return;
  }
  
  // Kontrol pompa (misting/irrigation)
  bool pompaOn = (rh < THRESHOLD_RH);
  digitalWrite(pinRelayPompa, pompaOn ? HIGH : LOW);
  
  // Kontrol grow light
  bool lampuOn = (cahaya > THRESHOLD_CAHAYA);  // Gelap
  digitalWrite(pinRelayLampu, lampuOn ? HIGH : LOW);
  
  // Display di OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("== GREENHOUSE ==");
  display.println();
  display.print("Suhu   : ");
  display.print(suhu,1);
  display.println(" C");
  display.print("RH     : ");
  display.print(rh,1);
  display.println(" %");
  display.print("Cahaya : ");
  display.println(cahaya);
  display.println();
  display.print("Pompa  : ");
  display.println(pompaOn ? "ON" : "OFF");
  display.print("Lampu  : ");
  display.println(lampuOn ? "ON" : "OFF");
  display.display();
  
  // Serial log
  Serial.printf("T:%.1f RH:%.1f C:%d | Pompa:%s Lampu:%s\n",
    suhu, rh, cahaya, pompaOn?"ON":"OFF", lampuOn?"ON":"OFF");
  
  delay(3000);
}

/*
  APLIKASI LANJUTAN:
  - CO2 injection untuk fotosintesis optimal
  - pH & EC monitoring (nutrient solution)
  - Automated ventilation (window/fan)
  - Schedule berbeda untuk fase vegetatif vs flowering
  - Data analytics untuk yield optimization
*/
