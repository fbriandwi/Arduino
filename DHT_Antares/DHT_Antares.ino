#include  <AntaresESP8266HTTP.h >   // Inisiasi library HTTP Antares

#define ACCESSKEY "61b68ba87dc2c7fe:17872d4cd7382673"       // Ganti dengan access key akun Antares anda
#define WIFISSID "pep"         // Ganti dengan SSID WiFi anda
#define PASSWORD "11111111"   // Ganti dengan password WiFi anda

#define projectName "Ss1"   // Ganti dengan application name Antares yang telah dibuat
#define deviceName "TempratureSensor"     // Ganti dengan device Antares yang telah dibuat

AntaresESP8266HTTP antares(ACCESSKEY);    // Buat objek antares

void setup() {
  Serial.begin(115200);     // Buka komunikasi serial dengan baudrate 115200
  antares.setDebug(true);   // Nyalakan debug. Set menjadi "false" jika tidak ingin pesan-pesan tampil di serial monitor
  antares.wifiConnection(WIFISSID,PASSWORD);  // Mencoba untuk menyambungkan ke WiFi
}

void loop() {
  // Isi variabel dengan nilai acak, dengan tipe data yang berbeda
  int temp = random(25,30) ;
  int hum = random(75,90);
  float windsp = float(random(20, 30))/3.33;
  float rainlv = float(random(0, 20))/6.99;
  String lat = "-6.8718189";
  String lon = "107.5872477";

  // Memasukkan nilai-nilai variabel ke penampungan data sementara
  antares.add("temperature", temp);
  antares.add("humidity", hum);

  // Kirim dari penampungan data ke Antares
  antares.send(projectName, deviceName);
  delay(1000);
}
