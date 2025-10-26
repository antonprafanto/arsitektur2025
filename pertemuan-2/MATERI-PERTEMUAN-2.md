# PERTEMUAN 2: SENSOR UNTUK MONITORING LINGKUNGAN

**Mata Kuliah**: Bangunan Cerdas
**Durasi**: 3 SKS (150 menit)
**Prasyarat**: Sudah memahami Pertemuan 1 (LED dan Button)

---

## 📋 TUJUAN PEMBELAJARAN

Setelah pertemuan ini, mahasiswa diharapkan dapat:
1. Memahami fungsi dan jenis-jenis sensor dalam bangunan cerdas
2. Membaca data dari sensor DHT11 (suhu dan kelembapan)
3. Membuat sistem pencahayaan otomatis dengan sensor LDR
4. Membuat sistem deteksi gerak dengan sensor PIR
5. Mengintegrasikan sensor dengan aktuator (LED, Buzzer)
6. Menggunakan Serial Monitor untuk debugging

---

## 📖 BAGIAN 1: TEORI SENSOR (30 menit)

### A. Apa itu Sensor?

**Definisi Sederhana:**
Sensor adalah alat yang dapat merasakan/mendeteksi perubahan lingkungan dan mengubahnya menjadi sinyal listrik yang bisa dibaca oleh mikrokontroler.

**Analogi Arsitektur:**
Jika bangunan adalah tubuh manusia, sensor adalah indera:
- **Sensor Suhu** = Kulit yang merasakan panas/dingin
- **Sensor Cahaya** = Mata yang melihat terang/gelap
- **Sensor Gerak** = Telinga yang mendengar gerakan
- **Sensor Gas** = Hidung yang mencium bau

### B. Klasifikasi Sensor

#### 1. **Berdasarkan Output:**

**a) Sensor Digital**
- Output: HIGH (1) atau LOW (0)
- Contoh: Sensor PIR (ada gerakan = HIGH, tidak ada = LOW)
- Pembacaan: `digitalRead(pin)`
- Sederhana dan mudah digunakan

**b) Sensor Analog**
- Output: Nilai kontinu (0-4095 di ESP32)
- Contoh: LDR (nilai berubah sesuai intensitas cahaya)
- Pembacaan: `analogRead(pin)`
- Lebih detail tapi perlu kalibrasi

**c) Sensor Serial/Komunikasi**
- Output: Data digital melalui protokol komunikasi
- Contoh: DHT11 (kirim data suhu via protokol khusus)
- Pembacaan: Perlu library khusus
- Lebih kompleks tapi lebih akurat

#### 2. **Berdasarkan Fungsi:**

| Jenis Sensor | Mengukur | Contoh | Aplikasi Bangunan |
|--------------|----------|--------|-------------------|
| **Suhu** | Temperatur | DHT11, DS18B20 | Kontrol AC/pemanas |
| **Kelembapan** | Humidity | DHT11, DHT22 | Dehumidifier otomatis |
| **Cahaya** | Intensitas cahaya | LDR, BH1750 | Lampu otomatis |
| **Gerak** | Pergerakan | PIR, Radar | Keamanan, lampu koridor |
| **Jarak** | Distance | Ultrasonik, IR | Pintu otomatis |
| **Gas** | Kualitas udara | MQ-2, MQ-135 | Deteksi kebakaran, ventilasi |
| **Suara** | Decibel | Mic, Sound sensor | Noise monitoring |
| **Tekanan** | Pressure | BMP280 | Ketinggian, cuaca |

### C. Sensor dalam Kit Kita

Mari kita pelajari 3 sensor utama yang akan digunakan hari ini:

---

#### **1. Sensor DHT11 - Suhu & Kelembapan**

**Spesifikasi:**
- Mengukur suhu: 0°C - 50°C (akurasi ±2°C)
- Mengukur kelembapan: 20% - 90% RH (akurasi ±5%)
- Tegangan: 3.3V - 5V
- Output: Digital (protokol 1-wire)

**Fisik:**
- 3 atau 4 pin (tergantung model)
- Pin: VCC (+), DATA (signal), NC (tidak dipakai), GND (-)

**Cara Kerja:**
- Elemen sensing mengukur suhu dan kelembapan
- Mikrokontroler internal mengolah data
- Data dikirim melalui pin DATA dengan protokol khusus
- ESP32 membaca data menggunakan library DHT

