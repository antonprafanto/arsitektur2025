# TUGAS 3: TEMPLATE PERSIAPAN PROYEK AKHIR

## Nama Proyek: _______________________________

## Anggota Kelompok:
1. _______________________________
2. _______________________________
3. _______________________________

## Tema Proyek:
- [ ] Smart Home
- [ ] Smart Office
- [ ] Smart Parking
- [ ] Smart Greenhouse
- [ ] Lainnya: _______________________

## Sensor yang Digunakan (min 2):
- [ ] DHT11 (Suhu & Kelembapan)
- [ ] LDR (Cahaya)
- [ ] PIR (Gerakan)
- [ ] Lainnya: _______________________

## Output yang Digunakan (min 2):
- [ ] Relay (Lampu/AC)
- [ ] OLED Display
- [ ] Buzzer
- [ ] LED
- [ ] Lainnya: _______________________

## Logika Sistem:
Jelaskan dengan kalimat sederhana bagaimana sistem bekerja:

Contoh:
"Lampu nyala otomatis jika gelap DAN ada orang. 
AC nyala jika suhu >28°C DAN ada orang.
OLED tampilkan suhu, kelembapan, status lampu & AC.
Buzzer bunyi jika suhu >35°C (alarm)."

Logika Anda:
_________________________________________________
_________________________________________________
_________________________________________________
_________________________________________________

## Diagram Blok:

```
[Sensor 1] ────┐
               │
[Sensor 2] ────┤──→ [ESP32] ──→ [Output 1]
               │         │
[Sensor 3] ────┘         │──→ [Output 2]
                         │
                         └──→ [OLED Display]
```

## Flowchart Sederhana:
(Buat dengan tangan atau draw.io)

1. Baca semua sensor
2. Jika [kondisi 1] → lakukan [aksi 1]
3. Jika [kondisi 2] → lakukan [aksi 2]
4. Update display
5. Ulangi

## Target Penyelesaian:
- Pertemuan 4: Konsultasi & demo prototype
- Minggu depan: Finalisasi maket & dokumentasi

## Catatan & Pertanyaan:
_________________________________________________
_________________________________________________
_________________________________________________

---

**TIPS:**
- Mulai dengan kode sederhana, test tiap sensor terpisah
- Gabungkan step by step, jangan langsung semua
- Dokumentasikan setiap progress
- Jangan ragu konsultasi dengan dosen!
