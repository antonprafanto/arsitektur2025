# PERTEMUAN 3: AKTUATOR & KONTROL OTOMATIS

**Mata Kuliah**: Bangunan Cerdas
**Durasi**: 3 SKS (150 menit)
**Prasyarat**: Pertemuan 1 & 2

---

## 📋 TUJUAN PEMBELAJARAN

Setelah pertemuan ini, mahasiswa diharapkan dapat:
1. Memahami fungsi aktuator dalam sistem IoT
2. Menggunakan Relay untuk kontrol perangkat listrik AC
3. Menampilkan data ke OLED Display
4. Menggunakan buzzer untuk notifikasi suara
5. Membuat sistem kontrol otomatis berbasis sensor
6. Mengintegrasikan sensor + aktuator dalam satu sistem

---

## 📖 BAGIAN 1: TEORI AKTUATOR (25 menit)

### A. Apa itu Aktuator?

**Definisi:**
Aktuator adalah komponen yang mengubah sinyal listrik menjadi aksi fisik (gerakan, suara, cahaya, panas, dll).

**Analogi Arsitektur:**
- **Sensor** = Mata dan telinga (input, merasakan)
- **Mikrokontroler** = Otak (proses, berpikir)
- **Aktuator** = Tangan dan kaki (output, beraksi)

### B. Jenis-Jenis Aktuator

| Jenis | Output | Contoh | Aplikasi Bangunan |
|-------|--------|--------|-------------------|
| **Relay** | Saklar elektronik | Relay 2CH | Kontrol lampu, AC, pompa |
| **Motor** | Gerakan rotasi | Servo, DC motor | Pintu otomatis, blind/tirai |
| **Display** | Visual/teks | OLED, LCD | Informasi suhu, status sistem |
| **Buzzer** | Suara | Active/Passive | Alarm, notifikasi |
| **LED** | Cahaya | RGB LED | Indikator, lampu hias |
| **Solenoid** | Gerakan linear | Door lock | Kunci pintu otomatis |

### C. Komponen yang Digunakan Hari Ini

#### 1. **Relay 2 Channel**

**Fungsi:** Saklar elektronik untuk kontrol perangkat listrik AC (220V)

**Spesifikasi:**
- Input: 3.3V atau 5V (signal dari ESP32)
- Output: Maksimal 250V AC, 10A
- 2 channel = bisa kontrol 2 perangkat berbeda
- Mode: Normally Open (NO) dan Normally Closed (NC)

**Cara Kerja:**
- ESP32 kirim sinyal HIGH → relay "klik" (on)
- Kontak dalam relay tertutup → arus mengalir → perangkat nyala
- ESP32 kirim sinyal LOW → relay off → perangkat mati

**Koneksi:**
- VCC → 5V
- GND → GND
- IN1 → GPIO pin (contoh: GPIO25)
- IN2 → GPIO pin (contoh: GPIO26)

**Terminal Output:**
- COM (Common): Input arus dari sumber (220V)
- NO (Normally Open): Output saat relay ON
- NC (Normally Closed): Output saat relay OFF

**PERINGATAN KEAMANAN:**
⚠️ Hati-hati dengan tegangan AC 220V!
- Gunakan isolasi yang baik
- Jangan sentuh terminal saat terhubung listrik
- Untuk praktikum, gunakan LED sebagai simulasi

---

#### 2. **OLED Display 0.96 inch**

**Fungsi:** Menampilkan teks, angka, grafik

**Spesifikasi:**
- Resolusi: 128x64 pixel
- Warna: Monochrome (putih/biru)
- Interface: I2C (hanya perlu 2 kabel: SDA, SCL)
- Tegangan: 3.3V - 5V
- Driver: SSD1306

**Keunggulan:**
- Low power consumption
- Tampilan tajam (OLED, bukan LCD)
- Mudah diprogram (library lengkap)
- Tidak perlu backlight

**Koneksi I2C:**
- VCC → 3.3V
- GND → GND
- SDA → GPIO21 (default I2C ESP32)
- SCL → GPIO22 (default I2C ESP32)

---

#### 3. **Buzzer**

**Ada 2 jenis:**

**a) Active Buzzer:**
- Bunyi langsung saat diberi tegangan
- Frekuensi tetap (~2kHz)
- Kontrol: digitalWrite(pin, HIGH/LOW)
- Cocok untuk: alarm sederhana

**b) Passive Buzzer:**
- Perlu sinyal PWM untuk bunyi
- Bisa mengatur nada/frekuensi
- Kontrol: tone(pin, frequency)
- Cocok untuk: melodi, beep pattern

---

## 💻 BAGIAN 2: SETUP LIBRARY OLED (15 menit)

