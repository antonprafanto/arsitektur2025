# PERTEMUAN 4: PLATFORM IoT CLOUD & KONSEP PROYEK AKHIR

**Mata Kuliah**: Bangunan Cerdas
**Durasi**: 3 SKS (150 menit)
**Sifat**: Workshop Blynk IoT & Konsultasi Proyek

---

## 📋 TUJUAN PEMBELAJARAN

Setelah pertemuan ini, mahasiswa diharapkan dapat:
1. Menggunakan platform Blynk IoT untuk monitoring & kontrol via smartphone
2. Mengintegrasikan minimal 3 sensor dan 3 output dengan Blynk
3. Membuat video demonstrasi sistem IoT (3-5 menit)
4. Membuat poster konsep bangunan cerdas (A3 landscape)
5. Mempresentasikan konsep dan demo sistem IoT di breadboard

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

## 📱 BAGIAN 2A: PLATFORM IoT BLYNK (50 menit)

### Pengenalan: Kenapa Perlu Blynk?

Sampai pertemuan 3, sistem smart building kita sudah bisa:
- ✅ Baca sensor (DHT11, LDR, PIR)
- ✅ Kontrol aktuator (Relay, LED, Buzzer)
- ✅ Display data di OLED
- ✅ Otomatis berdasarkan threshold

**Tapi... ada masalahnya:**
- ❌ Harus selalu di depan breadboard untuk lihat data (via Serial Monitor)
- ❌ Tidak bisa kontrol dari jarak jauh
- ❌ Tidak ada log/history data
- ❌ Sulit monitoring real-time

**Solusi: BLYNK IoT Platform!**

Dengan Blynk, kita bisa:
- ✅ Monitor sensor dari **smartphone** (dari mana saja!)
- ✅ Kontrol relay dari **smartphone** (nyalakan AC sebelum pulang)
- ✅ Lihat **grafik historis** suhu/kelembapan
- ✅ Dapat **notifikasi push** saat suhu tinggi
- ✅ Buat **dashboard** custom sesuai kebutuhan

---

### A. Apa Itu Blynk?

**Blynk** adalah platform IoT yang memudahkan kita membuat aplikasi mobile untuk mengontrol dan memonitor perangkat IoT (seperti ESP32) **tanpa coding app sendiri**.

**Arsitektur Blynk:**

```
┌──────────────────────────────────────────────────────┐
│                  EKOSISTEM BLYNK                     │
├──────────────────────────────────────────────────────┤
│                                                      │
│  [1] HARDWARE (ESP32)                                │
│      ┌─────────────────┐                             │
│      │  ESP32 + Sensor │                             │
│      │   - DHT11       │                             │
│      │   - LDR         │                             │
│      │   - Relay       │                             │
│      └────────┬────────┘                             │
│               │ WiFi                                 │
│               ↓                                      │
│  [2] BLYNK CLOUD                                     │
│      ┌─────────────────┐                             │
│      │  Blynk Server   │                             │
│      │  - Simpan data  │                             │
│      │  - Routing      │                             │
│      │  - Push notif   │                             │
│      └────────┬────────┘                             │
│               │ Internet                             │
│               ↓                                      │
│  [3] SMARTPHONE APP                                  │
│      ┌─────────────────┐                             │
│      │  Blynk App      │                             │
│      │  - Dashboard    │                             │
│      │  - Widgets      │                             │
│      │  - Grafik       │                             │
│      └─────────────────┘                             │
│                                                      │
└──────────────────────────────────────────────────────┘
```

**Keunggulan Blynk:**
1. **Gratis** untuk project mahasiswa (unlimited devices!)
2. **Mudah** - Drag & drop widget, no coding app
3. **Real-time** - Data update langsung
4. **Cloud-based** - Akses dari mana saja (ada internet)
5. **Professional** - Dipakai industri sungguhan

**Free Plan vs Paid Plan:**
- **Free:** 2 templates, unlimited devices, 100 datastreams → **Cukup banget untuk project!**
- **Paid:** 10 templates, unlimited, advanced features → Untuk profesional

---

### B. Komponen Blynk

**1. Template**
- Blueprint untuk jenis device
- Contoh: "Smart Home Monitor", "Greenhouse Controller"
- Satu template bisa untuk banyak device (50 kamar = 1 template)

**2. Device**
- ESP32 fisik yang terhubung
- Setiap device punya Auth Token unik
- Contoh: "ESP32_Kamar_101", "ESP32_Ruang_Tamu"

**3. Datastream**
- Jalur data antara ESP32 dan App
- 3 tipe:
  - **Virtual Pin** (V0, V1, V2, ..., V255) → **Paling sering dipakai**
  - Digital Pin (D2, D3, ...) → Jarang dipakai
  - Analog Pin (A0, A1, ...) → Jarang dipakai

**Virtual Pin itu apa?**
- Pin software (bukan pin fisik ESP32)
- Bisa kirim data apa saja (suhu, kelembapan, status, teks)
- Flexible: satu virtual pin bisa untuk suhu, V1 untuk kelembapan, dst.

**4. Widget**
- Komponen UI di dashboard
- Macam-macam widget:

| Widget | Fungsi | Contoh Use Case |
|--------|--------|-----------------|
| **Button** | Tombol ON/OFF | Kontrol relay |
| **Switch** | Toggle switch | Nyala/mati lampu |
| **Slider** | Geser nilai | Set threshold suhu |
| **Gauge** | Tampilan meter | Tampil suhu 0-50°C |
| **Value Display** | Tampil angka | Kelembapan 65% |
| **Chart** | Grafik historis | Grafik suhu 24 jam |
| **LED** | Indikator status | Hijau=AC ON, Merah=OFF |
| **Label** | Tampil teks | Status: "Ruangan Dingin" |
| **Notification** | Push notification | "Suhu >30°C!" |

---

### C. Setup Blynk Step-by-Step

#### Langkah 1: Install Blynk App

**Android:**
- Buka Google Play Store
- Cari "Blynk IoT"
- Install app yang icon-nya logo putih/hijau
- **PENTING:** Bukan "Blynk Legacy" (yang lama)!

**iOS:**
- Buka App Store
- Cari "Blynk IoT"
- Install

---

#### Langkah 2: Registrasi Akun

1. Buka Blynk app
2. Tap **"Create New Account"**
3. Isi:
   - Email (gunakan email aktif!)
   - Password (min 8 karakter)
4. Verify email (cek inbox/spam)
5. Login ke app

---

#### Langkah 3: Buat Template Pertama

**Di Blynk App:**

1. Tap **"+ New Template"**
2. Isi:
   - **Name:** "Smart Room Monitor"
   - **Hardware:** ESP32
   - **Connection Type:** WiFi
3. Tap **"Create"**

