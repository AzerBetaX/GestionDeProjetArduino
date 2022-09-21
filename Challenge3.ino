
#include <ES-

char ssid[] = "PoleDeVinci_IOT";
char password[] = "2c3Gt1oTw8vv40";
String serverName = "http://gdp.devinci.fr/wifi-challenge";
String token = "mrtkdi";
String postData = "38#"+token;
String queryString = String("?token="+postData);
WiFiClient client;
HTTPClient http;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //pourquoi 115200?
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println(" ");
  Serial.println(String(WiFi.localIP()[0])+"."+String(WiFi.localIP()[1])+"."+String(WiFi.localIP()[2])+"." + String(WiFi.localIP()[3])+ " : voici l'adresse IP locale");
}

void loop() {
  
    http.begin(client,"http://gdp.devinci.fr/wifi-challenge");
    http.addHeader("Content-Type","test/plain");
    int httpCode = http.POST(postData);
    http.end();
    delay(1000);
    
    }
