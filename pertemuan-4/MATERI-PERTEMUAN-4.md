# PERTEMUAN 4: INTEGRASI SISTEM & PROYEK MAKET

**Mata Kuliah**: Bangunan Cerdas
**Durasi**: 3 SKS (150 menit)
**Sifat**: Workshop & Konsultasi Proyek

---

## 📋 TUJUAN PEMBELAJARAN

Setelah pertemuan ini, mahasiswa diharapkan dapat:
1. Mengintegrasikan minimal 3 sensor dan 3 output dalam satu sistem
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

## 📱 BAGIAN 2A: PLATFORM IoT BLYNK (50 menit)

### Pengenalan: Kenapa Perlu Blynk?

Sampai pertemuan 3, sistem smart building kita sudah bisa:
- ✅ Baca sensor (DHT11, LDR, PIR)
- ✅ Kontrol aktuator (Relay, LED, Buzzer)
- ✅ Display data di OLED
- ✅ Otomatis berdasarkan threshold

**Tapi... ada masalahnya:**
- ❌ Harus selalu di depan maket untuk lihat data
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

### L. Integrasi Blynk ke Proyek Maket

**Rekomendasi Penggunaan Blynk di Proyek:**

1. **Monitoring Real-time:**
   - Suhu, kelembapan, cahaya, status PIR
   - Tampilkan di Gauge & Value Display
   - Grafik historis 24 jam

2. **Remote Control:**
   - Kontrol relay AC, lampu, pompa
   - Gunakan Button/Switch widget
   - Bisa kontrol dari rumah saat maket di kampus!

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
- Integrasikan Blynk ke proyek maket Anda
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
