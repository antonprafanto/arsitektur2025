# 📋 PANDUAN UJIAN AKHIR
## Mata Kuliah: Bangunan Cerdas - Internet of Things (IoT)

**Dosen:** Anton Prafanto, S.Kom., M.T.  
**Program Studi:** Arsitektur  
**Universitas:** Mulawarman  
**Semester:** Genap 2024/2025

---

## 📖 UNTUK MAHASISWA ARSITEKTUR (WAJIB BACA!)

### Tenang, Anda PASTI Bisa! 🎉

Ujian ini mungkin terlihat menakutkan dengan banyak requirements teknis, tapi **ingat**:

✅ Anda sudah belajar IoT selama **4 pertemuan**  
✅ Anda sudah praktik **SC1-SC5** (Smart Office, Parking, Home, dll)  
✅ Anda punya **kelompok** untuk saling membantu  
✅ Anda **TIDAK perlu** jadi programmer expert!

### 🎯 Yang Sudah Anda Kuasai:

| Skill | Dari Pertemuan | Bukti |
|-------|----------------|-------|
| Wiring sensor di breadboard | Pertemuan 2 | Anda pernah pasang DHT11, LDR, PIR |
| Upload kode ke ESP32 | Pertemuan 1 | LED blink berhasil! |
| Setup Blynk IoT | Pertemuan 4 | SC1-SC5 connect ke app |
| Sistem otomatis | Pertemuan 3 | IF suhu tinggi → AC nyala |

### 💡 Fokus di Ujian Ini:

**BUKAN tentang coding skill**, tapi tentang:

📐 **Integrasi Konsep Arsitektur + IoT**  
→ Bagaimana sensor membuat bangunan lebih nyaman?

🏗️ **Reasoning Penempatan Sensor**  
→ MENGAPA PIR di plafon pintu masuk? (bukan di sudut ruangan)

💰 **Manfaat untuk Pengguna Bangunan**  
→ Hemat energi 35%, kenyamanan meningkat, dll

### 🧠 Mindset yang Benar:

> **"Saya adalah ARSITEK yang paham IoT, bukan programmer yang jadi arsitek."**

Fokus pada:
- ✅ Konsep bangunan cerdas
- ✅ User experience pengguna bangunan  
- ✅ Efisiensi energi & sustainability  
- ❌ BUKAN pada syntax coding yang rumit

### 📚 Butuh Bantuan dengan Istilah Teknis?

