/* Código de Calibración para Ro

  Instrucciones para usarlo :

  * Subir este sketch a tu ESP32 con el MQ135 conectado.
  * Dejar el sensor funcionando unos 5 - 10 minutos antes de empezar para que se caliente un poco.
  * Abrir el Monitor Serial a 115200 baudios.
  * Vas a ver que toma 50 lecturas y al final te da un valor de Ro(en ohmios).
  * Ese valor lo copias después en tu programa principal,
  * por ejemplo: float Ro = 12345.67 // ← valor calibrado
  * 5972,43
 */

#include <Arduino.h>

// -------------------- Configuración -------------------- //
#define MQ135_PIN 34   // Pin analógico conectado al AO del MQ135
#define NUM_SAMPLES 50 // Cantidad de muestras para el promedio
#define ADC_RESOLUTION 4095.0
#define V_REF 3.3
#define RL_VALUE 10000.0 // Resistencia de carga en ohmios (normalmente 10k)

void setup()
{
  Serial.begin(115200);
  delay(2000);

  Serial.println("Iniciando calibración de Ro...");

  float rs_total = 0;

  for (int i = 0; i < NUM_SAMPLES; i++)
  {
    int raw_adc = analogRead(MQ135_PIN);
    float Vout = (raw_adc * V_REF) / ADC_RESOLUTION;
    float Rs = ((V_REF - Vout) * RL_VALUE) / Vout;

    rs_total += Rs;

    Serial.print("Muestra ");
    Serial.print(i + 1);
    Serial.print(": Rs = ");
    Serial.print(Rs);
    Serial.println(" ohm");

    delay(500); // Pequeño retardo entre muestras
  }

  float Ro = rs_total / NUM_SAMPLES;

  Serial.println("\n********** CALIBRACIÓN COMPLETA **********");
  Serial.print("Ro estimado = ");
  Serial.print(Ro);
  Serial.println(" ohm");
  Serial.println("*******************************************");
}

void loop()
{
  // No hace falta nada en loop
}
