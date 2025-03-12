import gps
import time

# Iniciar la sesión con gpsd
session = gps.gps(mode=gps.WATCH_ENABLE)

try:
    while True:
        report = session.next()
        if report['class'] == 'TPV':
            lat = getattr(report, 'lat', "Desconocido")
            lon = getattr(report, 'lon', "Desconocido")
            print(f"Latitud: {lat}, Longitud: {lon}")
        time.sleep(1)  # Esperar 1 segundo
except KeyboardInterrupt:
    print("Programa terminado")