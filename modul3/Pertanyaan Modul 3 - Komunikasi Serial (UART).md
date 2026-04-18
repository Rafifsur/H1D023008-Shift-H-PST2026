# Percobaan 3A: Komunikasi Serial (UART)

## Jawaban Pertanyaan Praktikum

---

## 1. Jelaskan proses dari input keyboard hingga LED menyala/mati!

Proses dimulai ketika pengguna mengetik perintah pada Serial Monitor. Data yang diketik (misalnya `'1'` atau `'0'`) akan dikirim ke Arduino melalui komunikasi serial (UART).

### Alur Proses:

1. User mengetik karakter pada keyboard  
2. Data dikirim melalui USB (UART) ke Arduino  
3. Data masuk ke buffer serial Arduino  
4. `Serial.available()` mengecek apakah data tersedia  
5. `Serial.read()` membaca data  
6. Program melakukan seleksi kondisi:
   - `'1'` → LED menyala  
   - `'0'` → LED mati  
7. Arduino mengirimkan feedback ke Serial Monitor  

### Penjelasan:

Dengan komunikasi UART, Arduino dapat menerima perintah secara langsung dari komputer dan mengontrol perangkat output seperti LED.

---

## 2. Mengapa digunakan `Serial.available()` sebelum membaca data?

### Fungsi:
Digunakan untuk memastikan bahwa data tersedia sebelum dibaca oleh `Serial.read()`.

### Jika dihilangkan:
- Program tetap membaca meskipun tidak ada data  
- Bisa menghasilkan data acak atau error  
- Sistem menjadi tidak stabil  

### Kesimpulan:
`Serial.available()` penting untuk menjaga kestabilan program.

---

## 3. Modifikasi program agar LED berkedip saat menerima input `'2'`

### Kode Program:

```cpp
#include <Arduino.h>

const int PIN_LED = 13;
bool blinkMode = false;
unsigned long prevMillis = 0;
const int interval = 500;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);
}

void loop() {

  if (Serial.available() > 0) {
    char data = Serial.read();

    if (data == '1') {
      blinkMode = false;
      digitalWrite(PIN_LED, HIGH);
    }
    else if (data == '0') {
      blinkMode = false;
      digitalWrite(PIN_LED, LOW);
    }
    else if (data == '2') {
      blinkMode = true;
    }
  }

  if (blinkMode) {
    unsigned long currentMillis = millis();

    if (currentMillis - prevMillis >= interval) {
      prevMillis = currentMillis;
      digitalWrite(PIN_LED, !digitalRead(PIN_LED));
    }
  }
}
```
## Penjelasan Program

Program ini digunakan untuk mengontrol LED menggunakan input dari Serial Monitor dengan tiga kondisi utama:

- `'1'` → LED menyala  
- `'0'` → LED mati  
- `'2'` → LED berkedip terus menerus  

---

### Penjelasan tiap bagian kode:

- `#include <Arduino.h>`  
  Mengimpor library dasar Arduino yang diperlukan untuk menjalankan program  

- `const int PIN_LED = 13;`  
  Menentukan pin digital yang digunakan untuk LED  

- `bool blinkMode = false;`  
  Variabel untuk menyimpan status apakah LED dalam mode berkedip atau tidak  

- `unsigned long prevMillis = 0;`  
  Menyimpan waktu sebelumnya untuk mengatur interval kedip  

- `const int interval = 500;`  
  Menentukan jeda waktu kedip LED (500 milidetik)  

- `Serial.begin(9600);`  
  Memulai komunikasi serial antara Arduino dan komputer  

- `pinMode(PIN_LED, OUTPUT);`  
  Mengatur pin LED sebagai output  

- `Serial.available()`  
  Mengecek apakah ada data yang masuk dari Serial Monitor  

- `Serial.read()`  
  Membaca satu karakter data yang dikirim dari Serial Monitor  

- `if (data == '1')`  
  Jika menerima input `'1'`, LED akan dinyalakan dan mode blink dimatikan  

- `if (data == '0')`  
  Jika menerima input `'0'`, LED akan dimatikan dan mode blink dimatikan  

- `if (data == '2')`  
  Jika menerima input `'2'`, mode LED berkedip akan diaktifkan  

- `millis()`  
  Digunakan sebagai pengganti delay untuk menghitung waktu tanpa menghentikan program  

- `currentMillis - prevMillis >= interval`  
  Digunakan untuk mengecek apakah waktu interval sudah tercapai  

- `digitalWrite(PIN_LED, !digitalRead(PIN_LED))`  
  Membalik kondisi LED (jika ON menjadi OFF, jika OFF menjadi ON)  

---

## 4. delay() atau millis()? Jelaskan pengaruhnya!

### delay()
- Menghentikan program sementara  
- Tidak bisa menerima input baru  
- Tidak efisien  

### millis()
- Tidak menghentikan program (non-blocking)  
- Bisa multitasking  
- Lebih responsif terhadap input  

### Kesimpulan

`millis()` lebih baik digunakan dibandingkan `delay()` karena tidak menghambat jalannya program dan memungkinkan sistem tetap berjalan secara real-time.