# STUDI KASUS 3: SMART HOME DASHBOARD dengan OLED + Blynk

**Mata Kuliah**: Bangunan Cerdas  
**Topik**: Sistem Monitoring Rumah Pintar dengan Display Lokal  
**Level**: Advanced

---

## 📖 UNTUK PEMULA ABSOLUT

**⚠️ PENTING: Ini Level ADVANCED!**

Studi Kasus 3 ini **lebih sulit** dari SC1 dan SC2 karena:
- Ada OLED display dengan menu 3 halaman
- Ada button navigation (Next & Select)
- Kode lebih kompleks (array, state machine)

**Rekomendasi:**
- ✅ **Mahasiswa baru:** Mulai dari SC1 → SC2 dulu
- ✅ **Sudah paham SC1-SC2:** Lanjut ke SC3
- ✅ **Tertarik UI/UX:** SC3 cocok untuk Anda!

### Kenapa SC3 Menarik?

**Untuk mahasiswa Arsitektur:**
- OLED seperti **panel kontrol** di dinding gedung
- Menu navigation seperti **touchscreen** di smart home
- Dual control (lokal + remote) = konsep **hybrid system**

### Yang Perlu Dipahami:

**1. OLED Display**
- Seperti layar HP kecil (hitam-putih)
- Bisa tampilkan teks, angka, grafik
- Ukuran 0.96 inch (kecil tapi cukup untuk dashboard)

**2. Button Navigation**
- Button NEXT = Pindah halaman (1→2→3→1)
- Button SELECT = Pilih/action
- Seperti remote TV (channel & OK button)

**3. Multi-Page Menu**
- Page 1: Home (data sensor)
- Page 2: Graph (bar chart suhu)
- Page 3: Control (toggle AC/Lampu)

**Tips:**
- Jangan stress jika tidak langsung paham semua kode
- Fokus lihat **hasilnya** dulu (OLED bekerja)
- Pahami **logika menu** (navigasi page)
- Detail coding bisa sambil jalan

**Alternatif Lebih Mudah:**
Jika SC3 terlalu sulit, tetap di SC1-SC2 untuk proyek akhir. SC3 opsional! 😊

---

## 🎯 TUJUAN PEMBELAJARAN

Setelah mempelajari studi kasus ini, mahasiswa dapat:
1. Mengintegrasikan OLED Display 0.96" untuk UI lokal
2. Membuat dual interface (OLED lokal + Blynk cloud)
3. Implementasi button control untuk navigasi menu OLED
4. Membuat dashboard multi-halaman dengan grafik
5. Sistem monitoring & kontrol hybrid (lokal + remote)

---

## 🏠 SKENARIO: SMART HOME CONTROL PANEL

**Konteks:**  
Merancang panel kontrol smart home dengan display OLED lokal + aplikasi Blynk untuk monitoring jarak jauh.

### Input (Sensor):
1. **DHT11** → Suhu & kelembapan ruangan
2. **PIR** → Deteksi kehadiran
3. **LDR** → Intensitas cahaya
4. **Button 1** → Navigasi menu OLED (Next)
5. **Button 2** → Select/Action

### Output (Aktuator):
1. **OLED 0.96"** → Display dashboard lokal (3 halaman)
2. **Relay 1** → AC/Heater
3. **Relay 2** → Lampu Ruangan
4. **Buzzer** → Notifikasi alarm
5. **3x LED** → Status indikator (Hijau=OK, Kuning=Warning, Merah=Alarm)

### Fitur Unik:
- **OLED Menu System** dengan 3 halaman:
  - Page 1: Home (suhu, kelembapan, status)
  - Page 2: Graph (bar chart suhu)
  - Page 3: Control (manual ON/OFF relay)
- **Dual Control**: Lokal (button di OLED) + Remote (Blynk app)
- **Smart Notifications**: OLED + Blynk + LED indikator
- **Auto Mode**: Relay otomatis berdasarkan sensor

---

## 📦 KOMPONEN (Sesuai Inventory)

