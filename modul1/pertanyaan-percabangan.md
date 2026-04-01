# **Percobaan 1A: Percabangan (if / if-else)**

## **Jawaban Pertanyaan Praktikum 1.5.4**

---

### **1. Pada kondisi apa program masuk ke blok if?**

Program masuk ke blok **if** ketika nilai variabel `timeDelay` sudah mencapai **kurang dari atau sama dengan 100 ms**.

```cpp
if (timeDelay <= 100) { ... }
```

Kondisi ini terjadi setelah nilai `timeDelay` terus dikurangi sebesar 100 ms pada setiap siklus kedip LED. Saat nilai delay menjadi sangat kecil (LED berkedip sangat cepat), program akan masuk ke blok **if** untuk memberikan jeda sebelum mengulang kembali ke kondisi awal.

---

### **2. Pada kondisi apa program masuk ke blok else?**

Program masuk ke blok **else** ketika nilai `timeDelay` masih **lebih besar dari 100 ms**.

```cpp
else {
  timeDelay -= 100;
}
```

Pada kondisi ini, program akan terus mengurangi nilai `timeDelay` sehingga kecepatan kedip LED meningkat secara bertahap dari lambat menjadi cepat.

---

### **3. Apa fungsi dari perintah delay(timeDelay)?**

Perintah `delay(timeDelay)` berfungsi untuk **menghentikan sementara eksekusi program** selama `timeDelay` milidetik.

Dalam program:

* Setelah `digitalWrite(HIGH)` → LED menyala selama `timeDelay`
* Setelah `digitalWrite(LOW)` → LED mati selama `timeDelay`

Karena nilai `timeDelay` berubah:

* Nilai besar → LED berkedip lambat
* Nilai kecil → LED berkedip cepat

---

# **4. Modifikasi: Mati → Lambat → Cepat → Sedang → Mati (tanpa langsung reset)**

### **Perubahan Alur**

* **Sebelum:** mati → lambat → cepat → reset
* **Sesudah:** mati → lambat → cepat → sedang → mati

---

## **Kode Program Modifikasi**

```cpp
const int ledPin = 11;   // LED pada pin 11
int timeDelay = 1000;    // delay awal (lambat)
bool percepat = true;    // arah perubahan delay

void setup() {
  pinMode(ledPin, OUTPUT); // set pin sebagai output
}

void loop() {
  // LED menyala
  digitalWrite(ledPin, HIGH);
  delay(timeDelay);

  // LED mati
  digitalWrite(ledPin, LOW);
  delay(timeDelay);

  // Percabangan perubahan kecepatan
  if (percepat) {
    // fase lambat → cepat
    if (timeDelay > 100) {
      timeDelay -= 100;
    } else {
      percepat = false; // ubah ke perlambatan
    }
  } else {
    // fase cepat → sedang → mati
    if (timeDelay < 600) {
      timeDelay += 100;
    } else {
      // fase mati
      digitalWrite(ledPin, LOW);
      delay(3000);

      // reset ke awal
      timeDelay = 1000;
      percepat = true;
    }
  }
}
```

---

## **Penjelasan Baris per Baris (README.md)**

```md
# Program LED Percabangan (Perubahan Kecepatan)

## Inisialisasi
const int ledPin = 11;
- Menentukan pin LED pada Arduino (pin 11)

int timeDelay = 1000;
- Nilai awal delay = 1000 ms (LED berkedip lambat)

bool percepat = true;
- Variabel untuk menentukan arah perubahan:
  true  = mempercepat
  false = memperlambat

## Setup
pinMode(ledPin, OUTPUT);
- Mengatur pin LED sebagai output

## Loop Utama

### LED Menyala
digitalWrite(ledPin, HIGH);
delay(timeDelay);
- LED menyala selama waktu tertentu

### LED Mati
digitalWrite(ledPin, LOW);
delay(timeDelay);
- LED mati selama waktu tertentu

## Percabangan

### Jika percepat = true (fase percepatan)
if (timeDelay > 100)
- Selama delay masih besar
timeDelay -= 100
- Delay dikurangi → LED makin cepat

else
percepat = false
- Jika sudah cepat maksimum → ubah ke perlambatan

### Jika percepat = false (fase perlambatan)
if (timeDelay < 600)
- Selama belum mencapai kecepatan sedang
timeDelay += 100
- Delay ditambah → LED melambat

else
digitalWrite(ledPin, LOW);
delay(3000);
- LED dimatikan selama 3 detik

timeDelay = 1000;
percepat = true;
- Reset ke kondisi awal
```

---

## **Alur Eksekusi Program**

```
Mulai
 ↓
LED mati (awal)
 ↓
LED berkedip lambat (1000 ms)
 ↓
Delay dikurangi → LED semakin cepat
 ↓
LED cepat maksimum (100 ms)
 ↓
Delay ditambah → LED melambat
 ↓
LED sedang (600 ms)
 ↓
LED mati (3 detik)
 ↓
Reset → ulang dari awal
```
