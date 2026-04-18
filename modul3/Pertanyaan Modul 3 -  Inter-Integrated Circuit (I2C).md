# Percobaan 3B: Komunikasi I2C

## Jawaban Pertanyaan Praktikum

---

## 1. Jelaskan bagaimana cara kerja komunikasi I2C antara Arduino dan LCD pada rangkaian tersebut!

I2C (Inter-Integrated Circuit) adalah protokol komunikasi serial yang menggunakan dua jalur utama, yaitu:

- SDA (Serial Data) → untuk mengirim data  
- SCL (Serial Clock) → untuk sinkronisasi waktu  

### Cara Kerja:

1. Arduino bertindak sebagai **Master**  
2. LCD bertindak sebagai **Slave** dengan alamat tertentu (misalnya `0x27`)  
3. Arduino mengirimkan alamat LCD melalui jalur SDA  
4. Setelah alamat cocok, Arduino mengirimkan data (teks/perintah)  
5. Sinyal clock (SCL) mengatur sinkronisasi pengiriman data  
6. LCD menerima data dan menampilkannya pada layar  

### Penjelasan:

Komunikasi I2C memungkinkan beberapa perangkat terhubung hanya dengan 2 kabel, sehingga lebih efisien dibandingkan komunikasi paralel yang membutuhkan banyak pin.

---

## 2. Apakah pin potensiometer harus seperti itu? Jelaskan jika tertukar!

Konfigurasi standar potensiometer:
- Kaki kiri → GND  
- Kaki tengah → A0 (input analog)  
- Kaki kanan → 5V  

### Jika kaki kiri dan kanan tertukar:
- Nilai ADC tetap terbaca  
- Namun arah pembacaan menjadi terbalik:
  - Putar kiri → nilai besar  
  - Putar kanan → nilai kecil  

### Kesimpulan:
Tidak menyebabkan kerusakan, tetapi arah perubahan nilai menjadi terbalik.

---

## 3. Modifikasi program UART + I2C (output ke LCD dan Serial Monitor)

### Kode Program:

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int pinPot = A0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  int nilai = analogRead(pinPot);

  float volt = nilai * (5.0 / 1023.0);
  int persen = (nilai * 100) / 1023;

  int panjangBar = map(nilai, 0, 1023, 0, 16);

  // Output ke Serial Monitor
  Serial.print("ADC: ");
  Serial.print(nilai);
  Serial.print(" Volt: ");
  Serial.print(volt);
  Serial.print(" V Persen: ");
  Serial.print(persen);
  Serial.println("%");

  // Output ke LCD
  lcd.setCursor(0, 0);
  lcd.print("ADC:");
  lcd.print(nilai);
  lcd.print(" ");
  lcd.print(persen);
  lcd.print("%   ");

  lcd.setCursor(0, 1);

  for (int i = 0; i < 16; i++) {
    if (i < panjangBar) {
      lcd.print((char)255);
    } else {
      lcd.print(" ");
    }
  }

  delay(200);
}
```
## Penjelasan Program

Program ini membaca nilai dari potensiometer kemudian menampilkannya ke LCD melalui komunikasi I2C serta ke Serial Monitor melalui UART.

---

### Penjelasan tiap bagian kode:

- `#include <Wire.h>`  
  Library untuk komunikasi I2C  

- `#include <LiquidCrystal_I2C.h>`  
  Library untuk mengontrol LCD berbasis I2C  

- `LiquidCrystal_I2C lcd(0x27, 16, 2);`  
  Inisialisasi LCD dengan alamat I2C `0x27` dan ukuran 16 kolom x 2 baris  

- `const int pinPot = A0;`  
  Menentukan pin analog yang digunakan untuk membaca potensiometer  

- `Serial.begin(9600);`  
  Memulai komunikasi serial dengan komputer  

- `lcd.init()`  
  Menginisialisasi LCD  

- `lcd.backlight()`  
  Mengaktifkan lampu latar LCD  

- `analogRead(pinPot)`  
  Membaca nilai analog dari potensiometer (rentang 0–1023)  

- `float volt = nilai * (5.0 / 1023.0);`  
  Mengonversi nilai ADC menjadi tegangan (Volt)  

- `int persen = (nilai * 100) / 1023;`  
  Mengonversi nilai ADC menjadi persentase (%)  

- `map(nilai, 0, 1023, 0, 16)`  
  Mengubah nilai ADC menjadi panjang bar (0–16 karakter pada LCD)  

- `Serial.print()`  
  Menampilkan data ke Serial Monitor  

- `lcd.setCursor(0, 0)`  
  Mengatur posisi kursor di baris pertama LCD  

- `lcd.setCursor(0, 1)`  
  Mengatur posisi kursor di baris kedua LCD  

- `lcd.print()`  
  Menampilkan teks atau data ke LCD  

- `(char)255`  
  Karakter blok penuh untuk membuat tampilan bar level  

- `delay(200)`  
  Memberikan jeda agar tampilan tidak terlalu cepat berubah  

---

## 4. Tabel Hasil Pengamatan

| ADC | Volt (V) | Persen (%) |
|-----|----------|------------|
| 1   | 0.00 V   | 0%         |
| 21  | 0.10 V   | 2%         |
| 49  | 0.24 V   | 4%         |
| 74  | 0.36 V   | 7%         |
| 96  | 0.47 V   | 9%         |