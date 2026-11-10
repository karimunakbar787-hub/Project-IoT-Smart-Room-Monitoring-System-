
#include <DHTesp.h>

DHTesp dht;

// Pin komponen
#define DHT_PIN 15
#define LDR_PIN 34
#define LED_MERAH 26
#define LED_BIRU 27

// Batas suhu dan cahaya
#define BATAS_SUHU 30
#define BATAS_CAHAYA 2000

void setup() {
  Serial.begin(115200);

  dht.setup(DHT_PIN, DHTesp::DHT22);

  pinMode(LDR_PIN, INPUT);
  pinMode(LED_MERAH, OUTPUT);
  pinMode(LED_BIRU, OUTPUT);

  Serial.println("Smart Room Monitoring System");
  Serial.println("Sistem dimulai...");
}

void loop() {

  // Membaca sensor DHT22
  TempAndHumidity data = dht.getTempAndHumidity();

  float suhu = data.temperature;
  float kelembapan = data.humidity;

  // Membaca sensor LDR
  int cahaya = analogRead(LDR_PIN);

  // Memeriksa data suhu
  if (isnan(suhu) || isnan(kelembapan)) {
    Serial.println("Sensor DHT22 gagal dibaca");
    delay(2000);
    return;
  }

  // Otomatisasi LED merah
  if (suhu >= BATAS_SUHU) {
    digitalWrite(LED_MERAH, HIGH);
  } else {
    digitalWrite(LED_MERAH, LOW);
  }

  // Otomatisasi LED biru
  // Asumsi nilai analog rendah berarti gelap
  if (cahaya < BATAS_CAHAYA) {
    digitalWrite(LED_BIRU, HIGH);
  } else {
    digitalWrite(LED_BIRU, LOW);
  }

  // Menampilkan data
  Serial.println("======================");
  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.println(" C");

  Serial.print("Kelembapan: ");
  Serial.print(kelembapan);
  Serial.println(" %");

  Serial.print("Nilai Cahaya: ");
  Serial.println(cahaya);

  Serial.println("======================");

  delay(2000);
}

