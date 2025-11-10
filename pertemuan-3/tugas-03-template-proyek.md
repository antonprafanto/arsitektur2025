# TEMPLATE PROYEK AKHIR: KONSEP BANGUNAN CERDAS
**Mata Kuliah: Bangunan Cerdas (IoT untuk Arsitektur)**

---

## 📋 INFORMASI KELOMPOK

### Nama Proyek:
_______________________________

### Anggota Kelompok:
1. _______________________________ (NPM: _____________)
2. _______________________________ (NPM: _____________)
3. _______________________________ (NPM: _____________)
4. _______________________________ (NPM: _____________) *opsional*
5. _______________________________ (NPM: _____________) *opsional*

---

## 🏢 KONSEP BANGUNAN CERDAS

### Tema Proyek:
- [ ] Smart Home (Rumah Tinggal)
- [ ] Smart Office (Kantor)
- [ ] Smart Hotel Room (Kamar Hotel)
- [ ] Smart Classroom (Ruang Kelas)
- [ ] Smart Greenhouse (Rumah Kaca)
- [ ] Smart Parking (Area Parkir)
- [ ] Lainnya: _______________________

### Deskripsi Konsep (3-5 kalimat):
Jelaskan bangunan yang akan dibuat, fungsinya, dan mengapa perlu teknologi IoT.

Contoh:
"Kami merancang Smart Office untuk 10 orang dengan 2 zona: Open Space dan Meeting Room.
Sistem IoT digunakan untuk menghemat energi dengan kontrol otomatis AC dan lampu
berdasarkan kehadiran dan kondisi ruangan. Estimasi penghematan energi 30-40%
dibanding office konvensional."

**Konsep Anda:**

_________________________________________________
_________________________________________________
_________________________________________________
_________________________________________________
_________________________________________________

---

## 🏗️ DENAH BANGUNAN & ZONA IoT

### Denah Sederhana:
(Gambar denah dengan zona-zona yang akan diintegrasikan dengan IoT)

**Zona 1:** _____________________ (Fungsi: __________________)
- Sensor yang digunakan: _______________________
- Output yang dikontrol: _______________________

**Zona 2:** _____________________ (Fungsi: __________________)
- Sensor yang digunakan: _______________________
- Output yang dikontrol: _______________________

**Zona 3:** _____________________ (Fungsi: __________________) *opsional*
- Sensor yang digunakan: _______________________
- Output yang dikontrol: _______________________

---

## 🔧 KOMPONEN IoT (Breadboard/Modul Terpisah)

### Sensor yang Digunakan (minimal 2):
- [ ] DHT11 (Suhu & Kelembapan) - untuk kontrol AC/ventilasi
- [ ] LDR (Cahaya) - untuk kontrol lampu otomatis
- [ ] PIR (Gerakan) - untuk deteksi kehadiran
- [ ] Lainnya: _______________________

### Output/Aktuator yang Digunakan (minimal 2):
- [ ] Relay (untuk kontrol Lampu/AC/Fan)
- [ ] OLED Display (untuk tampilan status lokal)
- [ ] Buzzer (untuk alarm/notifikasi)
- [ ] LED Indikator (status sistem)
- [ ] Lainnya: _______________________

### Platform IoT:
- [ ] Blynk (Smartphone App) - **WAJIB**
- [ ] Serial Monitor (untuk debugging)
- [ ] OLED Display (untuk status lokal)

---

## 🧠 LOGIKA SISTEM OTOMATIS

### Aturan Otomatis (If-Then Logic):

**Aturan 1:**
- **IF:** Suhu > ___°C **AND** Ada orang (PIR)
- **THEN:** AC nyala

**Aturan 2:**
- **IF:** Cahaya < ___ (gelap) **AND** Ada orang
- **THEN:** Lampu nyala

**Aturan 3:**
- **IF:** Tidak ada orang selama ___ menit
- **THEN:** Matikan semua (AC + Lampu)

**Aturan 4 (Opsional):**
- **IF:** _______________________
- **THEN:** _______________________

**Aturan 5 (Opsional - Alarm):**
- **IF:** Suhu > ___°C (berbahaya)
- **THEN:** Buzzer bunyi + Notifikasi Blynk

