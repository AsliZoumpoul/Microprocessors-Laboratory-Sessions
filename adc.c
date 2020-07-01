#include <msp430.h>
#include <math.h>

long ADCDATA;
float temp;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= 0x00;
    P1SEL1 |= BIT2; // Configure P1.2 for ADC
    P1SEL0 |= BIT2;



    ADC12CTL0 = ADC12SHT0_2 | ADC12ON; //sAMPLING TIME ADC12 ON
    ADC12CTL1 = ADC12SHP; // use sampling timer
    ADC12CTL2 |= ADC12RES_2; // conversion result 12bit
    ADC12MCTL0 |=ADC12VRSEL_0 | ADC12INCH_2; //SELECT BIT0 INPUT CHANNEL2
    ADC12IER0 |= ADC12IE0; //INTERRUPT ENABLE MEMORY 0


    while (1)
    {
        ADC12CTL0 |= ADC12ENC | ADC12SC; //start conversion
            _BIS_SR(LPM0_bits + GIE);
            }


            }

        #pragma vector = ADC12_VECTOR
        __interrupt void ADC12_ISR (void)
        {
            ADCDATA = ADC12MEM0;
            temp = ADCDATA * 0.087423687;
            __low_power_mode_off_on_exit();

        }

