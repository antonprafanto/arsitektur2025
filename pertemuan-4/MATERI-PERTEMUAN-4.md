# PERTEMUAN 4: INTEGRASI SISTEM & PROYEK MAKET

**Mata Kuliah**: Bangunan Cerdas
**Durasi**: 3 SKS (150 menit)
**Sifat**: Workshop & Konsultasi Proyek

---

## 📋 TUJUAN PEMBELAJARAN

Setelah pertemuan ini, mahasiswa diharapkan dapat:
1. Mengintegrasikan minimal 2 sensor dan 2 output dalam satu sistem
2. Mengatasi masalah troubleshooting yang umum terjadi
3. Merancang dan merakit maket rumah pintar
4. Mempresentasikan konsep dan demo sistem
5. Mendokumentasikan proyek dengan baik

---

## 📖 BAGIAN 1: REVIEW MATERI 1-3 (30 menit)

### Ringkasan Pertemuan 1: Dasar IoT
✅ Konsep IoT dan Smart Building
✅ ESP32 sebagai mikrokontroler
✅ Output: LED Blink, Button Control
✅ Struktur program: setup() dan loop()

### Ringkasan Pertemuan 2: Sensor
✅ DHT11 → Suhu & Kelembapan
✅ LDR → Intensitas Cahaya
✅ PIR → Deteksi Gerakan
✅ Konsep: Threshold, Hysteresis

### Ringkasan Pertemuan 3: Aktuator
✅ Relay → Kontrol perangkat AC
✅ OLED → Display informasi
✅ Buzzer → Notifikasi audio
✅ Integrasi sensor + aktuator

---

## 💡 BAGIAN 2: KONSEP SISTEM TERINTEGRASI (30 menit)

### A. Prinsip Integrasi yang Baik

**1. Modularitas**
- Setiap komponen bisa di-test terpisah
- Fungsi-fungsi dipisah (tidak campur aduk dalam satu fungsi besar)
- Mudah debug dan maintenance

**2. Reliabilitas**
- Error handling (cek sensor gagal)
- Failsafe (aman jika ada error)
- Redundancy (backup jika sensor utama rusak)

**3. Efisiensi**
- Hemat energi (sleep mode, timer)
- Optimal performance (tidak delay berlebihan)
- Resource management (memory, pin)

**4. User Experience**
- Feedback jelas (LED, display, buzzer)
- Kontrol mudah (button, smartphone)
- Dokumentasi lengkap

### B. Diagram Blok Sistem Smart Building

```
┌─────────────────────────────────────────────────┐
│              SISTEM SMART BUILDING              │
├─────────────────────────────────────────────────┤
│                                                 │
│  [INPUT LAYER - SENSING]                        │
│  ┌─────────┐  ┌─────────┐  ┌─────────┐         │
│  │  DHT11  │  │   LDR   │  │   PIR   │         │
│  │ Suhu+RH │  │ Cahaya  │  │ Gerakan │         │
│  └────┬────┘  └────┬────┘  └────┬────┘         │
│       │            │             │              │
│  ─────┴────────────┴─────────────┴─────         │
│                    │                            │
│  [PROCESSING LAYER - DECISION]                  │
│           ┌────────┴────────┐                   │
│           │     ESP32       │                   │
│           │  - Algoritma    │                   │
│           │  - Logika       │                   │
│           │  - Threshold    │                   │
│           └────────┬────────┘                   │
│                    │                            │
│  ─────┬────────────┴─────────────┬─────         │
│       │            │             │              │
│  [OUTPUT LAYER - ACTUATION]                     │
│  ┌────┴────┐  ┌───┴────┐  ┌────┴────┐          │
│  │  Relay  │  │  OLED  │  │ Buzzer  │          │
│  │ Lampu+AC│  │Display │  │  Alarm  │          │
│  └─────────┘  └────────┘  └─────────┘          │
│                                                 │
│  [CONNECTIVITY - Optional]                      │
│           WiFi/Bluetooth → Smartphone           │
│                                                 │
└─────────────────────────────────────────────────┘
```

### C. Checklist Sebelum Integrasi

**Hardware:**
- [ ] Semua komponen sudah di-test individual
- [ ] Wiring rapi dan aman (tidak ada short)
- [ ] Power supply cukup (min 5V 2A untuk relay)
- [ ] Breadboard stabil (kabel tidak mudah lepas)