**Aplikasi dalam Bangunan:**
- **Kontrol HVAC**: AC menyala otomatis jika suhu >28°C
- **Ventilasi**: Kipas exhaust nyala jika kelembapan >80%
- **Monitoring server room**: Suhu harus stabil 18-24°C
- **Greenhouse**: Kontrol suhu dan kelembapan tanaman
- **Museum**: Jaga kelembapan untuk preservasi artefak

**Kelebihan:**
- Murah dan mudah digunakan
- Ukuran kecil
- Low power consumption

**Kekurangan:**
- Akurasi standar (bukan untuk aplikasi presisi)
- Pembacaan lambat (max 1 kali per 2 detik)
- Tidak tahan air

---

#### **2. Sensor LDR (Light Dependent Resistor)**

**Spesifikasi:**
- Resistansi berubah sesuai intensitas cahaya
- Gelap: ~1MΩ (1.000.000 ohm)
- Terang: ~1KΩ (1.000 ohm)
- Tegangan: 3.3V - 5V
- Output: Analog (0-4095 di ESP32)

**Fisik:**
- 2 kaki (seperti resistor biasa)
- Bentuk bulat dengan permukaan fotosensitif
- Warna: cokelat/hijau tua

**Cara Kerja:**
- Terbuat dari material semikonduktor (Cadmium Sulfide)
- Cahaya mengenai permukaan → elektron terlepas → resistansi turun
- Gelap → sedikit elektron → resistansi tinggi
- Perlu voltage divider (LDR + resistor 10K) untuk dibaca ESP32

**Rangkaian Voltage Divider:**
```
3.3V
  │
  ├─── LDR ────┬──── Pin Analog ESP32
  │            │
  └─── 10KΩ ───┴──── GND

Rumus: Vout = Vin × (R2 / (R1 + R2))
Dimana R1 = LDR, R2 = 10KΩ
```

**Aplikasi dalam Bangunan:**
- **Street Lighting**: Lampu jalan nyala otomatis saat gelap
- **Kantor**: Lampu ruangan menyesuaikan cahaya alami
- **Blind/Tirai Otomatis**: Tutup saat matahari terik
- **Parking Lot**: Lampu parkir hemat energi
- **Billboard**: Kecerahan layar menyesuaikan ambient

**Kelebihan:**
- Sangat murah (<Rp 1.000)
- Sederhana, tidak perlu kalibrasi rumit
- Tahan lama

**Kekurangan:**
- Respon lambat (delay ~100ms)
- Tidak linear (nilai tidak proporsional sempurna)
- Tergantung suhu lingkungan
- Tidak bisa ukur lux secara akurat (pakai BH1750 jika perlu)

---

#### **3. Sensor PIR (Passive Infrared)**

**Spesifikasi:**
- Mendeteksi radiasi infrared dari tubuh manusia
- Jangkauan: 3-7 meter (tergantung model)
- Sudut deteksi: 100-120 derajat
- Output: Digital (HIGH = ada gerakan, LOW = tidak ada)
- Delay setelah deteksi: 2-5 detik (adjustable)

**Fisik:**
- Modul lengkap (sensor + elektronik)
- 3 pin: VCC, OUT (signal), GND
- Lensa fresnel putih (seperti kubah)
- 2 potensiometer: Sensitivity & Time Delay

**Cara Kerja:**
- Sensor pyroelectric mendeteksi radiasi IR
- Tubuh manusia memancarkan IR (panas tubuh)
- Saat ada gerakan → perubahan radiasi IR → trigger
- Lensa fresnel membagi area deteksi jadi zone
- Output HIGH selama delay time (misal 5 detik)

**Pengaturan Potensiometer:**
- **Sensitivity (S)**: Jarak deteksi (putar searah jarum jam = lebih jauh)
- **Time Delay (T)**: Durasi output HIGH setelah deteksi (2 detik - 5 menit)

**Aplikasi dalam Bangunan:**
- **Lampu Koridor**: Nyala otomatis saat ada orang lewat
- **Alarm Keamanan**: Deteksi penyusup
- **Toilet Otomatis**: Lampu, flush, hand dryer
- **Meeting Room**: Matikan AC jika kosong >30 menit
- **Lift**: Tahan pintu jika ada orang datang
- **Hemat Energi**: Monitor ruangan tidak terpakai

