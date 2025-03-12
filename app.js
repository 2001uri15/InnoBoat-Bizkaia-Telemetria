// Crear el mapa
var map = L.map('map').setView([43.3, -3.0], 10); // Ejemplo de coordenadas (puedes usar las tuyas)

// Agregar capa de mapa base (OpenStreetMap)
L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png').addTo(map);

// Función para obtener los datos de la API de Copernicus
async function getMarineCurrents(lat, lon) {
    // URL de la API de Copernicus (ajusta según las coordenadas y parámetros)
    const apiUrl = `https://api.marine.copernicus.eu/service?lat=${lat}&lon=${lon}&product=sea_surface_currents&start_date=2025-02-26T00:00:00Z&end_date=2025-02-26T23:59:59Z`;

    try {
        // Realizar la solicitud a la API
        const response = await fetch(apiUrl, {
            headers: {
                'Authorization': 'Bearer YOUR_API_KEY_HERE', // Reemplaza con tu clave API
            }
        });

        // Convertir la respuesta a JSON
        const data = await response.json();

        // Extraer datos relevantes de la respuesta
        const currents = data.features.map(feature => ({
            lat: feature.geometry.coordinates[1],
            lon: feature.geometry.coordinates[0],
            velocity: feature.properties.velocity,  // Velocidad de la corriente
            direction: feature.properties.direction  // Dirección de la corriente
        }));

        return currents;
    } catch (error) {
        console.error('Error obteniendo los datos de la API:', error);
        return [];
    }
}

// Función para actualizar las corrientes en el mapa
async function updateCurrents() {
    // Coordenadas para la solicitud (puedes ajustar según lo necesites)
    const lat = 43.3;
    const lon = -3.0;

    // Obtener los datos de las corrientes
    const currents = await getMarineCurrents(lat, lon);

    // Limpiar cualquier capa anterior de corrientes
    map.eachLayer(layer => {
        if (layer instanceof L.VelocityLayer) {
            map.removeLayer(layer);
        }
    });

    // Crear nueva capa de corrientes
    const currentsLayer = L.velocityLayer({
        data: {
            type: "FeatureCollection",
            features: currents.map(curr => ({
                type: "Feature",
                geometry: {
                    type: "Point",
                    coordinates: [curr.lon, curr.lat]
                },
                properties: {
                    velocity: curr.velocity,
                    direction: curr.direction
                }
            }))
        },
        velocityScale: 0.01,  // Ajustar para ver las corrientes de manera clara
        displayValues: true,
        displayOptions: { velocityType: 'velocity', position: 'bottomright' }
    }).addTo(map);
}

// Actualizar los datos cada minuto
setInterval(updateCurrents, 60000);  // 60000 ms = 1 minuto

// Inicializar la primera actualización
updateCurrents();
