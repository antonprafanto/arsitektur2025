# STUDI KASUS 5: SMART SECURITY SYSTEM dengan Blynk IoT

**Mata Kuliah**: Bangunan Cerdas  
**Topik**: Sistem Keamanan Rumah Pintar Multi-Zone  
**Level**: Intermediate

---

## 📖 UNTUK PEMULA ABSOLUT

**Studi Kasus 5: Smart Security** - Keamanan rumah modern! 🔒

**Sebelum mulai:** Baca `GLOSSARY-PEMULA.md` untuk istilah dasar.

### Kenapa SC5 Menarik?

**Untuk mahasiswa Arsitektur:**
- Security = critical aspect dalam desain bangunan
- Multi-zone monitoring (pintu, jendela, ruangan)
- Visual feedback (LED pattern blinking)
- Dual buzzer (alarm keras + notifikasi lembut)

### Yang Unik di SC5:

**SC5 (Smart Security):** ⭐ **ANDA DI SINI**
- **3 Push Button** sebagai door/window sensor (simulasi)
- **Active + Passive Buzzer** (2 jenis alarm!)
- **LED Blinking Pattern** (tidak hanya ON/OFF)
- **Multi-Zone** (Pintu Depan, Jendela, Ruang Dalam)
- **Arm/Disarm** system

### Analogi Security System Pro:

Seperti sistem alarm gedung/rumah:
- **Zone Sensors** = Button simulasi (pintu/jendela terbuka)
- **Active Buzzer** = Siren keras (intrusi!)
- **Passive Buzzer** = Beep peringatan (pintu terbuka mode armed)
- **LED Blinking** = Indikator status (armed/disarmed)
- **Blynk** = Push notification ke HP owner

**Anda akan belajar:**
1. Security system logic (armed/disarmed/triggered)
2. Multi-zone monitoring
3. LED blinking patterns (non-blocking)
4. Dual buzzer untuk alert level berbeda

---

## 🎯 TUJUAN PEMBELAJARAN

Setelah mempelajari studi kasus ini, mahasiswa dapat:
1. Membuat security system dengan multi-zone detection
2. Implementasi arm/disarm logic dengan password/button
3. Menggunakan dual buzzer (active + passive) untuk alert berbeda
4. LED blinking patterns tanpa blocking delay
5. Push notification Blynk untuk intrusion alert

---

## 🔒 SKENARIO: HOME SECURITY SYSTEM

**Konteks:**  
Merancang sistem keamanan rumah dengan monitoring 3 zone + kontrol via smartphone.

### Input (Sensor):
1. **DHT11** → Temperature monitoring (deteksi kebakaran jika suhu > 50°C)
2. **PIR** → Motion detector di ruang dalam
3. **LDR** → Deteksi cahaya (auto arm saat gelap/malam)
4. **3x Push Button** → Zone sensors (simulasi):
   - Button 1: Pintu Depan (Main Door)
   - Button 2: Jendela (Window)
   - Button 3: Pintu Belakang (Back Door)
5. **1x Push Button** → ARM/DISARM toggle

### Output (Aktuator):
1. **Relay 1** → Lampu luar (auto ON saat intrusion)
2. **Relay 2** → Electric lock (auto lock saat armed)
3. **Active Buzzer** → Siren keras (intrusion!)
4. **Passive Buzzer** → Beep peringatan (door opened saat armed)
5. **5x LED**:
   - LED Hijau: Status DISARMED (aman)
   - LED Merah: Status ARMED (aktif)
   - LED Kuning 1: Zone 1 (Main Door) triggered
   - LED Kuning 2: Zone 2 (Window) triggered
   - LED Kuning 3: Zone 3 (Back Door) triggered

### Logika Sistem:

**Mode DISARMED (Default):**
```
- LED Hijau nyala steady
- Semua buzzer mati
- Zone sensors tidak trigger alarm (hanya log)
- Electric lock terbuka
```

**Mode ARMED:**
```
- LED Merah blinking (1 detik ON, 1 detik OFF)
- Electric lock tertutup (Relay 2 ON)
- Jika zone sensor  triggered:
  → Passive buzzer beep 3x (peringatan)
  → Delay 10 detik (grace period untuk disarm)
  → Jika belum disarm: TRIGGERED mode!
```

