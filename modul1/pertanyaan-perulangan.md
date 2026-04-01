# **Percobaan 2A: Perulangan (for)**

## **Jawaban Pertanyaan Praktikum 1.6.4**

---

### **1. Gambarkan rangkaian schematic 5 LED running yang digunakan pada percobaan!**

Rangkaian menggunakan **5 LED** yang dihubungkan ke pin digital Arduino.

**Konfigurasi rangkaian:**

* LED 1 → Pin 2
* LED 2 → Pin 3
* LED 3 → Pin 4
* LED 4 → Pin 5
* LED 5 → Pin 6
* Semua kaki negatif LED → resistor → GND

**Penjelasan:**

* Setiap LED dikontrol oleh satu pin digital
* Setiap LED memiliki 2 kaki:
* Anoda (kaki panjang) → dihubungkan ke pin Arduino (2–6)
* Katoda (kaki pendek) → dihubungkan ke resistor → GND
* Resistor digunakan untuk membatasi arus
* Semua LED berbagi jalur GND

---

### **2. Jelaskan bagaimana program membuat efek LED berjalan dari kiri ke kanan!**

Efek LED berjalan dari kiri ke kanan dibuat menggunakan perulangan **for naik (increment)**.

```cpp id="y3y32l"
for (int ledPin = 2; ledPin < 7; ledPin++)
```

**Penjelasan:**

* `ledPin = 2` → mulai dari LED pertama
* `ledPin < 7` → berhenti di pin 6
* `ledPin++` → berpindah ke LED berikutnya

**Proses:**

1. LED pin 2 menyala → mati
2. LED pin 3 menyala → mati
3. LED pin 4 menyala → mati
4. LED pin 5 menyala → mati
5. LED pin 6 menyala → mati

Karena dilakukan berurutan dan diberi delay, terlihat seperti **LED berjalan dari kiri ke kanan**.

---

### **3. Jelaskan bagaimana program membuat LED kembali dari kanan ke kiri!**

Efek kembali dibuat dengan perulangan **for turun (decrement)**.

```cpp id="g1k8u6"
for (int ledPin = 6; ledPin >= 2; ledPin--)
```

**Penjelasan:**

* `ledPin = 6` → mulai dari LED terakhir
* `ledPin >= 2` → berhenti di LED pertama
* `ledPin--` → bergerak mundur

**Proses:**

1. LED pin 6 menyala → mati
2. LED pin 5 menyala → mati
3. LED pin 4 menyala → mati
4. LED pin 3 menyala → mati
5. LED pin 2 menyala → mati

Sehingga menghasilkan efek **LED kembali dari kanan ke kiri**.

---

# **4. Program: 3 LED kiri dan 2 LED kanan bergantian (sesuai 5 LED)**

---

## **Kode Program**

```cpp id="kkb7w4"
int timer = 200; // delay waktu

void setup() {
  // inisialisasi pin 2 sampai 6
  for (int ledPin = 2; ledPin < 7; ledPin++) {
    pinMode(ledPin, OUTPUT);
  }
}

void loop() {
  // === LED kiri menyala (pin 2,3,4) ===
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);

  digitalWrite(5, LOW);
  digitalWrite(6, LOW);

  delay(timer);

  // === LED kanan menyala (pin 5,6) ===
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);

  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);

  delay(timer);
}
```

---

## **Penjelasan Baris per Baris (README.md)**

```md id="hjflrz"
# Program LED Bergantian (5 LED)

## Inisialisasi
int timer = 200;
- Mengatur kecepatan perpindahan LED

## Setup
for (int ledPin = 2; ledPin < 7; ledPin++)
- Mengatur pin 2 sampai 6 sebagai OUTPUT

pinMode(ledPin, OUTPUT);
- Mengaktifkan pin sebagai output

## Loop Utama

### Bagian 1: LED kiri menyala
digitalWrite(2, HIGH);
digitalWrite(3, HIGH);
digitalWrite(4, HIGH);
- Menyalakan 3 LED sisi kiri

digitalWrite(5, LOW);
digitalWrite(6, LOW);
- Mematikan LED kanan

delay(timer);
- Memberi jeda

### Bagian 2: LED kanan menyala
digitalWrite(2, LOW);
digitalWrite(3, LOW);
digitalWrite(4, LOW);
- Mematikan LED kiri

digitalWrite(5, HIGH);
digitalWrite(6, HIGH);
- Menyalakan LED kanan

delay(timer);
- Memberi jeda sebelum mengulang
```

---

## **Alur Program**

```id="y0j23x"
Mulai
 ↓
LED kiri (2,3,4) menyala
 ↓
LED kanan mati
 ↓
Delay
 ↓
LED kanan (5,6) menyala
 ↓
LED kiri mati
 ↓
Delay
 ↓
Ulang terus
```

---
