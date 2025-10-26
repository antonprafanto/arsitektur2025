# PERTEMUAN 1: PENGENALAN IoT & BANGUNAN CERDAS

**Mata Kuliah**: Bangunan Cerdas
**Durasi**: 3 SKS (150 menit)
**Target**: Mahasiswa memahami konsep dasar IoT dan mampu membuat program sederhana untuk ESP32

---

## 📋 TUJUAN PEMBELAJARAN

Setelah pertemuan ini, mahasiswa diharapkan dapat:
1. Memahami konsep dasar Internet of Things (IoT)
2. Mengetahui aplikasi IoT dalam bangunan cerdas
3. Mengenal komponen ESP32 dan sensor-sensor dasar
4. Menginstal dan menggunakan Arduino IDE
5. Membuat program sederhana untuk menyalakan LED
6. Membuat program interaktif menggunakan tombol (push button)

---

## 📖 BAGIAN 1: TEORI (45 menit)

### A. Apa itu Internet of Things (IoT)?

**Definisi Sederhana:**
IoT adalah teknologi yang menghubungkan benda-benda fisik ke internet sehingga benda tersebut bisa:
- **Mengumpulkan data** (contoh: sensor suhu membaca suhu ruangan)
- **Mengirim data** (contoh: mengirim data suhu ke smartphone)
- **Menerima perintah** (contoh: menyalakan lampu dari smartphone)
- **Mengambil keputusan otomatis** (contoh: AC menyala sendiri saat ruangan panas)

**Analogi untuk Mahasiswa Arsitektur:**
Bayangkan sebuah bangunan seperti tubuh manusia:
- **Sensor** = Indera (mata, telinga, kulit) yang merasakan lingkungan
- **Mikrokontroler (ESP32)** = Otak yang memproses informasi
- **Aktuator (lampu, kipas, relay)** = Tangan dan kaki yang melakukan aksi
- **Internet/WiFi** = Sistem saraf yang menghubungkan semua bagian

### B. Kenapa IoT Penting untuk Bangunan Cerdas?

**Manfaat IoT dalam Bangunan:**

1. **Efisiensi Energi**
   - Lampu menyala otomatis hanya saat ada orang
   - AC menyesuaikan suhu berdasarkan jumlah penghuni
   - Hemat listrik hingga 30-40%

2. **Kenyamanan Penghuni**
   - Suhu ruangan selalu optimal
   - Pencahayaan otomatis sesuai waktu
   - Kontrol dari smartphone

3. **Keamanan**
   - Deteksi gerakan mencurigakan
   - Alarm otomatis saat ada gangguan
   - Monitoring real-time dari mana saja

4. **Monitoring & Maintenance**
   - Deteksi dini kerusakan peralatan
   - Data penggunaan untuk optimasi
   - Prediksi perawatan berkala

**Contoh Penerapan di Bangunan:**
- Hotel: Sistem check-in otomatis, kontrol AC kamar jarak jauh
- Gedung Perkantoran: Manajemen pencahayaan dan HVAC cerdas
- Rumah Tinggal: Smart home dengan kontrol suara dan otomasi
- Rumah Sakit: Monitoring pasien dan kontrol lingkungan steril

### C. Komponen-Komponen dalam Kit IoT Anda

Mari kita kenali peralatan yang akan digunakan:

#### 1. **ESP32 Development Kit**
   - **Fungsi**: Otak dari sistem IoT kita
   - **Kemampuan**:
     - Bisa terkoneksi WiFi dan Bluetooth
     - Bisa diprogram seperti komputer mini
     - Punya banyak pin untuk sensor dan aktuator
   - **Analogi**: Seperti kontraktor yang mengatur semua pekerjaan di proyek bangunan

#### 2. **Sensor Input** (Alat untuk "Merasakan" Lingkungan)

   - **DHT11**: Sensor Suhu & Kelembapan
     - Mengukur suhu ruangan (0-50°C)
     - Mengukur kelembapan udara (20-90%)
     - Aplikasi: Kontrol AC/pemanas otomatis

   - **Sensor PIR**: Sensor Gerak
     - Mendeteksi gerakan manusia/hewan
     - Jangkauan: 3-7 meter
     - Aplikasi: Lampu otomatis, sistem keamanan

   - **LDR (Light Dependent Resistor)**: Sensor Cahaya
     - Mendeteksi intensitas cahaya
     - Nilai berubah: gelap (tinggi) → terang (rendah)
     - Aplikasi: Lampu otomatis saat gelap

   - **Sensor Photo Dioda**: Sensor Penghalang
     - Mendeteksi ada/tidaknya objek
     - Aplikasi: Pintu otomatis, hitung orang masuk

