#include  <AntaresESP8266HTTP.h >   // Inisiasi library HTTP Antares

#define ACCESSKEY "61b68ba87dc2c7fe:17872d4cd7382673"       // Ganti dengan access key akun Antares anda
#define WIFISSID "pep"         // Ganti dengan SSID WiFi anda
#define PASSWORD "11111111"     // Ganti dengan password WiFi anda

#define projectName "Ss1"   // Ganti dengan application name Antares yang telah dibuat
#define deviceName "RelayStatus"     // Ganti dengan device Antares yang telah dibuat

AntaresESP8266HTTP antares(ACCESSKEY);    // Buat objek antares

void setup() {
  Serial.begin(115200);     // Buka komunikasi serial dengan baudrate 115200
  antares.setDebug(true);   // Nyalakan debug. Set menjadi "false" jika tidak ingin pesan-pesan tampil di serial monitor
  antares.wifiConnection(WIFISSID,PASSWORD);  // Mencoba untuk menyambungkan ke WiFi
}

void loop() {
  // Isi variabel dengan nilai acak, dengan tipe data yang berbeda
  int led1 = random(0,2); // 0= OFF, 1=ON
  int led2 = random(0,2);
  int led3 = random(0,2);
  
  // Memasukkan nilai-nilai variabel ke penampungan data sementara
  antares.add("Led1", led1);
  antares.add("Led2", led2);
   antares.add("Led3", led3);
 
  // Kirim dari penampungan data ke Antares
  antares.send(projectName, deviceName);
  delay(5000);
}
