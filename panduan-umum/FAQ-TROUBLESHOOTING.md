# FAQ & TROUBLESHOOTING
## Panduan Mengatasi Masalah Umum IoT dengan ESP32

---

## 📱 MASALAH UPLOAD & KONEKSI

### ❓ ESP32 tidak terdeteksi di Arduino IDE (tidak ada Port)

**Penyebab:**
- Driver USB-to-Serial belum terinstall
- Kabel USB rusak atau hanya untuk charging
- Port USB laptop bermasalah

**Solusi:**
1. **Install Driver:**
   - Cek tipe chip USB: CH340 atau CP2102
   - Download driver dari:
     - CH340: https://sparks.gogo.co.nz/ch340.html
     - CP2102: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers
   - Install dan restart komputer

2. **Cek Kabel USB:**
   - Ganti dengan kabel USB yang bisa transfer data
   - Kabel charging biasa tidak berfungsi

3. **Coba Port Lain:**
   - Coba port USB lain di laptop
   - Hindari USB hub (langsung ke laptop)

4. **Cek Device Manager (Windows):**
   - Buka Device Manager
   - Lihat di "Ports (COM & LPT)"
   - Jika ada "Unknown Device" → driver belum terinstall

---

### ❓ Error "Failed to connect to ESP32"

**Penyebab:**
- ESP32 tidak masuk boot mode
- Port COM salah
- Upload speed terlalu tinggi

**Solusi:**
1. **Manual Boot Mode:**
   - Tekan dan TAHAN tombol **BOOT**
   - Klik tombol **Upload** di Arduino IDE
   - Tahan BOOT sampai muncul "Connecting..."
   - Lepas tombol BOOT setelah upload dimulai

2. **Pilih Port yang Benar:**
   - Tools → Port → Pilih COM yang ada
   - Cabut-pasang USB untuk lihat port mana yang muncul/hilang

3. **Turunkan Upload Speed:**
   - Tools → Upload Speed → Pilih **115200**
   - Default 921600 kadang tidak stabil

4. **Tekan Tombol EN (Reset):**
   - Tekan EN sebelum upload
   - Atau tekan BOOT + EN, lepas EN, lepas BOOT

---

### ❓ Upload berhasil tapi program tidak jalan

**Penyebab:**
- Program crash/error runtime
- Power tidak cukup
- Code infinite loop di setup()

**Solusi:**
1. **Cek Serial Monitor:**
   - Buka Serial Monitor (baud 115200)
   - Lihat ada pesan error?
   - Jika blank → program hang

2. **Upload Kode Sederhana (Test):**
   ```cpp
   void setup() {
     Serial.begin(115200);
     pinMode(2, OUTPUT);
   }
   void loop() {
     Serial.println("Berjalan");
     digitalWrite(2, HIGH);
     delay(500);
     digitalWrite(2, LOW);
     delay(500);
   }
   ```
   - Jika ini jalan → masalah di kode Anda
   - Jika tidak → masalah hardware

3. **Power Supply:**
   - Gunakan adaptor 5V 2A (bukan USB laptop)
   - USB laptop kadang tidak cukup untuk relay/banyak sensor

---

## 🌡️ MASALAH SENSOR DHT11

### ❓ DHT11 selalu return "NaN" atau "Failed to read"

**Penyebab:**
- Koneksi longgar
- Pin salah
- Delay kurang
- Sensor rusak

**Solusi:**
1. **Cek Koneksi:**
   - VCC → 3.3V (bukan 5V untuk ESP32)
   - DATA → GPIO15 (atau pin yang di-define)
   - GND → GND
   - Pastikan kabel tidak longgar

2. **Tambah Delay di Setup:**
   ```cpp
   void setup() {
     Serial.begin(115200);
     dht.begin();
     delay(2000);  // PENTING! DHT butuh waktu settling
   }
   ```

3. **Delay Antar Pembacaan:**
   - DHT11 max sampling 1 Hz (1 detik)
   - Jangan baca lebih cepat dari 2 detik
   ```cpp
   void loop() {
     float t = dht.readTemperature();
     delay(2000);  // Minimal 2 detik
   }
   ```

