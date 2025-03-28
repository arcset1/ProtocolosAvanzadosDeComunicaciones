#include <msp430.h>

#define BUFFER_SIZE 30

volatile char buffer[BUFFER_SIZE]; // Arreglo para almacenar los caracteres
volatile int index = 0;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P4DIR |= BIT7; // Configura el LED verde como salida
    P3SEL |= BIT3 | BIT4; // Activar la función de comunicación en Tx y Rx en P3.3 y P3.4
    UCA0CTL1 |= UCSWRST; // Habilitamos el reset en USCI
    UCA0CTL1 |= UCSSEL__SMCLK; // Conectar la fuente SMCLK a la USCI
    UCA0BR0 = 109; // Establecer la velocidad de 9600 bds
    UCA0MCTL |= UCBRS_2; // Otro registro para configurar la velocidad, verificar tabla 36.4
    UCA0CTL1 &= ~UCSWRST; // Se desconecta el reset
    UCA0IE |= UCRXIE; // Habilitamos interrupción de recepción
    __bis_SR_register(GIE); // Habilita interrupciones globales
}

#pragma vector=USCI_A0_VECTOR
__interrupt void UARTEco1(void)
{
    char received = UCA0RXBUF; // Leer el carácter recibido

    if (received == '\n' || index >= BUFFER_SIZE - 1) {
        buffer[index] = '\0'; // Finalizar la cadena
        index = 0; // Reiniciar el índice para la próxima recepción
    } else {
        buffer[index++] = received; // Almacenar en el buffer
    }

    UCA0TXBUF = received; // Eco del carácter recibido

    if (received == 'A') {
        P4OUT |= BIT7; // Encender LED
    } else if (received == 'B') {
        P4OUT &= ~BIT7; // Apagar LED
    }
}