#### 3. **Output/Aktuator** (Alat untuk "Melakukan Aksi")

   - **LED** (Light Emitting Diode): Lampu kecil
     - Tersedia: Merah, Kuning, Hijau, RGB
     - Aplikasi: Indikator status, lampu hias

   - **OLED Display 0.96 inch**: Layar Mini
     - Menampilkan teks dan angka
     - Aplikasi: Menampilkan suhu, pesan, status

   - **Relay 2 Channel**: Saklar Elektronik
     - Menghidupkan perangkat listrik 220V
     - Aplikasi: Kontrol lampu rumah, kipas, pompa

   - **Buzzer**: Alat Suara
     - Active Buzzer: Bunyi langsung saat diberi tegangan
     - Passive Buzzer: Bisa diatur nada suaranya
     - Aplikasi: Alarm, notifikasi

#### 4. **Input Manual**

   - **Push Button**: Tombol tekan
     - Input manual dari pengguna
     - Aplikasi: Saklar lampu, tombol alarm

   - **Potensiometer**: Pengatur nilai analog
     - Mengatur tegangan 0-3.3V
     - Aplikasi: Mengatur kecerahan, volume

#### 5. **Komponen Pendukung**

   - **Breadboard**: Papan untuk merakit rangkaian tanpa solder
   - **Kabel Jumper**: Menghubungkan komponen
   - **Resistor**: Membatasi arus listrik (melindungi komponen)

---

## 💻 BAGIAN 2: SETUP ARDUINO IDE (30 menit)

### Langkah 1: Download dan Install Arduino IDE

1. Buka browser, ketik: **arduino.cc/en/software**
2. Download Arduino IDE versi terbaru (Windows/Mac/Linux)
3. Install seperti aplikasi biasa
4. Buka Arduino IDE setelah selesai install

### Langkah 2: Install Board ESP32

ESP32 tidak otomatis tersedia di Arduino IDE, perlu ditambahkan:

1. **Buka Arduino IDE**
2. **Masuk ke menu**: `File` → `Preferences`
3. **Cari kolom**: "Additional Board Manager URLs"
4. **Copy-paste link ini:**
   ```
   https://dl.espressif.com/dl/package_esp32_index.json
   ```
5. Klik **OK**

6. **Masuk ke menu**: `Tools` → `Board` → `Boards Manager`
7. **Ketik di pencarian**: `esp32`
8. **Install**: "ESP32 by Espressif Systems" (tunggu sampai selesai)
9. **Tutup** Boards Manager

### Langkah 3: Pilih Board ESP32

1. **Masuk ke menu**: `Tools` → `Board` → `ESP32 Arduino`
2. **Pilih**: `ESP32 Dev Module`

### Langkah 4: Install Driver USB

Untuk Windows:
1. Download driver **CH340** atau **CP2102** (tergantung tipe ESP32)
2. Install driver tersebut
3. Restart komputer jika perlu

### Langkah 5: Koneksikan ESP32 ke Komputer

1. Sambungkan ESP32 ke komputer dengan kabel Micro USB
2. Di Arduino IDE, masuk ke: `Tools` → `Port`
3. Pilih port COM yang muncul (contoh: COM3, COM5)
   - Jika tidak muncul, cek kabel atau driver

### Langkah 6: Test Koneksi

Kita akan coba upload program kosong untuk memastikan koneksi:

1. Buka Arduino IDE
2. Biarkan kosong (atau hapus semua kode)
3. Ketik kode ini:
   ```cpp
   void setup() {
   }

   void loop() {
   }
   ```
4. Klik tombol **Upload** (ikon panah ke kanan)
5. Tunggu proses compile dan upload
6. Jika muncul **"Done uploading"**, berarti berhasil!

