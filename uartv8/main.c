#include <msp430.h> 

int i;

// 1.-Activar la funcion
// 2.-Habilitar el reset en USCI
// 3.- Fuente
// 4.- Velocidad de TX1RX
// 5.- A trabajar
// 6.- Hab. interrupcion


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P4DIR |= BIT7; //Configura el LED verde como salida
    P3SEL |= BIT3 | BIT4;//Activar la funcion de comunicacion en Tx y Rx en P3.3 y P3.4
    UCA0CTL1 |= UCSWRST; //Habilitamos el reset en USCIAAAA
    UCA0CTL1 |= UCSSEL__SMCLK;//Conectar la fuente SMCLK a la USCI
    UCA0BR0 |= 109; //Establecer la velocidad de 9600 bds
    UCA0MCTL |= UCBRS_2; //Otro registro para configurar la velocidad verificar tabla 36.4
    UCA0CTL1 &= ~UCSWRST; //Se desconecta el Areset
    UCA0IE |= UCRXIE; // Habilitamos interrupcion de recepcion
    __bis_SR_register(GIE);

}

#pragma vector=USCI_A0_VECTOR
__interrupt void UARTEco1(void){

    UCA0TXBUF = UCA0RXBUF;
    if (UCA0RXBUF == 'A')
                P4OUT |= BIT7;
            else if (UCA0RXBUF == 'B')
                P4OUT &= ~BIT7;
    }
