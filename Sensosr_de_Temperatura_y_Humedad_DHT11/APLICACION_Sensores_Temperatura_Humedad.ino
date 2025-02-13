#include <DHT.h>
#include <DHT_U.h>

// Incluimos librería
#include "DHT.h"
 
// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 2
// Definir lector LDR
float LDRpin = 0;
float AGUADato = 0;

float LDRValor = 0;

boolean sendData = false;

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
       

    if(Serial.available()>0){
        char date = Serial.read();

            while (date == '1') {  

              delay(1100);
                
                  // VALOR DEL LDR luz
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
  


              Serial.println("h"+String(h));
              delay(600);
              Serial.println("t"+String(t));
              delay(600);
              Serial.println("l"+String(LDRValor));
              delay(600);
              Serial.println("a"+String(AGUADato));
              delay(600);              
              

                  char date = Serial.read();              
              if(date == '0'){
                break;                
              }              

              
            }
          
    }

  }
  