### Hardware:
- 1x ESP32
- 1x OLED Display 0.96" I2C (SSD1306)
- 1x DHT11
- 1x PIR Sensor
- 1x LDR + Resistor 10kΩ
- 1x Relay Module 2 Channel
- 1x Buzzer Aktif
- 3x LED (Hijau, Kuning, Merah)
- 2x Push Button (Menu navigation)
- Resistor 220Ω, Breadboard, Kabel jumper

### Software:
- Arduino IDE
- Library: WiFi, Blynk, DHT, Adafruit SSD1306, Adafruit GFX

---

## 🔌 WIRING DIAGRAM

```
ESP32 Connections:

OLED Display (I2C):
├─ VCC → 3.3V
├─ GND → GND
├─ SDA → GPIO21
└─ SCL → GPIO22

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

Button 1 (Next):
├─ Pin1 → GPIO14
└─ Pin2 → GND (pull-up internal)

Button 2 (Select):
├─ Pin1 → GPIO12
└─ Pin2 → GND (pull-up internal)

Relay 2 Channel:
├─ VCC → 5V
├─ GND → GND
├─ IN1 → GPIO25 (AC/Heater)
└─ IN2 → GPIO26 (Lampu)

LED Indikator:
├─ LED Hijau (OK) → GPIO2 + R220Ω → GND
├─ LED Kuning (Warn) → GPIO4 + R220Ω → GND
└─ LED Merah (Alarm) → GPIO5 + R220Ω → GND

Buzzer:
├─ (+) → GPIO33
└─ (-) → GND
```

---

## 📱 SETUP BLYNK

### Template: "Smart Home Dashboard"

### Datastreams:

| Pin | Name | Type | Min | Max | Units |
|-----|------|------|-----|-----|-------|
| V0 | Suhu | Double | 0 | 50 | °C |
| V1 | Kelembapan | Double | 0 | 100 | % |
| V2 | Cahaya | Integer | 0 | 4095 | - |
| V3 | PIR Status | Integer | 0 | 1 | - |
| V4 | Relay AC | Integer | 0 | 1 | - |
| V5 | Relay Lampu | Integer | 0 | 1 | - |
| V6 | Mode Auto | Integer | 0 | 1 | - |
| V7 | Status Sistem | String | - | - | - |
| V8 | OLED Page | Integer | 1 | 3 | - |

### Widgets:

1. **SuperChart** → V0, V1 (Grafik suhu & RH)
2. **Gauge** → V0 (Suhu)
3. **Value Display** → V1, V2, V3
4. **Switch** → V4 (Kontrol AC)
5. **Switch** → V5 (Kontrol Lampu)
6. **Switch** → V6 (Mode Auto ON/OFF)
7. **Label** → V7 (Status)
8. **Slider** → V8 (Remote page selector)

---

## 💻 FITUR KODE

### 1. OLED Menu System

**Page 1 - Home:**
```
┌─────────────────┐
│ SMART HOME      │
│ Temp: 28.5°C    │
│ RH:   65%       │
│ Light: GELAP    │
│ PIR:   ADA      │
│ [1/3]           │
└─────────────────┘
```

**Page 2 - Graph:**
```
┌─────────────────┐
│ SUHU 24H        │
│     █           │
│   █ █ █         │
│ █ █ █ █ █       │
│ ───────────     │
│ Bar Chart       │
└─────────────────┘
```

**Page 3 - Control:**
```
┌─────────────────┐
│ KONTROL MANUAL  │
│ >AC:    ON      │
│  Lampu: OFF     │
│  Mode:  AUTO    │
│ Tekan SELECT    │
│ [3/3]           │
└─────────────────┘
```

### 2. Button Controls

- **Button NEXT**: Pindah halaman (1→2→3→1)
- **Button SELECT**: 
  - Page 1: Toggle mode Auto/Manual
  - Page 2: Refresh graph
  - Page 3: Toggle selected item

### 3. Auto Logic

- **AC**: ON jika suhu > 28°C (mode auto)
- **Lampu**: ON jika gelap (LDR > 2500) DAN ada orang (PIR)
- **Buzzer**: Alarm jika suhu > 35°C
- **LED**:
  - Hijau: Semua normal
  - Kuning: Warning (suhu 30-35°C)
  - Merah: Alarm (suhu > 35°C)