**Di Blynk Web Console (opsional, lebih lengkap):**
- Buka https://blynk.cloud
- Login dengan akun yang sama
- Pilih **"Templates"** → **"New Template"**

---

#### Langkah 4: Buat Datastream

**Scenario:** Kita ingin monitoring suhu dari DHT11

1. Masuk ke Template yang sudah dibuat
2. Pilih tab **"Datastreams"**
3. Tap **"+ New Datastream"** → **"Virtual Pin"**
4. Isi konfigurasi:
   - **Name:** Suhu Ruangan
   - **Pin:** V0
   - **Data Type:** Double
   - **Min:** 0
   - **Max:** 50
   - **Units:** °C
5. Tap **"Save"**

Ulangi untuk datastream lain:
- **V1** → Kelembapan (0-100%)
- **V2** → Status Relay (0=OFF, 1=ON)
- **V3** → Intensitas Cahaya (0-4095)

---

#### Langkah 5: Tambah Widget ke Dashboard

**Tambah Gauge untuk Suhu:**

1. Di Template, pilih tab **"Mobile Dashboard"** (atau "Web Dashboard")
2. Tap **"+ Add Widget"**
3. Pilih **"Gauge"**
4. Konfigurasi:
   - **Title:** Suhu Ruangan
   - **Datastream:** V0 (Suhu Ruangan)
   - **Color:** Merah/Orange
5. Resize widget (drag pojok)
6. Tap **"Save"**

**Tambah Value Display untuk Kelembapan:**

1. Tap **"+ Add Widget"** lagi
2. Pilih **"Value Display"**
3. Konfigurasi:
   - **Title:** Kelembapan
   - **Datastream:** V1 (Kelembapan)
   - **Color:** Biru
4. Tap **"Save"**

**Tambah Button untuk Kontrol Relay:**

1. Tap **"+ Add Widget"**
2. Pilih **"Button"**
3. Konfigurasi:
   - **Title:** Kontrol AC
   - **Datastream:** V2 (Status Relay)
   - **Mode:** Switch (bukan Push)
   - **ON Label:** "AC ON"
   - **OFF Label:** "AC OFF"
4. Tap **"Save"**

---

#### Langkah 6: Buat Device & Dapatkan Auth Token

1. Keluar dari Template editor
2. Pilih menu **"Devices"**
3. Tap **"+ New Device"** → **"From Template"**
4. Pilih template "Smart Room Monitor"
5. Isi **Device Name:** "ESP32_Ruang_101"
6. Tap **"Create"**

**PENTING: Simpan 3 Credentials ini!**

Setelah device dibuat, akan muncul:

```
Template ID:    TMPL4xxxx
Device Name:    ESP32_Ruang_101
Auth Token:     abc123def456ghi789jkl
```

**SALIN** ketiga nilai ini! Akan dipakai di kode Arduino.

**Tips:**
- Tap tombol **"Copy All"** untuk copy semua
- Paste ke Notepad/Notes
- Atau tap tombol **Email** untuk kirim ke email sendiri

---

### D. Install Library Blynk di Arduino IDE

**Langkah 1: Buka Library Manager**

1. Buka Arduino IDE
2. Menu **Sketch → Include Library → Manage Libraries**
3. Tunggu loading

**Langkah 2: Install Blynk Library**

1. Di search box, ketik: **"Blynk"**
2. Cari library: **"Blynk" by Volodymyr Shymanskyy**
3. Pilih versi terbaru (1.3.2 atau lebih baru)
4. Klik **"Install"**
5. Tunggu hingga selesai (ada tulisan "Installed")

**Library WiFi sudah built-in** di ESP32, tidak perlu install.

---

### E. Struktur Kode Blynk Dasar

**Template Minimal:**

```cpp
// 1. Include library
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// 2. Credentials WiFi & Blynk
char ssid[] = "NAMA_WIFI_ANDA";
char pass[] = "PASSWORD_WIFI";
char auth[] = "AUTH_TOKEN_DARI_BLYNK";

// 3. Setup - Jalankan sekali
void setup() {
  Serial.begin(115200);

  // Koneksi ke Blynk
  Blynk.begin(auth, ssid, pass);
  // Fungsi ini akan:
  // - Connect ke WiFi
  // - Connect ke Blynk server
  // - Auto reconnect jika disconnect
}

// 4. Loop - Jalankan terus
void loop() {
  Blynk.run();  // WAJIB! Handle komunikasi Blynk

  // Kode lain di sini...
}
```

---

### F. Konsep Penting: Virtual Pin

**1. Kirim Data dari ESP32 ke App (Blynk.virtualWrite)**

```cpp
// Kirim suhu ke Virtual Pin V0
float suhu = 28.5;
Blynk.virtualWrite(V0, suhu);

// Kirim kelembapan ke V1
int kelembapan = 65;
Blynk.virtualWrite(V1, kelembapan);

// Kirim teks ke V5
Blynk.virtualWrite(V5, "Ruangan Dingin");
```

**Rate Limiting:**
- Free plan: Max 10 kali per detik per datastream
- **Best practice:** Kirim data setiap 1-2 detik (jangan setiap loop!)
- Gunakan timer: `millis()` atau `BlynkTimer`

---

**2. Terima Data dari App ke ESP32 (BLYNK_WRITE)**

Saat user tekan button di app, fungsi ini dipanggil:

```cpp
// V2 = Button kontrol relay
BLYNK_WRITE(V2) {
  int nilaiButton = param.asInt();  // 0=OFF, 1=ON

  if (nilaiButton == 1) {
    digitalWrite(pinRelay, HIGH);  // Nyalakan relay
    Serial.println("Relay ON dari app");
  } else {
    digitalWrite(pinRelay, LOW);   // Matikan relay
    Serial.println("Relay OFF dari app");
  }
}
```

**Penjelasan:**
- `BLYNK_WRITE(V2)` → Fungsi otomatis dipanggil saat V2 berubah
- `param.asInt()` → Ambil nilai sebagai integer
- `param.asFloat()` → Ambil nilai sebagai float
- `param.asString()` → Ambil nilai sebagai string

---

**3. Event Saat Blynk Connected**

```cpp
BLYNK_CONNECTED() {
  // Fungsi ini dipanggil saat ESP32 berhasil connect ke Blynk
  Serial.println("Blynk Connected!");

  // Sync data dari server (ambil nilai widget terakhir)
  Blynk.syncVirtual(V2);  // Sync button relay
}
```

---

### G. Contoh Lengkap: LED Control via Blynk

**Hardware:**
- ESP32
- 1x LED
- 1x Resistor 220Ω

**Wiring:**
```
LED Anode (+) → Resistor 220Ω → ESP32 GPIO2
LED Cathode (-) → ESP32 GND
```

