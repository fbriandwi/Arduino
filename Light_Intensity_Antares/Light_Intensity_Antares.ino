#include  <AntaresESP8266HTTP.h >   // Inisiasi library HTTP Antares

#define ACCESSKEY "6b28b025899bf725:6de14c772e48b226"       // Ganti dengan access key akun Antares anda
#define WIFISSID "pep"         // Ganti dengan SSID WiFi anda
#define PASSWORD "11111111"     // Ganti dengan password WiFi anda

#define projectName "sensor12"   // Ganti dengan application name Antares yang telah dibuat
#define deviceName "LightIntensity"     // Ganti dengan device Antares yang telah dibuat

AntaresESP8266HTTP antares(ACCESSKEY);    // Buat objek antares

void setup() {
  Serial.begin(115200);     // Buka komunikasi serial dengan baudrate 115200
  antares.setDebug(true);   // Nyalakan debug. Set menjadi "false" jika tidak ingin pesan-pesan tampil di serial monitor
  antares.wifiConnection(WIFISSID,PASSWORD);  // Mencoba untuk menyambungkan ke WiFi
}

void loop() {
  // Isi variabel dengan nilai acak, dengan tipe data yang berbeda
  int lux = random(35,450) ;
 
  
  // Memasukkan nilai-nilai variabel ke penampungan data sementara
  antares.add("Itensitas Cahaya", lux);
  
  // Kirim dari penampungan data ke Antares
  antares.send(projectName, deviceName);
  delay(10000);
}
