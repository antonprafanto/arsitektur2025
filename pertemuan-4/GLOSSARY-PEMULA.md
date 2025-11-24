# GLOSSARY UNTUK PEMULA: Pengenalan Coding IoT

**Dibuat untuk:** Mahasiswa Arsitektur yang **BELUM PERNAH** Coding  
**Tujuan:** Memahami istilah dasar sebelum mulai praktikum IoT

---

## 🎯 CARA MENGGUNAKAN GLOSSARY INI

Baca glossary ini **SEBELUM** mulai Studi Kasus 1-3.
Jangan hafal semua, cukup baca dan pahami **konsep umum**.
Saat praktikum, **kembali ke glossary ini** jika menemukan istilah yang bingung.

---

## 📖 BAGIAN 1: KONSEP DASAR PROGRAMMING

### 1. Apa itu "Program"?

**Program = Resep Masakan**

Seperti resep nasi goreng yang punya langkah-langkah:
1. Panaskan wajan
2. Tumis bawang
3. Masukkan nasi
4. Aduk hingga matang

Program untuk ESP32 juga begitu: kumpulan instruksi yang dijalankan satu per satu.

**Contoh di ESP32:**
```
1. Setup pin LED sebagai output
2. Nyalakan LED
3. Tunggu 1 detik
4. Matikan LED
5. Ulangi dari langkah 2
```

---

### 2. Variabel (Variable)

**Variabel = Kotak Penyimpanan**

Bayangkan kotak plastik untuk menyimpan barang.
- Kotak ada labelnya (nama variabel)
- Isi kotak bisa diganti-ganti

**Contoh kehidupan nyata:**
- Kotak "Suhu Ruangan" → Isinya: 28°C
- Kotak "Lampu Status" → Isinya: ON atau OFF

**Di kode:**
```cpp
float suhu = 28.5;          // Kotak bernama "suhu", isinya 28.5
bool lampuStatus = true;    // Kotak bernama "lampuStatus", isinya true (nyala)
```

---

### 3. Tipe Data

**Tipe Data = Jenis Barang dalam Kotak**

Tidak semua kotak bisa isi barang apa saja:
- Kotak sepatu → Isinya sepatu (bukan air!)
- Botol → Isinya air (bukan sepatu!)

**Tipe data umum:**

| Tipe Data | Isinya Apa? | Contoh | Analogi |
|-----------|-------------|--------|---------|
| `int` | Angka bulat | 25, -10, 0 | Jumlah kursi di ruangan |
| `float` | Angka desimal | 28.5, 3.14 | Suhu ruangan, tinggi badan |
| `bool` | Benar/Salah | true, false | Lampu ON (true) atau OFF (false) |
| `String` | Teks | "Smart Office" | Label pada pintu ruangan |

---

### 4. Fungsi (Function)

**Fungsi = Mesin Khusus**

Seperti mesin cuci: Anda masukkan baju kotor → Mesin cuci → Keluar baju bersih.

**Fungsi dalam program:**
Masukkan input → Proses → Keluar output (opsional)

**Contoh di ESP32:**
```cpp
void nyalakanLampu() {
  // Fungsi ini menyalakan lampu
  // Tidak ada input, tidak ada output
  digitalWrite(LED_PIN, HIGH);
}
```

Seperti tombol saklar: Tekan → Lampu nyala. Tidak ada "output" ke tangan Anda.

---

### 5. `void setup()` dan `void loop()`

Ini adalah **2 fungsi wajib** di setiap program Arduino/ESP32.

#### **`void setup()`** = Persiapan Awal

Seperti sebelum masak:
- Panaskan oven
- Siapkan bahan
- Cuci tangan

**Dijalankan SEKALI saat ESP32 pertama nyala.**

**Contoh:**
```cpp
void setup() {
  pinMode(LED_PIN, OUTPUT);  // Siapkan pin LED sebagai output
  Serial.begin(115200);      // Nyalakan komunikasi serial
}
```

#### **`void loop()`** = Kegiatan Berulang