**Software:**
- [ ] Semua library sudah terinstall
- [ ] Kode individual komponen sudah berjalan
- [ ] Struktur kode modular (fungsi-fungsi terpisah)
- [ ] Ada error handling (cek sensor gagal)

**Testing:**
- [ ] Test dalam kondisi normal
- [ ] Test dalam kondisi ekstrem (suhu tinggi/rendah)
- [ ] Test saat sensor dicabut (failsafe)
- [ ] Test power on/off berulang kali

---

## 🔧 BAGIAN 3: TROUBLESHOOTING PRAKTIS (40 menit)

### Masalah Umum & Solusi

#### 1. **ESP32 Tidak Bisa Upload**

**Gejala:** Error "Failed to connect" atau "Timeout"

**Solusi:**
1. Tekan dan tahan tombol **BOOT** saat upload
2. Ganti kabel USB (pastikan bisa transfer data)
3. Cek driver CH340/CP2102 sudah terinstall
4. Pilih port COM yang benar
5. Turunkan baud rate upload (Tools → Upload Speed → 115200)

---

#### 2. **Sensor DHT11 Selalu "Failed to Read"**

**Gejala:** Serial Monitor menampilkan "NaN" atau error

**Solusi:**
1. Cek koneksi VCC, DATA, GND
2. Pastikan pin DATA ke GPIO yang benar
3. Tambah delay 2 detik di setup() sebelum pembacaan pertama
4. Coba tambah pull-up resistor 10K antara DATA dan VCC
5. Ganti sensor DHT11 (mungkin rusak)

**Kode cek dasar:**
```cpp
void setup() {
  Serial.begin(115200);
  dht.begin();
  delay(2000);  // PENTING!
}

void loop() {
  float t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println("ERROR!");
  } else {
    Serial.println(t);
  }
  delay(2000);
}
```

---

#### 3. **LDR Nilai Tidak Berubah**

**Gejala:** Nilai LDR tetap 0 atau 4095

**Solusi:**
1. Pastikan menggunakan **voltage divider** (LDR + resistor 10K)
2. Cek koneksi: 3.3V → LDR → GPIO34 → 10KΩ → GND
3. Pastikan pakai pin ADC (GPIO32-39)
4. Test LDR dengan multimeter (ukur resistansi saat gelap/terang)

**Kode debug:**
```cpp
void loop() {
  int nilai = analogRead(34);
  Serial.print("LDR: ");
  Serial.println(nilai);
  delay(500);
}
// Tutup LDR dengan tangan, nilai harus berubah
```

---

#### 4. **PIR Terus Terdeteksi (False Positive)**

**Gejala:** PIR trigger terus meskipun tidak ada gerakan

**Solusi:**
1. Tunggu kalibrasi 60 detik setelah power on
2. Jauhkan PIR dari sumber panas (AC, heater, jendela)
3. Turunkan sensitivity (putar potensiometer S ke minimum)
4. Pastikan tidak ada objek bergerak (tirai, kipas)
5. Test di malam hari (siang hari banyak interferensi)

**Tips:** Pasang PIR di pojok ruangan, tinggi 2-2.5 meter

---

#### 5. **Relay Tidak Klik (Tidak Bunyi)**

**Gejala:** Relay tidak bekerja, tidak ada bunyi "klik"

**Solusi:**
1. Cek VCC relay ke **5V** (bukan 3.3V!)
2. Cek GND terhubung
3. Cek pin IN1/IN2 dari GPIO yang benar
4. Test dengan kode sederhana:
```cpp
digitalWrite(25, HIGH);
delay(1000);
digitalWrite(25, LOW);
delay(1000);
// Harus ada bunyi klik
```
5. Ukur tegangan pin IN1 saat HIGH (harus ~3.3V)
6. Coba relay lain (mungkin rusak)

---

#### 6. **OLED Tidak Tampil Apa-apa (Blank)**

**Gejala:** Layar OLED hitam/blank

