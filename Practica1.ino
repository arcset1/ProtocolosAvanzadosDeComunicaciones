const unsigned long timeout = 1000; // Tiempo máximo de espera (ms)
const int bufferSize = 64;          // Tamaño del buffer de recepción
char buffer[bufferSize];
int index = 0;
unsigned long lastReceiveTime = 0;

void setup() {
  // Inicializar comunicación serial a 115200 baudios, paridad par y 2 bits de stop
  Serial.begin(115200, SERIAL_8E2);
}

void loop() {
  // Envío continuo de una cadena de datos
  Serial.println("Mensaje continuo");
  delay(500);
  
  // Proceso de recepción de datos
  while (Serial.available() > 0) {
    char incomingByte = Serial.read();
    lastReceiveTime = millis(); // Actualiza el tiempo de la última recepción

    // Verificar si se recibe un salto de línea
    if (incomingByte == '\n') {
      buffer[index] = '\0'; // Termina la cadena
      Serial.print("Cadena recibida (por salto de línea): ");
      Serial.println(buffer);
      index = 0;  // Reinicia el índice del buffer
      continue;
    }
    
    // Agregar byte al buffer si hay espacio
    if (index < bufferSize - 1) {
      buffer[index++] = incomingByte;
    } else {
      // Condición de desbordamiento de buffer
      buffer[bufferSize - 1] = '\0'; // Asegura la terminación de la cadena
      Serial.print("Error: Desbordamiento del buffer. Cadena incompleta: ");
      Serial.println(buffer);
      index = 0;
    }
  }
  
  // Condición de timeout: si no se reciben datos por 'timeout' ms y hay datos en el buffer
  if (index > 0 && (millis() - lastReceiveTime) >= timeout) {
    buffer[index] = '\0';
    Serial.print("Cadena recibida (por timeout): ");
    Serial.println(buffer);
    index = 0;
  }
}