---

## 🧪 TESTING

### Test 1: OLED Navigation
1. Tekan button NEXT
2. **Expected**: Pindah Page 1 → 2 → 3 → 1
3. Lihat display update

### Test 2: OLED Control
1. Navigasi ke Page 3
2. Tekan SELECT
3. **Expected**: Toggle AC ON/OFF di OLED

### Test 3: Dual Interface
1. Nyalakan AC dari Blynk app
2. **Expected**: OLED Page 3 update status AC = ON
3. Matikan dari OLED
4. **Expected**: Blynk app update V4 = 0

### Test 4: Auto Mode
1. Set mode AUTO (Page 1 → SELECT)
2. Hangatkan DHT11 > 28°C
3. **Expected**: 
   - AC ON otomatis
   - OLED tampil "AUTO: AC ON"
   - LED Kuning nyala
   - Blynk update

### Test 5: Notifications
1. Hangatkan DHT11 > 35°C
2. **Expected**:
   - Buzzer bunyi
   - LED Merah menyala
   - OLED tampil "ALARM!"
   - Blynk notifikasi

---

## 🎨 KEUNGGULAN STUDI KASUS INI

### Dibanding Studi Kasus 1 & 2:

**Studi Kasus 1 (Smart Office):**
- ✅ Basic sensor integration
- ❌ Tidak ada UI lokal

**Studi Kasus 2 (Smart Parking):**
- ✅ LED RGB visual feedback
- ❌ Tidak ada display informasi detail

**Studi Kasus 3 (Smart Home Dashboard):** ⭐
- ✅ **OLED Display** dengan menu interaktif
- ✅ **Dual control** (lokal + remote)
- ✅ **Grafik real-time** di OLED
- ✅ **Button navigation** UX
- ✅ **Multi-mode** (Auto/Manual switchable)
- ✅ **Triple feedback** (OLED + LED + Blynk)

---

## 🏢 APLIKASI REAL-WORLD

### 1. Smart Hotel Room
- OLED panel di dinding
- Guest bisa kontrol lokal atau via app
- Display suhu, waktu, status AC

### 2. Smart Office Workstation
- Personal desk control panel
- Monitor kondisi kerja optimal
- Quick access controls

### 3. Smart Apartemen
- Main dashboard di ruang tamu
- Family members bisa kontrol lokal
- Owner monitoring via app saat traveling

---

## 📊 PERBANDINGAN 3 STUDI KASUS

| Aspek | SC1: Office | SC2: Parking | SC3: Dashboard |
|-------|-------------|--------------|----------------|
| **Sensor** | 3 | 4 | 5 (3 sensor + 2 button) |
| **Output** | 3 | 4 | 5 |
| **Display** | ❌ | LED RGB | ✅ OLED + LED |
| **UI Lokal** | ❌ | Basic | ✅ Advanced |
| **Interaktif** | ❌ | ❌ | ✅ Button Menu |
| **Grafik** | ❌ | ❌ | ✅ Bar Chart |
| **Dual Control** | Remote only | Remote only | ✅ Local + Remote |
| **Kompleksitas** | Basic | Intermediate | **Advanced** |

---

## 🎓 PENGEMBANGAN LANJUTAN

### Level 1:
- [ ] Tambah page 4: Scheduler (timer AC/Lampu)
- [ ] Tambah page 5: Settings (threshold adjustment)
- [ ] RTC module untuk clock display

### Level 2:
- [ ] SD Card untuk data logging
- [ ] Temperature trend prediction
- [ ] Energy consumption calculator

### Level 3:
- [ ] Touchscreen OLED
- [ ] Voice control (Google Assistant via Blynk)
- [ ] AI-powered automation

---

**Dibuat untuk:** Mata Kuliah Bangunan Cerdas  
**Instruktur:** Anton Prafanto, S.Kom., M.T.  
**Target:** Mahasiswa Arsitektur  
**Versi:** 1.0 - 2025
