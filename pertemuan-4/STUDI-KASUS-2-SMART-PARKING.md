# STUDI KASUS 2: SMART PARKING dengan Blynk IoT

**Mata Kuliah**: Bangunan Cerdas  
**Topik**: Sistem Parkir Cerdas dengan IoT  
**Level**: Intermediate

---

## 📖 UNTUK PEMULA ABSOLUT

**Studi Kasus 2 lebih menarik!** Ada LED RGB (lampu warna-warni) 🌈

**Sebelum mulai:** Baca `GLOSSARY-PEMULA.md` dulu untuk pahami istilah dasar.

### Bedanya dengan Studi Kasus 1:

**SC1 (Smart Office):**
- Fokus: Otomasi AC & Lampu
- Visual: LED indikator sederhana

**SC2 (Smart Parking):** ⭐ **ANDA DI SINI**
- Fokus: Deteksi slot parkir
- Visual: **LED RGB** (Hijau=kosong, Merah=penuh)
- Plus: Button simulasi (mudah testing tanpa banyak sensor!)

### Analogi Parking:

Bayangkan sistem parkir mall:
- **PIR Sensor** = Sensor di tanah yang deteksi mobil
- **LED RGB** = Lampu di atas slot (hijau=kosong, merah=terisi)
- **Exhaust Fan** = Kipas untuk buang asap kendaraan
- **Buzzer** = Alarm jika terlalu panas (bahaya CO/karbon)

**Anda cukup:**
1. Rakit hardware sesuai wiring
2. Copy-paste kode
3. Ganti WiFi & Auth Token
4. Upload & lihat LED RGB berubah warna! 🎨

---

## 🎯 TUJUAN PEMBELAJARAN

Setelah mempelajari studi kasus ini, mahasiswa dapat:
1. Mengintegrasikan multiple sensors (2x PIR + DHT11 + LDR)  
2. Mengontrol LED RGB untuk indikator visual
3. Membuat sistem parkir otomatis dengan deteksi ketersediaan
4. Implementasi dashboard monitoring via Blynk
5. Membuat sistem ventilasi otomatis pada area parkir

---

## 🚗 SKENARIO: SMART PARKING BASEMENT

**Konteks:**  
Merancang sistem parkir basement cerdas untuk gedung perkantoran dengan fitur:

### Input (Sensor):
1. **PIR Sensor 1** → Deteksi mobil di Slot A
2. **PIR Sensor 2** (simulasi dengan button) → Deteksi Slot B
3. **DHT11** → Monitor suhu & kelembapan ruang parkir
4. **LDR** → Deteksi pencahayaan area parkir

### Output (Aktuator):
1. **LED RGB** → Indikator ketersediaan (Hijau=Kosong, Merah=Terisi)
2. **Relay 1** → Exhaust Fan (ventilasi otomatis)
3. **Relay 2** → Lampu Parkir (auto lighting)
4. **Buzzer** → Alarm suhu tinggi (bahaya CO)

### Logika Sistem:
- **LED RGB**: Hijau jika slot kosong, Merah jika terisi
- **Exhaust Fan**: ON jika suhu > 30°C (simulasi polusi CO)
- **Lampu**: ON jika gelap (LDR > 2500)
- **Buzzer**: WARNING jika suhu > 35°C

---

## 📦 KOMPONEN YANG DIBUTUHKAN

### Hardware (Sesuai Inventory):
- 1x ESP32 Development Board
- 1x Sensor DHT11
- 1x Sensor PIR
- 1x Sensor LDR + Resistor 10kΩ
- 1x LED RGB (atau 3x LED terpisah: R, G, B)
- 1x Relay Module 2 Channel
- 1x Buzzer Aktif
- 2x Push Button (simulasi PIR slot B & entri manual)
- 1x Breadboard 830 point
- Resistor 220Ω (untuk LED)
- Kabel jumper

### Software:
- Arduino IDE
- Library: WiFi, Blynk, DHT

---

## 🔌 WIRING DIAGRAM

```
ESP32 Connections:

DHT11:
├─ VCC  → 3.3V
├─ DATA → GPIO15
└─ GND  → GND

PIR Sensor (Slot A):
├─ VCC → 5V
├─ OUT → GPIO27
└─ GND → GND

Button (Simulasi Slot B):
├─ Pin 1 → GPIO14
├─ Pin 2 → GND
└─ Pull-up internal ESP32

LDR:
├─ Pin 1 → 3.3V
├─ Pin 2 → GPIO34 + R10kΩ → GND

LED RGB (Common Cathode):
├─ R → GPIO2 + R220Ω
├─ G → GPIO4 + R220Ω
├─ B → GPIO5 + R220Ω
└─ GND → GND

Relay 2 Channel:
├─ VCC → 5V
├─ GND → GND
├─ IN1 → GPIO25 (Exhaust Fan)
└─ IN2 → GPIO26 (Lampu Parkir)

Buzzer:
├─ (+) → GPIO33
└─ (-) → GND
```

**💡 PENJELASAN RGB UNTUK PEMULA:**

LED RGB = 3 LED dalam 1 komponen (Red, Green, Blue)

**Teori Warna Digital:**
```
setRGB(255, 0, 0)   = Merah penuh (Red MAX, Green 0, Blue 0)
setRGB(0, 255, 0)   = Hijau penuh (Green MAX)
setRGB(0, 0, 255)   = Biru penuh (Blue MAX)
setRGB(255, 255, 0) = Merah + Hijau = KUNING 🟡
setRGB(255, 0, 255) = Merah + Biru = UNGU 🟣
setRGB(0, 0, 0)     = Semua mati = HITAM ⚫
```

