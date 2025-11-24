# STUDI KASUS LENGKAP: SMART BUILDING dengan 3 Sensor + 3 Output + Blynk

**Mata Kuliah**: Bangunan Cerdas  
**Topik**: Integrasi IoT dengan Platform Cloud  
**Level**: Intermediate

---

## 📖 UNTUK PEMULA ABSOLUT

**Belum pernah coding? Tidak masalah!** 🎉

Sebelum mulai, **WAJIB baca** file `GLOSSARY-PEMULA.md` terlebih dahulu.
Glossary menjelaskan istilah dasar coding dengan **analogi kehidupan sehari-hari**.

### Yang Perlu Anda Tahu:

**1. Program = Resep Masakan**
Program adalah kumpulan instruksi step-by-step seperti resep masakan:
- ESP32 = Chef (yang masak)
- Sensor = Bahan masakan
- Program = Resep
- Hasil = Sistem smart office yang jalan!

**2. Anda TIDAK Perlu Hafal Kode**
Di studi kasus ini, Anda cukup:
- ✅ Copy-paste kode yang sudah disediakan
- ✅ Ganti WiFi name & password
- ✅ Ganti Auth Token dari Blynk
- ✅ Upload ke ESP32
- ✅ Lihat hasilnya bekerja!

**3. Fokus pada Logika, Bukan Syntax**
Yang penting pahami LOGIKA sederhana:
```
JIKA suhu > 28°C → Nyalakan AC
JIKA gelap + ada orang → Nyalakan lampu
JIKA suhu > 32°C → Bunyi alarm
```

Detail syntax (`if`, `&&`, `digitalWrite`) bisa dipelajari sambil jalan.

**4. Gunakan Analogi Arsitektur**
- **ESP32** = BMS (Building Management System)
- **Sensor** = Mata/telinga bangunan
- **Relay** = Kontaktor di panel listrik
- **Blynk** = SCADA monitoring system

**5. Jangan Takut Error!**
Error itu **normal** dan bagian dari belajar.
Setiap error punya solusi (lihat bagian TROUBLESHOOTING & ERROR UMUM di bawah).

---

## 🎯 TUJUAN PEMBELAJARAN

Setelah mempelajari studi kasus ini, mahasiswa dapat:
1. Mengintegrasikan 3 sensor (DHT11, LDR, PIR) dengan 3 output (Relay AC, Relay Lampu, Buzzer)
2. Membuat dashboard monitoring dan kontrol via Blynk IoT
3. Menerapkan logika otomatis berbasis kondisi lingkungan
4. Membuat sistem yang reliable dengan error handling
5. Memahami konsep real-world smart building

---

## 📦 KOMPONEN YANG DIBUTUHKAN

### Hardware:
- 1x ESP32 Development Board
- 1x Sensor DHT11 (Suhu & Kelembapan)
- 1x Sensor LDR + Resistor 10kΩ (Cahaya)
- 1x Sensor PIR HC-SR501 (Gerakan)
- 1x Relay Module 2 Channel
- 1x Buzzer Aktif
- 3x LED (Merah, Kuning, Hijau) - Indikator status
- 1x Breadboard 830 point
- Kabel jumper & resistor 220Ω

### Software:
- Arduino IDE (1.8.19 atau lebih baru)
- Library: WiFi, Blynk, DHT sensor library
- Blynk IoT App (Android/iOS)

---

## 🏗️ SKENARIO: SISTEM SMART OFFICE

**Konteks:**  
Anda diminta merancang sistem otomasi untuk ruang kantor modern dengan fitur:

### Input (Sensor):
1. **DHT11** → Monitor suhu & kelembapan ruangan
2. **LDR** → Deteksi intensitas cahaya alami
3. **PIR** → Deteksi kehadiran orang

### Output (Aktuator):
1. **Relay AC** → Kontrol pendingin ruangan otomatis
2. **Relay Lampu** → Kontrol pencahayaan hemat energi
3. **Buzzer** → Alarm suhu tinggi

### Logika Otomatis:
- **AC**: Nyala otomatis jika suhu > 28°C
- **Lampu**: Nyala jika gelap (LDR > 2500) DAN ada orang (PIR = HIGH)
- **Buzzer**: Bunyi warning jika suhu > 32°C
- **Blynk**: Monitor real-time & kontrol manual via smartphone

---

## 🔌 WIRING DIAGRAM

