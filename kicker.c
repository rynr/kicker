#include <avr/io.h>
#include <avr/interrupt.h>

#include "kicker.h"

#define I2C_SLAVE_ADDRESS 0x32
#define I2C_DATA_INTERRUPT 0x80
#define I2C_BUS_COLLISION 0x08
#define I2C_ADDRESS_STOP_MATCH 0x40

volatile uint8_t command;
volatile uint8_t tx_buf[2];
volatile uint8_t tx_buf_index = 0;

void ATMEL_Save_Energy()
{
  PRR |= (1 << PRSPI) | // Disable Serial Peripheral Interface
         (1 << PRADC);  // Disable ADC
}

void TWI_Slave_Initialise(unsigned char TWI_ownAddress)
{
  TWSA = TWI_ownAddress << 1; // Set own TWI slave address.
  TWSCRA = (0 << TWSHE) |     // Disable TWI SDA Hold Time
           (1 << TWDIE) |     // Enable TWI Data Interrupt
           (1 << TWASIE) |    // Enable TWI Address/Stop Interrupt
           (1 << TWEN) |      // Enable Two-Wire Interface
           (1 << TWSIE) |     // Enable TWI Stop Interrupt
           (0 << TWPME) |     // Disable TWI Promiscuous Mode
           (1 << TWSME);      // Enable TWI Smart Mode
}

ISR(TWI_SLAVE_vect)
{
  uint8_t status = TWSSRA & 0xC0;

  if (status & I2C_DATA_INTERRUPT) // Daten wurden vom Master empfangen oder werden angefordert
  {
    if (TWSSRA & (1 << TWDIR)) // Master fordert Daten vom Slave an
    {
      if (tx_buf_index >= sizeof(tx_buf))
      {
        tx_buf_index = 0;
      }

      TWSD = tx_buf[tx_buf_index];
      tx_buf_index++;

      TWSCRB = (uint8_t)((1 << TWCMD1) | (1 << TWCMD0));
    }
    else // Master sendet Daten zum Slave
    {
      TWSCRB |= (uint8_t)((1 << TWCMD1) | (1 << TWCMD0));
      command = TWSD;
    }
  }
  else if (status & I2C_ADDRESS_STOP_MATCH)
  {
    if (TWSSRA & I2C_BUS_COLLISION)
    {
      TWSCRB = (uint8_t)(1 << TWCMD1);
    }
    else
    {
      if (TWSSRA & (1 << TWAS))
      {
        // ACK
        TWSCRB = (uint8_t)((1 << TWCMD1) | (1 << TWCMD0));
      }
      else
      {
        // Stop Condition
        TWSCRB = (uint8_t)(1 << TWCMD1);
      }
    }
  }
}

int main(void)
{
  TWI_Slave_Initialise(I2C_SLAVE_ADDRESS);
  ATMEL_Save_Energy();
  return (0);
}
