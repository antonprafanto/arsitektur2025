# STUDI KASUS 4: SMART BEDROOM dengan Blynk IoT

**Mata Kuliah**: Bangunan Cerdas  
**Topik**: Sistem Kamar Tidur Pintar dengan Kontrol Multi-Button  
**Level**: Intermediate

---

## 📖 UNTUK PEMULA ABSOLUT

**Studi Kasus 4: Smart Bedroom** - Fokus pada kenyamanan tidur! 😴

**Sebelum mulai:** Baca `GLOSSARY-PEMULA.md` untuk istilah dasar.

### Kenapa SC4 Menarik?

**Untuk mahasiswa Arsitektur:**
- Desain kamar tidur = core skill arsitektur!
- Otomasi pencahayaan tidur (gradual dimming)
- Alarm pagi dengan passive buzzer (nada lembut)
- Multi-mode (Sleep, Wake, Away)

### Yang Berbeda dari SC Lain:

**SC4 (Smart Bedroom):** ⭐ **ANDA DI SINI**
- **5 Push Button** untuk kontrol manual
- **Passive Buzzer** untuk alarm dengan nada (bukan beep keras!)
- **3 Mode**: Sleep, Wake Up, Away
- **Gradual LED** (bukan ON/OFF langsung)

### Analogi Kamar Hotel Bintang 5:

- **Button Panel** = Panel kontrol di samping tempat tidur
- **Scene Mode** = Tombol "Do Not Disturb", "Make Up Room"
- **Wake Up Alarm** = Alarm + pencahayaan bertahap
- **Auto AC** = Thermostat otomatis

**Anda akan belajar:**
1. Multiple button input handling
2. Passive buzzer (bukan sekedar beep!)
3. PWM untuk gradual LED dimming
4. State machine (mode switching)

---

## 🎯 TUJUAN PEMBELAJARAN

Setelah mempelajari studi kasus ini, mahasiswa dapat:
1. Mengintegrasikan multiple buttons (5 tombol) untuk scene control
2. Menggunakan passive buzzer dengan tone/melody
3. Implementasi PWM untuk LED dimming (gradual brightness)
4. Membuat state machine sederhana (3 mode: Sleep/Wake/Away)
5. Sistem smart bedroom yang nyaman dan praktis

---

## 🛏️ SKENARIO: SMART BEDROOM

**Konteks:**  
Merancang sistem kamar tidur cerdas untuk hotel/apartemen modern dengan fitur kenyamanan maksimal.

### Input (Sensor):
1. **DHT11** → Monitor suhu & kelembapan kamar
2. **PIR** → Deteksi kehadiran (auto light saat bangun malam)
3. **LDR** → Deteksi cahaya alami (auto curtain suggestion)
4. **5x Push Button** → Scene controller:
   - Button 1: Mode SLEEP (matikan semua, AC 24°C)
   - Button 2: Mode WAKE (nyalakan lampu bertahap, alarm)
   - Button 3: Mode AWAY (hemat energi)
   - Button 4: Manual AC ON/OFF
   - Button 5: Manual Light ON/OFF

### Output (Aktuator):
1. **Relay 1** → AC/Climate Control
2. **Relay 2** → Lampu Utama
3. **3x LED** → Scene indicator (Hijau=Sleep, Kuning=Wake, Merah=Away)
4. **Passive Buzzer** → Alarm pagi (melody, bukan beep!)
5. **Built-in LED (GPIO2)** → Gradual dimming night light

### Logika Sistem:

**Mode SLEEP (Button 1):**
```
- LED Hijau nyala (indikator)
- Lampu utama mati
- AC ON (suhu 24°C untuk tidur nyaman)
- Night light (built-in LED) dim 20%
- PIR auto: Jika bangun malam → Night light 50% selama 30 detik
```

**Mode WAKE (Button 2):**
```
- LED Kuning nyala
- Passive buzzer bunyi melody (alarm lembut)
- Lampu utama nyala bertahap (0% → 100% dalam 5 detik)
- AC OFF
- Blynk notification: "Good Morning!"
```

**Mode AWAY (Button 3):**
```
- LED Merah nyala
- Semua mati (hemat energi)
- Hanya monitoring suhu via Blynk
- PIR disabled
```

