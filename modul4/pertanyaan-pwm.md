#  Percobaan ADC & PWM: Kontrol Kecerahan LED

## Jawaban Pertanyaan Praktikum

---

## 1. Jelaskan mengapa LED dapat diatur kecerahannya menggunakan fungsi `analogWrite()`!

LED dapat diatur kecerahannya menggunakan fungsi `analogWrite()` karena Arduino menggunakan teknik **PWM (Pulse Width Modulation)**.

### Cara Kerja:
- `analogWrite()` tidak menghasilkan tegangan analog murni
- Arduino menghasilkan sinyal digital yang **ON-OFF sangat cepat**
- Perbandingan antara waktu ON dan OFF disebut **duty cycle**

### Contoh:
- PWM 0 → LED mati (0%)
- PWM 127 → LED setengah terang (~50%)
- PWM 255 → LED terang penuh (100%)

### Penjelasan:
Semakin besar nilai PWM, semakin lama LED dalam kondisi ON, sehingga terlihat lebih terang oleh mata manusia.

---

## 2. Apa hubungan antara nilai ADC (0–1023) dan nilai PWM (0–255)?

Nilai ADC dan PWM memiliki hubungan dalam proses konversi skala.

### Rentang:
- ADC: **0 – 1023** (10-bit)
- PWM: **0 – 255** (8-bit)

### Hubungan:
Nilai ADC biasanya dikonversi ke PWM menggunakan fungsi `map()`:

```cpp
pwm = map(adc, 0, 1023, 0, 255);

```
### Penjelasan:
- **ADC 0 → PWM 0**
- **ADC 1023 → PWM 255**

### Karena:
- **1023 ≈ 4 × 255**
- Maka nilai ADC perlu dikonversi (diperkecil skalanya) agar sesuai dengan rentang PWM

### Kesimpulan:
ADC digunakan sebagai **input**, sedangkan PWM digunakan sebagai **output** untuk mengontrol kecerahan LED.

---

## 3. Modifikasi Program (LED hanya menyala pada PWM 50–200)

###  Tujuan:
LED hanya menyala pada tingkat kecerahan sedang, yaitu ketika nilai PWM berada dalam rentang **50 hingga 200**.

---

###  Kode Program:
```cpp
#include <Arduino.h>

const int pinLED = 9;
const int pinPot = A0;

int adc = 0;
int pwm = 0;

void setup() {
  pinMode(pinLED, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  // Membaca nilai ADC
  adc = analogRead(pinPot);

  // Konversi ADC ke PWM (0–255)
  pwm = map(adc, 0, 1023, 0, 255);

  // Kondisi: hanya nyala jika PWM 50–200
  if (pwm >= 50 && pwm <= 200) {
    analogWrite(pinLED, pwm);
  } else {
    analogWrite(pinLED, 0); // LED mati
  }

  // Monitoring
  Serial.print("ADC: ");
  Serial.print(adc);
  Serial.print(" | PWM: ");
  Serial.println(pwm);

  delay(50);
}.