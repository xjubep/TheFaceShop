#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
 
// replace with your channel’s thingspeak API key and your SSID and password
//String apiKey = "XVDYQC4TAE3SPB7H";
const char* ssid = "U+Net3F5A";
const char* password = "1CB2019693";
//const char* server = "api.thingspeak.com";
const char* host = "3.21.37.105";
const uint16_t port = 8000;
int id = 5;
int tempInputPin = D12;
 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
//WiFiClient client;

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

  //Serial.println("Waiting 1 Minute before restarting...");
  //delay(58000);
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


 
//    if (client.connect(server,80)) {
//      String postStr = apiKey;
//      postStr +="&field4=";
//      postStr += String(ot);
//      postStr += "\r\n\r\n";
// 
//      client.print("POST /update HTTP/1.1\n");
//      client.print("Host: api.thingspeak.com\n");
//      client.print("Connection: close\n");
//      client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
//      client.print("Content-Type: application/x-www-form-urlencoded\n");
//      client.print("Content-Length: ");
//      client.print(postStr.length());
//      client.print("\n\n");
//      client.print(postStr);
// 
//      Serial.print("Object: "); Serial.print(ot); Serial.println(" *C");
//      Serial.println("Sending data to Thingspeak");
//    }
//    client.stop();
  }
  delay(10);
}
