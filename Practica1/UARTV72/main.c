#include <msp430.h>

int i;
static const char menuPrincipal[] = "\r\nMenú Principal\n\n\r1.Encender/Apagar led Verde\n\r2.Generar 3 Tonos\n\r3.Generar 3 señales PWM\n\r4 Leer el ADC\n\r5.Salir del sistema\n\n\r>_";
static const char subMenuLeds[] = " \n\rSubmenu de led rojo\n\ra.Encender el led rojo\n\rb.Apajar el led Rojo\n\rc.Regresar al menu principal\n\r";
void imprimir(const char mensaje[], unsigned int longitud );


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    // stop watchdog timer
    P4DIR |= BIT7; // LED verde como salida
    P4SEL |= BIT5 | BIT4; //Activar la funcion de  comunicacion en RX y TX P4.5 y P4.4
    UCA1CTL1 &= ~UCSWRST; // Habilitamos el reset en USCI
    UCA1CTL1 |= UCSSEL__SMCLK; //Conectamos la fuente SMCLK a la USCI
    UCA1BR0 = 109; // Establecer la velocidad de 9600 baudios. (Pagina 952 de la guia de usuario)
    UCA1MCTL = UCBRS_2; // Es un registro dentro de otro registro, por lo que es 2 porque nos dice que asi es la config, pero el valor es 4 porque esta dentro otro registro, pag. 960,
    UCA1CTL1 &= ~UCSWRST; // Se desconecta el RST para que pueda funcionar la comunicacion serial / se desconecta el reset
    UCA1IE |= UCRXIE; // La comunciacion, en este caso es unidireccional, activamos la interrupcion de Recepcion
    __bis_SR_register(GIE); // Habilitamos las interupciones generales

    return 0;

}


void imprimir(const char mensaje[], unsigned int longitud ){
    for (i = 1; i<longitud ;i++){
        UCA1TXBUF = mensaje[i] ;
        __delay_cycles(10000);
}

}

#pragma vector=USCI_A1_VECTOR
    __interrupt void cuenta (void){
        UCA1TXBUF = UCA1RXBUF; // Realizamos un Eco
        if(UCA1RXBUF=='A'){
            P4OUT |= BIT7;
            }else if(UCA1RXBUF=='B'){
                P4OUT &= ~BIT7;
            }
}
