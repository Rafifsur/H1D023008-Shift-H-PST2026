# Percobaan 2A: Perulangan (for)

## Jawaban Pertanyaan Praktikum 1.6.4

---

## 1. Gambarkan rangkaian schematic 5 LED running yang digunakan pada percobaan!

Rangkaian menggunakan **5 LED** yang dihubungkan ke pin digital Arduino.

![Schematic](modul1/schematic.png)

🔗 Link Tinkercad:
[https://www.tinkercad.com/things/5Lz7ddjyz3D-modul-1-praktikum](https://www.tinkercad.com/things/5Lz7ddjyz3D-modul-1-praktikum)

### Konfigurasi Rangkaian:

* LED 1 → Pin 2
* LED 2 → Pin 3
* LED 3 → Pin 4
* LED 4 → Pin 5
* LED 5 → Pin 6

### Penjelasan:

* Setiap LED memiliki dua kaki:

  * **Anoda (kaki panjang)** → dihubungkan ke pin Arduino (2–6)
  * **Katoda (kaki pendek)** → dihubungkan ke **resistor 220Ω → GND**
* Resistor berfungsi untuk membatasi arus agar LED tidak rusak
* Semua LED terhubung ke jalur GND yang sama
* Rangkaian ini memungkinkan setiap LED dikontrol secara individual

---

## 2. Jelaskan bagaimana program membuat efek LED berjalan dari kiri ke kanan!

Efek LED berjalan dari kiri ke kanan dibuat menggunakan perulangan **for dengan increment (++)**.

```cpp
for (int ledPin = 2; ledPin < 7; ledPin++)
```

### Penjelasan:

* `ledPin = 2` → memulai dari LED pertama
* `ledPin < 7` → berhenti di pin 6
* `ledPin++` → berpindah ke LED berikutnya

### Proses:

1. LED pin 2 menyala → mati
2. LED pin 3 menyala → mati
3. LED pin 4 menyala → mati
4. LED pin 5 menyala → mati
5. LED pin 6 menyala → mati

Karena dilakukan berurutan dengan delay, maka terlihat seperti **LED berjalan dari kiri ke kanan**.

---

## 3. Jelaskan bagaimana program membuat LED kembali dari kanan ke kiri!

Efek kembali dibuat menggunakan perulangan **for dengan decrement (--)**.

```cpp
for (int ledPin = 6; ledPin >= 2; ledPin--)
```

### Penjelasan:

* `ledPin = 6` → mulai dari LED terakhir
* `ledPin >= 2` → berhenti di LED pertama
* `ledPin--` → bergerak mundur

### Proses:

1. LED pin 6 menyala → mati
2. LED pin 5 menyala → mati
3. LED pin 4 menyala → mati
4. LED pin 3 menyala → mati
5. LED pin 2 menyala → mati

Sehingga menghasilkan efek **LED kembali dari kanan ke kiri**.

---

## 4. Program LED 3 Kiri dan 3 Kanan Bergantian (6 LED)

### Kode Program:

```cpp
void setup() {
  for (int i = 2; i <= 7; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // LED kanan menyala (pin 5, 6, 7)
  digitalWrite(7, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);
  digitalWrite(2, LOW);
  delay(1000);

  // LED kiri menyala (pin 2, 3, 4)
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(2, HIGH);
  delay(1000);
}
```

---

## Penjelasan Baris per Baris

```md
# Program LED Bergantian (3 Kiri - 3 Kanan)

## Setup
for (int i = 2; i <= 7; i++)
- Mengatur pin 2 sampai 7 sebagai OUTPUT

pinMode(i, OUTPUT);
- Mengaktifkan pin sebagai output

## Loop Utama

### Bagian 1 (LED kanan menyala)
digitalWrite(7, HIGH);
digitalWrite(6, HIGH);
digitalWrite(5, HIGH);
- Menyalakan LED sisi kanan

digitalWrite(4, LOW);
digitalWrite(3, LOW);
digitalWrite(2, LOW);
- Mematikan LED sisi kiri

delay(1000);
- Memberi jeda 1 detik

### Bagian 2 (LED kiri menyala)
digitalWrite(7, LOW);
digitalWrite(6, LOW);
digitalWrite(5, LOW);
- Mematikan LED kanan

digitalWrite(4, HIGH);
digitalWrite(3, HIGH);
digitalWrite(2, HIGH);
- Menyalakan LED kiri

delay(1000);
- Memberi jeda sebelum mengulang
```

---

## Alur Program

```md
Mulai
 ↓
LED kanan (5,6,7) menyala
 ↓
LED kiri mati
 ↓
Delay
 ↓
LED kiri (2,3,4) menyala
 ↓
LED kanan mati
 ↓
Delay
 ↓
Ulang terus
```

---
