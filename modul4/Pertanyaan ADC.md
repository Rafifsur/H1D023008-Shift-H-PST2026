#  Percobaan ADC & PWM: Kontrol Servo dengan Potensiometer

## Jawaban Pertanyaan Praktikum

---

## 1. Apa fungsi perintah `analogRead()` pada rangkaian praktikum ini?

Perintah `analogRead()` digunakan untuk membaca nilai tegangan analog dari potensiometer yang terhubung ke pin analog Arduino (A0).

### Cara Kerja:
- Potensiometer menghasilkan tegangan antara 0–5 Volt
- Arduino mengubah tegangan tersebut menjadi nilai digital menggunakan ADC (Analog to Digital Converter)
- Hasil pembacaan memiliki rentang:
  - 0 → 0 Volt  
  - 1023 → 5 Volt  

### Kesimpulan:
`analogRead()` berfungsi sebagai pengubah sinyal analog menjadi data digital agar dapat diproses oleh mikrokontroler.

---

## 2. Mengapa diperlukan fungsi `map()` dalam program tersebut?

Fungsi `map()` digunakan untuk mengubah rentang nilai dari satu skala ke skala lain agar sesuai dengan kebutuhan.

### Pada praktikum ini:
- Nilai dari `analogRead()` memiliki rentang: **0 – 1023**
- Sedangkan servo bekerja pada rentang sudut: **0 – 180 derajat**

### Cara Kerja:
Fungsi `map()` mengkonversi nilai ADC menjadi sudut servo secara proporsional:
```cpp
pos = map(val, 0, 1023, 0, 180);
```

### Artinya:
- **ADC 0 → Servo 0°**
- **ADC 1023 → Servo 180°**

### Kesimpulan:
Tanpa `map()`, nilai ADC tidak bisa langsung digunakan untuk mengontrol servo secara akurat.

---

## 3. Modifikasi Program (Servo 30° – 150°)

###  Tujuan:
Membatasi pergerakan servo agar tidak mencapai posisi ekstrem (0° dan 180°), sehingga lebih aman dan stabil.

---

###  Kode Program:
```cpp
#include <Servo.h>

Servo myservo;

const int potensioPin = A0;
const int servoPin = 9;

int pos = 0;
int val = 0;

void setup() {
  myservo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {

  // Membaca nilai dari potensiometer
  val = analogRead(potensioPin);

  // Mapping dari ADC (0–1023) ke sudut servo (30–150)
  pos = map(val, 0, 1023, 30, 150);

  // Membatasi agar tetap dalam range
  pos = constrain(pos, 30, 150);

  // Menggerakkan servo
  myservo.write(pos);

  // Monitoring Serial
  Serial.print("ADC: ");
  Serial.print(val);
  Serial.print(" | Sudut Servo: ");
  Serial.println(pos);

  delay(15);
}