const int pir = 12;
const int ledPin =  13;

int pirState = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Micro Project Thailand ~^.^~ ");
  pinMode(ledPin, OUTPUT);
  pinMode(pir, INPUT);
}

void loop() {
  pirState = digitalRead(pir);

  

  if (pirState == HIGH) {
    digitalWrite(ledPin, HIGH);
    Serial.println("1111111111111111");
  }

  else if (pirState == LOW) {
    digitalWrite(ledPin, LOW);
    Serial.println("0");

  }
delay(200);
}