---

## 📱 INTEGRASI BLYNK (Smartphone Control)

### Widget yang Digunakan:
- [ ] Gauge - untuk menampilkan suhu
- [ ] Value Display - untuk kelembapan/cahaya
- [ ] Button - untuk kontrol manual AC/Lampu
- [ ] LED Indicator - untuk status sensor PIR
- [ ] Notification - untuk alert suhu tinggi
- [ ] Chart - untuk grafik historis (opsional)

### Fitur Blynk:
- [ ] Monitoring real-time (data sensor update setiap 2 detik)
- [ ] Kontrol manual (override otomatis via app)
- [ ] Push notification (jika ada kondisi berbahaya)
- [ ] Dashboard informatif (mudah dipahami user)

---

## 📊 DIAGRAM SISTEM

### Diagram Blok:

```
┌─────────────┐
│   SENSOR    │
├─────────────┤
│ DHT11       │──┐
│ LDR         │──┤
│ PIR         │──┤
└─────────────┘  │
                 │
                 ▼
         ┌───────────────┐         ┌──────────────┐
         │    ESP32      │◄───────►│   Blynk      │
         │  (Kontroller) │  WiFi   │ Smartphone   │
         └───────────────┘         └──────────────┘
                 │
                 ▼
         ┌───────────────┐
         │    OUTPUT     │
         ├───────────────┤
         │ Relay AC      │
         │ Relay Lampu   │
         │ OLED Display  │
         │ Buzzer        │
         └───────────────┘
```

### Flowchart Logika:

```
START
  │
  ▼
┌─────────────────┐
│ Baca Sensor     │
│ - DHT11         │
│ - LDR           │
│ - PIR           │
└────────┬────────┘
         │
         ▼
┌─────────────────┐      YES    ┌──────────────┐
│ Suhu > 28°C     │────────────►│ AC ON        │
│ AND Ada Orang?  │              └──────────────┘
└────────┬────────┘
         │ NO
         ▼
┌─────────────────┐      YES    ┌──────────────┐
│ Gelap           │────────────►│ Lampu ON     │
│ AND Ada Orang?  │              └──────────────┘
└────────┬────────┘
         │ NO
         ▼
┌─────────────────┐
│ Kirim data ke   │
│ Blynk App       │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│ Update OLED     │
│ Display         │
└────────┬────────┘
         │
         ▼
       LOOP
```

---

## 🎬 VIDEO DEMONSTRASI

### Rencana Konten Video (Durasi: 3-5 menit):

**[00:00-00:30] INTRO**
- Perkenalan kelompok
- Judul proyek
- Overview singkat

**[00:30-01:30] KONSEP BANGUNAN**
- Tampilkan denah/poster
- Jelaskan zona-zona
- Mengapa perlu IoT?
- Benefit/manfaat

**[01:30-02:30] SISTEM IoT**
- Tampilkan breadboard + komponen
- Jelaskan sensor satu per satu
- Jelaskan output/aktuator
- Tunjuk ESP32 dan koneksi WiFi

**[02:30-04:30] DEMO LIVE**
- Demo 1: Sensor DHT11 baca suhu → Relay AC kerja
- Demo 2: LDR deteksi gelap → Lampu nyala
- Demo 3: PIR detect gerakan → Sistem aktif
- Demo 4: Buka Blynk app → Monitoring real-time
- Demo 5: Kontrol manual via app (optional)
- Slow motion untuk momen penting (optional)

**[04:30-05:00] OUTRO**
- Kesimpulan manfaat sistem
- Efisiensi energi (estimasi %)
- Terima kasih + nama kelompok

### Checklist Video:
- [ ] Durasi 3-5 menit (tidak terlalu panjang)
- [ ] Audio jelas (gunakan mic HP atau external)
- [ ] Pencahayaan bagus (terang, tidak gelap)
- [ ] Shot breadboard close-up (komponen terlihat jelas)
- [ ] Demo sistem bekerja (real, bukan simulasi)
- [ ] Blynk app terlihat jelas di HP
- [ ] Edit sederhana (cut, transition, text overlay)
- [ ] Upload ke YouTube (Unlisted) → link di laporan