**Setup Blynk:**
1. Buat datastream V0 (Digital, 0-1)
2. Tambah Button widget linked ke V0
3. Copy Auth Token

**Kode:**

```cpp
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// WiFi & Blynk credentials
char ssid[] = "NAMA_WIFI_ANDA";
char pass[] = "PASSWORD_WIFI";
char auth[] = "AUTH_TOKEN_ANDA";

// Pin LED
#define LED_PIN 2

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  // Koneksi ke Blynk
  Serial.println("Connecting to Blynk...");
  Blynk.begin(auth, ssid, pass);
  Serial.println("Connected!");
}

void loop() {
  Blynk.run();  // WAJIB!
}

// Terima perintah dari button V0
BLYNK_WRITE(V0) {
  int value = param.asInt();
  digitalWrite(LED_PIN, value);

  if (value == 1) {
    Serial.println("LED ON dari app");
  } else {
    Serial.println("LED OFF dari app");
  }
}
```

**Testing:**
1. Upload kode
2. Buka Serial Monitor (115200 baud)
3. Tunggu hingga "Connected!"
4. Buka Blynk app, tap button
5. LED harus nyala/mati sesuai button!

---

### H. Fitur-Fitur Blynk Lanjutan

#### 1. Push Notification

Kirim notifikasi ke smartphone saat event tertentu:

```cpp
// Kirim notifikasi
Blynk.logEvent("high_temp", "Suhu tinggi: 35°C!");
```

**Setup di Blynk:**
1. Buat Event di template: **"high_temp"**
2. Set message template
3. Enable notification

**Best Practice:**
- Jangan spam notifikasi (max 1 notif per menit)
- Gunakan flag agar tidak notif berulang-ulang

---

#### 2. Chart/Grafik Historis

**Setup:**
1. Tambah Chart widget
2. Link ke datastream V0 (suhu)
3. Set time range: 1 hour, 6 hours, 1 day, dst.

**Kode:** Tidak perlu ubah kode! Blynk otomatis simpan data.

---

#### 3. Timer/Automation

**Di Blynk App:**
1. Tambah widget **"Automation"**
2. Buat rule:
   - **Condition:** Setiap hari jam 18:00
   - **Action:** Set V2 (relay AC) = 1 (ON)

Sistem otomatis nyalakan AC jam 6 sore!

---

### I. Error Handling & Reconnect Otomatis

**Problem:** WiFi/Blynk sering disconnect, ESP32 hang.

**Solusi:** Gunakan timer dan cek status koneksi.

```cpp
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "NAMA_WIFI_ANDA";
char pass[] = "PASSWORD_WIFI";
char auth[] = "AUTH_TOKEN";

#define LED_STATUS 2  // LED indikator

unsigned long lastCheck = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_STATUS, OUTPUT);

  // Koneksi
  connectBlynk();
}

void loop() {
  // Cek koneksi setiap 10 detik
  if (millis() - lastCheck > 10000) {
    lastCheck = millis();

    if (!Blynk.connected()) {
      Serial.println("Blynk disconnected! Reconnecting...");
      connectBlynk();
    }
  }

  // Run Blynk
  if (Blynk.connected()) {
    Blynk.run();
    digitalWrite(LED_STATUS, HIGH);  // LED ON = connected
  } else {
    digitalWrite(LED_STATUS, LOW);   // LED OFF = disconnected
  }
}

void connectBlynk() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, pass);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    Serial.println("Connecting to Blynk...");
    Blynk.config(auth);
    Blynk.connect();

    if (Blynk.connected()) {
      Serial.println("Blynk connected!");
    }
  } else {
    Serial.println("\nWiFi connection failed!");
  }
}
```

---

### J. Tips & Best Practices

**1. Rate Limiting (PENTING!)**

❌ **JANGAN:**
```cpp
void loop() {
  Blynk.run();
  float suhu = dht.readTemperature();
  Blynk.virtualWrite(V0, suhu);  // Kirim 10x/detik! OVERLOAD!
}
```

✅ **LAKUKAN:**
```cpp
unsigned long lastSend = 0;

void loop() {
  Blynk.run();

  // Kirim data setiap 2 detik saja
  if (millis() - lastSend > 2000) {
    lastSend = millis();

    float suhu = dht.readTemperature();
    Blynk.virtualWrite(V0, suhu);
  }
}
```

---

**2. Jangan Gunakan delay() di Loop!**

❌ **JANGAN:**
```cpp
void loop() {
  Blynk.run();
  delay(5000);  // Blynk.run() tidak jalan 5 detik! Disconnect!
}
```

✅ **LAKUKAN:** Gunakan `millis()` seperti contoh di atas.

---

**3. Backup Plan: Mode Offline**

Sistem harus tetap jalan meskipun Blynk disconnect!

```cpp
void loop() {
  // Sistem otomatis lokal (tetap jalan tanpa Blynk)
  float suhu = dht.readTemperature();
  if (suhu > 30) {
    digitalWrite(relayAC, HIGH);  // AC ON
  }

  // Kirim ke Blynk (jika connected)
  if (Blynk.connected()) {
    Blynk.run();

    if (millis() - lastSend > 2000) {
      lastSend = millis();
      Blynk.virtualWrite(V0, suhu);
    }
  }
}
```

---

**4. WiFi Hotspot dari HP (Backup)**

Jika WiFi kampus/rumah bermasalah:

1. **Nyalakan Hotspot di HP:**
   - Android: Settings → Network & Internet → Hotspot & tethering
   - iOS: Settings → Personal Hotspot
   - Set SSID & Password

2. **Ubah kode:**
   ```cpp
   char ssid[] = "Hotspot_HP_Anda";
   char pass[] = "password_hotspot";
   ```

3. Upload & test!

**Catatan:** Kuota internet HP akan terpakai (sedikit, ~1-5 MB/jam).

---

### K. Troubleshooting Blynk

#### 1. "WiFi Connection Failed"

**Penyebab:**
- SSID atau password salah
- WiFi terlalu jauh
- WiFi 5GHz (ESP32 hanya support 2.4GHz)

**Solusi:**
- Cek SSID dan password (case sensitive!)
- Dekatkan ESP32 ke router
- Pastikan WiFi 2.4GHz, bukan 5GHz
- Test dengan WiFi hotspot HP dulu

---

#### 2. "Device Offline" di Blynk App

**Penyebab:**
- Auth Token salah
- ESP32 tidak connect ke internet
- Firewall block port Blynk

**Solusi:**
- Re-copy Auth Token dari Blynk app
- Cek `Serial.println(WiFi.localIP())` → jika 0.0.0.0 berarti tidak connect
- Test dengan hotspot HP

---

#### 3. Data Sensor Tidak Update