**Mode TRIGGERED (Intrusion!):**
```
- Active buzzer siren ON (keras!)
- LED Merah blinking cepat (0.2s ON, 0.2s OFF)
- Lampu luar ON (Relay 1)
- LED zone yang triggered nyala
- Blynk notification: "INTRUSION DETECTED! Zone: [X]"
- Auto disarm setelah 30 detik atau manual via Blynk
```

**Auto ARM (Fitur Bonus):**
```
- Jika LDR detect gelap (malam) DAN tidak ada gerakan 5 menit
- Otomatis ARM system
- Blynk notification: "System AUTO ARMED"
```

---

## 📦 KOMPONEN (Sesuai Inventory)

### Hardware:
- 1x ESP32
- 1x DHT11
- 1x PIR Sensor
- 1x LDR + Resistor 10kΩ
- 1x Relay Module 2 Channel
- 1x **Active Buzzer** (siren keras)
- 1x **Passive Buzzer** (beep peringatan)
- **5x LED** (1 Hijau, 1 Merah, 3 Kuning)
- **4x Push Button** (3 zone + 1 arm/disarm)
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

4x Push Buttons (pull-up internal):
├─ Button ARM/DISARM → GPIO14 + GND
├─ Zone 1 (Main Door) → GPIO12 + GND
├─ Zone 2 (Window) → GPIO13 + GND
└─ Zone 3 (Back Door) → GPIO32 + GND

Relay 2 Channel:
├─ VCC → 5V
├─ GND → GND
├─ IN1 → GPIO25 (Lampu Luar)
└─ IN2 → GPIO26 (Electric Lock)

Buzzer:
├─ Active Buzzer (+) → GPIO33 + GND
└─ Passive Buzzer (+) → GPIO23 + GND

LED Status:
├─ LED Hijau (DISARMED) → GPIO2 + R220Ω → GND
├─ LED Merah (ARMED) → GPIO4 + R220Ω → GND
├─ LED Kuning 1 (Zone 1) → GPIO5 + R220Ω → GND
├─ LED Kuning 2 (Zone 2) → GPIO18 + R220Ω → GND
└─ LED Kuning 3 (Zone 3) → GPIO19 + R220Ω → GND
```

---

## 📱 SETUP BLYNK

### Template: "Smart Security"

### Datastreams:

| Pin | Name | Type | Min | Max | Units |
|-----|------|------|-----|-----|-------|
| V0 | System Status | Integer | 0 | 2 | - |
| V1 | Zone 1 Status | Integer | 0 | 1 | - |
| V2 | Zone 2 Status | Integer | 0 | 1 | - |
| V3 | Zone 3 Status | Integer | 0 | 1 | - |
| V4 | PIR Motion | Integer | 0 | 1 | - |
| V5 | Temperature | Double | 0 | 100 | °C |
| V6 | ARM/DISARM | Integer | 0 | 1 | - |
| V7 | Alert Message | String | - | - | - |

**Status Code:**
- 0 = DISARMED
- 1 = ARMED
- 2 = TRIGGERED

### Widgets:

1. **LED Indicator** → V0 (System Status: Hijau/Merah)
2. **LED Indicator** → V1, V2, V3 (Zones)
3. **LED Indicator** → V4 (Motion)
4. **Value Display** → V5 (Temperature)
5. **Switch** → V6 (ARM/DISARM button)
6. **Label** → V7 (Alert messages)
7. **Notification** → Auto trigger saat intrusion

---

## 💻 FITUR KODE

### 1. LED Blinking Non-Blocking

```cpp
// Blinking tanpa delay (pakai millis)
unsigned long lastBlink = 0;
bool ledState = false;

void blinkLED(int pin, int interval) {
  if (millis() - lastBlink >= interval) {
    lastBlink = millis();
    ledState = !ledState;
    digitalWrite(pin, ledState);
  }
}

