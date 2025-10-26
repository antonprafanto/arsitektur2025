/*
  TUGAS 2: SMART LIGHTING SYSTEM - Lampu Hemat Energi
  
  Logika: Lampu HANYA nyala jika GELAP + ADA ORANG
  Hemat energi: Jika tidak ada orang, lampu mati meskipun gelap
  
  Komponen: ESP32, LDR+10K, PIR, LED+220Ω
  Koneksi:
  - LDR: 3.3V-LDR-GPIO34-10K-GND
  - PIR: 5V-OUT(GPIO13)-GND
  - LED: GPIO2-LED-220Ω-GND
*/

#include <DHT.h>

const int pinLDR = 34;
const int pinPIR = 13;
const int pinLED = 2;
const int thresholdGelap = 2500;

void setup() {
  Serial.begin(115200);
  pinMode(pinPIR, INPUT);
  pinMode(pinLED, OUTPUT);
  
  Serial.println("=== SMART LIGHTING SYSTEM ===");
  Serial.println("Hemat Energi: Lampu hanya nyala saat GELAP + ADA ORANG");
  Serial.println();
  
  // Kalibrasi PIR
  Serial.println("Kalibrasi PIR 30 detik...");
  for(int i=30; i>0; i--) {
    Serial.print(i); Serial.println(" detik");
    delay(1000);
  }
  Serial.println("Sistem aktif!\n");
}

void loop() {
  int nilaiLDR = analogRead(pinLDR);
  bool adaOrang = (digitalRead(pinPIR) == HIGH);
  bool gelap = (nilaiLDR > thresholdGelap);
  
  // Logika: Nyala HANYA jika gelap DAN ada orang
  bool lampuSeharusnyaNyala = (gelap && adaOrang);
  
  digitalWrite(pinLED, lampuSeharusnyaNyala ? HIGH : LOW);
  
  // Display status
  Serial.print("Cahaya: ");
  Serial.print(gelap ? "GELAP " : "TERANG");
  Serial.print(" | Orang: ");
  Serial.print(adaOrang ? "ADA " : "TIDAK");
  Serial.print(" | Lampu: ");
  Serial.println(lampuSeharusnyaNyala ? "NYALA 💡" : "MATI 🌙");
  
  if (gelap && !adaOrang) {
    Serial.println("   ⚡ HEMAT ENERGI: Gelap tapi tidak ada orang");
  }
  
  delay(2000);
}

/*
  KONSEP HEMAT ENERGI:
  - Lampu konvensional: Nyala saat gelap (boros jika tidak ada orang)
  - Lampu smart: Nyala HANYA saat gelap + ada orang
  - Penghematan: 30-50% energi di area jarang dilalui
  
  APLIKASI:
  - Koridor/tangga: Nyala saat ada orang lewat
  - Toilet: Nyala saat ada yang masuk
  - Parkiran: Dimmer saat kosong, terang saat ada mobil
  - Ruang meeting: Mati otomatis jika kosong >10 menit
  
  PENGEMBANGAN:
  1. Tambah timer: Tetap nyala 30 detik setelah orang pergi
  2. Dimming: Redup saat tidak ada orang (bukan mati total)
  3. Override manual: Button untuk paksa nyala
*/