**Kelebihan:**
- Jangkauan luas (3-7m)
- Konsumsi daya sangat rendah
- Tidak terpengaruh cahaya (beda dengan sensor foto)
- Harga terjangkau

**Kekurangan:**
- Hanya deteksi gerakan (bukan objek diam)
- False positive: hewan peliharaan, tirai tertiup angin
- Tidak bisa deteksi objek dingin (robot)
- Delay time fixed (tidak bisa terlalu cepat)

---

### D. Konsep Threshold (Ambang Batas)

Dalam sistem otomasi, kita sering pakai **threshold** untuk membuat keputusan:

**Contoh 1: Kontrol AC berdasarkan suhu**
```
if (suhu > 28) {
  // Nyalakan AC (terlalu panas)
} else if (suhu < 22) {
  // Nyalakan pemanas (terlalu dingin)
} else {
  // Suhu nyaman, matikan AC/pemanas
}
```

**Contoh 2: Lampu otomatis berdasarkan cahaya**
```
if (nilaiLDR > 3000) {
  // Gelap, nyalakan lampu
} else if (nilaiLDR < 1500) {
  // Terang, matikan lampu
} else {
  // Redup, setengah terang (PWM)
}
```

**Hysteresis (Dead Band):**
Untuk menghindari flicker (nyala-mati cepat), gunakan 2 threshold:
```
// Threshold atas: 3000 (nyalakan)
// Threshold bawah: 2500 (matikan)
// Gap 500 = hysteresis

if (nilaiLDR > 3000 && !lampuNyala) {
  nyalakanLampu();
} else if (nilaiLDR < 2500 && lampuNyala) {
  matikanLampu();
}
```

---

## 💻 BAGIAN 2: SETUP LIBRARY & SERIAL MONITOR (20 menit)

### A. Install Library DHT

DHT11 butuh library khusus untuk komunikasi:

**Cara Install:**
1. Buka Arduino IDE
2. Menu: `Sketch` → `Include Library` → `Manage Libraries...`
3. Ketik di search: `DHT sensor library`
4. Install library oleh **Adafruit** (yang namanya "DHT sensor library")
5. Akan muncul popup: "Install dependencies?" → Klik **Install All**
6. Tunggu sampai selesai
7. Tutup Library Manager

**Library yang ter-install:**
- DHT sensor library (by Adafruit)
- Adafruit Unified Sensor (dependency)

---

### B. Pengenalan Serial Monitor

**Apa itu Serial Monitor?**
Serial Monitor adalah jendela komunikasi antara ESP32 dengan komputer. Kita bisa:
- **Melihat output** dari ESP32 (print data sensor, debug)
- **Mengirim input** ke ESP32 (kontrol via keyboard)

**Cara Membuka:**
- Menu: `Tools` → `Serial Monitor`
- Atau shortcut: `Ctrl + Shift + M`

**Setting Penting:**
- **Baud Rate**: 115200 (harus sama dengan `Serial.begin(115200)` di kode)
- Line Ending: `No line ending` atau `Newline`

**Perintah Serial dalam Kode:**

```cpp
// Di setup():
Serial.begin(115200);  // Inisialisasi serial dengan baud rate 115200

// Print tanpa enter (di baris yang sama):
Serial.print("Suhu: ");
Serial.print(suhu);

// Print dengan enter (pindah baris):
Serial.println(" derajat Celcius");

// Print format:
Serial.printf("Suhu: %.1f C, Kelembapan: %.1f %%\n", suhu, kelembapan);
```

**Tips Debugging:**
- Gunakan Serial.println() di berbagai bagian kode untuk tracking
- Print nilai variabel untuk cek apakah logika benar
- Jika program hang, print bisa bantu cari di mana error terjadi

---

## 🔧 BAGIAN 3: PRAKTIKUM 1 - SENSOR DHT11 (30 menit)

### Tujuan:
Membaca data suhu dan kelembapan dari sensor DHT11 dan menampilkannya di Serial Monitor

### Komponen yang Dibutuhkan:
- 1x ESP32
- 1x Sensor DHT11
- 3x Kabel jumper
- 1x Breadboard

### Diagram Koneksi:

