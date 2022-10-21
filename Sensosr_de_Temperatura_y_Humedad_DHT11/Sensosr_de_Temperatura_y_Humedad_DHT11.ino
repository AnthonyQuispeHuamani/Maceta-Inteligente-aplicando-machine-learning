#include <DHT.h>
#include <DHT_U.h>

// Incluimos librería
#include "DHT.h"
 
// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 2
// Definir lector LDR
int LDRpin = 0;
int AGUADato = 0;

int LDRValor = 0;

// Dependiendo del tipo de sensor
#define DHTTYPE DHT11
 
// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Inicializamos comunicación serie
  Serial.begin(9600);
 
  // Comenzamos el sensor DHT
  dht.begin();
  
}

void loop() {
    // Esperamos 2 segundos entre medidas
  delay(2000);
 
  // VALOR DEL LDR
  LDRValor = analogRead(LDRpin);
  // VALOR DEL SENSOR DE AGUA
  AGUADato = analogRead(A1);

  // Esperamos 2 segundos entre medidas
  LDRValor = analogRead(LDRpin);
  // Leemos la humedad relativa
  float h = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  float t = dht.readTemperature();
  // Leemos la temperatura en grados Fahrenheit
  float f = dht.readTemperature(true);
 
  // Comprobamos si ha habido algún error en la lectura
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }
 
  // Calcular el índice de calor en Fahrenheit
  float hif = dht.computeHeatIndex(f, h);
  // Calcular el índice de calor en grados centígrados
  float hic = dht.computeHeatIndex(t, h, false);
 
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.println(" %\t");
  Serial.println("Temperatura: ");
  Serial.print(t);
  Serial.println(" *C ");
  Serial.print(f);
  Serial.println(" *F\t");
  Serial.println("Índice de calor: ");
  Serial.print(hic);
  Serial.println(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
  Serial.println("- - - - - - - - - - - - - - - - ");

  Serial.println("Valor del LUZ: ");
  Serial.println(LDRValor);
  if(LDRValor >= 1010){
    Serial.println("POCA ILUMINACION");    
  }
  else{
    Serial.println("Iluminacion ACEPTABLE");    
  }
  Serial.println("NIVEL DE AGUA");
  Serial.print(AGUADato);  

}