### Install Library

1. Buka Arduino IDE
2. `Sketch` → `Include Library` → `Manage Libraries`
3. Cari dan install:
   - **Adafruit SSD1306** (untuk OLED driver)
   - **Adafruit GFX Library** (untuk grafis)
4. Install dependencies jika diminta
5. Restart Arduino IDE

---

## 🔧 BAGIAN 3: PRAKTIKUM 1 - RELAY KONTROL (35 menit)

### Tujuan:
Mengontrol 2 LED (simulasi lampu rumah) dengan relay berdasarkan sensor DHT11

### Komponen:
- ESP32, Relay 2CH, DHT11, 2x LED, 2x Resistor 220Ω

### Logika:
- LED1 (simulasi AC) nyala jika suhu > 28°C
- LED2 (simulasi exhaust fan) nyala jika kelembapan > 70%

### Kode Program:
Lihat file: `kode-07-relay-dht11.ino`

---

## 🔧 BAGIAN 4: PRAKTIKUM 2 - OLED DISPLAY (35 menit)

### Tujuan:
Menampilkan data sensor DHT11 dan LDR ke layar OLED

### Komponen:
- ESP32, OLED 0.96", DHT11, LDR

### Kode Program:
Lihat file: `kode-08-oled-display.ino`

---

## 🔧 BAGIAN 5: PRAKTIKUM 3 - SISTEM INTEGRASI (40 menit)

### Tujuan:
Membuat sistem smart room sederhana dengan:
- DHT11: Monitor suhu & kelembapan
- LDR: Deteksi cahaya
- PIR: Deteksi kehadiran
- Relay: Kontrol AC dan lampu
- OLED: Display info
- Buzzer: Alarm suhu ekstrem

### Logika Sistem:
1. **Lampu (Relay 1):** Nyala jika GELAP + ADA ORANG
2. **AC (Relay 2):** Nyala jika PANAS (>28°C) + ADA ORANG
3. **Buzzer:** Bunyi jika suhu >35°C (ekstrem)
4. **OLED:** Tampilkan semua data sensor + status aktuator

### Kode Program:
Lihat file: `kode-09-sistem-smart-room.ino`

---

## 📝 TUGAS RUMAH

### Tugas 1: Smart Parking System
Buat sistem parkir dengan:
- PIR: Deteksi mobil masuk
- LED merah: Parkir penuh
- LED hijau: Parkir tersedia
- OLED: Tampil jumlah slot tersedia
- Buzzer: Beep saat mobil masuk/keluar

### Tugas 2: Smart Greenhouse
Sistem kontrol greenhouse:
- DHT11: Monitor suhu & kelembapan
- LDR: Monitor cahaya
- Relay 1: Pompa air (nyala jika kelembapan <40%)
- Relay 2: Lampu grow light (nyala jika cahaya kurang)
- OLED: Display semua parameter

### Tugas 3: Proyek Akhir (Persiapan)
Mulai rancang maket rumah pintar Anda:
1. Tentukan tema (smart home, smart office, dll)
2. Pilih minimal 2 sensor + 2 output
3. Buat diagram blok sistem
4. Tulis logika kontrol (flowchart sederhana)

---

## 📚 RANGKUMAN

1. ✅ **Aktuator** = Komponen output untuk beraksi
2. ✅ **Relay** = Saklar elektronik untuk perangkat AC
3. ✅ **OLED** = Display untuk informasi visual
4. ✅ **Buzzer** = Notifikasi audio
5. ✅ **Sistem Otomatis** = Sensor + Logika + Aktuator
6. ✅ **Integrasi** = Gabungkan semua komponen jadi sistem cerdas

---

## 🔜 PERSIAPAN PERTEMUAN 4

**Materi:** Integrasi Sistem & Proyek Maket

**Yang akan dipelajari:**
- Review semua materi
- Konsultasi proyek maket
- Tips integrasi multi-komponen
- Troubleshooting praktis
- Presentasi contoh proyek

**Persiapan:**
- Bawa semua komponen
- Rancangan proyek sudah jadi
- Mulai rakit prototype
- Siapkan pertanyaan

---

## ❓ FAQ

**Q: Apakah relay bisa rusak jika sering dipakai?**
A: Relay mekanis punya lifecycle (~100.000 switching). Untuk aplikasi sering on/off, pertimbangkan solid state relay (SSR).

**Q: OLED saya tidak muncul tampilan**
A: Cek alamat I2C (0x3C atau 0x3D). Scan dengan kode I2C scanner.

**Q: Buzzer passive tidak bunyi**
A: Gunakan `tone(pin, freq)` bukan digitalWrite.

---

**Sampai jumpa di Pertemuan 4! 🚀**