```
DHT11        ESP32
=====        =====
VCC   --->   3.3V
DATA  --->   GPIO15
GND   --->   GND
```

**Catatan:**
- Beberapa modul DHT11 punya 4 pin (NC tidak dipakai)
- Pastikan VCC ke 3.3V (bukan 5V untuk ESP32)

### Kode Program:

Lihat file: `kode-04-sensor-dht11.ino`

### Langkah Praktikum:

1. **Rakit rangkaian** sesuai diagram
2. **Buka kode** `kode-04-sensor-dht11.ino` di Arduino IDE
3. **Verify & Upload** ke ESP32
4. **Buka Serial Monitor** (Tools → Serial Monitor)
5. **Set baud rate** ke 115200
6. **Amati data** yang ditampilkan setiap 2 detik

**Yang Harus Terlihat:**
```
===== SENSOR DHT11 =====
Suhu: 28.00 °C
Kelembapan: 65.00 %
========================

===== SENSOR DHT11 =====
Suhu: 28.50 °C
Kelembapan: 66.00 %
========================
```

### Eksperimen:

1. **Tes Sensor Suhu:**
   - Pegang sensor DHT11 dengan tangan
   - Amati suhu naik perlahan
   - Lepas → suhu turun perlahan

2. **Tes Sensor Kelembapan:**
   - Dekatkan DHT11 ke mulut dan embuskan napas
   - Kelembapan akan naik (napas manusia lembap)

3. **Tambahkan LED Indikator:**
   - LED merah nyala jika suhu > 30°C (panas)
   - LED hijau nyala jika suhu 20-30°C (normal)
   - LED biru nyala jika suhu < 20°C (dingin)

---

## 🔧 BAGIAN 4: PRAKTIKUM 2 - SENSOR LDR (30 menit)

### Tujuan:
Membuat lampu otomatis yang menyala saat gelap dan mati saat terang

### Komponen yang Dibutuhkan:
- 1x ESP32
- 1x LDR (Light Dependent Resistor)
- 1x Resistor 10K ohm
- 1x LED
- 1x Resistor 220 ohm
- Kabel jumper
- 1x Breadboard

### Diagram Koneksi:

```
Rangkaian LDR (Voltage Divider):
3.3V
  │
  ├── LDR ────┬──── GPIO34 (Analog Input)
  │           │
  └── 10KΩ ───┴──── GND

Rangkaian LED:
GPIO2 ---> LED (+) ---> Resistor 220Ω ---> GND
```

**Catatan Penting:**
- GPIO34-39 adalah **input only** (hanya bisa analogRead)
- ADC ESP32: 0-4095 (12-bit resolution)
- Gelap = nilai tinggi, Terang = nilai rendah

### Kode Program:

Lihat file: `kode-05-sensor-ldr.ino`

### Langkah Praktikum:

1. **Rakit rangkaian** sesuai diagram
2. **Upload kode** `kode-05-sensor-ldr.ino`
3. **Buka Serial Monitor** (baud 115200)
4. **Amati nilai LDR** dalam berbagai kondisi:
   - Tutup LDR dengan tangan → nilai tinggi
   - Arahkan ke lampu → nilai rendah
   - Kondisi normal → nilai medium

5. **Catat threshold:**
   - Nilai saat ruangan gelap: __________
   - Nilai saat ruangan terang: __________
   - Tentukan threshold (nilai tengah): __________

6. **Sesuaikan threshold di kode** (line sekitar 30):
   ```cpp
   int threshold = 2500;  // Ganti dengan nilai yang sesuai
   ```

7. **Upload ulang** dan test:
   - Tutup LDR → LED nyala
   - Buka → LED mati

### Eksperimen:

1. **Tambahkan Hysteresis:**
   ```cpp
   int thresholdAtas = 3000;   // Nyalakan lampu
   int thresholdBawah = 2500;  // Matikan lampu
   ```

2. **Buat 3 Level Kecerahan (PWM):**
   - Sangat gelap: LED 100% terang
   - Redup: LED 50% terang
   - Terang: LED mati

3. **Kombinasi dengan Button:**
   - Mode AUTO: lampu tergantung LDR
   - Mode MANUAL: lampu bisa dikontrol button

---

## 🔧 BAGIAN 5: PRAKTIKUM 3 - SENSOR PIR (40 menit)