4. **Tambah Pull-up Resistor:**
   - Pasang resistor 10K antara DATA dan VCC
   - Beberapa modul DHT11 sudah punya built-in

5. **Test Sensor:**
   ```cpp
   void loop() {
     float t = dht.readTemperature();
     float h = dht.readHumidity();

     if (isnan(t) || isnan(h)) {
       Serial.println("Sensor ERROR!");
     } else {
       Serial.print("OK: ");
       Serial.print(t);
       Serial.print(" °C, ");
       Serial.print(h);
       Serial.println(" %");
     }
     delay(2000);
   }
   ```

6. **Ganti Sensor:**
   - DHT11 murah dan rentan rusak
   - Coba sensor lain untuk test

---

### ❓ Data DHT11 tidak akurat (selisih >5°C)

**Penyebab:**
- DHT11 bukan sensor presisi (akurasi ±2°C)
- Sensor terlalu dekat sumber panas
- Perlu kalibrasi

**Solusi:**
1. **Jauhkan dari Sumber Panas:**
   - ESP32 sendiri menghasilkan panas
   - Resistor, LED, relay juga panas
   - Gunakan kabel jumper 10-15cm

2. **Kalibrasi Manual:**
   - Bandingkan dengan termometer akurat
   - Tambah/kurang offset
   ```cpp
   float suhuKalibrasi = suhu - 2.0;  // Offset -2°C
   ```

3. **Upgrade ke DHT22:**
   - Akurasi lebih baik (±0.5°C)
   - Range lebih luas
   - Kode sama dengan DHT11

---

## 💡 MASALAH SENSOR LDR

### ❓ Nilai LDR tidak berubah (tetap 0 atau 4095)

**Penyebab:**
- Tidak pakai voltage divider
- Pin ADC salah
- LDR rusak

**Solusi:**
1. **Pastikan Pakai Voltage Divider:**
   ```
   3.3V
     │
     ├── LDR ────┬──── GPIO34 (ADC)
     │           │
     └── 10KΩ ───┴──── GND
   ```
   - WAJIB ada resistor 10K
   - Jika tidak ada → nilai tidak berubah

2. **Gunakan Pin ADC yang Benar:**
   - Pin ADC ESP32: GPIO32, 33, 34, 35, 36, 39
   - GPIO34-39 = input only (paling aman)
   - Jangan pakai GPIO25, 26 (DAC, bisa conflict)

3. **Test LDR dengan Multimeter:**
   - Ukur resistansi LDR
   - Gelap: ~1MΩ (1.000.000 ohm)
   - Terang: ~1KΩ (1.000 ohm)
   - Jika tidak berubah → LDR rusak

4. **Kode Test Dasar:**
   ```cpp
   void loop() {
     int nilai = analogRead(34);
     Serial.print("LDR: ");
     Serial.println(nilai);
     delay(500);
   }
   ```
   - Tutup LDR dengan tangan → nilai harus berubah

---

### ❓ LDR tidak stabil (nilai loncat-loncat)

**Penyebab:**
- Noise elektrik
- Kabel terlalu panjang
- Interferensi

**Solusi:**
1. **Moving Average (Filter Software):**
   ```cpp
   int bacaLDRStabil() {
     long total = 0;
     for (int i = 0; i < 10; i++) {
       total += analogRead(34);
       delay(10);
     }
     return total / 10;
   }
   ```

2. **Tambah Kapasitor (Filter Hardware):**
   - Pasang kapasitor 0.1uF paralel dengan LDR
   - Atau 10uF antara GPIO dan GND

3. **Kurangi Panjang Kabel:**
   - Kabel sensor maksimal 30cm
   - Lebih panjang → lebih banyak noise

---

## 🚨 MASALAH SENSOR PIR

### ❓ PIR terus terdeteksi meskipun tidak ada gerakan

**Penyebab:**
- Belum kalibrasi
- Terlalu dekat sumber panas
- Sensitivity terlalu tinggi

