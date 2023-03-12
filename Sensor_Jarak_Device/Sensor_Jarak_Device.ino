#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
/* pin sensor ultrasonic */
const int trigPin = D7;
const int echoPin = D6;
 
/* set SSID sensor parkir, tanpa password */
const char *ssid = "SensorParkir";
 
ESP8266WebServer server(80);
 
String webHeader1 = "<!DOCTYPE HTML>"
                    "<html><head><title>Jarak</title>"
                    "<meta name='viewport' content='width=device-width, initial-scale=1.0, minimum-scale = 1, maximum-scale = 1, user-scalable = no'/>"
                    "<meta name='apple-mobile-web-app-title' content='Sensor Parkir' />"
                    "<meta name='apple-mobile-web-app-capable' content='yes'>"
                    "<meta name='apple-mobile-web-app-status-bar-style' content='default' />"
                    "<style>"
                    "html, body {background: ";
String webHeader2 = " color: white;"
                    " text-align: center;"
                    " font-family: 'fontello';"
                    " font-size: 168px;"
                    "}"
                    "div.container3 { height: -webkit-fill-available;  display: flex;  align-items: center;  justify-content: center }"
                    "div.container3 p {  margin: 0 }"
                    "</style>";
String webFooter = "</body></html>";
 
int ukurJarak() {
  long waktuTempuh, jarak;
 
  digitalWrite(trigPin, HIGH); // kirim sinyal selama 10 micro second
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  waktuTempuh = pulseIn(echoPin, HIGH, 20000); // Tunggu pantulan suara kembali, dengan timeout 20ms (kurang lebih 3m)
 
  jarak = (waktuTempuh / 2) / 29.1; // Hitung jarak (kecepatan suara di udara kurang lebih 291m/s), dibagi 2 waktu tempuh datang dan kembali
 
  return jarak;
}
 
void handleRoot() {             // handle halaman root (http://192.168.4.1/), tampilan dengan HTML/CSS
  int jarak = ukurJarak();
  String s = webHeader1;
  
  if (jarak <= 15)              // membedakan warna background css sesuai jarak
    s += "red;";
  else if (jarak <= 30)
    s += "orange;";
  else
    s += "black;";
    
  s += webHeader2;
  s += "<div class='container3'><p>" + String(jarak) + "</p></div>";
  s += webFooter;
  server.send(200, "text/html", s);
}
 
void data() {               // handle halaman data (http://192.168.4.1/data/), kiriman data saja (tanpa css)
  server.send(200, "text/html", String(ukurJarak()));
}
 
void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid);
 
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/data", data);
  server.begin();
  Serial.println("HTTP server started");
 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop() {
  server.handleClient();
}