**Solusi:**
1. Cek koneksi I2C: SDA (GPIO21), SCL (GPIO22)
2. Cek alamat I2C (0x3C atau 0x3D)
3. Upload **I2C Scanner** untuk deteksi alamat:
```cpp
#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.println("Scanning I2C...");

  for (byte i = 1; i < 127; i++) {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0) {
      Serial.print("Device found at 0x");
      Serial.println(i, HEX);
    }
  }
}

void loop() {}
```
4. Sesuaikan `SCREEN_ADDRESS` dengan hasil scan
5. Pastikan library Adafruit SSD1306 terinstall
6. Coba OLED lain (mungkin rusak)

---

#### 7. **ESP32 Restart Sendiri (Crash)**

**Gejala:** ESP32 reboot terus atau hang

**Solusi:**
1. **Masalah power:** Gunakan power supply 5V 2A (bukan USB laptop)
2. **Memory overflow:** Kurangi variabel global, gunakan local
3. **Stack overflow:** Hindari rekursi dalam, kurangi variabel dalam fungsi
4. **Watchdog timeout:** Tambah `delay(10)` di loop atau `yield()`
5. Cek Serial Monitor saat crash (ada pesan error?)
6. Upload kode sederhana untuk test (LED blink)

---

#### 8. **Data Sensor Tidak Stabil (Bouncing)**

**Gejala:** Nilai sensor naik-turun cepat

**Solusi:**
1. Gunakan **moving average** (rata-rata 5-10 pembacaan)
```cpp
int bacaLDRStabil() {
  long total = 0;
  for (int i = 0; i < 10; i++) {
    total += analogRead(pinLDR);
    delay(10);
  }
  return total / 10;
}
```
2. Tambah **hysteresis** untuk threshold
3. Tambah kapasitor 0.1uF di sensor (filter hardware)
4. Hindari kabel sensor terlalu panjang (max 30cm)

---

### Tools Debug yang Berguna

**1. Serial Monitor**
- Print nilai sensor untuk monitoring
- Print status program (sudah sampai baris berapa)
- Format: `Serial.print()` untuk inline, `Serial.println()` untuk newline

**2. LED Indikator**
- Tambah LED untuk debug tanpa Serial Monitor
- Contoh: LED berkedip = program berjalan, LED mati = program hang

**3. Multimeter**
- Ukur tegangan pin (harus 3.3V atau 5V)
- Ukur resistansi sensor (cek sensor rusak atau tidak)
- Cek continuity (koneksi putus atau tidak)

**4. I2C Scanner**
- Untuk cek alamat I2C device (OLED, sensor I2C)
- Kode di atas

---

## 🏠 BAGIAN 4: PANDUAN PROYEK MAKET (50 menit)

### A. Tema Proyek yang Direkomendasikan

#### 1. **Smart Home (Rumah Pintar)**
**Fitur minimal:**
- Lampu otomatis (LDR + PIR + Relay)
- AC otomatis (DHT11 + PIR + Relay)
- OLED display: Tampil suhu, status ruangan
- Buzzer: Alarm suhu tinggi

**Ruangan:** Kamar tidur, ruang tamu, atau dapur

---

#### 2. **Smart Office/Meeting Room**
**Fitur minimal:**
- Deteksi occupancy (PIR)
- AC dan lampu otomatis saat ada orang
- OLED: Status "Available" atau "Occupied"
- Timer: Matikan semua jika kosong >30 menit

---

#### 3. **Smart Greenhouse/Indoor Farming**
**Fitur minimal:**
- Monitor suhu & kelembapan (DHT11)
- Lampu grow light otomatis (LDR + Relay)
- Pompa misting otomatis (kelembapan rendah)
- OLED: Display parameter lingkungan

---

#### 4. **Smart Parking System**
**Fitur minimal:**
- Deteksi mobil (PIR atau sensor jarak)
- LED merah/hijau: Penuh/Tersedia
- OLED: Jumlah slot tersedia
- Buzzer: Beep saat mobil masuk/keluar

---

#### 5. **Smart Security System**
**Fitur minimal:**
- Deteksi gerakan (PIR)
- Alarm buzzer + LED merah
- OLED: Log aktivitas (waktu terdeteksi)
- Button: Arm/Disarm sistem

---

### B. Langkah-Langkah Pembuatan Maket

**FASE 1: Perencanaan (sebelum pertemuan 4)**

