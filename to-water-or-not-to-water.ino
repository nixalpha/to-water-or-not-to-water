#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define WATER_SENSOR A0
#define MEASURE_INTERVAL 1000

unsigned long lastMeasureMillis;
int sensorValue;

const char* ssid = "";
const char* password = "";

ESP8266WebServer server(80);

void handleRoot() {
  char buf[5];
  server.send(200, "text/plain", itoa(sensorValue, buf, 10));
  Serial.print("Client connected");
}
 
void setup() {
  Serial.begin(115200);
  
  // Connection to WiFi
  Serial.println();
  Serial.print("Connecting with ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected with WiFi.");
 
  // Start WebServer.
  server.on("/", handleRoot);
  server.begin();
  Serial.println("WebServer started.");
 
  // This is IP of WebServer
  Serial.print("IP of WebServer: ");
  Serial.print("http://");
  Serial.println(WiFi.localIP());
}

void loop() {  
  server.handleClient();

  if (millis() - lastMeasureMillis > MEASURE_INTERVAL) {
    lastMeasureMillis = millis();
    sensorValue = analogRead(WATER_SENSOR);
    Serial.println(sensorValue);;
  }
}
