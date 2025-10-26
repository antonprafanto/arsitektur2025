/*
  TUGAS 1 PERTEMUAN 3: SMART PARKING SYSTEM
  
  Fitur:
  - PIR deteksi mobil masuk/keluar
  - LED merah: parkir penuh (slot=0)
  - LED hijau: parkir tersedia
  - OLED tampil jumlah slot tersedia
  - Buzzer beep saat mobil masuk/keluar
  
  Komponen: ESP32, PIR, 2x LED, OLED, Buzzer
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int pinPIR = 13;
const int pinLEDMerah = 2;
const int pinLEDHijau = 4;
const int pinBuzzer = 12;
const int pinButtonMasuk = 15;
const int pinButtonKeluar = 16;

const int MAX_SLOT = 10;
int slotTersedia = MAX_SLOT;

void setup() {
  Serial.begin(115200);
  pinMode(pinPIR, INPUT);
  pinMode(pinLEDMerah, OUTPUT);
  pinMode(pinLEDHijau, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinButtonMasuk, INPUT_PULLUP);
  pinMode(pinButtonKeluar, INPUT_PULLUP);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED gagal!");
    while(1);
  }
  
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  updateDisplay();
  
  Serial.println("=== SMART PARKING ===");
  Serial.println("Button Masuk: simulasi mobil masuk");
  Serial.println("Button Keluar: simulasi mobil keluar\n");
}

void loop() {
  static bool btnMasukSebelumnya = false;
  static bool btnKeluarSebelumnya = false;
  
  bool btnMasuk = (digitalRead(pinButtonMasuk) == LOW);
  bool btnKeluar = (digitalRead(pinButtonKeluar) == LOW);
  
  // Mobil masuk
  if (btnMasuk && !btnMasukSebelumnya && slotTersedia > 0) {
    slotTersedia--;
    Serial.println("🚗 Mobil masuk");
    beep();
    updateDisplay();
    delay(50);
  }
  
  // Mobil keluar
  if (btnKeluar && !btnKeluarSebelumnya && slotTersedia < MAX_SLOT) {
    slotTersedia++;
    Serial.println("🚗 Mobil keluar");
    beep();
    updateDisplay();
    delay(50);
  }
  
  btnMasukSebelumnya = btnMasuk;
  btnKeluarSebelumnya = btnKeluar;
  
  // LED indicator
  if (slotTersedia == 0) {
    digitalWrite(pinLEDMerah, HIGH);
    digitalWrite(pinLEDHijau, LOW);
  } else {
    digitalWrite(pinLEDMerah, LOW);
    digitalWrite(pinLEDHijau, HIGH);
  }
  
  delay(10);
}

void beep() {
  digitalWrite(pinBuzzer, HIGH);
  delay(100);
  digitalWrite(pinBuzzer, LOW);
}

void updateDisplay() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(10, 5);
  display.println("PARKING");
  
  display.setTextSize(3);
  display.setCursor(30, 30);
  display.println(slotTersedia);
  
  display.setTextSize(1);
  display.setCursor(15, 55);
  display.print("Available Slots");
  
  display.display();
}

/*
  PENGEMBANGAN:
  - Sensor ultrasonik untuk deteksi per slot
  - ANPR (Automatic Number Plate Recognition)
  - Payment integration (RFID/QR)
  - Cloud monitoring & booking
  - EV charging station integration
*/
