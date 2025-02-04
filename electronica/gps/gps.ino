#include <TinyGPS++.h>

TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600); // GPS en pines 18 (TX) y 19 (RX)
  Serial.println("Esperando datos del GPS...");
}

void loop() {
  while (Serial1.available() > 0) {
    char c = Serial1.read();
    gps.encode(c);

    if (gps.satellites.isUpdated() || gps.location.isUpdated()) {
      Serial.println("\n--- Información GPS ---");
      
      // Satélites en uso para el fix
      Serial.print("Satélites conectados: ");
      Serial.println(gps.satellites.value());

      // Satélites visibles (se actualiza con GSV)
      Serial.print("Satélites visibles: ");
      if (gps.satellites.isValid()) {
        Serial.println(gps.satellites.value()); // Mismo valor si GSV no está disponible
      } else {
        Serial.println("No disponible");
      }

      // Coordenadas
      if (gps.location.isValid()) {
        Serial.print("Latitud: ");
        Serial.println(gps.location.lat(), 6);
        
        Serial.print("Longitud: ");
        Serial.println(gps.location.lng(), 6);
      } else {
        Serial.println("Latitud: No disponible");
        Serial.println("Longitud: No disponible");
      }

      Serial.println("-------------------------");
    }
  }
}
