# Percobaan RTOS: Komunikasi Task Menggunakan Queue

## Jawaban Pertanyaan Praktikum

---

## 1. Apakah kedua task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!

Kedua task pada program FreeRTOS berjalan secara **concurrent (bergantian sangat cepat)**, bukan benar-benar paralel secara fisik.

Hal ini karena Arduino Uno hanya memiliki satu inti prosesor (single core), sehingga CPU hanya dapat menjalankan satu task dalam satu waktu. FreeRTOS menggunakan scheduler untuk mengatur pergantian eksekusi task sehingga terlihat berjalan bersamaan.

### Mekanisme Kerja:
- Fungsi `xTaskCreate()` digunakan untuk membuat task baru
- Setelah scheduler aktif, FreeRTOS mengatur giliran eksekusi setiap task
- Task `read_data` bertugas membaca data sensor
- Task `display` bertugas menampilkan data ke Serial Monitor
- Komunikasi antar task dilakukan menggunakan queue (`xQueueCreate()`)

### Cara Kerja Queue:
- Task `read_data` mengirim data ke queue menggunakan:
```cpp
xQueueSend(my_queue, &x, portMAX_DELAY);
```

- Task `display` menerima data dari queue menggunakan:
```cpp
xQueueReceive(my_queue, &x, portMAX_DELAY);
```

- Saat queue kosong, task `display` akan menunggu (blocked)
- Saat queue penuh, task `read_data` akan menunggu hingga queue tersedia

### Kesimpulan:
Kedua task berjalan secara bergantian dengan sangat cepat menggunakan scheduler FreeRTOS dan saling berkomunikasi menggunakan queue.

---

## 2. Apakah program ini berpotensi mengalami race condition? Jelaskan!

Program ini **tidak terlalu berpotensi mengalami race condition** karena komunikasi data antar task menggunakan mekanisme queue dari FreeRTOS.

### Pengertian Race Condition:
Race condition adalah kondisi ketika dua atau lebih task mengakses data yang sama secara bersamaan sehingga menyebabkan data menjadi tidak konsisten.

### Mengapa Program Aman?
Pada program ini:
- Data tidak diakses langsung secara bersamaan
- Data dikirim melalui queue
- Queue FreeRTOS memiliki mekanisme sinkronisasi internal

### Mekanisme Keamanan Queue:
- Task pengirim hanya menulis data ke queue
- Task penerima hanya membaca data dari queue
- FreeRTOS mengatur akses queue secara otomatis

### Contoh Aman:
```cpp
xQueueSend(my_queue, &x, portMAX_DELAY);
```

```cpp
xQueueReceive(my_queue, &x, portMAX_DELAY);
```

### Kesimpulan:
Program relatif aman dari race condition karena menggunakan queue sebagai media komunikasi antar task yang sudah memiliki sinkronisasi bawaan dari FreeRTOS.

---

## 3. Modifikasi Program Menggunakan Sensor DHT

### Tujuan:
Menggunakan sensor DHT asli agar data suhu dan kelembaban yang ditampilkan bersifat realtime dan dinamis.

---

## Kode Program

```cpp
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

struct readings {
  float temp;
  float hum;
};

QueueHandle_t my_queue;

void read_data(void *pvParameters);
void display(void *pvParameters);

void setup() {

  Serial.begin(9600);

  dht.begin();

  my_queue = xQueueCreate(5, sizeof(struct readings));

  xTaskCreate(read_data, "read sensors", 128, NULL, 1, NULL);
  xTaskCreate(display, "display", 128, NULL, 1, NULL);

  vTaskStartScheduler();
}

void loop() {
}

// Task membaca sensor DHT
void read_data(void *pvParameters) {

  struct readings data;

  while(1) {

    data.temp = dht.readTemperature();
    data.hum = dht.readHumidity();

    xQueueSend(my_queue, &data, portMAX_DELAY);

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

// Task menampilkan data
void display(void *pvParameters) {

  struct readings data;

  while(1) {

    if(xQueueReceive(my_queue, &data, portMAX_DELAY) == pdPASS) {

      Serial.print("Suhu = ");
      Serial.print(data.temp);
      Serial.println(" C");

      Serial.print("Kelembaban = ");
      Serial.print(data.hum);
      Serial.println(" %");

      Serial.println("-------------------");
    }
  }
}
```

---

## Penjelasan Program

### Library yang Digunakan:
```cpp
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <DHT.h>
```

### Fungsi Library:
- `Arduino_FreeRTOS.h` → menjalankan multitasking
- `queue.h` → komunikasi antar task menggunakan queue
- `DHT.h` → membaca sensor suhu dan kelembaban DHT11

---

## Struktur Data

```cpp
struct readings {
  float temp;
  float hum;
};
```

Struct digunakan untuk menyimpan:
- Nilai suhu (`temp`)
- Nilai kelembaban (`hum`)

---

## Cara Kerja Program

### Task `read_data`
Task ini bertugas:
- Membaca suhu dari sensor DHT
- Membaca kelembaban dari sensor DHT
- Mengirim data ke queue

```cpp
data.temp = dht.readTemperature();
data.hum = dht.readHumidity();
```

---

### Task `display`
Task ini bertugas:
- Menerima data dari queue
- Menampilkan data ke Serial Monitor

```cpp
xQueueReceive(my_queue, &data, portMAX_DELAY)
```

---

## Hasil Pengujian

### Hasil pada Serial Monitor:
```cpp
Suhu = 29.00 C
Kelembaban = 75.00 %

-------------------
```

### Pengamatan:
- Nilai suhu berubah sesuai kondisi ruangan
- Nilai kelembaban berubah secara realtime
- Data tampil secara terus menerus tanpa gangguan antar task

### Kesimpulan Hasil:
Sensor DHT berhasil digunakan untuk menghasilkan data suhu dan kelembaban secara dinamis menggunakan komunikasi task berbasis queue pada FreeRTOS.

---

## Kesimpulan

Program komunikasi task menggunakan queue berhasil dijalankan dengan baik pada FreeRTOS. Queue digunakan sebagai media pertukaran data antar task sehingga komunikasi menjadi aman dan terhindar dari race condition. Setelah dimodifikasi menggunakan sensor DHT, sistem mampu menampilkan data suhu dan kelembaban secara realtime dan dinamis pada Serial Monitor.