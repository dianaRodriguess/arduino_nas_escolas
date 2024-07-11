const int tempPin = A0;  // Pino do sensor de temperatura LM35
const int redPin = 9;    // Pino do LED RGB (vermelho)
const int greenPin = 10; // Pino do LED RGB (verde)
const int bluePin = 11;  // Pino do LED RGB (azul)

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  int tempValue = analogRead(tempPin);
  float tempCelsius = (tempValue / 1024.0) * 500.0;
  Serial.print("Temperatura: ");
  Serial.print(tempCelsius);
  Serial.println(" °C");

  if (tempCelsius < 25) {
    setColor(0, 0, 255); // Azul (Endotérmica)
  } else if (tempCelsius > 30) {
    setColor(255, 0, 0); // Vermelho (Exotérmica)
  } else {
    setColor(0, 255, 0); // Verde (Normal)
  }

  delay(1000);
}

void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

