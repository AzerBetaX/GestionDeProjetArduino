// Pour lire la valeur de sortie d'un potentiomètre / relier le ground, relier 3V et relier un fil sur A0 qui va recevoir la valeur
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  //Serial.println(sensorValue);
  delay(100);     // delay in between reads for stability
  String s = "38#"+String(sensorValue)+"/";
  Serial.println(s);
}
// solution de challenge trouvé sur https://docs.arduino.cc/built-in-examples/basics/AnalogReadSerial
// Rem : celui qui recoit RX et celui qui transmet TX, remier le ground des 1 nod et lire le potentiel de leur potentiomètre
