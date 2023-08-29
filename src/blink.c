// Default clock source is internal 8MHz RC oscillator
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

int main()
{
  DDRB |= (1 << PB0);

  while (1)
  {
    PORTB |= (1 << PB0);
    _delay_ms(1000);
    PORTB &= ~(1 << PB0);
    _delay_ms(1000);
  }
  return 0;
}