```
ESP32 Connections:

DHT11:
├─ VCC  → 3.3V
├─ DATA → GPIO15
└─ GND  → GND

LDR (Voltage Divider):
├─ LDR pin 1 → 3.3V
├─ LDR pin 2 → GPIO34 (ADC)
└─ Resistor 10kΩ: GPIO34 → GND

PIR HC-SR501:
├─ VCC → 5V
├─ OUT → GPIO27
└─ GND → GND

Relay Module 2 CH:
├─ VCC → 5V (PENTING!)
├─ GND → GND
├─ IN1 → GPIO25 (Relay AC)
└─ IN2 → GPIO26 (Relay Lampu)

LED Indikator:
├─ LED Hijau (WiFi) → GPIO2 + R220Ω → GND
├─ LED Kuning (Blynk) → GPIO4 + R220Ω → GND
└─ LED Merah (Error) → GPIO5 + R220Ω → GND

Buzzer:
├─ (+) → GPIO33
└─ (-) → GND
```

**⚠️ CATATAN PENTING:**
- Relay HARUS pakai 5V (bukan 3.3V)
- LDR butuh resistor 10kΩ sebagai pull-down
- PIR butuh kalibrasi 30-60 detik setelah power ON

---

## 📱 SETUP BLYNK CLOUD

### Langkah 1: Registrasi & Install App

1. Download **Blynk IoT** di PlayStore/AppStore
2. Buat akun dengan email aktif
3. Verify email
4. Login ke app

### Langkah 2: Buat Template (via Web Console - RECOMMENDED)

**Kenapa via Web?** Lebih mudah copy Auth Token!

1. Buka browser → **https://blynk.cloud**
2. Login dengan akun yang sama
3. Klik **"Templates"** → **"+ New Template"**
4. Isi form:
   - Name: **Smart Office**
   - Hardware: **ESP32**
   - Connection: **WiFi**
5. Klik **"Done"**

### Langkah 3: Buat Datastreams

Di Template "Smart Office", tab **"Datastreams"**:

| Pin | Name | Type | Min | Max | Units |
|-----|------|------|-----|-----|-------|
| V0 | Suhu | Double | 0 | 50 | °C |
| V1 | Kelembapan | Double | 0 | 100 | % |
| V2 | Intensitas Cahaya | Integer | 0 | 4095 | - |
| V3 | Status PIR | Integer | 0 | 1 | - |
| V4 | Kontrol AC | Integer | 0 | 1 | - |
| V5 | Kontrol Lampu | Integer | 0 | 1 | - |
| V6 | Status Sistem | String | - | - | - |

**Cara membuat 1 datastream:**
1. Klik **"+ New Datastream"** → **"Virtual Pin"**
2. Isi sesuai tabel di atas
3. Klik **"Create"**
4. Ulangi untuk V0-V6

### Langkah 4: Design Dashboard

Di tab **"Mobile Dashboard"** atau **"Web Dashboard"**:

**Widget 1: Gauge (Suhu)**
- Type: Gauge
- Datastream: V0 (Suhu)
- Label: "Suhu Ruangan"
- Color: Orange/Red

**Widget 2: Value Display (Kelembapan)**
- Type: Value Display
- Datastream: V1
- Label: "Kelembapan"
- Color: Blue

**Widget 3: Value Display (Cahaya)**
- Type: Value Display
- Datastream: V2
- Label: "Cahaya (ADC)"

**Widget 4: LED Indicator (PIR)**
- Type: LED
- Datastream: V3
- Label: "Gerakan Terdeteksi"
- Color: Green

**Widget 5: Button (AC)**
- Type: Button
- Datastream: V4
- Mode: **Switch** (bukan Push!)
- ON label: "AC ON"
- OFF label: "AC OFF"

**Widget 6: Button (Lampu)**
- Type: Button
- Datastream: V5
- Mode: Switch
- ON label: "Lampu ON"
- OFF label: "Lampu OFF"

**Widget 7: Label (Status)**
- Type: Label
- Datastream: V6
- Label: "Status Sistem"

### Langkah 5: Buat Device & Dapatkan Auth Token

1. Klik **"Devices"** → **"+ New Device"** → **"From Template"**
2. Pilih template: **"Smart Office"**
3. Device Name: **ESP32_Office_Room1**
4. Klik **"Create"**
5. Klik device yang baru dibuat
6. Tab **"Device Info"**
7. **COPY 3 credentials** ini (klik icon copy ⎘):
   - `BLYNK_TEMPLATE_ID` (contoh: TMPL4xRa1bXYZ)
   - `BLYNK_TEMPLATE_NAME` (contoh: Smart Office)
   - `BLYNK_AUTH_TOKEN` (panjang ~32 karakter)

**💡 TIP:** Kirim ke email sendiri atau paste ke Notepad

---

## 💻 IMPLEMENTASI KODE

Lihat file: **kode-14-studi-kasus-3sensor-3output.ino**

