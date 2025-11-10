# 📚 MATERI MATA KULIAH BANGUNAN CERDAS
## Internet of Things (IoT) untuk Arsitektur

**Dosen:** Anton Prafanto, S.T., M.T.
**Program Studi:** Teknik Informatika
**Universitas:** Mulawarman
**Target:** Mahasiswa Arsitektur (Tanpa Latar Belakang Pemrograman)

---

## 📖 DESKRIPSI MATA KULIAH

Mata kuliah ini dirancang khusus untuk mahasiswa Arsitektur yang ingin mempelajari konsep **Smart Building** menggunakan teknologi **Internet of Things (IoT)**. Materi disusun dari dasar hingga mahasiswa mampu membuat **maket rumah pintar** yang terintegrasi dengan sensor dan aktuator.

### 🎯 Tujuan Pembelajaran:
- Memahami konsep IoT dan aplikasinya dalam bangunan cerdas
- Mampu memprogram ESP32 untuk membaca sensor dan mengontrol aktuator
- Membuat sistem otomatis berbasis kondisi lingkungan (suhu, cahaya, gerakan)
- Mengintegrasikan multiple sensor dan aktuator dalam satu sistem
- Membuat prototype maket bangunan cerdas

### 📦 Hardware yang Digunakan:
- 1x ESP32 Development Kit
- 1x OLED 0.96 inch Display
- 1x DHT11 (Sensor Suhu & Kelembapan)
- 1x Sensor PIR (Deteksi Gerakan)
- 1x Sensor LDR (Intensitas Cahaya)
- 1x Relay 2 Channel
- 1x Active Buzzer & Passive Buzzer
- 5x LED (Merah, Kuning, Hijau, RGB)
- 5x Push Button
- 1x Breadboard 830 Point
- Kabel Jumper & Resistor Lengkap

---

## 📂 STRUKTUR MATERI

```
arsi2025/
├── README.md                          (File ini)
│
├── pertemuan-1/                       ✅ LENGKAP
│   ├── MATERI-PERTEMUAN-1.md          (Pengenalan IoT & ESP32)
│   ├── kode-01-led-blink.ino          (Hello World IoT)
│   ├── kode-02-button-led-langsung.ino (Kontrol Langsung)
│   ├── kode-03-button-led-toggle.ino  (Toggle ON/OFF)
│   ├── tugas-01-lampu-lalu-lintas.ino (Solusi Tugas 1)
│   ├── tugas-02-button-3-mode.ino     (Solusi Tugas 2)
│   └── tugas-03-sistem-voting.ino     (Solusi Tugas 3)
│
├── pertemuan-2/                       ✅ LENGKAP
│   ├── MATERI-PERTEMUAN-2.md          (Sensor Monitoring)
│   ├── kode-04-sensor-dht11.ino       (Suhu & Kelembapan)
│   ├── kode-05-sensor-ldr.ino         (Sensor Cahaya)
│   ├── kode-06-sensor-pir.ino         (Sensor Gerak)
│   ├── tugas-01-monitoring-ruangan.ino (Solusi Tugas 1)
│   ├── tugas-02-smart-lighting.ino    (Solusi Tugas 2)
│   ├── tugas-03-ventilasi-otomatis.ino (Solusi Tugas 3)
│   └── tugas-04-smart-bedroom.ino     (Solusi Tugas 4)
│
├── pertemuan-3/                       ✅ LENGKAP
│   ├── MATERI-PERTEMUAN-3.md          (Aktuator & Kontrol)
│   ├── kode-07-relay-dht11.ino        (Relay + DHT11)
│   ├── kode-08-oled-display.ino       (OLED Display)
│   ├── kode-09-sistem-smart-room.ino  (Sistem Terintegrasi)
│   ├── tugas-01-smart-parking.ino     (Solusi Tugas 1)
│   ├── tugas-02-smart-greenhouse.ino  (Solusi Tugas 2)
│   └── tugas-03-template-proyek.md    (Template Proyek Akhir)
│
├── pertemuan-4/                       ✅ LENGKAP
│   ├── MATERI-PERTEMUAN-4.md          (Platform IoT & Konsep Proyek)
│   ├── kode-10-blynk-led-control.ino  (Kontrol LED via Blynk)
│   ├── kode-11-blynk-monitor-suhu.ino (Monitoring DHT11 via App)
│   ├── kode-12-blynk-smart-home.ino   (Smart Home + Blynk)
│   ├── kode-13-blynk-wifi-reconnect.ino (WiFi & Blynk Reconnect)
│   ├── tugas-01-blynk-smart-room.ino  (Solusi Tugas 1)
│   └── tugas-02-blynk-notifikasi.ino  (Solusi Tugas 2)
│
├── panduan-umum/                      ✅ LENGKAP
│   ├── CHEAT-SHEET-ARDUINO.md         (Quick Reference)
│   └── FAQ-TROUBLESHOOTING.md         (Solusi Masalah Umum)
│
├── dokumentasi/                       📚 Dokumentasi Proyek
│   ├── AUDIT-LENGKAP.md               (Audit pertama)
│   ├── AUDIT-FINAL-LENGKAP.md         (Audit kedua)
│   └── AUDIT-KETIGA-FINAL.md          (Audit final - lengkap)
│
└── tasks/                             📋 Project Management
    └── todo.md                        (Progress & review lengkap)
```