**Troubleshooting jika gagal:**
- Tekan dan tahan tombol **BOOT** di ESP32 saat upload
- Ganti kabel USB (pastikan kabel bisa transfer data, bukan hanya charging)
- Cek driver sudah terinstall dengan benar

---

## 🔧 BAGIAN 3: PRAKTIKUM 1 - LED BLINK (30 menit)

### Tujuan:
Membuat LED berkedip (nyala-mati-nyala-mati) secara otomatis

### Komponen yang Dibutuhkan:
- 1x ESP32
- 1x LED (warna bebas)
- 1x Resistor 220 ohm
- 2x Kabel jumper
- 1x Breadboard

### Diagram Koneksi:

```
ESP32                    Breadboard
=====                    ==========
Pin GPIO2  ------>  (+) LED  ------>  Resistor 220Ω  ------>  GND ESP32
```

**Langkah-langkah Merakit:**

1. **Pasang LED di breadboard**
   - LED punya 2 kaki: Panjang (+) dan Pendek (-)
   - Kaki panjang = Anoda (+)
   - Kaki pendek = Katoda (-)

2. **Pasang Resistor**
   - Sambungkan resistor 220Ω ke kaki pendek LED (-)

3. **Hubungkan ke ESP32**
   - Kabel dari GPIO2 ESP32 → Kaki panjang LED (+)
   - Kabel dari resistor → GND ESP32

### Kode Program:

Buka Arduino IDE dan ketik kode berikut:

```cpp
/*
  Program: LED Blink (Berkedip)
  Deskripsi: Membuat LED nyala dan mati secara bergantian
  Komponen: ESP32, LED, Resistor 220 ohm
*/

// Deklarasi pin LED
// Angka 2 adalah nomor pin GPIO di ESP32
int pinLED = 2;

// Fungsi setup() dijalankan SATU KALI saat ESP32 dihidupkan
void setup() {
  // Mengatur pin LED sebagai OUTPUT (untuk mengirim sinyal)
  pinMode(pinLED, OUTPUT);
}

// Fungsi loop() dijalankan BERULANG-ULANG selamanya
void loop() {
  // Nyalakan LED (kirim sinyal HIGH = 3.3V)
  digitalWrite(pinLED, HIGH);

  // Tunggu 1000 milidetik (1 detik)
  delay(1000);

  // Matikan LED (kirim sinyal LOW = 0V)
  digitalWrite(pinLED, LOW);

  // Tunggu 1000 milidetik (1 detik)
  delay(1000);

  // Setelah ini, loop() akan dijalankan lagi dari awal
  // Sehingga LED akan berkedip terus menerus
}
```

### Penjelasan Kode:

1. **`int pinLED = 2;`**
   - Membuat variabel bernama `pinLED` dengan nilai 2
   - Variabel = tempat menyimpan data
   - Seperti memberi label "pinLED" untuk mengingat nomor pin

2. **`void setup() { ... }`**
   - Fungsi yang dijalankan sekali saat ESP32 pertama dinyalakan
   - Digunakan untuk pengaturan awal (konfigurasi)

3. **`pinMode(pinLED, OUTPUT);`**
   - Mengatur pin sebagai OUTPUT (mengirim sinyal keluar)
   - OUTPUT = untuk perangkat yang kita kontrol (LED, buzzer, relay)
   - INPUT = untuk sensor yang membaca data (nanti di praktikum selanjutnya)

4. **`void loop() { ... }`**
   - Fungsi yang dijalankan berulang-ulang selamanya
   - Seperti while(true) atau perulangan tak terbatas

5. **`digitalWrite(pinLED, HIGH);`**
   - Mengirim sinyal HIGH (3.3V) ke pin LED
   - HIGH = nyalakan
   - LOW = matikan

6. **`delay(1000);`**
   - Menunggu (berhenti) selama 1000 milidetik = 1 detik
   - Angka dalam milidetik: 1000 ms = 1 detik

### Upload dan Test:

1. Klik tombol **Verify** (✓) untuk cek kode tidak ada error
2. Klik tombol **Upload** (→) untuk upload ke ESP32
3. Tunggu sampai selesai
4. **LED akan berkedip** nyala 1 detik, mati 1 detik, dan berulang

### Eksperimen:

Coba modifikasi dan upload ulang:

**Eksperimen 1:** Ubah kecepatan kedip
```cpp
delay(1000);  // Ganti jadi 500 (lebih cepat) atau 2000 (lebih lambat)
```

**Eksperimen 2:** Buat pola kedip berbeda
```cpp
void loop() {
  digitalWrite(pinLED, HIGH);
  delay(200);  // Nyala sebentar
  digitalWrite(pinLED, LOW);
  delay(1000); // Mati lama
}
```

**Eksperimen 3:** Kedip 3 kali lalu berhenti lama
```cpp
void loop() {
  // Kedip 1
  digitalWrite(pinLED, HIGH);
  delay(200);
  digitalWrite(pinLED, LOW);
  delay(200);

  // Kedip 2
  digitalWrite(pinLED, HIGH);
  delay(200);
  digitalWrite(pinLED, LOW);
  delay(200);

  // Kedip 3
  digitalWrite(pinLED, HIGH);
  delay(200);
  digitalWrite(pinLED, LOW);
  delay(2000); // Berhenti 2 detik
}
```

---

## 🔧 BAGIAN 4: PRAKTIKUM 2 - PUSH BUTTON KONTROL LED (45 menit)

### Tujuan:
Membuat LED yang bisa dinyalakan/dimatikan dengan menekan tombol

### Komponen yang Dibutuhkan:
- 1x ESP32
- 1x LED
- 1x Push Button
- 1x Resistor 220 ohm (untuk LED)
- 1x Resistor 10K ohm (untuk button)
- Kabel jumper
- Breadboard

### Diagram Koneksi:

```
ESP32          Komponen
=====          ========
GPIO2    --->  LED (+) ---> Resistor 220Ω ---> GND
GPIO4    --->  Push Button ---> GND
         --->  (Pull-up internal diaktifkan di kode)
```

**Langkah-langkah Merakit:**

1. **LED tetap seperti praktikum 1**
   - GPIO2 → LED → Resistor → GND

2. **Pasang Push Button**
   - Satu kaki button → GPIO4
   - Kaki lain button → GND
   - (Tidak perlu resistor eksternal karena kita pakai internal pull-up)

### Kode Program - Versi 1 (Kontrol Langsung):

```cpp
/*
  Program: Button Kontrol LED (Versi Langsung)
  Deskripsi: LED nyala saat tombol ditekan, mati saat dilepas
  Komponen: ESP32, LED, Push Button
*/

// Deklarasi pin
int pinLED = 2;      // Pin untuk LED
int pinButton = 4;   // Pin untuk tombol

void setup() {
  // Set LED sebagai OUTPUT (kita kontrol)
  pinMode(pinLED, OUTPUT);

  // Set Button sebagai INPUT dengan PULL-UP
  // INPUT_PULLUP = pin akan HIGH secara default
  // Akan jadi LOW saat tombol ditekan
  pinMode(pinButton, INPUT_PULLUP);
}

void loop() {
  // Baca status tombol
  int statusButton = digitalRead(pinButton);

  // Logika: INPUT_PULLUP membuat pin HIGH saat tidak ditekan
  // Jadi kita perlu balik logikanya
  if (statusButton == LOW) {
    // Tombol DITEKAN (LOW karena terhubung ke GND)
    digitalWrite(pinLED, HIGH);  // Nyalakan LED
  } else {
    // Tombol TIDAK DITEKAN (HIGH karena pull-up)
    digitalWrite(pinLED, LOW);   // Matikan LED
  }

  // Delay kecil agar pembacaan stabil
  delay(10);
}
```

### Penjelasan Kode Versi 1:

1. **`pinMode(pinButton, INPUT_PULLUP);`**
   - Mengatur pin button sebagai INPUT (membaca sinyal masuk)
   - INPUT_PULLUP = aktifkan resistor pull-up internal ESP32
   - Pull-up membuat pin bernilai HIGH secara default
   - Saat button ditekan → pin terhubung ke GND → jadi LOW

2. **`int statusButton = digitalRead(pinButton);`**
   - Membaca status pin button
   - Hasilnya: HIGH (tidak ditekan) atau LOW (ditekan)
   - Disimpan dalam variabel `statusButton`