1. **Tentukan tema** dari pilihan di atas (atau kreasi sendiri)
2. **Buat diagram blok sistem:**
   - Input: Sensor apa saja?
   - Proses: Logika kontrolnya bagaimana?
   - Output: Aktuator apa saja?
3. **Buat flowchart** algoritma
4. **Sketsa desain maket** (tampak atas, samping)
5. **Daftar komponen** yang akan digunakan

---

**FASE 2: Prototyping (pertemuan 4 - workshop)**

1. **Test komponen individual**
   - Upload kode test untuk setiap sensor
   - Upload kode test untuk setiap aktuator
   - Pastikan semua berfungsi

2. **Rakit di breadboard**
   - Mulai dari power (3.3V, 5V, GND)
   - Tambah sensor satu per satu
   - Test setiap penambahan sensor

3. **Integrasi kode**
   - Gabungkan kode sensor + aktuator
   - Tambahkan logika kontrol
   - Upload dan test

4. **Troubleshooting**
   - Cek error satu per satu
   - Gunakan Serial Monitor untuk debug
   - Minta bantuan dosen/asisten jika stuck

---

**FASE 3: Finalisasi (di rumah)**

1. **Buat maket fisik**
   - Material: Kardus, styrofoam, atau kayu
   - Ukuran: Minimal 30x30 cm
   - Rapi dan kuat (tidak mudah rusak)

2. **Instalasi komponen ke maket**
   - Pasang ESP32 + breadboard di base
   - Pasang sensor di posisi yang tepat
   - Pasang aktuator (LED sebagai simulasi)
   - OLED display di depan (mudah dibaca)

3. **Wiring rapi**
   - Gunakan cable management (zip tie, duct tape)
   - Sembunyikan kabel di dalam maket
   - Pastikan tidak ada kabel lepas

4. **Testing final**
   - Test semua skenario
   - Rekam video demo (backup jika demo gagal)

---

**FASE 4: Dokumentasi**

Buat laporan proyek mencakup:

1. **Cover & Identitas Kelompok**
2. **Abstrak** (ringkasan proyek 1 paragraf)
3. **Pendahuluan**
   - Latar belakang
   - Tujuan proyek
   - Manfaat
4. **Tinjauan Pustaka** (teori singkat tentang komponen)
5. **Metodologi**
   - Diagram blok sistem
   - Flowchart algoritma
   - Wiring diagram
   - Spesifikasi komponen
6. **Implementasi**
   - Foto maket (berbagai sudut)
   - Penjelasan cara kerja
   - Kode program (dengan komentar)
7. **Pengujian & Hasil**
   - Tabel pengujian (skenario → hasil)
   - Screenshot Serial Monitor
   - Foto saat demo
8. **Kesimpulan & Saran**
   - Kesimpulan pencapaian
   - Keterbatasan sistem
   - Saran pengembangan
9. **Daftar Pustaka**
10. **Lampiran** (kode lengkap)

---

### C. Kriteria Penilaian

| Aspek | Bobot | Deskripsi |
|-------|-------|-----------|
| **Fungsionalitas** | 30% | Sistem bekerja sesuai logika, minimal 2 sensor + 2 output |
| **Kreativitas** | 20% | Ide menarik, bukan hanya copy paste |
| **Kerapian Maket** | 15% | Maket rapi, kuat, estetis |
| **Kode Program** | 15% | Kode rapi, ada komentar, modular |
| **Presentasi** | 10% | Penjelasan jelas, menjawab pertanyaan |
| **Dokumentasi** | 10% | Laporan lengkap, sistematis |

**Total: 100%**

---

## 📝 BAGIAN 5: TIPS & BEST PRACTICES

### Tips Umum

1. **Mulai Dari yang Sederhana**
   - Jangan langsung bikin sistem kompleks
   - Step by step: sensor 1 → test → sensor 2 → test → gabung

2. **Backup Adalah Kunci**
   - Simpan kode yang sudah jalan di folder berbeda
   - Buat video demo sebagai backup
   - Siapkan komponen cadangan

3. **Time Management**
   - Jangan tunggu mepet deadline
   - Alokasikan waktu: 60% coding, 40% maket fisik