**Penyebab:**
- Rate limiting (kirim terlalu cepat)
- `Blynk.run()` tidak dipanggil
- `delay()` blocking `Blynk.run()`

**Solusi:**
- Kirim data max setiap 1-2 detik
- Pastikan `Blynk.run()` di loop() tanpa delay
- Gunakan `millis()` bukan `delay()`

---

#### 4. Widget Button Tidak Respond

**Penyebab:**
- Datastream tidak match
- Fungsi `BLYNK_WRITE(Vx)` salah pin
- ESP32 offline

**Solusi:**
- Pastikan widget linked ke datastream yang benar
- Cek `BLYNK_WRITE(V2)` match dengan datastream V2
- Cek device online di app

---

#### 5. Notifikasi Tidak Masuk

**Penyebab:**
- Event name salah
- Notification disabled di HP
- Limit notifikasi exceeded (max 100/hari free plan)

**Solusi:**
- Cek event name di `Blynk.logEvent("nama_event")`
- Enable notification di settings HP
- Jangan spam notifikasi

---

### L. Integrasi Blynk ke Proyek Akhir

**Rekomendasi Penggunaan Blynk di Proyek:**

1. **Monitoring Real-time:**
   - Suhu, kelembapan, cahaya, status PIR
   - Tampilkan di Gauge & Value Display
   - Grafik historis 24 jam

2. **Remote Control:**
   - Kontrol relay AC, lampu, pompa
   - Gunakan Button/Switch widget
   - Bisa kontrol dari rumah saat sistem breadboard di kampus!

3. **Notifikasi:**
   - Alert saat suhu >30°C
   - Alert saat PIR detect gerakan
   - Alert saat kelembapan <40%

4. **Dashboard Presentasi:**
   - Buat dashboard menarik dengan warna tema
   - Susun widget rapi
   - Tunjukkan ke dosen saat presentasi (impressive!)

---

### M. File Praktikum Blynk

Silakan coba 4 contoh kode praktikum:

1. **kode-10-blynk-led-control.ino**
   - LED control dasar via Blynk
   - Belajar Button widget & BLYNK_WRITE()

2. **kode-11-blynk-monitor-suhu.ino**
   - Monitoring DHT11 real-time
   - Belajar Gauge, Value Display, Chart widget

3. **kode-12-blynk-smart-home.ino**
   - Smart home lengkap: DHT11 + LDR + PIR + Relay + OLED + Blynk
   - Status koneksi di OLED
   - Multi-sensor monitoring & control

4. **kode-13-blynk-wifi-reconnect.ino**
   - Demo reconnect otomatis WiFi & Blynk
   - Best practice error handling

---

### N. Tugas Mahasiswa (Opsional)

**Tugas 1: Smart Room Dashboard**
- Buat dashboard monitoring ruangan dengan DHT11 + LDR + PIR
- Widget: Gauge (suhu), Value (kelembapan, cahaya), LED indicator (PIR)
- **Solusi:** `tugas-01-blynk-smart-room.ino`

**Tugas 2: Push Notification**
- Kirim notifikasi ke HP saat suhu >30°C
- Threshold suhu bisa diatur via slider di app
- **Solusi:** `tugas-02-blynk-notifikasi.ino`

---

### O. Kesimpulan Blynk

✅ **Manfaat Blynk untuk Proyek:**
- Monitoring dari mana saja (via internet)
- Dashboard professional
- Remote control real-time
- Data logging otomatis
- Notifikasi push
- Impressive saat presentasi!

✅ **Yang Perlu Diingat:**
- Kirim data max 10x/detik (gunakan timer)
- Jangan gunakan `delay()` di loop
- Sistem harus tetap jalan offline (failsafe)
- Test dengan hotspot HP jika WiFi kampus bermasalah

✅ **Next Step:**
- Coba 4 contoh kode praktikum
- Integrasikan Blynk ke proyek akhir Anda (breadboard + video + poster)
- Buat dashboard custom sesuai tema proyek
- Presentasikan dengan demo live!

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

## 🎬 BAGIAN 4: PANDUAN VIDEO & POSTER PROYEK (60 menit)

> **CATATAN PENTING:** Konsep proyek telah diperbarui! Lihat detail lengkap di bawah.

---

## 🏠 BAGIAN 4A: TEMA PROYEK YANG DIREKOMENDASIKAN (Referensi)

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

**📌 Lihat detail lengkap implementasi proyek di BAGIAN 4B di bawah (Panduan Video & Poster)**

---

## 🎬 BAGIAN 4B: PANDUAN VIDEO & POSTER PROYEK (KONSEP BARU!)

### A. Konsep Baru: Sistem IoT Terpisah dari Maket

**PERUBAHAN PENTING!** 🔴

Berdasarkan evaluasi, kami mengubah konsep proyek akhir agar lebih **sustainable** dan **fokus pada konsep bangunan cerdas**:

#### ✅ **YANG WAJIB:**
1. **Sistem IoT lengkap di breadboard/modul terpisah**
   - Semua sensor + ESP32 + output di breadboard
   - Sistem harus berjalan sempurna dan bisa di-demo
   - Kabel rapi, komponen terorganisir

2. **Video demonstrasi 3-5 menit**
   - Penjelasan konsep bangunan
   - Demo sistem IoT bekerja
   - Upload ke YouTube (Unlisted)

3. **Poster konsep A3 (digital/print)**
   - Denah bangunan dengan zona IoT
   - Diagram sistem
   - Flowchart logika
   - Foto komponen

4. **Denah/isometri bangunan (digital)**
   - Bisa pakai SketchUp, AutoCAD, atau hand-drawing scan
   - Tunjukkan zona-zona smart building
   - Tandai lokasi sensor & output

5. **Kode program lengkap**
   - File .ino dengan komentar 60%+
   - Terintegrasi dengan Blynk

#### ❌ **YANG TIDAK WAJIB:**
- Maket fisik detail dengan komponen tertanam
- Craft rumah-rumahan dari kardus/styrofoam
- Furniture miniatur
- Komponen dipasang permanen di maket

#### ✅ **OPSIONAL (Nilai tambah):**
- Maket miniatur sederhana (hanya visual, tanpa komponen)
- Render 3D bangunan
- Prototype casing untuk breadboard

---

### B. Mengapa Konsep Ini Lebih Baik?

#### 1. **Sustainability & Reusability** ♻️
- Komponen bisa dipakai adik tingkat tahun depan
- Tidak rusak/hilang tertanam di maket
- Hemat budget jangka panjang
- **Ramah lingkungan!**

#### 2. **Fokus pada Konsep, Bukan Craft** 🧠
- Mahasiswa Arsitektur fokus ke **desain & konsep** bangunan cerdas
- Tidak buang waktu untuk craft detail maket
- Lebih sesuai kompetensi Arsitektur (konsep > craft)
- **Video & poster = skill presentasi profesional**