3. **`if (statusButton == LOW)`**
   - Kondisi: jika statusButton bernilai LOW (tombol ditekan)
   - Maka jalankan perintah di dalam { }

4. **`else`**
   - Jika kondisi if tidak terpenuhi (tombol tidak ditekan)
   - Jalankan perintah di else

### Test Versi 1:

Upload kode dan test:
- Tekan tombol → LED nyala
- Lepas tombol → LED mati

---

### Kode Program - Versi 2 (Toggle ON/OFF):

Sekarang kita buat yang lebih canggih: LED toggle (nyala-mati-nyala) setiap kali tombol ditekan

```cpp
/*
  Program: Button Toggle LED
  Deskripsi: Setiap kali tombol ditekan, LED berganti status
            Tekan 1x = nyala, tekan lagi = mati, dst.
  Komponen: ESP32, LED, Push Button
*/

// Deklarasi pin
int pinLED = 2;
int pinButton = 4;

// Variabel untuk menyimpan status
bool statusLED = false;           // Status LED saat ini (false = mati)
bool buttonDitekanSebelumnya = false;  // Untuk deteksi perubahan button

void setup() {
  pinMode(pinLED, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // LED mati di awal
  digitalWrite(pinLED, LOW);
}

void loop() {
  // Baca status button saat ini
  bool buttonSekarang = (digitalRead(pinButton) == LOW);

  // Deteksi PERUBAHAN dari tidak ditekan → ditekan
  // Ini mencegah LED berkedip cepat saat tombol ditahan
  if (buttonSekarang == true && buttonDitekanSebelumnya == false) {
    // Tombol baru saja ditekan!

    // Toggle (balik) status LED
    statusLED = !statusLED;

    // Update LED sesuai status
    if (statusLED) {
      digitalWrite(pinLED, HIGH);  // Nyalakan
    } else {
      digitalWrite(pinLED, LOW);   // Matikan
    }

    // Tunggu sebentar agar tidak dobel deteksi
    delay(50);
  }

  // Simpan status button untuk deteksi perubahan di loop berikutnya
  buttonDitekanSebelumnya = buttonSekarang;

  delay(10);
}
```

### Penjelasan Kode Versi 2:

1. **`bool statusLED = false;`**
   - Variabel tipe boolean (true/false)
   - Menyimpan status LED saat ini
   - false = mati, true = nyala

2. **`bool buttonDitekanSebelumnya = false;`**
   - Menyimpan status button di loop sebelumnya
   - Untuk mendeteksi perubahan (dari tidak ditekan → ditekan)

3. **`bool buttonSekarang = (digitalRead(pinButton) == LOW);`**
   - Membaca button dan langsung convert ke true/false
   - true jika LOW (ditekan), false jika HIGH (tidak ditekan)

4. **`if (buttonSekarang == true && buttonDitekanSebelumnya == false)`**
   - Kondisi: button ditekan SEKARANG DAN tidak ditekan SEBELUMNYA
   - Ini artinya: button BARU SAJA ditekan (edge detection)
   - Mencegah LED berkedip berkali-kali saat button ditahan

5. **`statusLED = !statusLED;`**
   - Operator `!` = NOT (membalik nilai boolean)
   - Jika statusLED = false → jadi true
   - Jika statusLED = true → jadi false
   - Ini yang disebut "toggle"

6. **`delay(50);`**
   - Debouncing: mencegah pembacaan ganda karena bouncing mekanis button
   - Bouncing = getaran kecil saat button ditekan

### Test Versi 2:

Upload kode dan test:
- Tekan tombol 1x → LED nyala
- Tekan lagi → LED mati
- Tekan lagi → LED nyala
- dst...

---

## 📝 TUGAS RUMAH

### Tugas 1: Lampu Lalu Lintas
Buat simulasi lampu lalu lintas dengan 3 LED:
- Merah nyala 5 detik
- Kuning nyala 2 detik
- Hijau nyala 5 detik
- Berulang terus

**Komponen:** 3x LED (merah, kuning, hijau), 3x resistor 220Ω

**Hint:** Gunakan 3 pin GPIO berbeda untuk 3 LED

### Tugas 2: Tombol dengan 3 Mode
Buat program dengan 1 tombol dan 1 LED RGB yang memiliki 3 mode:
- Tekan 1x → LED merah
- Tekan 2x → LED hijau
- Tekan 3x → LED biru
- Tekan 4x → kembali merah, dst.