**Solusi:**
1. **Tunggu Kalibrasi:**
   - PIR butuh 30-60 detik settling setelah power on
   - Jangan ada gerakan selama kalibrasi
   ```cpp
   void setup() {
     pinMode(13, INPUT);
     Serial.println("Kalibrasi 60 detik...");
     delay(60000);
     Serial.println("Siap!");
   }
   ```

2. **Jauhkan dari Sumber Panas:**
   - Jangan dekat AC, heater, jendela
   - Sinar matahari langsung → false positive
   - Pasang di tempat teduh

3. **Kurangi Sensitivity:**
   - Putar potensiometer S berlawanan arah jarum jam
   - Mulai dari posisi minimum

4. **Kurangi Time Delay:**
   - Putar potensiometer T ke minimum
   - Delay minimal ~2-3 detik

---

### ❓ PIR tidak pernah terdeteksi

**Penyebab:**
- VCC tidak sesuai
- Sensitivity terlalu rendah
- Jarak terlalu jauh

**Solusi:**
1. **Cek Tegangan VCC:**
   - Kebanyakan PIR: 5V
   - Beberapa bisa 3.3V-5V
   - Cek datasheet atau coba 5V

2. **Naikkan Sensitivity:**
   - Putar potensiometer S searah jarum jam
   - Coba posisi maksimal untuk test

3. **Gerakan Jelas:**
   - Gerakkan tangan 1-2 meter dari sensor
   - Gerakan terlalu lambat/halus tidak terdeteksi
   - PIR mendeteksi perubahan radiasi IR, bukan objek diam

4. **Kode Test Sederhana:**
   ```cpp
   void loop() {
     int pir = digitalRead(13);
     Serial.print("PIR: ");
     Serial.println(pir == HIGH ? "TERDETEKSI" : "Normal");
     delay(500);
   }
   ```

---

## 🔌 MASALAH RELAY

### ❓ Relay tidak klik (tidak ada bunyi)

**Penyebab:**
- VCC relay tidak 5V
- Pin GPIO salah
- Relay rusak

**Solusi:**
1. **Pastikan VCC = 5V:**
   - Relay module butuh 5V untuk coil
   - Jika pakai 3.3V → tidak cukup tenaga
   ```
   Relay VCC → ESP32 5V (atau VIN)
   Relay GND → ESP32 GND
   ```

2. **Cek Pin GPIO:**
   ```cpp
   void setup() {
     pinMode(25, OUTPUT);
   }
   void loop() {
     Serial.println("Relay ON");
     digitalWrite(25, HIGH);
     delay(2000);
     Serial.println("Relay OFF");
     digitalWrite(25, LOW);
     delay(2000);
   }
   ```
   - Harus ada bunyi "klik" saat HIGH

3. **Ukur Tegangan Pin IN:**
   - Saat digitalWrite(pin, HIGH)
   - Ukur tegangan pin IN dengan multimeter
   - Harus ~3.3V
   - Jika 0V → masalah di ESP32 atau kode

4. **Coba Relay Lain:**
   - Relay mekanis bisa rusak
   - Coba channel lain (IN2, IN3)

---

### ❓ Relay klik tapi LED tidak nyala

**Penyebab:**
- Terminal output salah
- Polaritas LED terbalik
- Beban terlalu besar

**Solusi:**
1. **Cek Terminal Output:**
   ```
   Sumber (5V) → COM
   NO → LED (+) → Resistor → GND
   ```
   - COM = Common (input)
   - NO = Normally Open (output saat relay ON)
   - NC = Normally Closed (output saat relay OFF)

2. **Cek Polaritas LED:**
   - Kaki panjang = Anoda (+) ke NO
   - Kaki pendek = Katoda (-) ke resistor

3. **Pastikan Ada Resistor:**
   - LED butuh resistor 220Ω
   - Tanpa resistor → LED rusak

4. **Test dengan Multimeter:**
   - Set multimeter ke continuity mode
   - Cek koneksi COM ke NO saat relay ON
   - Harus ada continuity (bunyi beep)

---

## 📺 MASALAH OLED DISPLAY

### ❓ OLED tidak tampil apa-apa (blank/hitam)

**Penyebab:**
- Alamat I2C salah
- Koneksi I2C longgar
- Library tidak terinstall