**Jika menemukan istilah yang bingung**, buka file ini:
→ [`GLOSSARY-PEMULA.md`](file:///c:/Users/anton/arsi2025/pertemuan-4/GLOSSARY-PEMULA.md)

Glossary menjelaskan istilah coding dengan **analogi kehidupan sehari-hari** dan **analogi arsitektur**.

---

## 🎯 OVERVIEW UJIAN AKHIR

Ujian akhir mata kuliah ini berbentuk **presentasi kelompok** yang mencakup **5 komponen utama**:

1. **3D Maket** (Video/Gambar) - Visualisasi sistem IoT dalam konteks bangunan
2. **Implementasi Breadboard** - Demonstrasi sistem nyata yang berfungsi
3. **Integrasi Blynk** - Platform IoT untuk monitoring dan kontrol
4. **Poster Digital** - Dokumentasi visual sistem secara keseluruhan
5. **Video YouTube** - Penjelasan lengkap sistem dan cara kerja

### �️ Analogi untuk Arsitek:

Bayangkan ujian ini seperti **merancang sistem MEP (Mechanical, Electrical, Plumbing) untuk bangunan**:

| Komponen Ujian | Analogi Arsitektur | Yang Dinilai |
|----------------|-------------------|-------------|
| **3D Maket** | Gambar kerja + RKS | Penjelasan sistem MEP di denah |
| **Breadboard** | Prototype panel listrik | Sistem benar-benar berfungsi |
| **Blynk** | SCADA/BMS gedung | Monitoring & kontrol jarak jauh |
| **Poster A1** | Presentation board | Komunikasi visual untuk klien |
| **Video YouTube** | Video walkthrough | Penjelasan untuk owner/pengguna |

Anda tidak perlu jadi electrical engineer, tapi Anda harus bisa **jelaskan konsep** seperti saat presentasi desain!

### �🎓 Tujuan Pembelajaran:

Mahasiswa mampu **mengintegrasikan konsep arsitektur dengan teknologi IoT** untuk menciptakan prototype bangunan cerdas yang:
- ✅ **Fungsional** (sistem benar-benar jalan)
- ✅ **Efisien energi** (ada perhitungan/estimasi penghematan)
- ✅ **User-friendly** (mudah dimonitor & dikontrol)
- ✅ **Well-documented** (orang lain bisa replicate)

---

## 📋 PERSYARATAN TEKNIS

### 1️⃣ Kompleksitas Minimum Sistem

**Sensor (Input) - Minimal 3:**

> **Sensor = Mata/Telinga/Hidung Bangunan** (mendeteksi kondisi lingkungan)

- **DHT11** → Suhu & Kelembapan (seperti termometer digital di dinding)
- **LDR** → Intensitas Cahaya (seperti sensor cahaya otomatis lampu taman)
- **PIR** → Gerakan/Kehadiran (seperti sensor pintu otomatis di mall)
- Atau kombinasi sensor lain sesuai konsep

**Aktuator/Output - Minimal 3:**

> **Aktuator = Tangan/Kaki Bangunan** (melakukan aksi berdasarkan keputusan)

- **Relay AC** → Kontrol kipas/pendingin (seperti kontaktor di panel listrik gedung)
- **Relay Lampu** → Kontrol pencahayaan
- **Buzzer** → Alarm/notifikasi (seperti bel pintu, alarm kebakaran)
- **LED Indikator** → Status sistem (seperti lampu "KELUAR" hijau)
- **OLED Display** → Tampilan data (seperti display suhu di AC)
- Atau kombinasi output lain sesuai konsep

### 2️⃣ Komponen Hardware yang Tersedia

Sesuai dengan [README.md](file:///c:/Users/anton/arsi2025/README.md#L22-L33):
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

> **💡 Catatan:** Kelompok boleh menambah komponen sendiri jika diperlukan untuk konsep yang lebih kompleks.

### 3️⃣ Software & Platform

**Wajib Menggunakan:**
- Arduino IDE untuk pemrograman ESP32
- **Blynk IoT Platform** untuk monitoring dan kontrol
- YouTube untuk upload video penjelasan

**Library yang Dibutuhkan:**
- WiFi (built-in ESP32)
- Blynk (by Volodymyr Shymanskyy)
- DHT sensor library (by Adafruit)
- Adafruit SSD1306 (untuk OLED)
- Adafruit GFX Library

---

## 🏗️ KOMPONEN UJIAN AKHIR

### 1️⃣ 3D MAKET (25%)

**Format:**
- Video (MP4, maks 10 menit) **ATAU**
- Gambar (PNG/JPG, minimal 3 view berbeda)

**Konten yang Harus Ditampilkan:**
1. **Visualisasi Bangunan/Ruang**
   - Denah/layout ruangan yang jelas
   - Furnitur dan elemen arsitektur
   - Skala dan proporsi yang realistis

2. **Penempatan Sensor**
   - Tunjukkan lokasi **setiap sensor** dengan jelas
   - Berikan label/keterangan
   - Jelaskan **mengapa** ditempatkan di lokasi tersebut

3. **Penempatan Output/Aktuator**
   - Lokasi relay/aktuator yang terhubung (AC, lampu, dll)
   - Zona cakupan (misalnya area yang didinginkan AC)
   - Visual indikator (LED, display, dll)

4. **Alur Kerja Sistem**
   - Diagram/animasi sederhana
   - Contoh: "Jika PIR deteksi gerakan → Lampu ON"
   - Bisa gunakan panah, flowchart, atau animasi

**Software yang Bisa Digunakan:**
- SketchUp (RECOMMENDED untuk arsitektur)
- Blender (lebih advanced)
- Tinkercad (simple & online)
- AutoCAD/Revit (jika mahir)
- Bahkan mockup fisik yang difoto/video

**Kriteria Penilaian:**
- ✅ Kejelasan visualisasi (20%)
- ✅ Penempatan sensor yang logis (30%)
- ✅ Penjelasan alur kerja sistem (30%)
- ✅ Kualitas presentasi visual (20%)

---

### 2️⃣ IMPLEMENTASI BREADBOARD (25%)

**Apa yang Dinilai:**
Sistem IoT yang **benar-benar berfungsi** di breadboard saat presentasi.

**Kriteria Fungsionalitas:**

1. **Koneksi Hardware (20%)**
   - Semua komponen terpasang dengan benar
   - Wiring rapi dan aman
   - Tidak ada short circuit

2. **Pembacaan Sensor (30%)**
   - Minimal 3 sensor berfungsi dengan baik
   - Data sensor akurat dan real-time
   - Ditampilkan di Serial Monitor atau OLED

3. **Kontrol Output (30%)**
   - Minimal 3 aktuator/output berfungsi
   - Respons terhadap kondisi sensor
   - Kontrol manual dari Blynk bekerja

4. **Logika Otomatis (20%)**
   - Sistem merespons input sensor dengan benar
   - Contoh: Suhu tinggi → AC nyala
   - Logika if-else sesuai dengan konsep

**⚠️ PENTING:**
- **TIDAK ada backup plan**: Jika breadboard error saat presentasi, nilai komponen ini akan berkurang.
- **Persiapkan dengan matang**: Test berkali-kali sebelum hari H.
- **Bawa komponen cadangan** jika memungkinkan (sensor/relay backup).

**Tips Keandalan:**
```markdown
✅ Test sistem minimal 3x sebelum presentasi
✅ Solder kabel yang sering lepas
✅ Gunakan breadboard berkualitas baik
✅ Beri label pada setiap kabel
✅ Dokumentasikan wiring dengan foto
```

---

### 3️⃣ INTEGRASI BLYNK IoT (20%)

**Wajib Menggunakan Platform Blynk**

**Fitur Minimum yang Harus Ada:**

1. **Monitoring Real-Time (50%)**
   - Tampilkan data dari minimal 3 sensor
   - Update otomatis (setiap 1-3 detik)
   - Widget yang sesuai:
     - Gauge untuk suhu
     - Value Display untuk kelembapan
     - LED Indicator untuk PIR
     - Chart (opsional, bonus)

2. **Kontrol Manual (50%)**
   - Minimal 2 aktuator bisa dikontrol dari app
   - Menggunakan button/switch widget
   - Sinkronisasi dengan kondisi fisik device

**Setup yang Diperlukan:**

```markdown
1. Buat Blynk Template
   - Name: [Nama Kelompok - Konsep] (Contoh: "Kelompok3-SmartOffice")
   - Hardware: ESP32
   - Connection: WiFi

2. Buat Datastreams (Virtual Pins)
   💡 Datastream = Saluran data (seperti pipa air untuk kirim data)
   💡 Virtual Pin = Nomor saluran (V0, V1, V2, dst)
   
   - V0-V2: Data sensor (suhu, cahaya, PIR)
   - V3-V5: Kontrol aktuator  
   - V6: Status sistem (String)

3. Design Dashboard
   - Mobile Dashboard (wajib) → App di smartphone
   - Web Dashboard (bonus) → Buka di browser
   - Layout yang intuitif dan menarik

4. Test Koneksi
   - ESP32 harus status ONLINE (hijau di app)
   - Data update real-time (setiap 1-3 detik)
   - Kontrol manual responsif (tap button → relay klik)
```

**Kriteria Penilaian:**
- ✅ Device connect ke Blynk (20%)
- ✅ Monitoring sensor berfungsi (40%)
- ✅ Kontrol aktuator berfungsi (30%)
- ✅ Dashboard design menarik (10%)

**Referensi Lengkap:**

Untuk **step-by-step setup Blynk** yang sangat detail (dengan screenshot placeholder), lihat:
→ [SC1-SMART-OFFICE.md bagian "Setup Blynk Cloud"](file:///c:/Users/anton/arsi2025/pertemuan-4/SC1-SMART-OFFICE.md#L152-L255)

📖 **Tips:** Ikuti panduan SC1 dulu untuk latihan, baru buat template sendiri untuk ujian.

---

### 4️⃣ POSTER DIGITAL A1 (15%)

**Format:**
- **Ukuran:** A1 Digital (594 x 841 mm atau 1754 x 2480 px)
- **Format File:** PDF atau PNG (high resolution)
- **Orientasi:** Portrait (tegak)

**Konten yang Harus Ada:**

```markdown
┌─────────────────────────────────┐
│   JUDUL PROYEK & LOGO UNMUL     │
├─────────────────────────────────┤
│   KONSEP & DESKRIPSI SINGKAT    │
├─────────────────────────────────┤
│   3D MAKET/VISUALISASI          │
│   (Screenshot atau render)      │
├─────────────────────────────────┤
│   DIAGRAM SISTEM IoT            │
│   - Input (Sensor)              │
│   - Process (ESP32)             │
│   - Output (Aktuator)           │
├─────────────────────────────────┤
│   WIRING DIAGRAM / SCHEMATIC    │
│   (Gambar koneksi kabel ESP32   │
│    ke sensor & relay)           │
├─────────────────────────────────┤
│   SCREENSHOT BLYNK DASHBOARD    │
├─────────────────────────────────┤
│   MANFAAT & DAMPAK              │
│   - Hemat energi: X%            │
│   - Kenyamanan                  │
│   - Efisiensi                   │
├─────────────────────────────────┤
│   NAMA KELOMPOK & ANGGOTA       │
│   QR Code ke Video YouTube      │
└─────────────────────────────────┘
```

**Tips Design:**
1. **Gunakan Template:** Canva, PowerPoint, atau Adobe Illustrator
2. **Hierarki Visual:** Judul besar, konten jelas, footer kecil
3. **Color Scheme:** Konsisten dengan tema bangunan (housing, office, etc.)
4. **Tipografi:** Maksimal 2-3 jenis font
5. **Whitespace:** Jangan terlalu padat, beri ruang bernafas

**Kriteria Penilaian:**
- ✅ Kelengkapan informasi (40%)
- ✅ Kejelasan diagram (30%)
- ✅ Estetika design (20%)
- ✅ Kreativitas (10%)

---

### 5️⃣ VIDEO YOUTUBE (15%)

**WAJIB:** Upload video penjelasan lengkap ke YouTube

**Spesifikasi Video:**

| Aspek | Requirement |
|-------|-------------|
| **Durasi** | 5-10 menit |
| **Resolusi** | Minimal 720p (HD) |
| **Format** | MP4 (upload ke YouTube) |
| **Bahasa** | Indonesia |
| **Visibility** | Public atau Unlisted |

**Konten yang Harus Dijelaskan:**

**Bagian 1: Intro (1 menit)**
- Salam pembuka
- Judul proyek
- Anggota kelompok
- Konsep singkat

**Bagian 2: Konsep & 3D Maket (2-3 menit)**
- Tampilkan 3D maket
- Jelaskan penempatan sensor & output
- Alur kerja sistem
- Manfaat yang diharapkan

**Bagian 3: Demonstrasi Breadboard (3-4 menit)**
- Tunjukkan hardware yang sudah dirakit
- Demonstrasi sensor (misalnya: tutup LDR → lampu nyala)
- Demonstrasi output/aktuator
- Tunjukkan Serial Monitor/OLED

**Bagian 4: Demonstrasi Blynk (2-3 menit)**
- Buka app Blynk di smartphone
- Tunjukkan data sensor real-time
- Demonstrasi kontrol manual (nyalakan/matikan)
- Tunjukkan sinkronisasi app ↔ hardware

**Bagian 5: Penutup (1 menit)**
- Kesimpulan
- Pembelajaran yang didapat
- Ucapan terima kasih

**Tips Pembuatan Video:**
```markdown
✅ Rekam dengan HP (landscape mode)
✅ Pencahayaan yang cukup
✅ Audio jelas (gunakan mic eksternal jika perlu)
✅ Gunakan tripod atau penyangga HP
✅ Edit dengan CapCut/KineMaster (tambah text, zoom)
✅ Background music lembut (opsional)
✅ Tambah subtitle jika perlu
```

**Kriteria Penilaian:**
- ✅ Kejelasan penjelasan (40%)
- ✅ Demonstrasi sistem berfungsi (30%)
- ✅ Kualitas audio/visual (20%)
- ✅ Kreativitas penyampaian (10%)

**Format Link YouTube:**
Cantumkan di poster dengan:
- QR Code (mudah di-scan)
- Short URL (youtube.com/...)

---

## 📚 PILIHAN STUDI KASUS (SC)

Kelompok **boleh menggunakan atau memodifikasi** salah satu dari 5 studi kasus berikut:

### SC1: Smart Office
- **File:** [SC1-SMART-OFFICE.md](file:///c:/Users/anton/arsi2025/pertemuan-4/SC1-SMART-OFFICE.md)
- **Kode:** `SC1-smart-office.ino`
- **Fokus:** Kantor otomatis (AC, lampu, kehadiran)
- **Sensor:** DHT11, LDR, PIR
- **Output:** Relay AC, Relay Lampu, Buzzer

### SC2: Smart Parking
- **File:** [SC2-SMART-PARKING.md](file:///c:/Users/anton/arsi2025/pertemuan-4/SC2-SMART-PARKING.md)
- **Kode:** `SC2-smart-parking.ino`
- **Fokus:** Parkir pintar dengan monitoring slot
- **Sensor:** Ultrasonic, PIR
- **Output:** LED indikator, OLED, Buzzer

### SC3: Smart Home + OLED
- **File:** [SC3-SMART-HOME-OLED.md](file:///c:/Users/anton/arsi2025/pertemuan-4/SC3-SMART-HOME-OLED.md)
- **Kode:** `SC3-smart-home-oled.ino`
- **Fokus:** Rumah pintar dengan display
- **Sensor:** DHT11, LDR, PIR
- **Output:** Relay, OLED Display, Buzzer

### SC4: Smart Bedroom
- **File:** [SC4-SMART-BEDROOM.md](file:///c:/Users/anton/arsi2025/pertemuan-4/SC4-SMART-BEDROOM.md)
- **Kode:** `SC4-smart-bedroom.ino`
- **Fokus:** Kamar tidur dengan mode otomatis
- **Sensor:** DHT11, LDR, PIR
- **Output:** Relay lampu, Relay kipas, Buzzer

### SC5: Smart Security
- **File:** [SC5-SMART-SECURITY.md](file:///c:/Users/anton/arsi2025/pertemuan-4/SC5-SMART-SECURITY.md)
- **Kode:** `SC5-smart-security.ino`
- **Fokus:** Sistem keamanan dengan alarm
- **Sensor:** PIR, Magnetic Door Sensor
- **Output:** Buzzer, LED, Blynk notification

---

**Modifikasi Diperbolehkan:**
- ✅ Ganti nama/tema (misalnya Smart Classroom)
- ✅ Tambah sensor/output
- ✅ Ubah threshold/logika
- ✅ Improve Blynk dashboard
- ❌ Tidak boleh kurang dari 3 sensor + 3 output

---

## 🎯 RUBRIK PENILAIAN LENGKAP

| No | Komponen | Bobot | Kriteria Detail | Nilai |
|----|----------|-------|----------------|-------|
| **1** | **3D Maket** | **25%** | | |
| 1.1 | Kejelasan Visualisasi | 5% | 3D model jelas, skala proporsional | /5 |
| 1.2 | Penempatan Sensor Logis | 7.5% | Lokasi sensor sesuai fungsi, ada reasoning | /7.5 |
| 1.3 | Alur Kerja Sistem | 7.5% | Diagram/flowchart jelas, mudah dipahami | /7.5 |
| 1.4 | Kualitas Presentasi | 5% | Render bagus, view angle informatif | /5 |
| **2** | **Breadboard** | **25%** | | |
| 2.1 | Koneksi Hardware | 5% | Wiring benar, rapi, aman | /5 |
| 2.2 | Sensor Berfungsi | 7.5% | Minimal 3 sensor baca data akurat | /7.5 |
| 2.3 | Output Berfungsi | 7.5% | Minimal 3 aktuator responsif | /7.5 |
| 2.4 | Logika Otomatis | 5% | Sistem merespons input dengan benar | /5 |
| **3** | **Blynk IoT** | **20%** | | |
| 3.1 | Device Online | 4% | ESP32 connect ke Blynk | /4 |
| 3.2 | Monitoring Sensor | 8% | Data real-time update di app | /8 |
| 3.3 | Kontrol Aktuator | 6% | Manual control dari app berfungsi | /6 |
| 3.4 | Dashboard Design | 2% | UI intuitif dan menarik | /2 |
| **4** | **Poster A1** | **15%** | | |
| 4.1 | Kelengkapan Informasi | 6% | Semua elemen penting ada | /6 |
| 4.2 | Kejelasan Diagram | 4.5% | Wiring & flowchart mudah dibaca | /4.5 |
| 4.3 | Estetika Design | 3% | Layout menarik, color scheme baik | /3 |
| 4.4 | Kreativitas | 1.5% | Unik, tidak copy-paste | /1.5 |
| **5** | **Video YouTube** | **15%** | | |
| 5.1 | Kejelasan Penjelasan | 6% | Narasi jelas, tidak terburu-buru | /6 |
| 5.2 | Demo Sistem Berfungsi | 4.5% | Bukti hardware & Blynk jalan | /4.5 |
| 5.3 | Kualitas Audio/Visual | 3% | Resolusi HD, audio clear | /3 |
| 5.4 | Kreativitas | 1.5% | Editing bagus, engaging | /1.5 |
| **TOTAL** | | **100%** | | **/100** |

---

## 📅 TIMELINE & DEADLINE

⚠️ **WAKTU SANGAT KETAT!** Hanya **18 hari** untuk menyelesaikan semua komponen!

**Tanggal Penting:**
- 📅 **24 November 2024** → Mulai kerja (SEKARANG!)
- 📅 **10 Desember 2024** → Deadline submission (H-2)
- 📅 **12 Desember 2024** → PRESENTASI UJIAN AKHIR

---

### 🗓️ MINGGU 1: Planning & Implementation (24-30 Nov)

**Target:** Konsep jelas + Breadboard mulai jalan

- [ ] **24-25 Nov (Hari 1-2):** PERSIAPAN AWAL
  - [ ] Bentuk kelompok (3-5 orang)
  - [ ] Pilih/modifikasi studi kasus (SC1-SC5)
  - [ ] **KONSULTASI ke dosen** (tentukan konsep!)
  - [ ] Bagi tugas kelompok (siapa coding, siapa 3D, siapa video)

- [ ] **26-28 Nov (Hari 3-5):** MULAI IMPLEMENTASI
  - [ ] Rakit breadboard (minimal 3 sensor + 3 output)
  - [ ] Upload & test kode ESP32 (pakai SC1-5 sebagai base)
  - [ ] Sketch 3D maket (rough draft di kertas/SketchUp)
  - [ ] Setup Blynk template & datastream

- [ ] **29-30 Nov (Hari 6-7):** TESTING AWAL
  - [ ] Test setiap sensor berfungsi
  - [ ] Test setiap output berfungsi
  - [ ] ESP32 connect ke Blynk (cek status ONLINE)
  - [ ] Dokumentasi (foto breadboard, screenshot Blynk)

---

### 🗓️ MINGGU 2: Integration & Content Creation (1-7 Des)

**Target:** Sistem terintegrasi + Konten (3D, poster, video) mulai dibuat

- [ ] **1-2 Des (Hari 8-9):** INTEGRASI PENUH
  - [ ] Logika otomatis berfungsi (IF sensor → THEN aktuator)
  - [ ] Kontrol manual dari Blynk berfungsi
  - [ ] Test sistem end-to-end minimal 3x
  - [ ] Perbaiki bug/error

- [ ] **3-5 Des (Hari 10-12):** BUAT KONTEN
  - [ ] 3D maket finalisasi (render/video walkthrough)
  - [ ] Buat draft poster A1 (gunakan template Canva/PPT)
  - [ ] Rekam video demonstrasi (breadboard + Blynk)
  - [ ] **KONSULTASI ke dosen** (tunjukkan progress!)

- [ ] **6-7 Des (Hari 13-14):** REFINEMENT
  - [ ] Edit video (tambah text, zoom, background music)
  - [ ] Finalisasi poster (cek kelengkapan: wiring diagram, manfaat, QR code)
  - [ ] Upload video ke YouTube

---

### 🗓️ MINGGU 3: Finalisasi & Submission (8-10 Des)

**Target:** Submit H-2 + Siap presentasi

- [ ] **8-9 Des (Hari 15-16):** PERSIAPAN SUBMISSION
  - [ ] Compile semua file sesuai format submisi
  - [ ] Cek checklist: 3D maket ✓, kode ✓, poster ✓, video ✓, dokumentasi ✓
  - [ ] Test breadboard FINAL (pastikan semua berfungsi!)
  - [ ] Buat catatan kelompok (pembagian tugas)

- [ ] **10 Des (Hari 17):** DEADLINE SUBMISSION ⏰
  - [ ] **Submit semua file ke Google Drive/Email** (sebelum jam 23:59!)
  - [ ] Konfirmasi dosen sudah terima
  - [ ] Backup semua file (cloud + flashdisk)

---

### 📍 HARI PRESENTASI: 12 Desember 2024

**Persiapan Sehari Sebelumnya (11 Des):**
- [ ] Rehearsal presentasi (minimal 2x, time it: max 10 menit)
- [ ] Test breadboard sekali lagi
- [ ] Charge laptop, power bank, HP
- [ ] Siapkan hotspot HP (jangan andalkan WiFi kampus!)
- [ ] Print/siapkan backup (kode, diagram) jika diperlukan

**Hari H (12 Des):**
- ⏰ **Datang 30 menit lebih awal**
- 🔌 Setup breadboard & test koneksi
- 📱 Buka Blynk app & pastikan ONLINE
- 🎤 **Presentasi 15 menit:** Demo + Q&A
- 🎉 SELESAI!

---

### ⚠️ PERINGATAN PENTING

```
🚨 TIMELINE SANGAT KETAT!
- Jangan tunda pekerjaan ke minggu terakhir
- Mulai SEKARANG (24 Nov)
- Konsultasi dosen di minggu pertama (validasi konsep)
- Testing breadboard berkali-kali (jangan sampai error saat presentasi)
- Submit H-2 (10 Des), JANGAN mepet H-1!
```

**Tips Survival:**
- ✅ Kerja paralel: Coding + 3D maket + Poster bisa dikerjakan bersamaan oleh anggota berbeda
- ✅ Manfaatkan SC1-SC5: Jangan mulai dari nol, modifikasi kode yang sudah ada
- ✅ Daily standup: Meet kelompok setiap hari (15 menit) untuk update progress
- ✅ Buffer time: Selalu kasih buffer 1-2 hari untuk handling error

---

## 📦 FORMAT SUBMISI

**Deadline:** **10 Desember 2024** (H-2 sebelum presentasi)

**Submit ke:** [Google Drive/WhatsApp akan diinformasikan]

### File yang Dikumpulkan:

```
[KELOMPOK-XX]_UjianAkhir/
│
├── 1_3D-MAKET/
│   ├── maket.mp4 (video) ATAU
│   ├── maket-view1.png
│   ├── maket-view2.png
│   └── maket-view3.png
│
├── 2_KODE-PROGRAM/
│   ├── [nama-kelompok].ino
│   ├── wiring-diagram.png
│   └── README.txt (kredensial Blynk, PIN mapping)
│
├── 3_POSTER/
│   └── poster-A1.pdf (atau .png high-res)
│
├── 4_VIDEO/
│   └── youtube-link.txt (link ke video YouTube)
│
└── 5_DOKUMENTASI/
    ├── foto-breadboard.jpg
    ├── screenshot-blynk.png
    └── CATATAN-KELOMPOK.txt (anggota, pembagian tugas)
```

**Penamaan Folder:**
```
Format: KELOMPOK-[Nomor]_[NamaKonsep]
Contoh: KELOMPOK-03_SmartOffice
```

---

## 🎤 FORMAT PRESENTASI (15 Menit)

### Pembagian Waktu:

| Tahap | Durasi | Konten |
|-------|--------|--------|
Ready | 2 menit | Setup breadboard & buka Blynk app |
| **Presentasi** | **10 menit** | |
| Intro | 1 menit | Perkenalan & konsep |
| 3D Maket | 2 menit | Tunjukkan visualisasi & penempatan sensor |
| Demo Breadboard | 3 menit | Demonstrasi sensor & output bekerja |
| Demo Blynk | 2 menit | Monitoring & kontrol via app |
| Poster | 1 menit | Highlight poster & manfaat sistem |
| Penutup | 1 menit | Kesimpulan & pembelajaran |
| **Q&A** | **3 menit** | Tanya jawab dosen |
| **TOTAL** | **15 menit** | |

### Checklist Hari Presentasi:

**Hardware:**
- [ ] ESP32 + Breadboard lengkap
- [ ] Kabel USB & Laptop
- [ ] Charger/Power Bank
- [ ] Komponen cadangan (jika ada)

**Software:**
- [ ] Blynk app sudah login
- [ ] Video YouTube siap diputar (backup offline juga)
- [ ] Poster digital (PDF di laptop)

**Presentasi:**
- [ ] Semua anggota hadir
- [ ] Pembagian tugas presentasi jelas
- [ ] Sudah rehearsal minimal 2x

**⚠️ PENTING:**
- Datang **30 menit** sebelum jadwal untuk setup
- Test koneksi WiFi/hotspot di lokasi presentasi
- Jika WiFi tidak stabil, siapkan hotspot HP sebagai backup

---

## 💡 TIPS SUKSES

### 1. Planning yang Matang
```markdown
✅ Mulai dari sekarang, jangan tunggu H-7
✅ Bagi tugas kelompok dengan jelas
✅ Pakai project management (Trello/Google Sheets)
✅ Meet rutin minimal 2x seminggu
```

### 2. Pilih Studi Kasus yang Tepat
```markdown
✅ Sesuaikan dengan keahlian kelompok
✅ Jika baru belajar: Pakai SC1/SC3 (paling sederhana)
✅ Jika sudah mahir: Modifikasi atau buat custom
✅ Konsultasi dosen sebelum finalisasi konsep
```

### 3. Testing Berulang
```markdown
✅ Test setiap komponen secara terpisah dulu
✅ Baru integrasikan semua
✅ Buat checklist testing (sensor A ✓, relay B ✓, etc.)
✅ Record hasil testing dalam video
```

### 4. Dokumentasi Lengkap
```markdown
✅ Foto/video setiap tahap (bisa jadi konten YouTube)
✅ Catat error & solusi (bisa jadi pembelajaran)
✅ Simpan versi kode sebelumnya (backup!)
✅ Dokumentasi = penyelamat jika ada pertanyaan
```

### 5. Presentasi yang Menarik
```markdown
✅ Berlatih presenter confidence
✅ Gunakan analogi arsitektur (bukan jargon teknis)
✅ Fokus pada MANFAAT, bukan hanya fitur
✅ Siapkan jawaban untuk pertanyaan umum
```

---

## ❓ FAQ (Frequently Asked Questions)

### Q1: Bolehkah menggunakan sensor/komponen di luar daftar README?
**A:** Boleh, asal tetap memenuhi minimal 3 sensor + 3 output. Tapi harus beli/sediakan sendiri.

---

### Q2: Apakah boleh konsep tidak sama persis dengan SC1-SC5?
**A:** Sangat boleh! Malah dianjurkan untuk kreativitas. SC1-SC5 hanya referensi.

---

### Q3: Jika breadboard error saat presentasi, apa yang harus dilakukan?
**A:** Tetap presentasikan video YouTube sebagai backup. Nilai breadboard akan berkurang, tapi masih bisa dapat nilai dari komponen lain. Oleh karena itu, **testing berkali-kali sebelum hari H!**

---

### Q4: Apakah video YouTube boleh unlisted (tidak public)?
**A:** Boleh unlisted (hanya orang dengan link yang bisa akses). Yang penting link bisa dibuka saat presentasi.

---

### Q5: Berapa orang ideal dalam 1 kelompok?
**A:** 3-5 orang. Jangan terlalu banyak (susah koordinasi) atau terlalu sedikit (beban berat).

---

### Q6: Apakah wajib pakai WiFi kampus saat presentasi?
**A:** Tidak wajib. Lebih baik pakai hotspot HP sendiri untuk stabilitas.

---

### Q7: Bolehkah pakai ESP8266 instead of ESP32?
**A:** Sebaiknya ESP32 sesuai materi. Tapi jika terpaksa (ESP32 rusak), boleh ESP8266 dengan persetujuan dosen.

---

### Q8: Apakah poster harus dicetak atau digital saja?
**A:** Cukup digital (PDF/PNG). Akan ditampilkan via proyektor saat presentasi.

---

### Q9: Jika anggota kelompok ada yang tidak kontribusi, bagaimana?
**A:** Cantumkan pembagian tugas di file `CATATAN-KELOMPOK.txt`. Dosen akan evaluasi kontribusi individu saat Q&A.

---

### Q10: Apakah ada konsultasi dengan dosen sebelum presentasi?
**A:** Ada! Manfaatkan waktu pertemuan 4 atau via WhatsApp (0811553393). **Sangat dianjurkan konsultasi konsep di 24-25 Nov** (hari pertama, untuk validasi konsep).

---

### Q11: Saya tidak punya laptop untuk rendering 3D, bagaimana?
**A:** 3D maket bisa dibuat dengan cara alternatif:
1. ✅ Pakai **SketchUp Web** (gratis, online, tidak perlu laptop kuat)
2. ✅ Pakai HP dengan app **"Planner 5D"** (gratis di PlayStore)
3. ✅ Buat **mockup fisik** dari kardus lalu foto/video (BOLEH!)
4. ✅ Pinjam laptop teman kelompok

Yang dinilai: **Kejelasan konsep**, bukan kualitas rendering profesional.

---

### Q12: Bagaimana jika saya masih belum paham coding sama sekali?
**A:** TIDAK MASALAH! Anda bisa:
1. ✅ Pakai kode **SC1-SC5** yang sudah ada (tinggal modifikasi WiFi & Blynk Token)
2. ✅ Fokus pada **konsep arsitektur**, biarkan teman kelompok handle coding
3. ✅ Tugas Anda: Jelaskan **MENGAPA** sensor di lokasi tertentu (ini skill arsitek!)
4. ✅ Di presentasi, jelaskan **manfaat untuk pengguna bangunan** (bukan teknis coding)

**Pembagian tugas kelompok yang baik:**
- 1-2 orang: Coding & breadboard (yang suka teknis)
- 1-2 orang: 3D maket & poster (yang jago design)
- 1 orang: Video editing & koordinasi

---

### Q13: Breadboard saya sering error, apa yang salah?
**A:** 90% masalah breadboard karena:
1. **Kabel lepas** → Solusi: Tekan kencang atau solder
2. **Relay tidak dapat 5V** → Harus dari VIN atau power supply terpisah (bukan 3.3V!)
3. **DHT11 butuh delay 2 detik** → Tunggu setelah power ON
4. **PIR belum kalibrasi** → Diamkan 30-60 detik, jangan gerak dulu
5. **Short circuit** (hubungan pendek) → Periksa kabel + dan - tidak ketemu

Lihat bagian **TROUBLESHOOTING** di SC1-SMART-OFFICE.md untuk detail lebih lengkap.

---

## 📞 KONTAK & BANTUAN

**Konsultasi:**
- **WhatsApp:** 0811553393 (untuk pertanyaan & konsultasi)
- **Office Hour:** Setiap Jumat, 13:00-15:00 WIB
- **WhatsApp Grup:** [Link akan dibagikan di kelas]

**Referensi Tambahan:**
- Materi Lengkap: [README.md](file:///c:/Users/anton/arsi2025/README.md)
- Studi Kasus: Folder `pertemuan-4/SC1-SC5`
- Troubleshooting: `panduan-umum/FAQ-TROUBLESHOOTING.md`
- Blynk Docs: https://docs.blynk.io

---

## 🎓 KATA PENUTUP

Ujian akhir ini dirancang untuk mengintegrasikan semua pembelajaran selama 4 pertemuan ke dalam satu proyek yang mencerminkan aplikasi nyata **Smart Building**. 

**Fokuslah pada:**
1. Konsep arsitektur yang kuat (WHY sensor di lokasi ini?)
2. Implementasi teknis yang berfungsi (DOES it work?)
3. Dokumentasi yang lengkap (CAN others replicate it?)
4. Presentasi yang engaging (DO people understand it?)

> **"Smart Building is not just about technology, it's about creating better, more efficient, and sustainable spaces for people."**

Jangan ragu untuk bereksperimen, bertanya, dan belajar dari error. Ini adalah kesempatan Anda untuk menunjukkan bahwa **Arsitektur + IoT = Masa Depan Bangunan**.

Selamat mengerjakan dan semoga sukses! 🚀

---

**Dokumen ini dibuat:** November 2025  
**Versi:** 1.0  
**Last Updated:** 2025-11-24

---

## 📊 CHECKLIST KELOMPOK

> Print/copy checklist ini untuk tracking progress kelompok

```markdown
KELOMPOK: _____________  KONSEP: _____________

🚨 DEADLINE: 10 Desember 2024 | PRESENTASI: 12 Desember 2024

[ ] MINGGU 1 (24-30 Nov): Planning & Implementation
    [ ] 24-25 Nov: Kelompok terbentuk + konsep dipilih
    [ ] 25 Nov: KONSULTASI dosen (validasi konsep)
    [ ] 26-28 Nov: Breadboard dirakit + kode diupload
    [ ] 29-30 Nov: Testing awal (sensor & output berfungsi)
    [ ] 30 Nov: Blynk connect (status ONLINE)
    
[ ] MINGGU 2 (1-7 Des): Integration & Content
    [ ] 1-2 Des: Sistem terintegrasi penuh (logika otomatis jalan)
    [ ] 3-5 Des: 3D maket dibuat + Poster draft + Video rekam
    [ ] 4 Des: KONSULTASI dosen (tunjukkan progress)
    [ ] 6-7 Des: Edit video + finalisasi poster + upload YouTube
    
[ ] MINGGU 3 (8-10 Des): Finalisasi & Submission
    [ ] 8-9 Des: Compile semua file + test breadboard FINAL
    [ ] 10 Des (23:59): SUBMIT semua file ✅
    [ ] 10 Des: Konfirmasi dosen terima submission
    
[ ] HARI H (11-12 Des): Presentasi
    [ ] 11 Des: Rehearsal 2x + charge semua device + backup
    [ ] 12 Des: Datang 30 menit lebih awal
    [ ] 12 Des: Setup breadboard & test koneksi
    [ ] 12 Des: PRESENTASI 15 menit 🎤
    [ ] 🎉 SELESAI!

⚠️ TIPS: Jangan tunda! Mulai SEKARANG (24 Nov)!
```

**Good Luck! 🎉**