### Tools Video (Gratis):
- **Recording:** Kamera HP (minimal 720p)
- **Editing:** CapCut, Filmora Free, DaVinci Resolve
- **Upload:** YouTube (Unlisted link)

---

## 🎨 POSTER KONSEP

### Format Poster:
- **Ukuran:** A3 Landscape (297mm x 420mm)
- **Orientasi:** Horizontal/Landscape
- **Format File:** PDF (untuk print) atau JPG (digital)
- **Resolution:** Minimal 300 DPI (jika print)

### Konten Wajib di Poster:

**1. Header:**
- Judul Proyek (font besar, bold)
- Logo Universitas + Prodi
- Nama anggota kelompok

**2. Denah/Isometri Bangunan:**
- Gambar denah dengan zona IoT
- Tandai lokasi sensor (icon)
- Tandai lokasi output (icon)
- Legend/keterangan

**3. Diagram Sistem:**
- Sensor → ESP32 → Output
- Koneksi WiFi ke Blynk
- Virtual pin mapping (V0, V1, V2...)

**4. Flowchart Logika:**
- If-Then logic dalam bentuk diagram
- Mudah dipahami non-teknis

**5. Foto Komponen:**
- Foto breadboard + komponen
- Annotate setiap komponen (arrow + label)

**6. Manfaat & Efisiensi:**
- Estimasi hemat energi (%)
- Kenyamanan user
- Kemudahan kontrol (smartphone)

**7. QR Code (Opsional):**
- QR code link ke video YouTube
- QR code link ke Blynk dashboard

### Checklist Poster:
- [ ] Judul jelas dan menarik
- [ ] Denah bangunan dengan zona IoT
- [ ] Diagram sistem lengkap (sensor-ESP32-output)
- [ ] Flowchart logika if-then
- [ ] Foto breadboard dengan label
- [ ] Manfaat & efisiensi energi
- [ ] Desain clean & profesional (tidak penuh sesak)
- [ ] Font terbaca (minimal 12pt untuk teks biasa)
- [ ] Warna konsisten (pakai max 3 warna utama)

### Tools Poster (Gratis):
- **Canva** (template poster gratis, mudah)
- **PowerPoint** (ubah slide size ke A3, export PDF)
- **Adobe Illustrator** (advanced, jika mahir)
- **Google Slides** (collaborative editing)

### Contoh Layout Poster:

```
┌─────────────────────────────────────────────────────────────┐
│  LOGO UNIV     SMART OFFICE IoT SYSTEM     NAMA KELOMPOK    │
├──────────────────┬──────────────────┬──────────────────────┤
│                  │                  │                       │
│  DENAH BANGUNAN  │  DIAGRAM SISTEM  │  FLOWCHART LOGIKA    │
│  (Zona IoT)      │  (Sensor-Output) │  (If-Then Rules)     │
│                  │                  │                       │
├──────────────────┴──────────────────┴──────────────────────┤
│                                                              │
│         FOTO BREADBOARD + KOMPONEN (Annotated)              │
│                                                              │
├──────────────────────────────────────────────────────────────┤
│  MANFAAT:                │  EFISIENSI ENERGI:               │
│  • Hemat energi 30%      │  • AC auto OFF saat kosong       │
│  • Kontrol smartphone    │  • Lampu auto sesuai cahaya      │
│  • Monitoring real-time  │  • Estimasi hemat Rp 500k/bulan  │
└──────────────────────────┴──────────────────────────────────┘
```

---

## 📝 KRITERIA PENILAIAN

### 1. KONSEP BANGUNAN (25%)
- [ ] Originalitas ide (5%)
- [ ] Relevansi dengan smart building (10%)
- [ ] Penjelasan zona & fungsi jelas (5%)
- [ ] Manfaat & efisiensi dijelaskan (5%)

### 2. SISTEM IoT (30%)
- [ ] Fungsionalitas sistem (semua sensor & output jalan) (15%)
- [ ] Kode program (logika otomatis benar) (10%)
- [ ] Integrasi Blynk (monitoring smartphone) (5%)