**Solusi:**
1. **Scan Alamat I2C:**
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
     Serial.println("Done");
   }

   void loop() {}
   ```
   - Upload dan buka Serial Monitor
   - Lihat alamat yang terdeteksi (biasanya 0x3C atau 0x3D)

2. **Sesuaikan Alamat di Kode:**
   ```cpp
   #define SCREEN_ADDRESS 0x3C  // Ganti sesuai hasil scan
   ```

3. **Cek Koneksi I2C:**
   ```
   OLED VCC → ESP32 3.3V
   OLED GND → ESP32 GND
   OLED SDA → ESP32 GPIO21
   OLED SCL → ESP32 GPIO22
   ```

4. **Install Library:**
   - Adafruit SSD1306
   - Adafruit GFX Library

5. **Test Kode Sederhana:**
   ```cpp
   void setup() {
     if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
       Serial.println("OLED gagal!");
       while(1);
     }
     display.clearDisplay();
     display.setTextSize(1);
     display.setTextColor(SSD1306_WHITE);
     display.setCursor(0, 0);
     display.println("TEST OK");
     display.display();
   }
   ```

---

## 🔋 MASALAH POWER & SISTEM

### ❓ ESP32 restart sendiri (reboot terus)

**Penyebab:**
- Power supply tidak cukup
- Arus relay terlalu besar
- Code error (watchdog timeout)

**Solusi:**
1. **Gunakan Power Supply yang Cukup:**
   - Minimal: 5V 2A
   - USB laptop hanya ~500mA (tidak cukup untuk relay)
   - Gunakan adaptor atau power bank 2A+

2. **Pisahkan Power ESP32 dan Relay:**
   ```
   Adaptor 5V 2A → Terminal Block
      ├─→ ESP32 VIN
      └─→ Relay VCC
   GND semua terhubung (common ground)
   ```

3. **Tambah Kapasitor:**
   - Pasang kapasitor 1000uF di VIN ESP32
   - Stabilkan tegangan saat relay switch

4. **Cek Kode (Watchdog):**
   - Watchdog timeout jika loop() tidak return
   - Tambah `delay(10)` atau `yield()` di loop

5. **Monitor Serial untuk Error:**
   - Buka Serial Monitor saat reboot
   - Lihat pesan error sebelum reboot
   ```
   Guru Meditation Error
   Brownout detector was triggered
   → Power tidak cukup!
   ```

---

## 🐛 MASALAH KODE PROGRAM

### ❓ Error "... was not declared in this scope"

**Penyebab:**
- Variabel belum di-declare
- Typo nama variabel
- Variable scope salah

**Solusi:**
```cpp
// ❌ SALAH:
void loop() {
  int suhu = 25;
}
void fungsiLain() {
  Serial.println(suhu);  // Error! suhu tidak dikenal
}

// ✅ BENAR:
int suhu = 25;  // Global variable

void loop() {
  suhu = 30;  // Bisa diakses
}

void fungsiLain() {
  Serial.println(suhu);  // OK!
}
```

---

### ❓ Program hang / tidak responsif

**Penyebab:**
- Infinite loop tanpa delay
- Blocking code (delay terlalu lama)

**Solusi:**
```cpp
// ❌ SALAH: Infinite loop tanpa delay
while(true) {
  // kode
}

// ✅ BENAR: Tambah delay
while(true) {
  // kode
  delay(10);  // Beri ESP32 waktu untuk task lain
}