#### 3. **Fleksibilitas Demonstrasi** 🎥
- Demo breadboard lebih mudah troubleshooting
- Sistem terlihat jelas saat presentasi
- Dosen bisa test fungsionalitas langsung
- **Video bisa menunjukkan sistem bekerja dengan jelas**

#### 4. **Profesionalisme** 💼
- Video = skill komunikasi visual (penting untuk arsitek)
- Poster = skill presentasi desain (core skill arsitektur)
- Mirip presentasi proyek arsitektur ke klien
- **Portfolio-worthy!**

#### 5. **Efisiensi Waktu** ⏱️
- Lebih banyak waktu untuk konsep matang
- Fokus ke programming & integrasi IoT
- **Quality over quantity!**

---

### C. Panduan Membuat Video Demonstrasi

#### Struktur Video (3-5 menit):

**[00:00-00:30] INTRO**
- Perkenalan kelompok
- Judul proyek
- Overview singkat

**Contoh Script:**
> "Halo, kami kelompok 5 dari Prodi Arsitektur. Kami akan presentasikan Smart Office System yang menghemat energi hingga 30% dengan teknologi IoT."

---

**[00:30-01:30] KONSEP BANGUNAN**
- Tampilkan denah/poster
- Jelaskan zona-zona bangunan
- Mengapa perlu IoT?
- Benefit/manfaat

**Contoh Script:**
> "Office ini punya 3 zona: Open Space untuk 10 orang, Meeting Room, dan Pantry. Sistem IoT kami gunakan untuk kontrol otomatis AC dan lampu berdasarkan kehadiran dan kondisi ruangan. Ini bisa hemat energi 30-40% dibanding office konvensional."

**Tips:**
- Show denah dengan pointer/arrow
- Zoom in ke zona penting
- Gunakan visual yang jelas

---

**[01:30-02:30] SISTEM IoT**
- Tampilkan breadboard + komponen
- Jelaskan sensor satu per satu
- Jelaskan output/aktuator
- Tunjuk ESP32 dan koneksi WiFi

**Contoh Script:**
> "Ini adalah breadboard sistem IoT kami. Ada DHT11 untuk baca suhu, LDR untuk deteksi cahaya, PIR untuk deteksi gerakan. Output-nya ada relay untuk kontrol AC dan lampu, plus OLED display untuk status lokal. Semua dikontrol ESP32 yang terkoneksi WiFi dan Blynk."

**Tips:**
- Close-up shot breadboard
- Tunjuk komponen saat disebutkan
- Label komponen (text overlay di editing)

---

**[02:30-04:30] DEMO LIVE**
- Demo 1: Sensor DHT11 baca suhu → Relay AC kerja
- Demo 2: LDR deteksi gelap → Lampu nyala
- Demo 3: PIR detect gerakan → Sistem aktif
- Demo 4: Buka Blynk app → Monitoring real-time
- Demo 5: Kontrol manual via app

**Contoh Script:**
> "Sekarang saya akan demo sistemnya. Perhatikan, saat saya tutup LDR dengan tangan, nilai cahaya turun... dan lampu otomatis nyala. Kemudian saat saya buka HP, di Blynk app terlihat data real-time dari semua sensor. Saya juga bisa kontrol manual AC dari smartphone."

**Tips:**
- **PENTING:** Slow motion untuk momen kunci (relay click, LED nyala)
- Split screen: breadboard + HP Blynk app
- Tunjukkan serial monitor (opsional, untuk tech-savvy)

---

**[04:30-05:00] OUTRO**
- Kesimpulan manfaat sistem
- Efisiensi energi (estimasi %)
- Terima kasih + nama kelompok

**Contoh Script:**
> "Kesimpulannya, sistem Smart Office kami bisa hemat energi 35% dengan kontrol otomatis. User juga bisa monitor dan kontrol dari smartphone. Terima kasih! Kami kelompok 5: Anton, Budi, Citra."

---

#### Checklist Video:

**Teknis:**
- [ ] Durasi 3-5 menit (tidak terlalu panjang/pendek)
- [ ] Resolusi minimal 720p (HD)
- [ ] Audio jelas (mic HP atau external)
- [ ] Pencahayaan bagus (terang, tidak gelap/backlight)
- [ ] Kamera stabil (gunakan tripod atau letakkan HP di tempat fix)

**Konten:**
- [ ] Shot breadboard close-up (komponen terlihat)
- [ ] Demo sistem bekerja (real, bukan simulasi)
- [ ] Blynk app terlihat jelas di HP
- [ ] Semua anggota kelompok muncul/voice (pembagian adil)
- [ ] Ada subtitle (opsional, tapi nilai tambah)

**Editing:**
- [ ] Cut yang tidak perlu (jangan ada "uhm...", "eee...")
- [ ] Transition smooth antar scene
- [ ] Text overlay untuk label komponen
- [ ] Background music (volume kecil, jangan ganggu voice)
- [ ] Intro slide (judul + nama kelompok)
- [ ] Outro slide (terima kasih)

**Upload:**
- [ ] Upload ke YouTube (setting: **Unlisted**)
- [ ] Judul: "[Kelas] Smart Office IoT - Kelompok 5"
- [ ] Deskripsi: Anggota kelompok + ringkasan konsep
- [ ] Thumbnail menarik (screenshot breadboard atau denah)

---

#### Tools Video (Gratis):

**Recording:**
- Kamera HP (minimal 720p, most HP sekarang 1080p)
- Webcam laptop (jika ada yang bagus)

**Editing:**
- **CapCut** (mobile & PC, paling mudah untuk pemula)
- **Filmora Free** (PC, banyak fitur)
- **DaVinci Resolve** (PC, professional tapi gratis)
- **OpenShot** (PC, open-source)
- **iMovie** (Mac, bawaan)

**Screen Recording (untuk Blynk app demo):**
- Android: Bawaan (Screen Recorder di quick settings)
- iPhone: Bawaan (Control Center → Screen Recording)

**Tips Recording:**
1. Rekam di siang hari (natural light terbaik)
2. Background polos/rapi (tidak berantakan)
3. Script dulu, practice sebelum rekam final
4. Rekam beberapa take, pilih yang terbaik
5. Jangan pakai zoom digital (mendekatlah secara fisik)

---

### D. Panduan Membuat Poster Konsep

#### Format Poster:

**Ukuran:** A3 Landscape (297mm × 420mm)
**Orientasi:** Horizontal/Landscape
**Format File:** PDF (print) atau JPG/PNG (digital)
**Resolution:** Minimal 300 DPI (untuk print)

---

#### Layout Poster (Template):