**Komponen:** 1x LED RGB, 1x button

**Hint:** Gunakan variabel counter yang bertambah setiap tekan

### Tugas 3: Kombinasi Bebas
Buat kreasi bebas menggunakan minimal:
- 2x LED (warna bebas)
- 2x Push Button

Contoh ide:
- Sistem voting (button A = LED merah, button B = LED hijau)
- Game cepat tekan tombol
- Lampu hias dengan pola unik

---

## 📚 RANGKUMAN

Hari ini kita telah belajar:

1. ✅ **Konsep IoT dan Smart Building**
   - IoT menghubungkan benda fisik ke internet
   - Aplikasi dalam efisiensi energi, kenyamanan, dan keamanan

2. ✅ **Komponen IoT**
   - ESP32 sebagai otak sistem
   - Sensor sebagai input (mata dan telinga)
   - Aktuator sebagai output (tangan dan kaki)

3. ✅ **Setup Arduino IDE**
   - Install board ESP32
   - Koneksi dan upload program

4. ✅ **Pemrograman Dasar**
   - Struktur program: setup() dan loop()
   - pinMode() untuk konfigurasi pin
   - digitalWrite() untuk kontrol output
   - digitalRead() untuk baca input
   - Logika if-else

5. ✅ **Praktikum**
   - LED Blink (kontrol output)
   - Button kontrolLED (baca input dan kontrol output)

---

## 🔜 PERSIAPAN PERTEMUAN 2

**Materi selanjutnya:** Sensor untuk Monitoring Lingkungan

**Yang akan dipelajari:**
- Membaca data dari sensor DHT11 (suhu & kelembapan)
- Membuat lampu otomatis dengan sensor LDR
- Sistem keamanan sederhana dengan sensor PIR

**Persiapan:**
- Bawa laptop dengan Arduino IDE sudah terinstall
- Pastikan ESP32 bisa upload program
- Bawa kit lengkap (terutama DHT11, LDR, PIR)
- Review materi hari ini

---

## ❓ PERTANYAAN & DISKUSI

**FAQ (Frequently Asked Questions):**

**Q: Kenapa LED saya tidak nyala?**
A: Cek hal berikut:
- Apakah LED terpasang dengan polaritas benar? (kaki panjang ke GPIO)
- Apakah resistor sudah terpasang?
- Apakah kode sudah di-upload dengan benar?
- Coba ganti LED, mungkin rusak

**Q: Kenapa button tidak berfungsi?**
A:
- Pastikan menggunakan INPUT_PULLUP di kode
- Cek koneksi: satu kaki button ke GPIO, satunya ke GND
- Test dengan Serial Monitor untuk lihat nilai yang dibaca

**Q: Apa bedanya HIGH/LOW dengan true/false?**
A:
- HIGH/LOW → untuk sinyal digital (tegangan)
- true/false → untuk logika boolean
- Secara nilai sama: HIGH = 1 = true, LOW = 0 = false

**Q: Kenapa harus pakai resistor?**
A:
- Resistor membatasi arus listrik
- Tanpa resistor, arus terlalu besar → LED/ESP32 bisa rusak
- Rumus: V = I × R (Hukum Ohm)

**Q: Boleh pakai pin GPIO lain?**
A: Ya! ESP32 punya banyak pin GPIO. Yang perlu dihindari:
- GPIO 0, 2, 12, 15 → digunakan saat booting
- GPIO 34-39 → input only (tidak bisa output)
- Pin 3V3, GND, VIN, EN → pin power

---

## 📖 REFERENSI TAMBAHAN

1. **Dokumentasi ESP32:**
   https://docs.espressif.com/projects/esp-idf/en/latest/esp32/

2. **Arduino Reference:**
   https://www.arduino.cc/reference/en/

3. **Tutorial IoT Indonesia:**
   https://www.nyebarilmu.com (berbagai tutorial IoT)

4. **Video Tutorial (YouTube):**
   - Channel: "Kelas Robot"
   - Channel: "Innovative Electronics"

---

**Selamat Belajar! Jangan ragu untuk bertanya! 😊**
