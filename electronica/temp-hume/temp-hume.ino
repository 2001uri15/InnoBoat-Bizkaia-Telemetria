#include <DHT.h>

#define DHTPIN 2        // Pin de datos conectado al DHT11 (puedes cambiar este pin)
#define DHTTYPE DHT11   // Definimos el tipo de sensor DHT11

DHT dht(DHTPIN, DHTTYPE);  // Inicializamos el sensor

void setup() {
  Serial.begin(9600);      // Inicia la comunicación serial
  dht.begin();             // Inicia el sensor
}

void loop() {
  delay(2000);  // Espera 2 segundos entre lecturas

  // Leer la humedad y la temperatura
  float humedad = dht.readHumidity();
  float temperatura = dht.readTemperature();

  // Verificar si las lecturas son válidas
  if (isnan(humedad) || isnan(temperatura)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }

  // Mostrar los resultados
  Serial.print("Humedad: ");
  Serial.print(humedad);
  Serial.print(" %\t");

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");
}