```
┌───────────────────────────────────────────────────────────────┐
│  [LOGO UNIV]   SMART OFFICE IoT SYSTEM    [NAMA KELOMPOK]     │
├────────────────────┬────────────────────┬─────────────────────┤
│                    │                    │                     │
│  DENAH BANGUNAN    │  DIAGRAM SISTEM    │  FLOWCHART LOGIKA   │
│  (Zona IoT)        │  (Sensor→ESP32→    │  (If-Then Rules)    │
│                    │   Output)          │                     │
│                    │                    │                     │
├────────────────────┴────────────────────┴─────────────────────┤
│                                                                │
│         FOTO BREADBOARD + KOMPONEN (dengan label)              │
│                                                                │
├────────────────────────────────────────────────────────────────┤
│  MANFAAT:                 │  EFISIENSI ENERGI:                │
│  • Hemat energi 30-40%    │  • AC auto OFF saat ruangan kosong│
│  • Kontrol via smartphone │  • Lampu menyala sesuai cahaya    │
│  • Monitoring real-time   │  • Estimasi hemat Rp 500rb/bulan  │
└───────────────────────────┴───────────────────────────────────┘
```

---

#### Konten Wajib di Poster:

**1. Header (Top):**
- Logo Universitas + Prodi
- **Judul Proyek** (font besar, bold, eye-catching)
- Nama anggota kelompok (font kecil, tapi terbaca)

**Contoh:**
```
UNIVERSITAS MULAWARMAN
SMART OFFICE IoT AUTOMATION SYSTEM
Kelompok 5: Anton • Budi • Citra • Dewi
```

---

**2. Denah/Isometri Bangunan:**
- Gambar denah dengan zona IoT
- Tandai lokasi sensor (icon sensor + label)
- Tandai lokasi output (icon lampu/AC)
- Legend/keterangan warna

**Tips:**
- Gunakan warna berbeda untuk zona berbeda
- Icon sensor harus jelas (bukan terlalu kecil)
- Arrow menunjuk lokasi exact

**Contoh annotation:**
```
[DHT11] → Zona Open Space (ceiling)
[PIR] → Entrance door
[Relay AC] → AC unit
```

---

**3. Diagram Sistem:**
- Flowchart: Sensor → ESP32 → Output
- Koneksi WiFi ke Blynk (cloud icon)
- Virtual pin mapping (V0, V1, V2, ...)

**Contoh diagram:**
```
┌──────────┐
│ DHT11    │──► V0 (Suhu)
│ LDR      │──► V1 (Cahaya)    ┌──────────┐
│ PIR      │──► V2 (Gerakan)──►│  ESP32   │
└──────────┘                   └────┬─────┘
                                    │ WiFi
                            ┌───────▼──────┐
                            │    Blynk     │
                            │  Dashboard   │
                            └──────────────┘
```

---

**4. Flowchart Logika (If-Then):**
- Aturan otomatis dalam bentuk diagram
- Mudah dipahami non-teknis
- Gunakan warna untuk decision (kuning) dan action (hijau)

**Contoh:**
```
[Baca Sensor] → [Suhu > 28°C?] ─YES→ [AC ON]
                       │
                       NO
                       ▼
              [Cahaya < 500?] ─YES→ [Lampu ON]
```

---

**5. Foto Komponen (Breadboard):**
- Foto breadboard dengan semua komponen
- **WAJIB:** Annotate setiap komponen (arrow + label)
- Background polos (white atau abu-abu)
- Lighting bagus (tidak ada bayangan)

**Tips foto:**
- Ambil dari atas (bird eye view)
- Fokus tajam, tidak blur
- Gunakan editing tool untuk tambah arrow & text
  - Canva: Elemen → Shapes → Arrow
  - PowerPoint: Insert → Shapes → Arrow

**Contoh annotation:**
```
[Arrow ke DHT11] → "DHT11: Sensor Suhu & Kelembapan"
[Arrow ke ESP32] → "ESP32: Microcontroller"
[Arrow ke Relay] → "Relay 2CH: Kontrol AC & Lampu"
```

---

**6. Manfaat & Efisiensi:**
- Bullet points singkat, jelas
- Fokus pada benefit untuk user
- Include angka (30%, Rp 500rb, etc.)

**Contoh:**
```
MANFAAT:
✓ Hemat energi 30-40% (estimasi)
✓ Kontrol dari smartphone (remote)
✓ Monitoring real-time 24/7
✓ Notifikasi otomatis (push notification)

EFISIENSI ENERGI:
✓ AC auto OFF saat tidak ada orang
✓ Lampu menyesuaikan cahaya alami
✓ Estimasi penghematan: Rp 500.000/bulan
✓ ROI (Return on Investment): 8 bulan
```

---

**7. QR Code (Opsional - Nilai Tambah):**
- QR code link ke video YouTube
- QR code link ke Blynk web dashboard (jika ada)
- Letakkan di corner bawah kanan

**Cara buat QR code (gratis):**
- Website: https://www.qr-code-generator.com/
- Masukkan URL video YouTube
- Download PNG

---

#### Checklist Poster:

**Konten:**
- [ ] Judul jelas dan menarik
- [ ] Denah bangunan dengan zona IoT
- [ ] Diagram sistem lengkap (sensor-ESP32-output-Blynk)
- [ ] Flowchart logika if-then
- [ ] Foto breadboard dengan label/annotation
- [ ] Manfaat & efisiensi energi
- [ ] QR code ke video (opsional)

**Desain:**
- [ ] Layout clean & tidak sesak (beri white space)
- [ ] Hierarchy jelas (info penting lebih besar)
- [ ] Warna konsisten (max 3 warna utama)
- [ ] Font max 2 jenis (heading + body)
- [ ] Font terbaca (minimal 12pt untuk body text)
- [ ] Alignment rapi (tidak miring-miring)

**Teknis:**
- [ ] Format: PDF atau JPG (high res)
- [ ] Resolution: 300 DPI (jika print)
- [ ] Ukuran: A3 Landscape (297×420mm)
- [ ] File size: < 10 MB (untuk upload/email)

---

#### Tools Poster (Gratis):

**1. Canva (RECOMMENDED - Paling Mudah!)**
- Website: https://www.canva.com
- Template poster gratis banyak
- Drag & drop, tidak perlu skill design
- Bisa collaborative (kelompok edit bareng)
- Export PDF high quality (300 DPI)

**Cara pakai:**
1. Sign up gratis
2. Search "Poster" → Filter by "Free"
3. Pilih template landscape
4. Ganti teks, gambar, warna sesuai konsep Anda
5. Download → PDF Print (high quality)

---

**2. PowerPoint/Google Slides**
- Bawaan Windows/Google
- Familiar untuk mahasiswa
- Bisa custom size ke A3