// Atau gunakan non-blocking code
unsigned long previousMillis = 0;
void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;
    // Kode dijalankan setiap 1 detik
  }
  // Loop tetap berjalan
}
```

---

## 📱 MASALAH BLYNK & WIFI

### ❓ WiFi tidak connect (stuck di "Connecting...")

**Penyebab:**
- SSID atau password salah
- WiFi 5GHz (ESP32 hanya support 2.4GHz)
- Router terlalu jauh
- Channel WiFi tidak compatible

**Solusi:**
1. **Cek Credentials:**
   ```cpp
   char ssid[] = "NAMA_WIFI_ANDA";  // Case sensitive!
   char pass[] = "PASSWORD_WIFI_ANDA";
   ```
   - SSID harus persis sama (huruf besar/kecil)
   - Password jangan ada spasi di awal/akhir

2. **Pastikan WiFi 2.4GHz:**
   - ESP32 tidak support WiFi 5GHz
   - Cek setting router: enable 2.4GHz
   - Atau buat SSID terpisah untuk 2.4GHz

3. **Dekatkan Router:**
   - ESP32 butuh sinyal cukup kuat
   - Coba dekatkan dulu untuk test
   - Cek signal strength di Serial Monitor:
   ```cpp
   Serial.print("RSSI: ");
   Serial.println(WiFi.RSSI());
   // -30 to -50 dBm = Excellent
   // -50 to -60 dBm = Good
   // -60 to -70 dBm = Fair
   // -70 to -80 dBm = Weak
   ```

4. **Test dengan Hotspot HP:**
   - Buat hotspot dari HP (2.4GHz)
   - Nama: TestWiFi, Password: 12345678
   - Jika connect → masalah di router
   - Jika tidak → masalah di ESP32 atau kode

5. **Reset WiFi Settings:**
   ```cpp
   void setup() {
     WiFi.disconnect(true);  // Reset WiFi
     WiFi.mode(WIFI_STA);
     delay(100);
     WiFi.begin(ssid, pass);
   }
   ```

---

### ❓ WiFi connect tapi Blynk offline (Device Offline)

**Penyebab:**
- Auth Token salah
- Template ID/Name tidak match
- Koneksi internet bermasalah
- Firewall memblok

**Solusi:**
1. **Cek Auth Token:**
   - **Via WEB (RECOMMENDED):** Buka browser → https://blynk.cloud → Devices → Pilih device → Device Info → Copy BLYNK_AUTH_TOKEN (klik icon ⎘)
   - Via App: Buka Blynk app → Device → Info → Auth Token (susah copy di HP)
   - Copy ulang dengan teliti (jangan ketik manual)
   - Pastikan tidak ada spasi di awal/akhir
   ```cpp
   #define BLYNK_AUTH_TOKEN "abcdefgh123456789ijklmnopqrstuv"
   ```

2. **Cek Template ID:**
   - Template ID harus sama dengan di Blynk Console
   - Format: TMPL4xxxxxxxxx
   ```cpp
   #define BLYNK_TEMPLATE_ID "TMPL4xRa1bXYZ"  // Sesuaikan!
   #define BLYNK_TEMPLATE_NAME "LED Control"
   ```

3. **Test Koneksi Internet:**
   ```cpp
   void setup() {
     // ... WiFi connect ...

     if (WiFi.status() == WL_CONNECTED) {
       Serial.println("WiFi OK!");
       Serial.print("IP: ");
       Serial.println(WiFi.localIP());

       // Test ping google
       Serial.println("Test ping...");
       // Jika bisa browsing dari laptop di WiFi yang sama → OK
     }
   }
   ```

4. **Cek Firewall/Network:**
   - Beberapa jaringan kampus/kantor memblok Blynk
   - Coba WiFi rumah atau hotspot HP
   - Blynk server: blynk.cloud (port 80/443)

5. **Recreate Device:**
   - Di Blynk Console, hapus device lama
   - Buat device baru dari template
   - Copy Auth Token yang baru
   - Upload kode dengan token baru

---

### ❓ Blynk sering disconnect/reconnect

**Penyebab:**
- Signal WiFi lemah
- Router restart
- Tidak ada Blynk.run() di loop
- Delay() terlalu lama di loop

**Solusi:**
1. **Pastikan Blynk.run() Ada di Loop:**
   ```cpp
   void loop() {
     Blynk.run();  // WAJIB! Di awal loop()

     // Kode lainnya di bawah
   }
   ```

2. **Hindari delay() Lama:**
   ```cpp
   // ❌ SALAH:
   void loop() {
     Blynk.run();
     delay(10000);  // 10 detik → Blynk timeout!
   }

   // ✅ BENAR: Gunakan millis()
   unsigned long lastTime = 0;
   void loop() {
     Blynk.run();

     if (millis() - lastTime >= 10000) {
       lastTime = millis();
       // Kode yang dijalankan setiap 10 detik
     }
   }
   ```

3. **Implementasi Auto-Reconnect:**
   - Gunakan kode dari kode-13-blynk-wifi-reconnect.ino
   - Check koneksi setiap 10 detik
   - Reconnect otomatis jika disconnect

4. **Perbaiki Signal WiFi:**
   - Gunakan antena eksternal ESP32
   - Tambah WiFi repeater
   - Pindahkan router lebih dekat

---

### ❓ Widget di app tidak update (data lama terus)

**Penyebab:**
- Datastream tidak di-link ke widget
- Virtual pin salah
- Rate limiting (kirim terlalu cepat)
- Blynk.virtualWrite() tidak dipanggil

**Solusi:**
1. **Cek Datastream & Widget:**
   - Buka Blynk Console → Datastream
   - Pastikan V0, V1, etc sudah dibuat
   - Buka Web Dashboard/Mobile App
   - Edit widget → pastikan linked ke Virtual Pin yang benar

2. **Cek Virtual Pin di Kode:**
   ```cpp
   Blynk.virtualWrite(V0, suhu);  // V0 harus match dengan datastream
   ```

3. **Rate Limiting:**
   - Blynk free plan: max 10 writes/second
   - Kirim data maksimal setiap 1-2 detik
   ```cpp
   unsigned long lastSend = 0;
   void loop() {
     Blynk.run();

     if (millis() - lastSend >= 2000) {  // Setiap 2 detik
       lastSend = millis();
       Blynk.virtualWrite(V0, suhu);
     }
   }
   ```

4. **Serial Monitor Debug:**
   ```cpp
   if (Blynk.connected()) {
     Blynk.virtualWrite(V0, suhu);
     Serial.print("[Blynk] Sent V0: ");
     Serial.println(suhu);
   } else {
     Serial.println("[Blynk] Disconnected!");
   }
   ```

---

### ❓ Push notification tidak muncul di HP

**Penyebab:**
- Event belum dibuat di Blynk Console
- Enable Notification = OFF
- Izin notification di HP diblok
- Event code tidak match

**Solusi:**
1. **Buat Event di Blynk Console:**
   - Developer Zone → Events → New Event
   - Event Code: `high_temp` (harus sama dengan kode)
   - Name: "High Temperature"
   - Enable Notification: **ON** ✓
   - Save

2. **Cek Event Code di Kode:**
   ```cpp
   Blynk.logEvent("high_temp", "Suhu: 35°C");
   //             ^^^^^^^^^^
   //             Harus sama dengan Event Code!
   ```

3. **Izin Notification di HP:**
   - Android: Settings → Apps → Blynk → Notifications → Allow
   - iOS: Settings → Blynk → Notifications → Allow

4. **Cek Limit Notification:**
   - Free plan: 1 notification/minute
   - Max 100 notifications/day
   - Implementasi cooldown di kode:
   ```cpp
   unsigned long lastNotif = 0;
   if (millis() - lastNotif >= 60000) {  // 60 detik
     Blynk.logEvent("high_temp", "Alert!");
     lastNotif = millis();
   }
   ```

5. **Test di Serial Monitor:**
   ```cpp
   Serial.println("[Blynk] Sending notification...");
   Blynk.logEvent("high_temp", "Test");
   Serial.println("[Blynk] Notification sent!");
   ```
   - Jika Serial print muncul tapi notifikasi tidak → cek setting di Blynk Console

---

## 📞 KONTAK BANTUAN

Jika masih mengalami masalah setelah mencoba solusi di atas:

1. **Forum Arduino Indonesia:**
   - https://forum.arduino.cc
   - https://www.facebook.com/groups/arduino.indonesia

2. **Konsultasi Dosen/Asisten:**
   - Bawa laptop dan hardware
   - Siapkan deskripsi masalah yang jelas

3. **Dokumentasikan Error:**
   - Screenshot Serial Monitor
   - Foto wiring
   - Salin pesan error lengkap

---

**Troubleshooting adalah bagian dari belajar. Sabar dan teliti! 🔍**