---

## 📅 SILABUS 4 PERTEMUAN

### **Pertemuan 1: Pengenalan IoT & Bangunan Cerdas** (3 SKS)
**Topik:**
- Konsep dasar IoT dan Smart Building
- Pengenalan ESP32 dan komponen elektronik
- Setup Arduino IDE & driver
- Praktikum: LED Blink & Push Button

**Output:** Mahasiswa bisa menyalakan LED dan kontrol dengan button

---

### **Pertemuan 2: Sensor untuk Monitoring Lingkungan** (3 SKS)
**Topik:**
- Jenis-jenis sensor dalam bangunan cerdas
- DHT11 (Suhu & Kelembapan)
- LDR (Intensitas Cahaya)
- PIR (Deteksi Gerakan)
- Praktikum: Membaca dan menggunakan sensor

**Output:** Mahasiswa bisa membaca data sensor dan membuat respons sederhana

---

### **Pertemuan 3: Aktuator & Kontrol Otomatis** (3 SKS)
**Topik:**
- Relay untuk kontrol perangkat listrik
- OLED Display untuk menampilkan data
- Buzzer untuk notifikasi
- Praktikum: Sistem kontrol otomatis

**Output:** Mahasiswa bisa membuat sistem yang merespon sensor dengan aktuator

---

### **Pertemuan 4: IoT Cloud Platform & Konsep Proyek Akhir** (3 SKS)
**Topik:**
- Platform IoT Cloud (Blynk)
- Remote monitoring via smartphone
- Push notification dan alert system
- Panduan video demonstrasi & poster konsep
- Konsultasi proyek kelompok

**Output:** Mahasiswa bisa kontrol sistem via smartphone + membuat video demonstrasi & poster konsep bangunan cerdas

---

## 🚀 CARA MENGGUNAKAN MATERI INI

### Untuk Mahasiswa:

