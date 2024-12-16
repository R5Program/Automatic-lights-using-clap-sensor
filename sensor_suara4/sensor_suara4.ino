const int sensorPin = 2;    // Pin sensor tepukan terhubung ke D2
const int relayPin = 13;    // Pin relay terhubung ke D13
const int switchPin = 3;    // Pin saklar manual terhubung ke D3

int sensorState = 0;        // Menyimpan status dari sensor tepukan
int switchState = 0;        // Menyimpan status dari saklar manual
bool lampState = true;     // Status lampu (ON/OFF)

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);  // Menggunakan internal pull-up resistor
  
  digitalWrite(relayPin, LOW);       // Pastikan lampu mati saat awal

  Serial.begin(9600);                // Inisialisasi komunikasi Serial
  Serial.println("Lampu otomatis siap.");
}

void loop() {
  // Baca status sensor tepukan
  sensorState = digitalRead(sensorPin);
  
  // Baca status saklar manual
  switchState = digitalRead(switchPin);

  // Jika sensor mendeteksi tepukan
  if (sensorState == HIGH) { 
    delay(100); // Debouncing
    lampState = !lampState; // Toggle status lampu
    digitalWrite(relayPin, lampState ? HIGH : LOW);
    Serial.print("Sensor Tepukan: ");
    Serial.println(lampState ? "Lampu Menyala" : "Lampu Mati");
    while(digitalRead(sensorPin) == HIGH); // Tunggu hingga tepukan berakhir
  }
  
  // Jika saklar manual ditekan
  if (switchState == LOW) {
    delay(100); // Debouncing
    lampState = !lampState; // Toggle status lampu
    digitalWrite(relayPin, lampState ? HIGH : LOW);
    Serial.print("Saklar Manual: ");
    Serial.println(lampState ? "Lampu Menyala" : "Lampu Mati");
    while(digitalRead(switchPin) == LOW); // Tunggu hingga saklar dilepas
  }
}
