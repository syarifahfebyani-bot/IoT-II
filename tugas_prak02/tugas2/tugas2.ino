#include <DHT.h>

// ===============================
// PIN
// ===============================
#define DHTPIN D7
#define DHTTYPE DHT11

#define LDR_PIN A0
#define RELAY_PIN D6
#define LED_PIN D1

DHT dht(DHTPIN, DHTTYPE);

// ===============================
// SETUP
// ===============================
void setup() {

  Serial.begin(115200);

  // Konfigurasi pin
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  // Kondisi awal: AKTUATOR MATI
  // Relay diasumsikan Active-Low
  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(LED_PIN, LOW);

  // Mulai sensor DHT
  dht.begin();

  // Tampilan awal
  Serial.println("================================");
  Serial.println(" SMART WAREHOUSE - EDGE CONTROL ");
  Serial.println("================================");
}

// ===============================
// LOOP
// ===============================
void loop() {

  // Membaca sensor DHT
  float suhu = dht.readTemperature();

  // Membaca LDR
  int nilaiLDR = analogRead(LDR_PIN);

  // Cek apakah DHT gagal dibaca
  if (isnan(suhu)) {
    Serial.println("Gagal membaca sensor DHT!");
    Serial.println("-------------------------------");

    delay(2000);
    return;
  }

  // ===============================
  // TAMPILKAN DATA SENSOR
  // ===============================

  Serial.print("Suhu     : ");
  Serial.print(suhu, 2);
  Serial.println(" C");

  Serial.print("Nilai LDR: ");
  Serial.println(nilaiLDR);

  // ===============================
  // RULE ENGINE
  // ===============================
  // Aktuator aktif jika:
  // Suhu > 34 C ATAU LDR < 300

  if (suhu > 34 || nilaiLDR < 300) {

    // Relay ON
    // Untuk relay Active-Low
    digitalWrite(RELAY_PIN, LOW);

    // LED ON
    digitalWrite(LED_PIN, HIGH);

    Serial.println("PERINGATAN: Aktuator Aktif!");

    // Cek penyebab
    if (suhu > 34) {
      Serial.println("- Suhu terlalu panas!");
    }

    if (nilaiLDR < 300) {
      Serial.println("- Ruangan terlalu gelap!");
    }

  } 
  else {

    // Relay OFF
    digitalWrite(RELAY_PIN, HIGH);

    // LED OFF
    digitalWrite(LED_PIN, LOW);

    Serial.println("Kondisi Aman");
  }

  // Garis pemisah
  Serial.println("-------------------------------");

  // Delay pembacaan sensor
  delay(2000);
}