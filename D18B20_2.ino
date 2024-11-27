#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pino digital ao qual o sensor DS18B20 está conectado
#define ONE_WIRE_BUS 2

// Instancia o objeto OneWire e associa o pino do sensor
OneWire oneWire(ONE_WIRE_BUS);

// Repassa as referências do OneWire para o sensor DS18B20
DallasTemperature sensor(&oneWire);

float leituraInicial = 0; // temperatura inicial
float leituraAtual = 0;    // leitura atual

void escreveTemperatura(const char* tipo, float temp) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(tipo);
  lcd.setCursor(0, 1);
  lcd.print(temp, 2); // Mostra 1 casa decimal
}

void setup() {
  lcd.init();
  lcd.setBacklight(HIGH);
  Serial.begin(9600);
  Serial.println("Sensor de temperatura Dallas DS18B20");
  
  // Inicializa o sensor DS18B20
  sensor.begin();

  // pega uma temperatura inicial
  sensor.requestTemperatures();
  leituraInicial = sensor.getTempCByIndex(0);
}

void loop() {
  Serial.println("");
  Serial.print("Temperatura inicial: ");
  Serial.println(leituraInicial);
  // Solicita uma nova leitura do sensor
  sensor.requestTemperatures();
  leituraAtual = sensor.getTempCByIndex(0);
  
  // Calcula a variação de temperatura
  float variacao = leituraAtual - leituraInicial;

  // Exibe os resultados no LCD e na Serial
  if (variacao >= 0.85 && variacao <= 5) {
    escreveTemperatura("Exotermica:", leituraAtual);
    Serial.print("Exotermica: ");
    Serial.println(leituraAtual);
  } else if (variacao <= -1 && variacao >= -5) {
    escreveTemperatura("Endotermica:", leituraAtual);
    Serial.print("Endotermica: ");
    Serial.println(leituraAtual);
  } else {
    escreveTemperatura("Normal:", leituraAtual);
    Serial.print("Normal: ");
    Serial.println(leituraAtual);
  }

  // Aguarda antes de atualizar leituraInicial
  delay(1000); // 1 segundo
  
  // Atualiza a leitura anterior para a próxima iteração
  // leituraInicial = leituraAtual;
}
