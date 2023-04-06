#include <tiny10.h>

#include <delay.h>

// Declare your global variables here

// Pin change interrupt service routine
interrupt [PC_INT0] void pin_change_isr(void)
{
// Place your code here

}

// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
{
// Place your code here

}


// Read the AD conversion result
unsigned char read_adc(unsigned char adc_input)
{
ADMUX=adc_input & 0x03;
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=(1<<ADSC);
// Wait for the AD conversion to complete
while ((ADCSRA & (1<<ADIF))==0);
ADCSRA|=(1<<ADIF);
return ADCL;
}

void main(void)
{
// Declare your local variables here

// Main Clock source: Calibrated Internal 8 MHz Osc.
CCP=0xd8;
CLKMSR=(0<<CLKMS1) | (0<<CLKMS0);
// Clock Prescaler division factor: 8
CCP=0xd8;
CLKPSR=(0<<CLKPS3) | (0<<CLKPS2) | (1<<CLKPS1) | (1<<CLKPS0);

// Reset Source checking
if (RSTFLR & (1<<PORF))
   {
   // Power-on Reset
   RSTFLR=0;
   // Place your code here

   }
else if (RSTFLR & (1<<EXTRF))
   {
   // External Reset
   RSTFLR=0;
   // Place your code here

   }
else if (RSTFLR & (1<<WDRF))
   {
   // Watchdog Reset
   RSTFLR=0;
   // Place your code here

   }

// Voltage Level Monitor initialization
// Trigger Level: Voltage Level Monitor Disabled
// Interrupt: Off
VLMCSR=(0<<VLMF) | (0<<VLMIE) | (0<<VLM2) | (0<<VLM1) | (0<<VLM0);

// Input/Output Ports initialization
// Port B initialization
// Pull-up initialization:
// Bit3=Off Bit2=Off Bit1=Off Bit0=Off 
PUEB=(0<<PUEB3) | (0<<PUEB2) | (0<<PUEB1) | (0<<PUEB0);
// Function: Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Break Before Make Mode PORTB: On
PORTCR=(1<<BBMB);

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFFFF
// Input Capture on Falling Edge
// Input Capture Noise Canceler: Off
// OC0A output: Disconnected
// OC0B output: Disconnected
TCCR0A=(0<<COM0A1) | (0<<COM0A0) | (0<<COM0B1) | (0<<COM0B0) | (0<<WGM01) | (0<<WGM00);
TCCR0B=(0<<ICNC0) | (0<<ICES0) | (0<<WGM03) | (0<<WGM02) | (0<<CS02) | (0<<CS01) | (0<<CS00);
TCNT0=0x0000;
ICR0=0x0000;
OCR0A=0x0000;
OCR0B=0x0000;

// Timer/Counter 0 Interrupt(s) initialization
TIMSK0=(0<<ICIE0) | (0<<OCIE0B) | (0<<OCIE0A) | (0<<TOIE0);

// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Any change
// Interrupt on any change on pins PCINT0-3: On
EICRA=(0<<ISC01) | (1<<ISC00);
EIMSK=(1<<INT0);
EIFR=(1<<INTF0);
PCMSK=(1<<PCINT3) | (1<<PCINT2) | (1<<PCINT1) | (1<<PCINT0);
PCICR=(1<<PCIE0);
PCIFR=(1<<PCIF0);

// Analog Comparator initialization
// Analog Comparator: On
// The Analog Comparator's positive input is
// connected to the AIN0 pin
// The Analog Comparator's negative input is
// connected to the AIN1 pin
// Analog Comparator Input Capture by Timer/Counter 0: On
ACSR=(0<<ACD) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (1<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
// Digital input buffer on AIN0: On
// Digital input buffer on AIN1: On
DIDR0=(0<<ADC0D) | (0<<ADC1D);

// ADC initialization
// ADC Clock frequency: 625.000 kHz
// ADC Auto Trigger Source: Free Running
// Digital input buffers on ADC0: On, ADC1: On, ADC2: On, ADC3: On
DIDR0=(0<<ADC3D) | (0<<ADC2D) | (0<<ADC1D) | (0<<ADC0D);
ADCSRA=(1<<ADEN) | (0<<ADSC) | (1<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
ADCSRB=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);


// Globally enable interrupts
#asm("sei")

while (1)
      {
      // Place your code here

      }
}