### Tujuan:
Membuat sistem keamanan sederhana: LED dan Buzzer nyala saat terdeteksi gerakan

### Komponen yang Dibutuhkan:
- 1x ESP32
- 1x Sensor PIR
- 1x LED merah
- 1x Active Buzzer
- 1x Resistor 220 ohm
- Kabel jumper
- 1x Breadboard

### Diagram Koneksi:

```
PIR Sensor:
VCC  --->  5V (atau 3.3V)
OUT  --->  GPIO13
GND  --->  GND

LED (Indikator):
GPIO2  --->  LED (+)  --->  Resistor 220Ω  --->  GND

Buzzer (Alarm):
GPIO12  --->  Active Buzzer (+)
GND     --->  Active Buzzer (-)
```

### Kode Program:

Lihat file: `kode-06-sensor-pir.ino`

### Langkah Praktikum:

1. **Rakit rangkaian** sesuai diagram
2. **Atur PIR sensor:**
   - Putar potensiometer **Sensitivity** ke posisi tengah
   - Putar potensiometer **Time Delay** ke posisi minimum (2 detik)

3. **Upload kode** `kode-06-sensor-pir.ino`
4. **Buka Serial Monitor**
5. **Tunggu 30-60 detik** (PIR perlu waktu kalibrasi awal)
6. **Gerakkan tangan** di depan sensor (jarak 1-2 meter)
7. **Amati:**
   - Serial Monitor: "GERAKAN TERDETEKSI!"
   - LED merah nyala
   - Buzzer bunyi
   - Status kembali normal setelah 2 detik

### Eksperimen:

1. **Sistem Keamanan dengan Countdown:**
   - Berikan waktu 10 detik untuk keluar setelah sistem aktif
   - Buzzer beep setiap detik sebagai peringatan
   - Setelah 10 detik, sistem siaga

2. **Lampu Koridor Otomatis:**
   - LED nyala saat ada gerakan
   - LED tetap nyala selama 30 detik
   - Timer reset jika ada gerakan lagi

3. **Counter Orang Masuk:**
   - Hitung berapa kali PIR terdeteksi
   - Tampilkan di Serial Monitor
   - (Catatan: tidak akurat untuk hitung orang, hanya hitung trigger)

4. **Kombinasi DHT11 + PIR:**
   - Sistem hemat energi: AC hanya nyala jika:
     * Ada orang (PIR) DAN
     * Suhu > 28°C

---

## 📝 TUGAS RUMAH

### Tugas 1: Sistem Monitoring Ruangan
Buat sistem yang menampilkan status ruangan di Serial Monitor:
- Suhu dan kelembapan (DHT11)
- Tingkat cahaya (LDR)
- Status kehadiran (PIR)

Format output:
```
=================================
MONITORING RUANGAN
=================================
Suhu         : 28.5 °C
Kelembapan   : 65 %
Cahaya       : Terang (nilai: 1200)
Kehadiran    : Ada Orang
Waktu        : 00:12:45 (gunakan millis)
=================================
```

### Tugas 2: Smart Lighting System
Buat sistem pencahayaan cerdas dengan logika:
- Lampu hanya nyala jika: **GELAP** DAN **ADA ORANG**
- Jika gelap tapi tidak ada orang → lampu mati (hemat energi)
- Jika terang → lampu mati (meskipun ada orang)
- Tampilkan status di Serial Monitor

**Komponen:** DHT11 (optional), LDR, PIR, LED

### Tugas 3: Sistem Ventilasi Otomatis
Buat sistem ventilasi (simulasi dengan LED):
- LED hijau (kipas exhaust) nyala jika kelembapan > 70%
- LED biru (AC) nyala jika suhu > 30°C
- LED merah (alarm) nyala jika suhu > 35°C DAN kelembapan > 80%

**Komponen:** DHT11, 3x LED (merah, hijau, biru)

### Tugas 4: Kreasi Bebas (BONUS)
Buat sistem kombinasi minimal 2 sensor dan 2 output dengan tema:
- Smart bedroom
- Smart toilet
- Smart parking
- Atau kreasi sendiri

**Dokumentasi:**
- Jelaskan konsep dan logika sistem
- Screenshot Serial Monitor
- Foto rangkaian
- Penjelasan threshold yang digunakan