### 3. VIDEO DEMONSTRASI (25%)
- [ ] Clarity penjelasan konsep (10%)
- [ ] Kualitas video (audio, visual, editing) (5%)
- [ ] Demo sistem live (bekerja real, bukan simulasi) (10%)

### 4. POSTER KONSEP (20%)
- [ ] Desain visual menarik & profesional (10%)
- [ ] Kelengkapan informasi (denah, diagram, foto) (5%)
- [ ] Kemudahan dipahami (clarity) (5%)

### BONUS (Maksimal +10%)
- [ ] Fitur tambahan (Chart, Automation, etc.) (+5%)
- [ ] Kreativitas desain poster exceptional (+3%)
- [ ] Video editing sangat baik (transition, subtitle, etc.) (+2%)

**Total: 100% (+ 10% bonus)**

---

## ⚠️ CATATAN PENTING: KONSEP BARU!

### 🔴 **KOMPONEN DI BREADBOARD, BUKAN DI MAKET!**

**Mengapa konsep ini lebih baik?**

1. **Sustainability:** Komponen bisa dipakai adik tingkat tahun depan
2. **Fokus Konsep:** Mahasiswa fokus ke konsep bangunan cerdas, bukan craft
3. **Fleksibilitas:** Demo lebih mudah, troubleshooting cepat
4. **Profesional:** Video & poster = skill presentasi arsitektur
5. **Efisiensi Waktu:** Tidak buang waktu untuk craft maket detail

**Apa yang harus dibuat?**

✅ **WAJIB:**
- Sistem IoT lengkap di breadboard (sensor + ESP32 + output)
- Video demonstrasi 3-5 menit
- Poster konsep A3
- Denah/isometri bangunan (digital, bisa pakai SketchUp/AutoCAD)
- Kode program lengkap dengan komentar
- Laporan singkat (optional tapi recommended)

❌ **TIDAK WAJIB:**
- Maket fisik detail dengan komponen tertanam
- Craft rumah-rumahan dari kardus/styrofoam
- Furniture miniatur

✅ **OPSIONAL (Nilai tambah):**
- Maket miniatur sederhana (hanya representasi visual, tanpa komponen)
- Render 3D bangunan (SketchUp, Blender)
- Prototype casing untuk breadboard

---

## 📅 TIMELINE PENGERJAAN

### Minggu 1: Konsep & Perencanaan
- [ ] Diskusi kelompok: tentukan tema & konsep
- [ ] Buat denah bangunan dengan zona IoT
- [ ] Tentukan sensor & output yang digunakan
- [ ] Buat flowchart logika sistem

### Minggu 2: Implementasi Sistem IoT
- [ ] Test sensor satu per satu (individual testing)
- [ ] Test output/aktuator satu per satu
- [ ] Gabungkan sensor + output (integration testing)
- [ ] Setup Blynk app (Template, Datastream, Widget)
- [ ] Test komunikasi ESP32 ↔ Blynk

### Minggu 3: Finalisasi & Dokumentasi
- [ ] Finalisasi kode program (tambah komentar)
- [ ] Rekam video demonstrasi (3-5 menit)
- [ ] Buat poster konsep (A3 landscape)
- [ ] Edit video (cut, transition, text overlay)
- [ ] Upload video ke YouTube (Unlisted)

### Minggu 4: Presentasi & Demo
- [ ] Print poster (atau siapkan PDF untuk presentasi)
- [ ] Bawa breadboard + ESP32 untuk demo live
- [ ] Siapkan HP dengan Blynk app
- [ ] Presentasi di depan kelas (10 menit/kelompok)
- [ ] Demo live sistem bekerja

---

## 🎯 DELIVERABLES (Yang Harus Dikumpulkan)

### 1. File Digital:
- [ ] **Video demonstrasi** (link YouTube Unlisted)
- [ ] **Poster konsep** (PDF, minimal 300 DPI)
- [ ] **Kode program** (.ino file dengan komentar lengkap)
- [ ] **Denah bangunan** (JPG/PNG/PDF)
- [ ] **Laporan singkat** (optional, format bebas)

