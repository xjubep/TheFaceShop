#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

const char* ssid = "U+Net3F5A";
const char* password = "1CB2019693";
const char* host = "3.21.37.105";
const uint16_t port = 8000;
int id = 5;
int tempInputPin = D12;
 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setupWiFi(void) {
  WiFi.begin(ssid, password);
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");   
}

double getTemp(void) {
  double ot = mlx.readObjectTempC();

  if (isnan(ot)) {
      Serial.println("Failed to read from sensor!");
      return -1;
  }

  return ot;
}

void sendData(void) {
  String url;
  double temp = getTemp();

  if (temp == -1) {
    return;
  }
  
  url = "/input?id=" + String(id);
  url += "&skintemp=" + String(temp);
  Serial.println(url);

  WiFiClient client;

  if (!client.connect(host, port)) {
    Serial.println("Connection failed.");
    return;
  }

  client.print("GET " + url + " HTTP/1.1\n\n");

  int maxloops = 0;

  while (!client.available() && maxloops < 1000) {
    maxloops++;
    delay(1);
  }

  if (client.available() > 0) {
    String line = client.readStringUntil('\r');
    Serial.println(line);
  }
  else {
    Serial.println("client.available() timed out");
  }

  Serial.println("Closing connection.");
  client.stop();
}
 
void setup() {
  Serial.begin(115200);
  delay(10);
  mlx.begin();  
  pinMode(tempInputPin, INPUT);
 
  setupWiFi();
}
 
void loop() { 
  int tempBtn = digitalRead(tempInputPin);

  if (tempBtn == HIGH) {
    sendData();
  }
  
  delay(10);
}