1. **Persiapan Awal:**
   - Install Arduino IDE (https://arduino.cc/en/software)
   - Install driver ESP32 (CH340 atau CP2102)
   - Siapkan semua komponen hardware

2. **Ikuti Urutan Pertemuan:**
   - Mulai dari Pertemuan 1
   - Baca materi di file `.md`
   - Praktikkan kode program di file `.ino`
   - Kerjakan tugas di setiap pertemuan

3. **Gunakan Panduan Pendukung:**
   - **Cheat Sheet** saat coding
   - **FAQ** saat ada masalah

4. **Proyek Akhir:**
   - Bentuk kelompok (3-5 orang)
   - Pilih tema (smart home, smart office, dll)
   - Ikuti panduan di Pertemuan 4

### Untuk Dosen/Pengajar:

1. **Persiapan Mengajar:**
   - Baca materi pertemuan terkait
   - Siapkan demo hardware (test sebelumnya)
   - Print/share materi ke mahasiswa

2. **Delivery:**
   - 30-40% teori (penjelasan konsep)
   - 60-70% praktikum (hands-on)
   - Bantu troubleshooting mahasiswa

3. **Penilaian:**
   - Lihat kriteria di Pertemuan 4
   - Fokus pada fungsionalitas (70%)
   - Kreativitas & dokumentasi (30%)

---

## 💡 FITUR MATERI

### ✅ Bahasa Indonesia yang Mudah Dipahami
- Tidak menggunakan jargon teknis berlebihan
- Penjelasan dengan analogi arsitektur
- Komentar kode sangat detail (setiap baris)

### ✅ Pembelajaran Progresif
- Dimulai dari sangat dasar (LED Blink)
- Bertahap menuju kompleks (Sistem Terintegrasi)
- Setiap konsep dijelaskan sebelum praktik

### ✅ Kode Program Siap Pakai
- 13 file kode praktikum `.ino` lengkap (termasuk 4 materi Blynk IoT)
- 12 file solusi tugas (11 `.ino` + 1 template `.md`)
- Bisa langsung di-upload ke ESP32
- Banyak komentar dan penjelasan
- Troubleshooting di setiap kode

### ✅ Aplikasi Real-World
- Setiap sensor dijelaskan aplikasinya di bangunan
- Contoh kasus nyata (hotel, kantor, rumah)
- Perhitungan hemat energi
- Tips instalasi praktis

### ✅ Troubleshooting Lengkap
- FAQ untuk setiap masalah umum
- Screenshot/contoh kasus
- Solusi step-by-step
- Tips debug

---

## 🎓 LEARNING OUTCOMES

Setelah menyelesaikan mata kuliah ini, mahasiswa akan mampu:

1. ✅ **Memahami Konsep IoT:**
   - Definisi dan komponen IoT
   - Aplikasi IoT dalam smart building
   - Sensor, processor, aktuator, connectivity

2. ✅ **Memprogram ESP32:**
   - Setup Arduino IDE
   - Struktur program (setup & loop)
   - Digital I/O, Analog I/O
   - Serial communication

3. ✅ **Menggunakan Sensor:**
   - DHT11: Membaca suhu & kelembapan
   - LDR: Mendeteksi intensitas cahaya
   - PIR: Mendeteksi gerakan manusia

4. ✅ **Mengontrol Aktuator:**
   - Relay untuk perangkat AC
   - OLED Display untuk UI
   - Buzzer untuk notifikasi audio

5. ✅ **Membuat Sistem Otomatis:**
   - Logika if-else berbasis sensor
   - Threshold dan hysteresis
   - Integrasi multi-sensor
   - Error handling

6. ✅ **Project Management:**
   - Kerja tim (kelompok)
   - Dokumentasi teknis
   - Presentasi dan demo
   - Troubleshooting

---

## 📊 STATISTIK MATERI

| Aspek | Jumlah |
|-------|--------|
| **Total File** | 33 file |
| **Materi Pertemuan** | 4 pertemuan |
| **Kode Praktikum** | 13 file `.ino` (termasuk 4 materi Blynk) |
| **Solusi Tugas** | 12 file (11 `.ino` + 1 template `.md`) |
| **Panduan Pendukung** | 2 file (Cheat Sheet + FAQ) |
| **Total Baris Kode + Dokumentasi** | ~12,500+ baris |
| **Bahasa** | Indonesia 100% |
| **Lisensi** | Open untuk pendidikan |

---

## 🛠️ INSTALASI & SETUP

### 1. Install Arduino IDE
1. Download dari: https://www.arduino.cc/en/software
2. Install seperti aplikasi biasa
3. Buka Arduino IDE

### 2. Install Board ESP32
1. `File` → `Preferences`
2. Tambahkan URL ini di "Additional Board Manager URLs":
   ```
   https://dl.espressif.com/dl/package_esp32_index.json
   ```
3. `Tools` → `Board` → `Boards Manager`
4. Cari "esp32" dan install "ESP32 by Espressif Systems"

### 3. Install Library
Dari `Sketch` → `Include Library` → `Manage Libraries`, install:
- **DHT sensor library** (by Adafruit)
- **Adafruit Unified Sensor**
- **Adafruit SSD1306**
- **Adafruit GFX Library**
- **Blynk** (by Volodymyr Shymanskyy) - untuk Pertemuan 4

### 4. Install Driver USB
- **CH340:** https://sparks.gogo.co.nz/ch340.html
- **CP2102:** https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers

### 5. Test Upload
1. Hubungkan ESP32 ke komputer
2. Pilih Board: `Tools` → `Board` → `ESP32 Dev Module`
3. Pilih Port: `Tools` → `Port` → (pilih COM yang muncul)
4. Upload kode sederhana (LED Blink)
5. Jika berhasil → Setup selesai!

---

## 🤝 KONTRIBUSI

Materi ini dikembangkan untuk membantu mahasiswa Arsitektur memahami IoT tanpa latar belakang pemrograman.

**Jika Anda menemukan:**
- Typo atau kesalahan
- Kode yang tidak berfungsi
- Penjelasan yang kurang jelas
- Ide improvement

Silakan laporkan ke dosen atau buat issue di repository ini.

---

## 📞 KONTAK & BANTUAN

**Dosen Pengampu:**
- Nama: Anton Prafanto, S.T., M.T.
- Prodi: Teknik Informatika
- Universitas: Mulawarman

**Sumber Belajar Tambahan:**
- Arduino Forum: https://forum.arduino.cc
- Random Nerd Tutorials: https://randomnerdtutorials.com
- ESP32 Official: https://docs.espressif.com

---

## 📄 LISENSI

Materi ini dibuat untuk keperluan pendidikan dan dapat digunakan secara bebas untuk:
- Pembelajaran di institusi pendidikan
- Workshop dan pelatihan non-profit
- Referensi pribadi

Untuk penggunaan komersial, mohon hubungi dosen pengampu.

---

## 🎉 KATA PENUTUP

Selamat belajar! IoT dan Smart Building adalah bidang yang sangat menarik dan terus berkembang. Dengan menguasai dasar-dasar ini, Anda sebagai mahasiswa Arsitektur akan memiliki nilai tambah dalam merancang bangunan modern yang cerdas, efisien, dan nyaman.

> **"The future of architecture is smart, connected, and sustainable."**

Jangan ragu untuk bertanya dan bereksperimen. Kesalahan adalah bagian dari pembelajaran!

Selamat berkarya! 🚀

---

**Last Updated:** 2025
**Version:** 1.0
**Status:** ✅ Complete