---

## 📦 KOMPONEN (Sesuai Inventory)

### Hardware:
- 1x ESP32
- 1x DHT11
- 1x PIR Sensor
- 1x LDR + Resistor 10kΩ
- 1x Relay Module 2 Channel
- 1x **Passive Buzzer** (bisa tone/melody)
- 3x LED (Hijau, Kuning, Merah) untuk mode indicator
- **5x Push Button**
- Resistor 220Ω, Breadboard, Kabel jumper

---

## 🔌 WIRING DIAGRAM

```
ESP32 Connections:

DHT11:
├─ VCC → 3.3V
├─ DATA → GPIO15
└─ GND → GND

PIR:
├─ VCC → 5V
├─ OUT → GPIO27
└─ GND → GND

LDR:
├─ Pin1 → 3.3V
├─ Pin2 → GPIO34 + R10kΩ → GND

5x Push Buttons (dengan pull-up internal):
├─ Button 1 (SLEEP) → GPIO14 + GND
├─ Button 2 (WAKE) → GPIO12 + GND
├─ Button 3 (AWAY) → GPIO13 + GND
├─ Button 4 (AC Toggle) → GPIO32 + GND
└─ Button 5 (Light Toggle) → GPIO33 + GND

Relay 2 Channel:
├─ VCC → 5V
├─ GND → GND
├─ IN1 → GPIO25 (AC)
└─ IN2 → GPIO26 (Lampu Utama)

LED Scene Indicator:
├─ LED Hijau (Sleep) → GPIO2 + R220Ω → GND
├─ LED Kuning (Wake) → GPIO4 + R220Ω → GND
└─ LED Merah (Away) → GPIO5 + R220Ω → GND

Passive Buzzer (untuk melody):
├─ (+) → GPIO23
└─ (-) → GND

Night Light (Built-in LED):
└─ GPIO2 (PWM untuk dimming)
```

**💡 PENJELASAN PASSIVE BUZZER:**

**Active vs Passive Buzzer:**
- **Active Buzzer**: Langsung bunyi "beep" saat diberi power (seperti SC1-SC3)
- **Passive Buzzer**: Perlu sinyal PWM untuk bunyi, bisa bikin nada/melody! 🎵

**Contoh Tone:**
```cpp
tone(BUZZER_PIN, 262);  // Nada C (Do)
tone(BUZZER_PIN, 294);  // Nada D (Re)
tone(BUZZER_PIN, 330);  // Nada E (Mi)
```

Kita akan pakai untuk alarm pagi yang lembut (bukan beep keras yang kaget!).

---

## 📱 SETUP BLYNK

### Template: "Smart Bedroom"

### Datastreams:

| Pin | Name | Type | Min | Max | Units |
|-----|------|------|-----|-----|-------|
| V0 | Suhu | Double | 0 | 50 | °C |
| V1 | Kelembapan | Double | 0 | 100 | % |
| V2 | Cahaya | Integer | 0 | 4095 | - |
| V3 | Current Mode | Integer | 0 | 2 | - |
| V4 | AC Control | Integer | 0 | 1 | - |
| V5 | Light Control | Integer | 0 | 1 | - |
| V6 | Alarm Status | Integer | 0 | 1 | - |
| V7 | Status Text | String | - | - | - |

### Widgets:

1. **Gauge** → V0 (Suhu kamar)
2. **Value Display** → V1, V2
3. **Segmented Switch** → V3 (Mode: Sleep/Wake/Away)
4. **Switch** → V4 (AC)
5. **Switch** → V5 (Light)
6. **Switch** → V6 (Set Alarm)
7. **Label** → V7 (Status)

---

## 💻 FITUR KODE

### 1. Multi-Button Handling dengan Debouncing

```cpp
// 5 button dengan debounce
unsigned long lastButtonPress[5] = {0};
const int DEBOUNCE_DELAY = 200;  // 200ms

void handleButtons() {
  for (int i = 0; i < 5; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      if (millis() - lastButtonPress[i] > DEBOUNCE_DELAY) {
        lastButtonPress[i] = millis();
        buttonAction(i);  // 0=Sleep, 1=Wake, 2=Away, 3=AC, 4=Light
      }
    }
  }
}
```