---

## 📚 RANGKUMAN

Hari ini kita telah belajar:

1. ✅ **Konsep Sensor**
   - Sensor sebagai "indera" bangunan cerdas
   - Klasifikasi: Digital vs Analog, Input vs Komunikasi

2. ✅ **Sensor DHT11**
   - Membaca suhu dan kelembapan
   - Menggunakan library DHT
   - Aplikasi: kontrol HVAC, monitoring

3. ✅ **Sensor LDR**
   - Mendeteksi intensitas cahaya
   - Voltage divider circuit
   - Aplikasi: lampu otomatis, hemat energi

4. ✅ **Sensor PIR**
   - Deteksi gerakan/kehadiran
   - Passive infrared (tidak pancarkan sinyal)
   - Aplikasi: keamanan, lampu koridor

5. ✅ **Konsep Penting**
   - Threshold (ambang batas)
   - Hysteresis (dead band)
   - Serial Monitor untuk debugging
   - Kombinasi sensor untuk sistem cerdas

---

## 🔜 PERSIAPAN PERTEMUAN 3

**Materi selanjutnya:** Aktuator & Kontrol Otomatis

**Yang akan dipelajari:**
- Relay untuk kontrol perangkat listrik 220V
- OLED Display untuk menampilkan data
- Buzzer untuk alarm dan notifikasi
- PWM untuk kontrol kecerahan/kecepatan
- Membuat sistem kontrol otomatis lengkap

**Persiapan:**
- Review materi Pertemuan 1 & 2
- Pastikan DHT11, Relay, OLED, Buzzer siap
- Bawa laptop dengan Arduino IDE
- Kerjakan tugas rumah

---

## ❓ FAQ (FREQUENTLY ASKED QUESTIONS)

**Q: Kenapa DHT11 selalu baca "Failed to read"?**
A:
- Cek koneksi: VCC, DATA, GND
- Pastikan pakai pin yang benar (GPIO15 di contoh)
- Tambah delay 2 detik antara pembacaan
- Cek library DHT sudah terinstall
- Coba ganti sensor DHT11 (mungkin rusak)

**Q: Nilai LDR tidak berubah meskipun gelap/terang**
A:
- Pastikan pakai voltage divider (LDR + resistor 10K)
- Cek pin analog (GPIO34-39)
- Test dengan Serial Monitor print nilai mentah
- Resistor 10K, bukan 10 ohm atau 10M

**Q: PIR terus terdeteksi meskipun tidak ada gerakan**
A:
- Tunggu 30-60 detik kalibrasi awal
- Jauhkan dari sumber panas (AC, heater, sinar matahari langsung)
- Putar potensiometer Sensitivity ke posisi minimum
- Pastikan tidak ada objek bergerak (tirai, kipas)

**Q: Serial Monitor tidak muncul data**
A:
- Cek baud rate (harus 115200)
- Pastikan `Serial.begin(115200)` ada di setup()
- Close-open Serial Monitor setelah upload
- Coba kabel USB lain

**Q: Bagaimana cara kalibrasi sensor?**
A:
- **LDR**: Print nilai dalam berbagai kondisi, tentukan threshold
- **DHT11**: Bandingkan dengan termometer akurat, beri offset jika perlu
- **PIR**: Atur potensiometer Sensitivity dan Time Delay

**Q: Apakah bisa baca beberapa sensor sekaligus?**
A: Ya! Contoh:
```cpp
void loop() {
  float suhu = dht.readTemperature();
  int cahaya = analogRead(pinLDR);
  int gerak = digitalRead(pinPIR);

  // Logika berdasarkan semua sensor
  if (gerak == HIGH && cahaya > 3000 && suhu > 28) {
    // Nyalakan AC dan lampu
  }
}
```

---

## 📖 REFERENSI

1. **Datasheet Sensor:**
   - DHT11: https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf
   - PIR: https://www.mpja.com/download/31227sc.pdf

2. **Tutorial:**
   - Random Nerd Tutorials: https://randomnerdtutorials.com/esp32-dht11-dht22-temperature-humidity-sensor-arduino-ide/
   - Last Minute Engineers: https://lastminuteengineers.com

3. **Library:**
   - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library

---

**Sampai jumpa di Pertemuan 3! Jangan lupa kerjakan tugas! 📚**
