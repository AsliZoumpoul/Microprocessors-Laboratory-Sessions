#include <msp430.h> 

// toggles LED using timer interrupts

int main(void) {
    WDTCTL = WDTPW + WDTHOLD;
    PM5CTL0 &= ~LOCKLPM5;

    P1SEL0=P3SEL0=0x00;
    P1SEL1=P3SEL1=0x00;
    P1DIR =0xFC;
    P3DIR =0x10;

    int i=0;
    int port1[]={0xFC,0x18,0x6C,0x3C,0x9B,0xB4,0xF4,0x1C,0xFC,0xBC};
    int port3[]={0x00,0x00,0x10,0x10,0x10,0x10,0x10,0x00,0xF10,0x10};
    // Timer0_A setup
    TA0CCR0 = 32767; // Counter value
    TA0CCTL0 |= CCIE; // Enable Timer interrupts
    TA0CTL |= TASSEL_1 + MC_1; // Source: ACLK, Up Mode (Counts to TA0CCR0), input divider by 2
    _BIS_SR(GIE);

    #pragma vector=TIMER0_A0_VECTOR // Timer0 A0 interrupt service routine
    __interrupt void TIMER (void){
        P1OUT=0xFC;
        P3OUT=0x00;
    }
}