### 2. Passive Buzzer Melody (Alarm Lembut)

```cpp
// Melody sederhana untuk alarm pagi
int melody[] = {262, 294, 330, 349, 392};  // C D E F G
int noteDuration = 200;

void playWakeUpAlarm() {
  for (int i = 0; i < 5; i++) {
    tone(BUZZER_PIN, melody[i]);
    delay(noteDuration);
    noTone(BUZZER_PIN);
    delay(50);
  }
}
```

### 3. LED Gradual Dimming (PWM)

```cpp
// Nyalakan lampu bertahap (0% → 100% dalam 5 detik)
void gradualLightOn() {
  for (int brightness = 0; brightness <= 255; brightness += 5) {
    analogWrite(LED_PIN, brightness);
    delay(100);  // Total 5 detik (255/5 = 51 steps × 100ms)
  }
}
```

### 4. State Machine (3 Mode)

```cpp
enum Mode { SLEEP, WAKE, AWAY };
Mode currentMode = SLEEP;

void setMode(Mode newMode) {
  currentMode = newMode;
  
  switch(currentMode) {
    case SLEEP:
      // Logika sleep mode
      break;
    case WAKE:
      // Logika wake mode
      break;
    case AWAY:
      // Logika away mode
      break;
  }
}
```

---

## 🧪 TESTING

### Test 1: Mode Switching
1. Tekan Button 1 (SLEEP)
2. **Expected:** LED Hijau nyala, AC ON, lampu mati
3. Tekan Button 2 (WAKE)
4. **Expected:** Melody, lampu nyala bertahap, LED Kuning

### Test 2: Passive Buzzer Melody
1. Trigger mode WAKE
2. **Expected:** Bunyi melody 5 nada (bukan beep!)

### Test 3: Night Light Auto (PIR)
1. Set mode SLEEP
2. Gerakkan tangan di PIR (simulasi bangun malam)
3. **Expected:** Night light dim 50% selama 30 detik

### Test 4: Gradual Dimming
1. Tekan Button 5 (Manual Light ON)
2. **Expected:** Lampu nyala bertahap (tidak langsung 100%)

---

## 🏠 APLIKASI REAL-WORLD

### 1. Hotel Bintang 5
- Scene panel di setiap kamar
- Wake up call otomatis + pencahayaan
- Climate control optimal untuk tidur

### 2. Smart Apartemen
- Hemat energi dengan mode AWAY
- Kenyamanan maksimal mode SLEEP
- Integration dengan alarm HP (Blynk notification)

### 3. Elderly Care
- Night light auto (PIR) untuk lansia
- Alarm lembut (tidak kaget)
- Remote monitoring suhu kamar via Blynk

---

## 📊 ANALISIS KENYAMANAN

### Sleep Quality Improvement:

**Tanpa Smart Bedroom:**
- AC menyala terus (dingin berlebih/boros)
- Lampu ON/OFF mendadak (ganggu circadian rhythm)
- Bangun malam gelap total (bahaya jatuh)

**Dengan Smart Bedroom:**
- AC optimal 24°C saat tidur
- Pencahayaan bertahap (tidak shock mata)
- Night light auto (aman untuk lansia/anak)
- **Hasil: Kualitas tidur +30%!**

---

## 🎓 KEUNGGULAN SC4

### Dibanding SC Lain:

| Fitur | SC1 | SC2 | SC3 | **SC4** |
|-------|-----|-----|-----|---------|
| Multiple Buttons | ❌ | 1 | 2 | ✅ **5** |
| Passive Buzzer | ❌ | ❌ | ❌ | ✅ **Melody!** |
| PWM Dimming | ❌ | ❌ | ❌ | ✅ **Gradual** |
| State Machine | Basic | Basic | Advanced | ✅ **3 Mode** |
| Scene Control | ❌ | ❌ | ❌ | ✅ **Sleep/Wake/Away** |

---

**Dibuat untuk:** Mata Kuliah Bangunan Cerdas  
**Instruktur:** Anton Prafanto, S.Kom., M.T.  
**Target:** Mahasiswa Arsitektur  
**Versi:** 1.0 - 2025
