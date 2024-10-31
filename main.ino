#include <OneWire.h>
#include <DallasTemperature.h>

//variavel do pino que esta plugado o Sensor
//Neste caso é o pino 2, mais pode usar qualquer pino digital
#define ONE_WIRE_BUS 2

//Instacia o Objeto oneWire e Seta o pino do Sensor para iniciar as leituras
OneWire oneWire(ONE_WIRE_BUS);

//Repassa as referencias do oneWire para o Sensor Dallas (DS18B20)
DallasTemperature sensor(&oneWire);


void setup() {
  Serial.begin(9600);
  Serial.println("Sensor de temperatura Dallas DS18b20");
  //Inicia o objeto da biblioteca do Dallas
  sensor.begin();
}

void loop() {
  sensor.requestTemperatures();
  // A temperatura em Celsius para o dispositivo 1 no índice 0 (é possivel ligar varios sensores usando a mesma porta do arduino)
  float leitura = sensor.getTempCByIndex(0);
  //Imprime na serial a varivel que recebe os dados do Sensor
  Serial.println(leitura);
  delay(100);
}