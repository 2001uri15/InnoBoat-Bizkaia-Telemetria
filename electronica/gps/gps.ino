#include <TinyGPS++.h>

// Instancia de TinyGPS++
TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);       // Monitor Serie
  Serial1.begin(9600);      // Comunicación con el GPS (pines 18 y 19)
  Serial.println("Esperando datos del GPS...");
}

void loop() {
  while (Serial1.available() > 0) {
    char c = Serial1.read();
    Serial.write(c); // Imprime datos NMEA crudos

    // Procesar datos con TinyGPS++
    gps.encode(c);

    if (gps.location.isUpdated()) {
      Serial.println("\n--- Datos GPS ---");
      Serial.print("Latitud: "); Serial.println(gps.location.lat(), 6);
      Serial.print("Longitud: "); Serial.println(gps.location.lng(), 6);
      Serial.print("Altitud: "); Serial.println(gps.altitude.meters());
      Serial.print("Satélites: "); Serial.println(gps.satellites.value());
      Serial.print("Velocidad (km/h): "); Serial.println(gps.speed.kmph());
      Serial.print("Fecha: "); Serial.print(gps.date.day());
      Serial.print("/"); Serial.print(gps.date.month());
      Serial.print("/"); Serial.println(gps.date.year());
      Serial.print("Hora (UTC): "); Serial.print(gps.time.hour());
      Serial.print(":"); Serial.print(gps.time.minute());
      Serial.print(":"); Serial.println(gps.time.second());
      Serial.println("-----------------\n");
    }
  }
}