Kode mencakup:
- ✅ Koneksi WiFi & Blynk dengan auto-reconnect
- ✅ Pembacaan 3 sensor dengan error handling
- ✅ Logika otomatis AC, Lampu, Buzzer
- ✅ Kontrol manual dari Blynk app
- ✅ Rate limiting (kirim data setiap 2 detik)
- ✅ Serial monitoring untuk debugging

---

## 🧪 TESTING & VALIDASI

### Test 1: Koneksi Blynk
1. Upload kode ke ESP32
2. Buka Serial Monitor (115200 baud)
3. Tunggu pesan: **"Blynk Connected!"**
4. Buka Blynk app → Device harus status **Online**

### Test 2: Monitoring Sensor
1. Lihat widget Gauge (suhu) → harus update setiap 2 detik
2. Tutup sensor LDR dengan tangan → nilai cahaya naik (gelap)
3. Gerakkan tangan di depan PIR → LED indicator hijau

### Test 3: Kontrol Manual
1. Tap button AC di app → Relay harus klik (bunyi)
2. Tap button Lampu → Relay lampu ON/OFF
3. Cek Serial Monitor: ada log "MANUAL ON/OFF"

### Test 4: Otomatis AC
1. Pegang sensor DHT11 (hangatkan dengan tangan)
2. Tunggu suhu naik > 28°C
3. Relay AC harus nyala otomatis
4. Buzzer bunyi 2x sebagai notifikasi

### Test 5: Otomatis Lampu
1. Tutup LDR (simulasi gelap)
2. Gerakkan tangan di PIR (simulasi orang masuk)
3. Lampu harus nyala otomatis

---

## 🔧 TROUBLESHOOTING

### Problem 1: Blynk tidak connect

**Gejala:** Serial Monitor stuck di "Connecting to Blynk..."

**Solusi:**
1. Cek WiFi SSID & password (case-sensitive!)
2. Pastikan WiFi 2.4GHz (bukan 5GHz)
3. Cek Auth Token sudah benar (32 karakter)
4. Pastikan BLYNK_TEMPLATE_ID juga sudah diisi
5. Coba hotspot HP sebagai backup WiFi

### Problem 2: DHT11 返回 NaN

**Gejala:** Suhu/kelembapan = 0 atau "NaN"

**Solusi:**
1. Cek wiring (VCC, DATA, GND)
2. Tambah resistor pull-up 10kΩ: DATA → VCC
3. Tunggu 2 detik setelah power ON
4. Ganti sensor jika rusak

### Problem 3: PIR selalu trigger

**Gejala:** PIR detect gerakan terus-menerus

**Solusi:**
1. Kalibrasi **30-60 detik** setelah power ON (jangan gerak!)
2. Putar potensio "Sensitivity" ke tengah
3. Putar potensio "Time Delay" ke minimum
4. Jauhkan dari sumber panas (AC, lampu)

### Problem 4: Relay tidak bunyi klik

**Solusi:**
1. Pastikan relay pakai **5V** (bukan 3.3V!)
2. Cek wiring IN1/IN2
3. Test dengan kode sederhana: `digitalWrite(25, HIGH);`
4. Cek LED indikator di relay module

---

## 📊 ANALISIS PERFORMA

### Penghematan Energi

**Tanpa Sistem Otomatis:**
- Lampu nyala 24 jam: 60W × 24h = 1.44 kWh/hari
- AC nyala 8 jam: 1000W × 8h = 8 kWh/hari
- **Total: 9.44 kWh/hari**

**Dengan Sistem Smart (estimasi):**
- Lampu hanya saat gelap + ada orang: ~4 jam → 0.24 kWh
- AC hanya saat panas: ~5 jam → 5 kWh
- **Total: 5.24 kWh/hari**

**Hemat: 44.5% per hari!**

---

## 🎓 PENGEMBANGAN LANJUTAN

### Level 1: Tambah Fitur
- [ ] Notifikasi push Blynk saat suhu > 32°C
- [ ] Chart/grafik suhu 24 jam
- [ ] Timer automation (AC nyala jam 08:00-17:00)

### Level 2: Multi-Room
- [ ] 3 ESP32 untuk 3 ruangan berbeda
- [ ] 1 dashboard Blynk untuk semua ruangan
- [ ] Perbandingan suhu antar ruangan

### Level 3: AI/ML
- [ ] Prediksi pola penggunaan AC
- [ ] Optimasi threshold berdasarkan histori
- [ ] Anomaly detection (sensor rusak)

---

## 📚 REFERENSI

1. **Blynk Documentation**: https://docs.blynk.io
2. **ESP32 Pinout**: https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
3. **DHT11 Datasheet**: https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf

---

**Dibuat untuk:** Mata Kuliah Bangunan Cerdas  
**Instruktur:** Anton Prafanto, S.Kom., M.T.  
**Target:** Mahasiswa Arsitektur  
**Versi:** 1.0 - 2025