Seperti saat mengaduk masakan:
- Aduk → Cek matang? → Aduk lagi → Cek lagi... (terus-menerus!)

**Dijalankan TERUS-MENERUS setelah setup selesai.**

**Contoh:**
```cpp
void loop() {
  digitalWrite(LED_PIN, HIGH);  // Nyalakan LED
  delay(1000);                  // Tunggu 1 detik
  digitalWrite(LED_PIN, LOW);   // Matikan LED
  delay(1000);                  // Tunggu 1 detik
  // Ulangi lagi dari awal!
}
```

---

## 📖 BAGIAN 2: ISTILAH ELEKTRONIKA IoT

### 6. Pin (GPIO)

**Pin = Colokan Listrik Mini**

ESP32 punya banyak "colokan" (pin) untuk hubungkan sensor/LED/relay.

**GPIO = General Purpose Input/Output**
- **Input**: Pin terima sinyal dari sensor (seperti tombol)
- **Output**: Pin kirim sinyal ke LED/relay (seperti saklar)

**Contoh:**
- GPIO2 → Output untuk LED (ESP32 nyalakan LED di pin ini)
- GPIO27 → Input untuk PIR (ESP32 baca sensor di pin ini)

---

### 7. VCC, GND, DATA

Ini adalah **label kabel** di komponen elektronika:

- **VCC** = Kabel **Positif** listrik (biasanya merah) → Hubungkan ke 3.3V atau 5V
- **GND** = Kabel **Ground/Negatif** (biasanya hitam) → Hubungkan ke GND ESP32
- **DATA/OUT/SDA/SCL** = Kabel data (kirim/terima informasi)

**Analogi:**
VCC + GND = Seperti kutub + dan - di baterai.

---

### 8. Sensor

**Sensor = Mata/Telinga/Hidung Bangunan**

Komponen yang **mendeteksi** kondisi lingkungan.

| Sensor | Apa yang Dideteksi? | Analogi Arsitektur |
|--------|---------------------|--------------------|
| **DHT11** | Suhu & Kelembapan | Termometer digital di dinding |
| **LDR** | Intensitas Cahaya | Sensor cahaya otomatis (lampu taman) |
| **PIR** | Gerakan/Kehadiran | Sensor gerak (pintu otomatis mall) |

---

### 9. Aktuator

**Aktuator = Tangan/Kaki Bangunan**

Komponen yang **melakukan aksi** berdasarkan keputusan ESP32.

| Aktuator | Apa yang Dilakukan? | Analogi Arsitektur |
|----------|---------------------|--------------------|
| **Relay** | Nyalakan/matikan perangkat besar (AC, pompa) | Kontaktor di panel listrik gedung |
| **LED** | Nyalakan lampu kecil (indikator) | Lampu indikator "KELUAR" |
| **Buzzer** | Bunyi alarm/notifikasi | Bel pintu, alarm kebakaran |

---

### 10. ESP32

**ESP32 = Otak Bangunan**

Mikrokontroler (komputer mini) yang:
1. Baca data dari sensor
2. Putuskan apa yang harus dilakukan (logika)
3. Kontrol aktuator

**Seperti BMS (Building Management System)** di gedung modern!

---

## 📖 BAGIAN 3: LOGIKA PROGRAMMING

### 11. `if-else` (Kondisi)

**if-else = Jika... Maka...**

Seperti keputusan di kehidupan nyata:

**Kehidupan nyata:**
```
JIKA hujan
  MAKA bawa payung
JIKA TIDAK (else)
  MAKA tidak perlu payung
```

**Di kode:**
```cpp
if (suhu > 28) {
  // Jika suhu lebih dari 28°C
  nyalakanAC();  // Maka nyalakan AC
} else {
  // Jika tidak (suhu <= 28°C)
  matikanAC();   // Maka matikan AC
}
```

---

### 12. Operator Perbandingan

Untuk membandingkan dua nilai:

| Operator | Arti | Contoh | Penjelasan |
|----------|------|--------|------------|
| `>` | Lebih besar | `suhu > 28` | Suhu lebih dari 28? |
| `<` | Lebih kecil | `cahaya < 1000` | Cahaya kurang dari 1000? |
| `>=` | Lebih besar atau sama | `kelembapan >= 80` | RH minimal 80? |
| `<=` | Lebih kecil atau sama | `suhu <= 26` | Suhu max 26? |
| `==` | Sama dengan | `status == true` | Status = true? |
| `!=` | Tidak sama dengan | `mode != AUTO` | Mode bukan AUTO? |

**⚠️ PENTING:** 
- `=` (satu) → **Mengisi** (assignment)
- `==` (dua) → **Membandingkan** (comparison)

---

### 13. Boolean Logic (DAN, ATAU, TIDAK)

**AND (`&&`) = DAN**

Kedua syarat harus benar.

**Contoh kehidupan:**
"Lampu nyala **JIKA** gelap **DAN** ada orang"

**Di kode:**
```cpp
if (cahaya > 2500 && gerakan == true) {
  // Gelap DAN ada orang → Nyalakan lampu
  digitalWrite(LED_PIN, HIGH);
}
```

---

**OR (`||`) = ATAU**

Salah satu syarat benar sudah cukup.

**Contoh kehidupan:**
"AC nyala **JIKA** suhu tinggi **ATAU** kelembapan tinggi"

**Di kode:**
```cpp
if (suhu > 30 || kelembapan > 80) {
  // Salah satu kondisi terpenuhi → AC ON
  nyalakanAC();
}
```

---

**NOT (`!`) = TIDAK/KEBALIKAN**

Balik nilai boolean.

```cpp
bool lampuStatus = true;

if (!lampuStatus) {
  // Jika TIDAK nyala (false)
  // Ini tidak akan jalan karena lampuStatus = true
}
```

---

## 📖 BAGIAN 4: FUNGSI ARDUINO/ESP32

### 14. `pinMode(pin, mode)`

**Atur pin sebagai INPUT atau OUTPUT**

Seperti atur colokan: Mau terima listrik atau kirim listrik?

```cpp
pinMode(2, OUTPUT);  // GPIO2 jadi OUTPUT (untuk LED/relay)
pinMode(27, INPUT);  // GPIO27 jadi INPUT (untuk sensor)
```

---

### 15. `digitalWrite(pin, value)`

**Nyalakan atau matikan pin digital**

```cpp
digitalWrite(2, HIGH);  // Nyalakan pin 2 (LED ON)
digitalWrite(2, LOW);   // Matikan pin 2 (LED OFF)
```

- `HIGH` = Nyala (3.3V)
- `LOW` = Mati (0V)

---

### 16. `digitalRead(pin)`

**Baca status pin digital**

```cpp
bool buttonPressed = digitalRead(14);
// true = Button ditekan
// false = Button tidak ditekan
```

---

### 17. `analogRead(pin)`

**Baca nilai analog (0-4095)**

Untuk sensor analog seperti LDR:

```cpp
int cahaya = analogRead(34);
// Hasil: 0 (gelap total) sampai 4095 (terang total)
```

---

### 18. `delay(ms)`

**Tunggu beberapa milidetik**

```cpp
delay(1000);  // Tunggu 1000 ms = 1 detik
delay(500);   // Tunggu 500 ms = 0.5 detik
```

**⚠️ HATI-HATI:** 
Saat `delay()`, ESP32 **tidak bisa melakukan apa-apa**!
Seperti tidur. Untuk project advanced, pakai `millis()` (akan dijelaskan nanti).

---

### 19. `Serial.println()`

**Tampilkan teks di Serial Monitor**

Seperti `console.log()` untuk debug.

```cpp
Serial.println("Halo dari ESP32!");
Serial.print("Suhu: ");
Serial.println(suhu);
```

Buka **Tools → Serial Monitor** di Arduino IDE untuk lihat hasilnya.

---

### 20. `millis()`

