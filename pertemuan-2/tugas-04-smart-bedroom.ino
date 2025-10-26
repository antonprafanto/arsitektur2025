/*
  TUGAS 4: SMART BEDROOM - Kamar Tidur Cerdas
  
  Fitur Otomatis:
  - Lampu (LED) menyala saat ada orang + gelap
  - AC (LED biru) nyala saat panas + ada orang
  - Night mode: Semua redup saat malam
  - Alarm: Buzzer jika suhu ekstrem
  
  Komponen: ESP32, DHT11, LDR+10K, PIR, 2xLED, buzzer
  
  Mode: AUTO (sensor) vs MANUAL (button override)
*/

#include <DHT.h>

#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int pinLDR = 34;
const int pinPIR = 13;
const int pinLampu = 2;
const int pinAC = 4;
const int pinBuzzer = 12;
const int pinButton = 16;  // Mode switch

bool modeManual = false;
bool lampuManual = false;

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(pinPIR, INPUT);
  pinMode(pinLampu, OUTPUT);
  pinMode(pinAC, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);
  
  Serial.println("=== SMART BEDROOM ===");
  Serial.println("Mode: AUTO (tekan button untuk MANUAL)");
  Serial.println("Kalibrasi PIR 30 detik...\n");
  
  for(int i=30; i>0; i--) { delay(1000); }
  Serial.println("Siap!\n");
}

void loop() {
  // Cek button mode
  static bool btnSebelumnya = false;
  bool btnSekarang = (digitalRead(pinButton) == LOW);
  if (btnSekarang && !btnSebelumnya) {
    modeManual = !modeManual;
    Serial.print("Mode: ");
    Serial.println(modeManual ? "MANUAL" : "AUTO");
    delay(50);
  }
  btnSebelumnya = btnSekarang;
  
  // Baca sensor
  float suhu = dht.readTemperature();
  float rh = dht.readHumidity();
  int ldr = analogRead(pinLDR);
  bool orang = (digitalRead(pinPIR) == HIGH);
  
  if (isnan(suhu) || isnan(rh)) {
    Serial.println("DHT Error!");
    delay(2000);
    return;
  }
  
  if (!modeManual) {
    // Mode AUTO
    bool gelap = (ldr > 2500);
    digitalWrite(pinLampu, (gelap && orang) ? HIGH : LOW);
    digitalWrite(pinAC, (suhu > 28 && orang) ? HIGH : LOW);
  } else {
    // Mode MANUAL (contoh sederhana: toggle lampu)
    if (btnSekarang) {
      lampuManual = !lampuManual;
      digitalWrite(pinLampu, lampuManual ? HIGH : LOW);
    }
  }
  
  // Alarm suhu ekstrem
  if (suhu > 35) {
    digitalWrite(pinBuzzer, HIGH);
    delay(200);
    digitalWrite(pinBuzzer, LOW);
  }
  
  // Display
  Serial.printf("T:%.1f°C RH:%.0f%% LDR:%d Orang:%s Mode:%s\n",
    suhu, rh, ldr, orang?"ADA":"NO", modeManual?"MANUAL":"AUTO");
  
  delay(2000);
}

/*
  FITUR LANJUTAN:
  - Schedule: Lampu auto dim jam 22:00-06:00
  - Wake-up light: Lampu perlahan terang saat alarm pagi
  - Sleep tracking: Monitor gerakan malam hari
  - Voice control: Integrasi Alexa/Google Home
  - Curtain control: Buka/tutup tirai otomatis
*/