### 2. Demo Live (Presentasi):
- [ ] **Breadboard + ESP32** (sistem lengkap, siap demo)
- [ ] **HP dengan Blynk app** (untuk show monitoring)
- [ ] **Poster** (print A3 atau tampil di proyektor)

### 3. Presentasi:
- [ ] Durasi: 10 menit (7 menit presentasi + 3 menit Q&A)
- [ ] Semua anggota kelompok harus presentasi (pembagian adil)

---

## �� TIPS SUKSES

### Untuk Sistem IoT:
1. **Mulai sederhana:** Test 1 sensor dulu, baru tambah yang lain
2. **Dokumentasi progress:** Foto setiap tahap untuk laporan
3. **Backup plan:** Siapkan kode alternatif jika ada yang error
4. **Test Blynk:** Pastikan WiFi & internet stabil saat demo

### Untuk Video:
1. **Script dulu:** Tulis apa yang akan dijelaskan di setiap detik
2. **Practice:** Latihan presentasi sebelum rekam final
3. **Lighting:** Rekam di tempat terang (siang hari atau lampu bagus)
4. **Stable camera:** Gunakan tripod atau letakkan HP di tempat stabil

### Untuk Poster:
1. **Less is more:** Jangan penuh sesak, beri white space
2. **Hierarchy:** Info penting (judul, denah) lebih besar
3. **Consistent:** Gunakan max 3 warna utama + font max 2 jenis
4. **Review:** Minta teman lihat, apakah mudah dipahami?

---

## ❓ FAQ (Pertanyaan yang Sering Muncul)

**Q: Apakah harus buat maket rumah/bangunan fisik?**
A: TIDAK WAJIB. Fokus ke sistem IoT di breadboard + video + poster. Maket fisik hanya opsional (nilai tambah kecil).

**Q: Berapa minimal sensor & output?**
A: Minimal 2 sensor + 2 output. Recommended: 3 sensor + 3 output untuk konsep lebih kaya.

**Q: Apakah Blynk wajib?**
A: YA, Blynk wajib untuk monitoring via smartphone (sesuai materi Pertemuan 4).

**Q: Boleh pakai sensor lain selain yang diajarkan?**
A: Boleh, tapi harus konsultasi dosen dulu. Pastikan ada library Arduino-nya.

**Q: Video harus professional editing?**
A: Tidak perlu Hollywood-level. Cukup audio jelas, visual terang, dan demo terlihat jelas. Edit sederhana pakai CapCut sudah cukup.

**Q: Poster harus print atau boleh digital?**
A: Boleh digital (PDF tampil di proyektor saat presentasi). Print lebih bagus tapi tidak wajib.

**Q: Kalau sistem error saat demo live gimana?**
A: Makanya ada video backup! Jika live demo error, tunjukkan video. Tapi usahakan live demo sukses (test sebelumnya).

**Q: Berapa orang per kelompok?**
A: 3-5 orang. Recommended: 3-4 orang agar pembagian tugas merata.

---

## 📞 KONSULTASI & BANTUAN

### Konsultasi dengan Dosen:
- **Jadwal:** Setiap Pertemuan 4 atau by appointment
- **Topik konsultasi:** Konsep, troubleshooting kode, review progress
- **Cara:** Langsung di kelas atau via email/WA (jika urgent)

### Self-Help Resources:
- **CHEAT-SHEET-ARDUINO.md** → Quick reference Arduino & Blynk
- **FAQ-TROUBLESHOOTING.md** → Solusi masalah umum
- **File kode praktikum** → Referensi kode dari pertemuan 1-4

### Jangan Ragu Bertanya!
Lebih baik tanya dari awal daripada stuck di akhir deadline! 😊

---

## 🎓 SEMANGAT MENGERJAKAN PROYEK!

> **"The best way to predict the future is to create it."**
> — Peter Drucker

Proyek ini bukan hanya tugas kuliah, tapi portfolio Anda sebagai calon arsitek modern yang paham teknologi smart building. Kerjakan dengan serius dan kreatif!

**Good luck! 🚀**

---

**Template Version:** 2.0 (Updated: 2025)
**Last Modified:** Konsep baru - Sistem IoT terpisah dari maket
**Contact:** Dosen Pengampu Mata Kuliah Bangunan Cerdas
