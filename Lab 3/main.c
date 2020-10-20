// Thomas Dodds
// Lab 3

#include <msp430g2553.h>

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    //set i/o function for 2.6 and 2.7
    P2SEL = 0;
    P2SEL2 = 0;
    // port 2 all pins output
    P2DIR = 0xFF;
    // port 2 initial output off
    P2OUT = 0x00;

    //set port 1 pins 5, 6, and 7 to be output
    P1DIR &= ~(BIT5 | BIT6 | BIT7);
    //enable resistors for port 1 pins 5, 6, and 7
    P1REN |= BIT5 | BIT6 | BIT7;
    //set resistors to be pull up on port 1 pins 5, 6, and 7
    P1OUT |= BIT5 | BIT6 | BIT7;

    //enable interrupt on P1 5, 6, and 7
    P1IES |= BIT5 | BIT6 | BIT7;
    P1IE |= BIT5 | BIT6 | BIT7;
    P1IFG &= ~(BIT5 | BIT6 | BIT7);

    _BIS_SR(LPM4_bits + GIE);
}

#pragma vector = PORT1_VECTOR;
__interrupt void Port_1(void){
    int x;
    if(P1IFG & BIT5) { // button 1
        for(x = 0; x < 8; x++){
            P2OUT |= (P2OUT << 1) + BIT0;
            __delay_cycles(200000);
        }
        __delay_cycles(1000000);
        P2OUT = 0x00;
        P1IFG &= ~BIT5;
    }else if(P1IFG & BIT6) { // button 2
        for(x = 0; x < 8; x++){
            P2OUT |= (P2OUT >> 1) + BIT7;
            __delay_cycles(200000);
        }
        __delay_cycles(1000000);
        P2OUT = 0x00;
        P1IFG &= ~BIT6;
    }else if(P1IFG & BIT7) { // button 3
        for(x = 0; x < 8; x++){
            P2OUT = 0xAA;
            __delay_cycles(200000);
            P2OUT = 0x55;
            __delay_cycles(200000);
        }
        __delay_cycles(1000000);
        P2OUT = 0x00;
        P1IFG &= ~BIT7;
    }
}
