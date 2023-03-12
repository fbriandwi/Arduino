#include  <AntaresESP8266HTTP.h >   // Inisiasi library HTTP Antares

#define ACCESSKEY "61b68ba87dc2c7fe:17872d4cd7382673"       // Ganti dengan access key akun Antares anda
#define WIFISSID "A32.CKL"         // Ganti dengan SSID WiFi anda
#define PASSWORD "cangkula32"     // Ganti dengan password WiFi anda

#define projectName "SJ"   // Ganti dengan application name Antares yang telah dibuat
#define deviceName "Sengsor"     // Ganti dengan device Antares yang telah dibuat

AntaresESP8266HTTP antares(ACCESSKEY);    // Buat objek antares

const int trigPin = D1;
const int echoPin = D2;

// defines variables
long duration;
int distance;
int safetyDistance;


void setup() {
   Serial.begin(115200);     // Buka komunikasi serial dengan baudrate 115200
  antares.setDebug(true);   // Nyalakan debug. Set menjadi "false" jika tidak ingin pesan-pesan tampil di serial monitor
  antares.wifiConnection(WIFISSID,PASSWORD);  // Mencoba untuk menyambungkan ke WiFi
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}


void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH); 
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;

// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);

  // Memasukkan nilai-nilai variabel ke penampungan data sementara
  antares.add("distance", distance);
 
  // Kirim dari penampungan data ke Antares
  antares.send(projectName, deviceName);
  delay(1000);
}
