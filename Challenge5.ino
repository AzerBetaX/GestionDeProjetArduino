#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTTYPE DHT11
#define DHTPIN  D1

char ssid[] = "PoleDeVinci_IOT";
char password[] = "2c3Gt1oTw8vv40";
char token[] = "4yp2TO77";
char username[] = "group38";
WiFiClient client;
PubSubClient pubsubclient("gdp.devinci.fr",1883,client);
DHT dht(DHTPIN, DHTTYPE, 11); // 11 works fine for ESP8266

void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //pourquoi 115200?
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println(" ");
  pubsubclient.setCallback(callback);
  if (!pubsubclient.connect("ESP8266Client",username,token)) 
  {
   Serial.print("MQTT connection failed! Error code = ");
    }else{
   Serial.println("CONNECTE AU MQTTBROKER");
 }
  delay(1000);
}

void loop() {
 
  pubsubclient.loop();
  float newTemp = dht.readTemperature();
  float newHum = dht.readHumidity();
  Serial.println(String(newTemp) + "degre");
  Serial.println(String(newHum) + " %");
   delay(1000);
  pubsubclient.publish("challenge5/38/temp",String(newTemp).c_str(),true);
   delay(5000);
  pubsubclient.publish("challenge5/38/hum",String(newHum).c_str(),true);
  delay(1000);
    

    
    }
