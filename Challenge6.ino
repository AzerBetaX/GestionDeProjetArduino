
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char WIFI_SSID[] = "PoleDeVinci_IOT";
const char WIFI_PASSWORD[] = "2c3Gt1oTw8vv40";

const char MQTT_HOST[] = "gdp.devinci.fr";
const int MQTT_PORT = 1883;
const char MQTT_CLIENT_ID[] = "ESP8266 NodeMCU";
const char MQTT_USER[] = "group38";
const char MQTT_PASSWORD[] = "4yp2TO77";
const char TOPIC[] = "challenge6/38/task";

WiFiClient client;
PubSubClient mqttClient(client);
void callback(char* topic, byte* payload, unsigned int length) {
  String str = "";
  Serial.print("Message: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    str+= (char)payload[i];
  }
  Serial.println();
  //String(newTemp).c_str()
  int i = slice(String(str));
  mqttClient.publish("challenge6/38/submit",String(i).c_str(),true);

  
}

int slice(String str){
  String s = "";
  int j = 0;
  while(String(str[j]) != " ")
  {
    s+= str[j];
    j++;
  }
  int integer1 = atoi(s.c_str());
  s = "";

  int k=str.length()-1;
  while(String(str[k])!=" "){
    s+=str[k];
    k--;
  }
  String sp = "";
  for (int m=s.length()-1; m>=0; m--){
    sp+=s[m];
  }
  int integer2 = atoi(sp.c_str());
  Serial.println(integer2);
String operateur = String(str[j+1]);
Serial.println(operateur);

int resultat = 0;
if (operateur == "+"){
    resultat = integer1 + integer2;
}
if (operateur == "x"){
    resultat = integer1 * integer2;
}
if (operateur == "X"){
    resultat = integer1 ^ integer2;
}
if (operateur == "<"){
    resultat = integer1 << integer2;
}
Serial.println(resultat);
  return resultat;
}


void setup()
{
    Serial.begin(9600);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected to Wi-Fi");

    mqttClient.setServer(MQTT_HOST, MQTT_PORT);
    mqttClient.setCallback(callback);

    while (!client.connected()) {
        if (mqttClient.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD )) {
            Serial.println("Connected to MQTT broker");
        } else {
            delay(500);
            Serial.print(".");
        }
    }

    mqttClient.subscribe(TOPIC);
}

void loop()
{
    mqttClient.loop();
    delay(1);
}