4. **Kolaborasi Tim**
   - Pembagian tugas jelas (hardware, software, dokumentasi)
   - Meeting rutin (minimal 2x seminggu)
   - Komunikasi lancar (grup chat)

5. **Ask for Help**
   - Jangan malu bertanya ke dosen/asisten
   - Manfaatkan forum online (Arduino Forum, Reddit)
   - Dokumentasikan error untuk konsultasi

### Best Practices Kode

```cpp
// ✅ GOOD: Nama variabel jelas
int pinSensorSuhu = 15;
int pinRelayLampu = 25;

// ❌ BAD: Nama variabel tidak jelas
int p1 = 15;
int x = 25;

// ✅ GOOD: Fungsi terpisah
void bacaSensor() {
  // kode baca sensor
}

void kontrolAktuator() {
  // kode kontrol relay
}

// ❌ BAD: Semua dalam loop()
void loop() {
  // 200 baris kode campur aduk
}

// ✅ GOOD: Ada error handling
float suhu = dht.readTemperature();
if (isnan(suhu)) {
  Serial.println("Error sensor!");
  return;  // Skip loop ini
}

// ❌ BAD: Tidak cek error
float suhu = dht.readTemperature();
// Langsung pakai, bisa crash jika NaN
```

### Best Practices Hardware

1. **Gunakan kabel warna standar:**
   - Merah: VCC (5V atau 3.3V)
   - Hitam/Cokelat: GND
   - Kuning/Orange: Signal
   - Hijau: SDA (I2C)
   - Biru: SCL (I2C)

2. **Pasang kapasitor decoupling:**
   - 100uF di input power ESP32
   - 0.1uF di setiap sensor

3. **Gunakan terminal block untuk power:**
   - Jangan cabang power dari breadboard (tidak stabil)
   - Gunakan terminal block untuk distribusi 5V dan GND

---

## 🎯 KESIMPULAN MATA KULIAH

Selamat! Anda telah menyelesaikan pembelajaran tentang:

✅ **Konsep IoT** dan aplikasinya dalam Smart Building
✅ **ESP32** sebagai platform IoT
✅ **Sensor** untuk monitoring lingkungan
✅ **Aktuator** untuk kontrol otomatis
✅ **Sistem Terintegrasi** yang bekerja secara otomatis

**Skill yang Didapat:**
- Pemrograman dasar Arduino/ESP32
- Membaca datasheet dan wiring diagram
- Troubleshooting hardware & software
- Integrasi multi-komponen
- Dokumentasi teknis
- Kerja tim (kelompok)

**Aplikasi Ilmu:**
- Smart Home
- Smart Building
- IoT dalam arsitektur
- Building automation
- Energy management

---

## 📚 REFERENSI & SUMBER BELAJAR

**Website:**
- Arduino Official: https://www.arduino.cc
- Random Nerd Tutorials: https://randomnerdtutorials.com/esp32-tutorials/
- Last Minute Engineers: https://lastminuteengineers.com
- ESP32.com Forum: https://esp32.com

**YouTube Channel:**
- GreatScott!
- Andreas Spiess
- Kelas Robot (Indonesia)
- Innovative Electronics

**Buku:**
- "ESP32 Projects" - Neil Cameron
- "IoT Fundamentals" - David Hanes
- "Smart Home Automation with Linux and Raspberry Pi" - Steven Goodwin

---

## 🎤 JADWAL PRESENTASI PROYEK

**Format Presentasi:**
- Durasi: 10 menit per kelompok (7 menit presentasi + 3 menit Q&A)
- Persiapkan: Slide PPT + Demo langsung

**Isi Presentasi:**
1. Judul dan anggota kelompok (1 slide)
2. Latar belakang & tujuan (1 slide)
3. Diagram blok sistem (1 slide)
4. Penjelasan komponen (1 slide)
5. **DEMO LANGSUNG** (5 menit)
6. Kesimpulan & pengembangan (1 slide)

**Tips Presentasi:**
- Latihan demo sebelumnya (jangan dadakan!)
- Backup plan jika demo gagal (video)
- Jelaskan dengan bahasa sederhana (bukan teknis semua)
- Tunjukkan antusiasme!

---

**Selamat mengerjakan proyek! Semoga sukses! 🚀**

**"The best way to predict the future is to create it." - Peter Drucker**
