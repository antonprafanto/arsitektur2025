# DAFTAR STUDI KASUS BLYNK IoT

**Mata Kuliah:** Bangunan Cerdas  
**Instruktur:** Anton Prafanto, S.Kom., M.T.

---

## 📚 PANDUAN LENGKAP

**Sebelum mulai, baca file ini terlebih dahulu:**
- **GLOSSARY-PEMULA.md** → Istilah dasar coding untuk pemula absolut

---

## 📋 DAFTAR 5 STUDI KASUS

### SC1: SMART OFFICE
**File:**
- 📄 `SC1-SMART-OFFICE.md` (Material)
- 💻 `SC1-smart-office.ino` (Arduino Code)

**Deskripsi:** Sistem kantor pintar dengan otomasi AC & Lampu  
**Sensor:** DHT11, LDR, PIR  
**Output:** Relay AC, Relay Lampu, Buzzer, 3x LED  
**Level:** Basic  
**Cocok untuk:** Pemula, pengenalan IoT

---

### SC2: SMART PARKING
**File:**
- 📄 `SC2-SMART-PARKING.md` (Material)
- 💻 `SC2-smart-parking.ino` (Arduino Code)

**Deskripsi:** Sistem parkir basement dengan multi-zone detection  
**Sensor:** PIR, DHT11, LDR, Button (simulasi slot)  
**Output:** LED RGB, Relay Fan, Relay Lampu, Buzzer  
**Level:** Intermediate  
**Fitur Unik:** LED RGB color mixing  
**Cocok untuk:** Mahasiswa yang suka visual feedback

---

### SC3: SMART HOME OLED
**File:**
- 📄 `SC3-SMART-HOME-OLED.md` (Material)
- 💻 `SC3-smart-home-oled.ino` (Arduino Code)

**Deskripsi:** Dashboard smart home dengan OLED display & button navigation  
**Sensor:** DHT11, PIR, LDR, 2x Button  
**Output:** OLED 0.96", Relay 2CH, Buzzer, 3x LED  
**Level:** Advanced  
**Fitur Unik:** Menu 3 halaman, Bar chart, Dual control (lokal + remote)  
**Cocok untuk:** Mahasiswa yang tertarik UI/UX

---

### SC4: SMART BEDROOM
**File:**
- 📄 `SC4-SMART-BEDROOM.md` (Material)
- 💻 `SC4-smart-bedroom.ino` (Arduino Code)

**Deskripsi:** Sistem kamar tidur dengan scene control & passive buzzer melody  
**Sensor:** DHT11, PIR, LDR, 5x Button (scene controller)  
**Output:** Relay 2CH, Passive Buzzer, 3x LED  
**Level:** Intermediate  
**Fitur Unik:** 5 button scene, Melody alarm, PWM dimming, 3 mode (Sleep/Wake/Away)  
**Cocok untuk:** Mahasiswa yang suka comfort automation

---

### SC5: SMART SECURITY
**File:**
- 📄 `SC5-SMART-SECURITY.md` (Material)
- 💻 `SC5-smart-security.ino` (Arduino Code)

**Deskripsi:** Sistem keamanan rumah dengan multi-zone & dual buzzer  
**Sensor:** DHT11, PIR, LDR, 4x Button (3 zone + ARM/DISARM)  
**Output:** Active + Passive Buzzer, Relay 2CH, 5x LED  
**Level:** Intermediate  
**Fitur Unik:** Multi-zone detection, LED blinking pattern, Grace period, State machine  
**Cocok untuk:** Mahasiswa yang tertarik security system

---

## 🎯 REKOMENDASI BELAJAR

### Untuk Pemula Absolut:
1. Baca **GLOSSARY-PEMULA.md** (30 menit)
2. Mulai dari **SC1** (paling mudah)
3. Lanjut **SC2**
4. **SC3** opsional (advanced)
5. **SC4** atau **SC5** sesuai minat

### Untuk Yang Sudah Pernah Coding:
- Langsung ke SC yang paling menarik
- SC3, SC4, SC5 = lebih challenging

---

## 📊 PERBANDINGAN CEPAT

| No | Nama | Level | Sensor | Output | Fitur Unik |
|----|------|-------|--------|--------|------------|
| SC1 | Smart Office | ⭐ Basic | 3 | 3 | Otomasi dasar |
| SC2 | Smart Parking | ⭐⭐ Medium | 4 | 4 | LED RGB |
| SC3 | Smart Home OLED | ⭐⭐⭐ Advanced | 5 | 5 | OLED menu |
| SC4 | Smart Bedroom | ⭐⭐ Medium | 5 | 4 | Melody alarm |
| SC5 | Smart Security | ⭐⭐ Medium | 5 | 5 | Multi-zone |

---

## 🔧 SETUP UMUM

Semua studi kasus membutuhkan:
1. **Arduino IDE** (1.8.19 atau lebih baru)
2. **Library:**
   - WiFi (built-in ESP32)
   - Blynk (by Volodymyr Shymanskyy)
   - DHT sensor library (by Adafruit)
   - Adafruit SSD1306 (khusus SC3)
3. **Hardware:** Lihat masing-masing file SC
4. **Akun Blynk:** Daftar gratis di https://blynk.cloud

---

## 💡 TIPS SUKSES

1. **Jangan skip GLOSSARY** → Ini kunci pahami istilah dasar
2. **Copy-paste OK** untuk pemula → Fokus lihat hasil dulu
3. **Wiring hati-hati** → Double-check sebelum power ON
4. **Serial Monitor** → Tools terbaik untuk debugging
5. **Error normal** → Baca section ERROR UMUM di setiap SC
6. **Bertahap** → Jangan langsung ke SC advanced

---

## 📁 STRUKTUR FILE

```
pertemuan-4/
├── GLOSSARY-PEMULA.md         (Baca ini PERTAMA!)
├── README-STUDI-KASUS.md      (File ini)
├── SC1-SMART-OFFICE.md
├── SC1-smart-office.ino
├── SC2-SMART-PARKING.md
├── SC2-smart-parking.ino
├── SC3-SMART-HOME-OLED.md
├── SC3-smart-home-oled.ino
├── SC4-SMART-BEDROOM.md
├── SC4-smart-bedroom.ino
├── SC5-SMART-SECURITY.md
└── SC5-smart-security.ino
```

---

**Update:** 24 November 2025  
**Status:** ✅ Complete & Tested  
**Rating:** 9/10 Beginner-Friendly

**Selamat Belajar IoT! 🚀**
