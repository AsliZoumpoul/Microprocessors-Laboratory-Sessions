#include <msp430.h> 

int j=0;

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;
    P1DIR |= 0xFC;
    P3DIR |= 0x10;


         int port1[]={0xFC,0x18,0x6C,0x3C,0x9B,0xB4,0xF4,0x1C,0xFC,0xBC};
         int port3[]={0x00,0x00,0x10,0x10,0x10,0x10,0x10,0x00,0x10,0x10};

    TA0CCR0 |= 32767;
    TA0CCTL0 |= CCIE; // Enable Timer interrupts
    TA0CTL |= TASSEL_1 + MC_1+ ID_0; // ACLK, Up Mode (Counts to TA0CCR0)
    _BIS_SR(GIE);
    while(1)
      {

          if(j!=10)
                  {
                      P3OUT = port3[j];
                      P1OUT = port1[j];
                  }

          else if(j==10)
                  {
              j=0;
                  }

  }
}
#pragma vector=TIMER0_A0_VECTOR // Timer0 A0 interrupt service routine
__interrupt void Timer0_A0 (void)
{
        j+=1;
}