**Sistem Parkir Kita:**
- Hijau (0, 255, 0) = Slot KOSONG ✅
- Kuning (255, 255, 0) = 1 Slot TERISI ⚠️
- Merah (255, 0, 0) = PENUH ❌

Angka 0-255 = tingkat kecerahan (0=mati, 255=terang penuh)

---

## 📱 SETUP BLYNK CLOUD

### Template: "Smart Parking"

### Datastreams:

| Pin | Name | Type | Min | Max | Units |
|-----|------|------|-----|-----|-------|
| V0 | Slot A Status | Integer | 0 | 1 | - |
| V1 | Slot B Status | Integer | 0 | 1 | - |
| V2 | Total Terisi | Integer | 0 | 2 | slots |
| V3 | Suhu Parkir | Double | 0 | 50 | °C |
| V4 | Kelembapan | Double | 0 | 100 | % |
| V5 | Cahaya | Integer | 0 | 4095 | - |
| V6 | Exhaust Fan | Integer | 0 | 1 | - |
| V7 | Lampu | Integer | 0 | 1 | - |
| V8 | Status Sistem | String | - | - | - |

### Widgets:

1. **LED Indicator (V0)** - Slot A (Hijau=Kosong)
2. **LED Indicator (V1)** - Slot B
3. **Value Display (V2)** - Total Slot Terisi
4. **Gauge (V3)** - Suhu
5. **Value Display (V4)** - Kelembapan
6. **Chart (V3)** - Grafik suhu 6 jam
7. **Switch (V6)** - Kontrol Fan
8. **Switch (V7)** - Kontrol Lampu
9. **Label (V8)** - Status Sistem

---

## 💻 IMPLEMENTASI KODE

Lihat file: **kode-15-smart-parking-blynk.ino**

### Fitur:
- ✅ Multi-sensor parking detection
- ✅ LED RGB indicator real-time
- ✅ Exhaust fan otomatis
- ✅ Auto lighting system
- ✅ Temperature alarm (bahaya CO)
- ✅ Blynk dashboard monitoring
- ✅ Manual override via app

---

## 🧪 TESTING & VALIDASI

### Test 1: Parking Detection
1. Gerakkan tangan di PIR (simulasi mobil masuk Slot A)
2. **Expected:** LED RGB → Merah, Blynk V0 = 1
3. Diamkan 30 detik
4. **Expected:** PIR reset, LED → Hijau, V0 = 0

### Test 2: Multi-Slot
1. Trigger PIR (Slot A)
2. Tekan button (Slot B)
3. **Expected:** V2 (Total Terisi) = 2

### Test 3: Exhaust Fan
1. Pegang DHT11 (hangatkan)
2. Tunggu suhu > 30°C
3. **Expected:** Relay Fan ON

### Test 4: Auto Lighting
1. Tutup LDR (gelap)
2. **Expected:** Relay Lampu ON

### Test 5: Temperature Alarm
1. Hangatkan DHT11 > 35°C
2. **Expected:** Buzzer bunyi, notifikasi Blynk

---

## 🔧 TROUBLESHOOTING

### Problem: PIR selalu trigger

**Solusi:**
1. Kalibrasi 30-60 detik setelah power ON
2. Putar potensio sensitivity ke tengah
3. Putar time delay ke minimum

### Problem: Button tidak responsif

**Solusi:**
1. Cek pull-up internal: `pinMode(14, INPUT_PULLUP);`
2. Tambah debounce delay (50ms)
3. Cek wiring button

---

## 🏢 APLIKASI REAL-WORLD

### Building Management
- Basement parking monitoring
- Mall parking system
- Hotel/apartemen parking

### Smart City
- Public parking monitoring
- Park & ride system
- Traffic management

### Features yang Bisa Ditambah:
- [ ] RFID access control
- [ ] Payment integration
- [ ] License plate recognition (camera + AI)
- [ ] Mobile app reservation

---

## 📊 ANALISIS EFISIENSI

### Penghematan Energi

**Manual Lighting:**
- Lampu parkir nyala 24 jam
- Konsumsi: 200W × 24h = 4.8 kWh/hari

**Smart Lighting (LDR):**
- Nyala hanya saat gelap (~12 jam)
- Konsumsi: 200W × 12h = 2.4 kWh/hari
- **Hemat: 50%**

### Ventilasi Optimal

**Manual Fan:**
- ON terus = boros

**Smart Fan:**
- ON hanya saat suhu tinggi
- Hemat ~40% energi

---

## 🎓 PENGEMBANGAN LANJUTAN

### Level 1:
- [ ] Tambah OLED untuk display lokal
- [ ] Counter mobil masuk/keluar
- [ ] Timer auto-reset slot

### Level 2:
- [ ] Barrier gate integration (servo)
- [ ] Ticket dispenser
- [ ] Payment terminal

### Level 3:
- [ ] Computer vision (deteksi plat nomor)
- [ ] Firebase database (logging)
- [ ] Mobile app (Android/iOS)

---

**Dibuat untuk:** Mata Kuliah Bangunan Cerdas  
**Instruktur:** Anton Prafanto, S.Kom., M.T.  
**Target:** Mahasiswa Arsitektur  
**Versi:** 1.0 - 2025