**Waktu sejak ESP32 nyala (dalam milidetik)**

```cpp
unsigned long waktuSekarang = millis();
// Jika ESP32 nyala 5 detik, hasilnya: 5000
```

**Kenapa pakai ini daripada `delay()`?**
Karena ESP32 tetap bisa jalankan kode lain sambil tunggu.

**Contoh pattern:**
```cpp
if (millis() - waktuTerakhir >= 2000) {
  // Sudah lewat 2 detik?
  bacaSensor();
  waktuTerakhir = millis();  // Reset timer
}
```

---

## 📖 BAGIAN 5: ISTILAH BLYNK IoT

### 21. Blynk

**Blynk = Remote Control Bangunan via Smartphone**

Platform cloud untuk kontrol ESP32 dari HP, seperti:
- Smart home app (Philips Hue, Xiaomi Mi Home)
- Monitoring dari jarak jauh
- Dashboard custom

---

### 22. Template

**Template = Blueprint untuk Tipe Device**

Seperti denah standar untuk rumah tipe 36.

**Contoh:**
- Template "Smart Office" → Bisa dipakai untuk 10 kantor
- Template "Smart Parking" → Bisa dipakai untuk 5 basement

---

### 23. Datastream

**Datastream = Saluran Data**

Bayangkan pipa air:
- Pipa 1 (V0) untuk data suhu
- Pipa 2 (V1) untuk data kelembapan
- Pipa 3 (V2) untuk data cahaya

**Virtual Pin (V0, V1, V2...)** = Nomor saluran

---

### 24. Widget

**Widget = Komponen UI di Dashboard**

Seperti saklar, termometer, grafik di panel kontrol gedung.

**Macam-macam:**
- **Gauge** = Jarum penunjuk (seperti speedometer)
- **Button** = Tombol ON/OFF
- **Chart** = Grafik
- **Value Display** = Tampilkan angka

---

### 25. Auth Token

**Auth Token = Kunci Rahasia**

Seperti password WiFi, untuk hubungkan ESP32 ke akun Blynk Anda.

**Format:** String panjang 32 karakter  
**Contoh:** `abcd1234efgh5678ijkl9012mnop3456`

**⚠️ JANGAN BAGIKAN** ke orang lain!

---

## 🎓 TIPS BELAJAR UNTUK MAHASISWA ARSITEKTUR

### 1. Jangan Takut Error!

Error = Guru terbaik Anda.
Setiap error ada pesan, baca dan cari solusinya.

### 2. Copy-Paste Dulu, Pahami Kemudian

Di awal, **tidak apa-apa** copy-paste kode.
Fokus lihat **hasilnya** dulu.
Nanti baru pahami **cara kerjanya**.

### 3. Fokus pada Logika, Bukan Syntax

Yang penting pahami **logika**:
```
JIKA suhu > 28 → AC nyala
JIKA gelap + ada orang → Lampu nyala
```

Syntax (`if`, `&&`, dll) bisa sambil jalan.

### 4. Gunakan Analogi Arsitektur

Setiap komponen IoT punya analogi di bangunan:
- ESP32 = BMS
- Sensor = Mata/telinga bangunan
- Relay = Kontaktor listrik
- Blynk = SCADA system

### 5. Belajar Bertahap

Jangan langsung ke Studi Kasus 3.
Mulai dari SC1 → SC2 → SC3 (jika mampu).

---

## 📚 REFERENSI CEPAT

**Saat praktikum, bingung istilah?**

1. Buka glossary ini
2. Ctrl+F → Cari istilah
3. Baca penjelasan + analoginya

**Masih bingung?**

Tanya dosen atau teman! 
Coding itu **kolaboratif**, bukan kompetisi.

---

**Dibuat untuk:** Mata Kuliah Bangunan Cerdas  
**Instruktur:** Anton Prafanto, S.Kom., M.T.  
**Versi:** 1.0 - 2025

**Selamat Belajar! 🚀**  
Ingat: Setiap programmer hebat pernah jadi pemula!