**Cara setup A3:**
1. Design → Slide Size → Custom
2. Width: 42 cm, Height: 29.7 cm (A3 Landscape)
3. Design poster di 1 slide
4. File → Save As → PDF

---

**3. Adobe Illustrator (Advanced)**
- Jika ada yang mahir design
- Professional tools
- Vector-based (scalable)

---

**4. Figma (Design Kolaboratif)**
- Website: https://www.figma.com
- Gratis untuk tim kecil
- Real-time collaboration
- Export PDF/PNG

---

#### Tips Desain Poster:

**1. Less is More**
- Jangan penuh sesak informasi
- Beri white space (ruang kosong)
- 60% konten, 40% white space

**2. Visual Hierarchy**
- Judul paling besar (48-60pt)
- Subheading menengah (24-36pt)
- Body text kecil (12-18pt)
- **Info penting = ukuran besar**

**3. Warna Konsisten**
- Gunakan max 3 warna utama
- Contoh: Biru (primary), Orange (accent), Abu-abu (text)
- Gunakan color palette generator: https://coolors.co

**4. Font Pairing**
- Max 2 jenis font:
  - **Heading:** Sans-serif tebal (Montserrat, Poppins)
  - **Body:** Sans-serif ringan atau Serif (Open Sans, Roboto)
- Hindari Comic Sans, Papyrus (tidak professional)

**5. Alignment Rapi**
- Gunakan grid/guideline
- Semua elemen rata (kiri, tengah, atau kanan)
- Jarak antar elemen konsisten

**6. Contrast**
- Text harus kontras dengan background
- Dark text on light background (atau sebaliknya)
- Hindari: kuning on white, abu on hitam

**7. Icon & Gambar**
- Gunakan icon gratis: Flaticon, Icons8
- Gambar high resolution (tidak pixelated)
- Consistent style (semua icon 1 style)

---

#### Contoh Workflow Pembuatan Poster:

**Minggu 1:**
- [ ] Kumpulkan semua material (denah, foto breadboard, flowchart)
- [ ] Pilih template Canva atau buat layout di PowerPoint
- [ ] Draft kasar layout

**Minggu 2:**
- [ ] Design poster lengkap
- [ ] Review dengan kelompok (apakah mudah dipahami?)
- [ ] Revisi berdasarkan feedback

**Minggu 3:**
- [ ] Finalisasi design
- [ ] Export PDF (300 DPI)
- [ ] Test print A4 dulu (untuk cek warna & keterbacaan)
- [ ] Print final A3 atau siapkan PDF untuk proyektor

---

### E. Kriteria Penilaian (Updated)

#### 1. KONSEP BANGUNAN (25%)
- Originalitas ide (5%)
- Relevansi dengan smart building (10%)
- Penjelasan zona & fungsi jelas (5%)
- Manfaat & efisiensi dijelaskan (5%)

#### 2. SISTEM IoT (30%)
- Fungsionalitas sistem (semua sensor & output jalan) (15%)
- Kode program (logika otomatis benar, komentar 60%+) (10%)
- Integrasi Blynk (monitoring smartphone) (5%)

#### 3. VIDEO DEMONSTRASI (25%)
- Clarity penjelasan konsep bangunan (10%)
- Kualitas video (audio jelas, visual terang, editing rapi) (5%)
- Demo sistem live (bekerja real, bukan simulasi) (10%)

#### 4. POSTER KONSEP (20%)
- Desain visual menarik & profesional (10%)
- Kelengkapan informasi (denah, diagram, foto, flowchart) (5%)
- Kemudahan dipahami oleh non-teknis (5%)

#### BONUS (Maksimal +10%)
- Fitur tambahan (Chart, advanced automation, multi-zone) (+5%)
- Kreativitas desain poster exceptional (+3%)
- Video editing sangat baik (slow-mo, split screen, subtitle) (+2%)

**Total: 100% (+ 10% bonus)**

---

### F. FAQ Konsep Baru

**Q: Apakah harus buat maket rumah/bangunan fisik?**
**A:** TIDAK WAJIB. Fokus ke sistem IoT di breadboard + video + poster. Maket fisik hanya opsional (nilai tambah kecil, max +2%).

**Q: Kalau tidak ada maket, bagaimana tunjukkan konsep bangunan?**
**A:** Gunakan denah digital (SketchUp, AutoCAD, atau hand-drawing scan) + poster + video penjelasan. Ini lebih profesional dan sesuai skill Arsitektur.

**Q: Komponen breadboard tidak rusak kalau sering dibongkar-pasang?**
**A:** Tidak, asalkan hati-hati. Justru ini bagus untuk adik tingkat bisa pakai lagi. Ajari mereka bongkar-pasang dengan benar.

**Q: Video harus diupload ke YouTube? Boleh Google Drive?**
**A:** YouTube Unlisted recommended (lebih professional, mudah embed di laporan). Tapi boleh Google Drive jika prefer. Pastikan link public/anyone with link can view.

**Q: Poster harus print atau boleh digital?**
**A:** Boleh digital (PDF ditampilkan di proyektor saat presentasi). Print A3 lebih bagus untuk dipajang tapi tidak wajib.

**Q: Berapa minimal sensor & output?**
**A:** Minimal 2 sensor + 2 output. Recommended: 3 sensor + 3 output untuk konsep lebih kaya dan comprehensive.

**Q: Apakah semua anggota kelompok harus muncul di video?**
**A:** Minimal suara/voice semua anggota (tidak harus face reveal). Tapi face reveal lebih professional dan menunjukkan teamwork.

**Q: Kalau sistem error saat demo live presentasi gimana?**
**A:** Makanya ada video backup! Jika live demo error, tunjukkan video. Tapi usahakan live demo sukses (test berkali-kali sebelumnya).

---

### G. Timeline Pengerjaan (4 Minggu)

**Minggu 1: Konsep & Perencanaan**
- Diskusi kelompok: tentukan tema (Smart Office, Home, etc.)
- Buat denah bangunan dengan zona IoT
- Tentukan sensor & output yang digunakan
- Buat flowchart logika sistem (if-then rules)
- **Deliverable:** Denah + flowchart draft

**Minggu 2: Implementasi Sistem IoT**
- Test sensor satu per satu (individual testing)
- Test output/aktuator satu per satu
- Gabungkan sensor + output (integration testing)
- Setup Blynk app (Template, Datastream, Widget)
- Test komunikasi ESP32 ↔ Blynk
- **Deliverable:** Sistem IoT di breadboard jalan 80%

**Minggu 3: Finalisasi & Dokumentasi**
- Finalisasi kode program (tambah komentar 60%+)
- Rekam video demonstrasi (3-5 menit, multiple takes)
- Buat poster konsep (Canva/PowerPoint, A3)
- Edit video (CapCut: cut, transition, text overlay)
- Upload video ke YouTube (Unlisted)
- **Deliverable:** Video + Poster + Kode final

