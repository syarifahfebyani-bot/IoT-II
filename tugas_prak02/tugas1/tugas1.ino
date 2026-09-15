const int buttonPin = 4;
const int ledPin = 5;

int buttonState = 0;
int lastButtonState = LOW;

// Variabel untuk menyimpan status LED (ON atau OFF)
bool ledState = false;

void setup() {
  Serial.begin(115200);

  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // Saat sistem dinyalakan, LED dalam keadaan mati
  digitalWrite(ledPin, LOW);
}

void loop() {
  // Membaca kondisi tombol saat ini
  buttonState = digitalRead(buttonPin);

  // Mendeteksi tombol baru saja ditekan
  // LOW ke HIGH berarti terjadi satu kali tekanan
  if (buttonState == HIGH && lastButtonState == LOW) {

    // Membalik status LED: OFF menjadi ON, atau ON menjadi OFF
    ledState = !ledState;

    // Mengatur LED sesuai status yang tersimpan
    digitalWrite(ledPin, ledState ? HIGH : LOW);

    // Menampilkan status LED pada Serial Monitor
    if (ledState) {
      Serial.println("Tombol ditekan! -> LED ON");
    } else {
      Serial.println("Tombol ditekan! -> LED OFF");
    }

    // Debouncing: memberikan jeda untuk mengatasi
    // pantulan mekanis pada tombol fisik
    delay(200);
  }

  // Menyimpan kondisi tombol untuk mendeteksi tekanan berikutnya
  lastButtonState = buttonState;
}