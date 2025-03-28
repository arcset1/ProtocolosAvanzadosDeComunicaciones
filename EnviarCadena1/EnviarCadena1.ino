#include <Arduino.h>

#define BUFFER_SIZE 30

char buffer[BUFFER_SIZE] = "ABABAAAAAAAAAAABBBBBABABABAA"; // Arreglo con 29 caracteres más salto de línea

void setup() {
    Serial.begin(9600); // Iniciar comunicación serial a 9600 bps
}

void loop() {
    for (int i = 0; i < BUFFER_SIZE - 1; i++) { // Enviar solo los primeros 29 caracteres
        Serial.print(buffer[i]); // Enviar cada carácter uno por uno
        delay(100); // Pequeño retraso entre caracteres
    }
    Serial.println(); // Enviar el salto de línea explícitamente
    delay(1000); // Esperar 1 segundo antes de reenviar la secuencia completa
}
