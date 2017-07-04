#include <avr/io.h>
#include <avr/interrupt.h>

#include "kicker.h"

#define SLAVE_ADDRESS 0x32

void ATMEL_Save_Energy() {
  PRR |= (1 << PRSPI)|                    // Disable Serial Peripheral Interface
         (1 << PRADC);                    // Disable ADC
}

void TWI_Slave_Initialise(unsigned char TWI_ownAddress) {
  TWSA   = TWI_ownAddress << 1;            // Set own TWI slave address.
  TWSCRA = (0 << TWSHE)|                   // Disable TWI SDA Hold Time
           (1 << TWDIE)|                   // Enable TWI Data Interrupt
           (1 << TWASIE)|                  // Enable TWI Address/Stop Interrupt
           (1 << TWEN)|                    // Enable Two-Wire Interface
           (1 << TWSIE)|                   // Enable TWI Stop Interrupt
           (0 << TWPME)|                   // Disable TWI Promiscuous Mode
           (1 << TWSME);                   // Enable TWI Smart Mode
}

ISR(TWI_SLAVE_vect)
{
  // int8_t status = TWSSRA & 0xC0;
}

int main(void) {
  ATMEL_Save_Energy();
  TWI_Slave_Initialise(SLAVE_ADDRESS);
  return(0);
}
