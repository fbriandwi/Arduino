// Deklarasi pin sensor
const int pinTrigger = 2;
const int pinEcho = 3;

void setup() {
  Serial.begin(9600);
  pinMode(pinTrigger, OUTPUT);
  pinMode(pinEcho, INPUT);
}

void loop() {
  // Mengirimkan sinyal ultrasonik selama 10 mikrodetik
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);

  // Menerima sinyal kembali dari sensor
  long duration = pulseIn(pinEcho, HIGH);

  // Menghitung jarak berdasarkan waktu yang diperlukan sinyal untuk pergi dan kembali
  float distance = duration * 0.034 / 2;

  // Mengirimkan hasil ke Serial Monitor
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Delay sejenak sebelum mengukur jarak lagi
  delay(500);
}
