# Percobaan RTOS: Multitasking dengan FreeRTOS

## Jawaban Pertanyaan Praktikum

---

## 1. Apakah ketiga task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!

Ketiga task pada program FreeRTOS berjalan secara **concurrent (bergantian sangat cepat)**, bukan benar-benar paralel secara fisik.

Hal ini karena Arduino Uno hanya memiliki satu inti prosesor (single core), sehingga CPU hanya dapat menjalankan satu task dalam satu waktu. Namun, FreeRTOS menggunakan scheduler untuk mengatur pergantian task dengan sangat cepat sehingga terlihat berjalan bersamaan.

### Mekanisme Kerja:
- Fungsi `xTaskCreate()` digunakan untuk membuat task baru
- Setelah `vTaskStartScheduler()` dijalankan, scheduler FreeRTOS mulai bekerja
- Setiap task memiliki prioritas yang sama yaitu `1`
- Ketika sebuah task menjalankan `vTaskDelay()`, task tersebut masuk ke status **blocked**
- Scheduler kemudian memberikan giliran CPU kepada task lain yang siap dijalankan

### Pada Program:
- `TaskBlink1` mengontrol LED pin 9 dengan delay 200 ms
- `TaskBlink2` mengontrol LED pin 8 dengan delay 300 ms
- `Taskprint` menampilkan counter setiap 500 ms

### Kesimpulan:
Task tidak berjalan benar-benar bersamaan, tetapi dijalankan secara bergantian dengan sangat cepat oleh scheduler FreeRTOS sehingga tampak seperti multitasking.

---

## 2. Bagaimana cara menambahkan task keempat? Jelaskan langkahnya!

Untuk menambahkan task keempat, perlu dilakukan beberapa langkah berikut:

### Langkah-Langkah:
1. Membuat prototype function task baru
2. Membuat isi function task
3. Menambahkan `xTaskCreate()` pada `setup()`
4. Menentukan pin/output yang digunakan
5. Menambahkan delay menggunakan `vTaskDelay()`

---

### Contoh Program Task Keempat

```cpp
void TaskBlink3(void *pvParameters);

void setup() {

  Serial.begin(9600);

  xTaskCreate(TaskBlink1, "task1", 128, NULL, 1, NULL);
  xTaskCreate(TaskBlink2, "task2", 128, NULL, 1, NULL);
  xTaskCreate(Taskprint, "task3", 128, NULL, 1, NULL);

  // Task keempat
  xTaskCreate(TaskBlink3, "task4", 128, NULL, 1, NULL);

  vTaskStartScheduler();
}
```

---

### Isi Function Task Keempat

```cpp
void TaskBlink3(void *pvParameters) {

  pinMode(7, OUTPUT);

  while(1) {

    Serial.println("Task4");

    digitalWrite(7, HIGH);
    vTaskDelay(100 / portTICK_PERIOD_MS);

    digitalWrite(7, LOW);
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}
```

### Penjelasan:
- `TaskBlink3` merupakan task tambahan untuk mengontrol LED pada pin 7
- Fungsi `while(1)` membuat task berjalan terus menerus
- `vTaskDelay()` digunakan agar scheduler dapat menjalankan task lain

### Kesimpulan:
Task baru dapat ditambahkan dengan membuat function task baru lalu mendaftarkannya ke scheduler menggunakan `xTaskCreate()`.

---

## 3. Modifikasi Program dengan Potensiometer untuk Mengontrol Kecepatan LED

### Tujuan:
Menggunakan sensor potensiometer untuk mengontrol kecepatan kedip LED secara realtime menggunakan FreeRTOS.

---

## Kode Program

```cpp
#include <Arduino_FreeRTOS.h>

void TaskBlink1(void *pvParameters);
void TaskBlink2(void *pvParameters);
void TaskPotensio(void *pvParameters);

int delayLed = 200;

void setup() {

  Serial.begin(9600);

  xTaskCreate(TaskBlink1, "Blink1", 128, NULL, 1, NULL);
  xTaskCreate(TaskBlink2, "Blink2", 128, NULL, 1, NULL);
  xTaskCreate(TaskPotensio, "Potensio", 128, NULL, 1, NULL);

  vTaskStartScheduler();
}

void loop() {
}

void TaskBlink1(void *pvParameters) {

  pinMode(9, OUTPUT);

  while(1) {

    digitalWrite(9, HIGH);
    vTaskDelay(delayLed / portTICK_PERIOD_MS);

    digitalWrite(9, LOW);
    vTaskDelay(delayLed / portTICK_PERIOD_MS);
  }
}

void TaskBlink2(void *pvParameters) {

  pinMode(8, OUTPUT);

  while(1) {

    digitalWrite(8, HIGH);
    vTaskDelay((delayLed + 100) / portTICK_PERIOD_MS);

    digitalWrite(8, LOW);
    vTaskDelay((delayLed + 100) / portTICK_PERIOD_MS);
  }
}

void TaskPotensio(void *pvParameters) {

  while(1) {

    int nilaiPot = analogRead(A0);

    delayLed = map(nilaiPot, 0, 1023, 50, 1000);

    Serial.print("Nilai Potensiometer: ");
    Serial.print(nilaiPot);

    Serial.print(" | Delay LED: ");
    Serial.println(delayLed);

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}
```

---

## Penjelasan Program

### Cara Kerja:
- Potensiometer dibaca menggunakan `analogRead(A0)`
- Nilai ADC memiliki rentang:
  - `0 → 1023`
- Fungsi `map()` digunakan untuk mengubah nilai ADC menjadi delay:
  - `50 ms → 1000 ms`
- Nilai delay digunakan untuk mengatur kecepatan kedip LED

### Cara Kerja Mapping:
```cpp
delayLed = map(nilaiPot, 0, 1023, 50, 1000);
```

### Artinya:
- ADC kecil → delay kecil → LED berkedip cepat
- ADC besar → delay besar → LED berkedip lambat

---

## Hasil Pengujian

### Saat Potensiometer Diputar ke Kanan:
- Nilai ADC meningkat
- Delay LED semakin besar
- LED berkedip lebih lambat

### Saat Potensiometer Diputar ke Kiri:
- Nilai ADC menurun
- Delay LED semakin kecil
- LED berkedip lebih cepat

### Monitoring Serial:
```cpp
Serial.print("Nilai Potensiometer: ");
Serial.print(nilaiPot);

Serial.print(" | Delay LED: ");
Serial.println(delayLed);
```

Serial Monitor menampilkan nilai ADC dan delay LED secara realtime.

---

## Kesimpulan

Potensiometer berhasil digunakan untuk mengontrol kecepatan LED secara realtime tanpa mengganggu task lain. Hal ini menunjukkan bahwa FreeRTOS mampu menjalankan multitasking dengan baik pada sistem embedded Arduino.