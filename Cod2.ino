const int ledPin = 12; // Pin donde está conectado el LED

void setup() {
  pinMode(ledPin, OUTPUT); // Configura el pin del LED como salida
  Serial.begin(9600); // Inicializa la comunicación serial a 9600 baudios
}

void loop() {
  if (Serial.available() > 0) { // Si hay datos disponibles para leer
    String receivedData = Serial.readStringUntil(""); // Lee la cadena de datos hasta el delimitador ""
    
    // Interpretar los datos recibidos y controlar el LED
    if (receivedData == "LED1ON_") {
      digitalWrite(ledPin, HIGH); // Enciende el LED
    } else if (receivedData == "LED1OFF_") {
      digitalWrite(ledPin, LOW); // Apaga el LED
    }
  }
}