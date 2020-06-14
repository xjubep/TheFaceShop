#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

const char* ssid = "U+Net3F5A";
const char* password = "1CB2019693";
const char* host = "3.21.37.105";
const uint16_t port = 8000;

int id = 5; // device id
// sda = 21, scl = 22
int leftTempBtn = 12;
int rightTempBtn = 13;
int trig = 2;
int echo = 5;
int led = 27;
int buzzer = 14;

double distance;
double leftTemp, rightTemp;
 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setupWiFi(void) {
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

void sendData(double leftTemp, double rightTemp) {
  String url;

  if (leftTemp == -1 || rightTemp == -1) {
    return;
  }
  
  url = "/input?id=" + String(id);
  url += "&leftTemp=" + String(leftTemp);
  url += "&rightTemp=" + String(rightTemp);
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
    tone(buzzer,262);
    delay(100);
    noTone();
    tone(buzzer,294);
    delay(100);
    noTone();
    tone(buzzer,330);
    delay(100);
    noTone();        
  }
  else {
    Serial.println("client.available() timed out");
    tone(buzzer,330);
    delay(100);
    noTone();
    tone(buzzer,294);
    delay(100);
    noTone();
    tone(buzzer,262);
    delay(100);
    noTone();       
  }

  Serial.println("Closing connection.");
  client.stop();
}

int playing = 0;
void tone(byte pin, int freq) {
  ledcSetup(0, 2000, 8); // setup beeper
  ledcAttachPin(pin, 0); // attach beeper
  ledcWriteTone(0, freq); // play tone
  playing = pin;
}

void noTone() {
  tone(playing, 0);
}

double getDistance() {
  double distance = -1;
  
  digitalWrite(trig, 1);
  delayMicroseconds(10);
  digitalWrite(trig, 0);

  if (digitalRead(echo) == 0) {
    distance = (double)pulseIn(echo, 1) / 29 / 2;
  }
  else {
    pinMode(echo, OUTPUT);
    digitalWrite(echo, 0);
    pinMode(echo, INPUT);
  }

  Serial.print(distance);
  Serial.println("cm");
  delay(10);

  return distance; 
}

void setup() {
  Serial.begin(115200);
  delay(10);
  
  mlx.begin();  
  pinMode(leftTempBtn, INPUT);
  pinMode(rightTempBtn, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
 
  setupWiFi();

}

void loop() {
  double d = getDistance();

  if (d > 3 && d < 7) {
    tone(buzzer,330);
    delay(10);
    noTone();
    tone(buzzer,330);
    delay(10);
    noTone();  
    tone(buzzer,330);
    delay(10);
    noTone();    
  }
  
  if (digitalRead(leftTempBtn) == HIGH) {
    leftTemp = getTemp();
    tone(buzzer,262);
    delay(100);
    noTone();
  }
  else if (digitalRead(rightTempBtn) == HIGH) {
    rightTemp = getTemp();
    tone(buzzer,262);
    delay(100);
    noTone();
    sendData(leftTemp, rightTemp); 
    leftTemp = 0;
    rightTemp = 0;
  }
  
  delay(100);
}