// Slow blink: blinkLED(LED_RED, 1000);  // 1 detik
// Fast blink: blinkLED(LED_RED, 200);   // 0.2 detik
```

### 2. Multi-Zone Detection

```cpp
bool zoneTriggered[3] = {false};  // 3 zones

void checkZones() {
  for (int i = 0; i < 3; i++) {
    if (digitalRead(zonePins[i]) == LOW) {
      zoneTriggered[i] = true;
      Serial.printf("Zone %d TRIGGERED!\n", i+1);
      
      if (systemArmed) {
        handleIntrusion(i);
      }
    }
  }
}
```

### 3. State Machine (3 Status)

```cpp
enum SystemStatus { DISARMED, ARMED, TRIGGERED };
SystemStatus currentStatus = DISARMED;

void setStatus(SystemStatus newStatus) {
  currentStatus = newStatus;
  
  switch(currentStatus) {
    case DISARMED:
      digitalWrite(LED_GREEN, HIGH);
      digitalWrite(LED_RED, LOW);
      noTone(PASSIVE_BUZZER);
      digitalWrite(ACTIVE_BUZZER, LOW);
      break;
      
    case ARMED:
      digitalWrite(LED_GREEN, LOW);
      // LED_RED will blink
      break;
      
    case TRIGGERED:
      digitalWrite(ACTIVE_BUZZER, HIGH);  // Siren!
      digitalWrite(RELAY_LIGHT, HIGH);
      sendBlynkAlert();
      break;
  }
}
```

### 4. Dual Buzzer Usage

```cpp
// Passive buzzer: Beep peringatan
void warningBeep() {
  for (int i = 0; i < 3; i++) {
    tone(PASSIVE_BUZZER, 1000);  // 1kHz
    delay(100);
    noTone(PASSIVE_BUZZER);
    delay(100);
  }
}

// Active buzzer: Siren intrusion
void activateSiren() {
  digitalWrite(ACTIVE_BUZZER, HIGH);
}
```

---

## 🧪 TESTING

### Test 1: ARM/DISARM
1. Tekan button ARM/DISARM
2. **Expected:** LED Merah blinking, LED Hijau mati

### Test 2: Zone Trigger (Saat ARMED)
1. ARM system
2. Tekan Zone 1 button (Main Door)
3. **Expected:** 
   - Passive buzzer beep 3x
   - Delay 10 detik (grace period)
   - Active buzzer siren ON (jika tidak disarm)
   - LED Kuning 1 nyala

### Test 3: Auto ARM
1. Tutup LDR (simulasi malam)
2. Diamkan 5 menit tanpa gerakan PIR
3. **Expected:** System auto ARM, Blynk notification

### Test 4: Fire Detection
1. Panaskan DHT11 > 50°C (simulasi)
2. **Expected:** Active buzzer ON, Blynk alert "FIRE!"

---

## 🏢 APLIKASI REAL-WORLD

### 1. Rumah Tinggal
- Multi-zone monitoring (pintu, jendela)
- Auto arm saat malam
- Push notification ke HP owner

### 2. Kantor/Toko
- After-hours security
- Motion detection
- Fire alarm terintegrasi

### 3. Gudang/Warehouse
- Intrusion detection
- Temperature monitoring
- Remote monitoring 24/7

---

## 📊 PERBANDINGAN 5 STUDI KASUS

| Fitur | SC1 | SC2 | SC3 | SC4 | **SC5** |
|-------|-----|-----|-----|-----|---------|
| **Sensor** | 3 | 4 | 5 | 5 | **5** |
| **Buttons** | 0 | 1 | 2 | 5 | **4** |
| **Buzzer** | Active | Active | Active | Passive | **Both!** |
| **LED** | 3 | RGB | 3 | 3 | **5 zones** |
| **Kompleksitas** | Basic | Medium | Advanced | Medium | **Medium** |
| **Use Case** | Office | Parking | Home UI | Bedroom | **Security** |

---

**Dibuat untuk:** Mata Kuliah Bangunan Cerdas  
**Instruktur:** Anton Prafanto, S.Kom., M.T.  
**Target:** Mahasiswa Arsitektur  
**Versi:** 1.0 - 2025