**Minggu 4: Presentasi & Demo**
- Print poster A3 (atau siapkan PDF high-res)
- Bawa breadboard + ESP32 untuk demo live
- Siapkan HP dengan Blynk app installed & tested
- Latihan presentasi kelompok (timing 10 menit)
- **Presentasi di kelas** (7 menit presentasi + 3 menit Q&A)
- Demo live sistem bekerja (backup: video jika gagal)

---

### H. Deliverables Checklist

**File Digital (dikumpulkan via LMS/Email):**
- [ ] Video demonstrasi (link YouTube Unlisted)
- [ ] Poster konsep (PDF, 300 DPI, <10 MB)
- [ ] Kode program (.ino file, komentar 60%+)
- [ ] Denah bangunan (JPG/PNG/PDF)
- [ ] Laporan singkat (opsional, 1-2 halaman)

**Demo Live (bawa saat presentasi):**
- [ ] Breadboard + ESP32 (sistem lengkap, tested)
- [ ] HP dengan Blynk app (login, dashboard siap)
- [ ] Poster (print A3 atau laptop untuk proyektor)
- [ ] Kabel charging ESP32 + power bank/adaptor

**Presentasi:**
- [ ] Slide PPT (max 6 slides)
- [ ] Durasi 10 menit (7 presentasi + 3 Q&A)
- [ ] Semua anggota presentasi (bagi rata)

---

### I. Contoh Konsep Proyek

**1. Smart Home (Rumah Tinggal 2 Lantai)**
- **Zona:** Living Room, Bedroom, Kitchen, Bathroom
- **Sensor:** DHT11 (setiap ruangan), PIR (entrance), LDR (outdoor)
- **Output:** Relay AC (bedroom), Relay lampu (all rooms), OLED (living room)
- **Logika:** AC nyala jika suhu >28°C DAN ada orang di bedroom. Lampu nyala jika gelap DAN PIR detect motion.
- **Estimasi hemat:** 30% energi (AC auto off saat kosong)

**2. Smart Office (10 Workstations)**
- **Zona:** Open Space, Meeting Room, Pantry
- **Sensor:** DHT11 (open space + meeting room), PIR (entrance), LDR (ceiling)
- **Output:** Relay AC (2 unit), Relay lampu (3 zone), Buzzer (alarm suhu)
- **Logika:** AC/lampu auto berdasarkan occupancy. Buzzer bunyi jika suhu >32°C (warning overheat).
- **Estimasi hemat:** 35-40% energi

**3. Smart Hotel Room**
- **Zona:** Bedroom, Bathroom, Balcony
- **Sensor:** DHT11, PIR (door), LDR (window)
- **Output:** Relay AC, Relay lampu, OLED display (welcome message)
- **Logika:** Saat tamu masuk (PIR), OLED tampilkan "Welcome!". AC auto sesuai suhu preference. Lampu auto saat malam.
- **Estimasi hemat:** 25% energi (guest tidak perlu manual control)

**4. Smart Classroom**
- **Zona:** Ruang kelas (40 seats), Area Dosen
- **Sensor:** DHT11, PIR (pintu depan), LDR (jendela)
- **Output:** Relay AC (2 unit), Relay lampu (4 zone), Buzzer (bell otomatis)
- **Logika:** AC/lampu nyala saat PIR detect (kelas ada orang). Buzzer auto jam 07:00, 08:40, dst (schedule kuliah).
- **Estimasi hemat:** 40% energi (sering lupa matikan AC)

**5. Smart Greenhouse**
- **Zona:** Growing area, Irrigation system
- **Sensor:** DHT11 (suhu/humidity), LDR (sunlight), Soil moisture (opsional)
- **Output:** Relay fan (ventilation), Relay water pump (irrigation), Relay grow light
- **Logika:** Fan nyala jika suhu >35°C atau humidity >80%. Pump nyala jika soil dry (<30%). Grow light nyala jika kurang cahaya.
- **Estimasi:** Optimal growing condition 24/7

---

### J. Tips Sukses Proyek

#### Untuk Sistem IoT:
1. **Mulai sederhana:** Test 1 sensor → 2 sensor → 3 sensor (incremental)
2. **Dokumentasi progress:** Foto/video setiap tahap (berguna untuk laporan)
3. **Backup plan:** Siapkan kode alternatif jika sensor rusak (bisa pakai nilai simulasi)
4. **Test Blynk offline:** Pastikan sistem tetap jalan tanpa Blynk (failsafe mode)
5. **Cable management:** Rapi breadboard pakai zip-tie/tape (terlihat professional)

#### Untuk Video:
1. **Script dulu:** Tulis word-by-word apa yang akan diucapkan (latihan baca)
2. **Practice makes perfect:** Latihan 3-5x sebelum rekam final
3. **Lighting is key:** Rekam siang hari natural light atau gunakan ring light
4. **Stable camera:** Tripod HP (~Rp 50rb) atau letakkan HP di stack buku
5. **Voice over:** Jika video blur/gelap, bisa voice-over pakai recording terpisah

#### Untuk Poster:
1. **Less is more:** Jangan penuh sesak, beri white space 30-40%
2. **Get feedback:** Tunjukkan ke teman non-teknis, apakah mereka paham?
3. **Print test:** Print A4 dulu sebelum final A3 (cek warna & readability)
4. **High contrast:** Text harus sangat jelas terbaca dari jarak 2 meter
5. **Save multiple versions:** Simpan draft v1, v2, v3 (jaga-jaga perlu rollback)

---

### K. Kesimpulan Konsep Baru

✅ **Konsep baru ini LEBIH BAIK karena:**
1. **Sustainable** - Komponen reusable untuk adik tingkat
2. **Fokus Konsep** - Mahasiswa Arsitektur fokus ke desain, bukan craft
3. **Professional** - Video & poster = skill presentasi modern
4. **Praktis** - Demo lebih mudah, troubleshooting cepat
5. **Cost-Effective** - Hemat budget jangka panjang

✅ **Yang dipelajari mahasiswa:**
- Konsep smart building (zone planning, energy efficiency)
- IoT system design (sensor-controller-output)
- Programming & integration
- Video production (storyboard, recording, editing)
- Poster design (layout, visual communication)
- **Presentation skills** (public speaking, demo live)

✅ **Outcome:**
- **Portfolio-worthy project** (bisa ditunjukkan ke calon employer)
- **Real IoT skills** (applicable di industri smart building)
- **Communication skills** (video & poster = modern presentation)

---

**Selamat mengerjakan proyek dengan konsep baru! Fokus pada konsep, bukan craft. Quality over quantity! 🚀**

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
