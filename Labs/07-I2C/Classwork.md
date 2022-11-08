In the lab, we are using I2C/TWI library developed by Tomas Fryza according to Microchip Atmel ATmega16 and ATmega328P manuals. Use the [`twi.h`](../library/include/twi.h) header file and add input parameters and description of the following functions.

   | **Function name** | **Function parameters** | **Description** | **Example** |
   | :-- | :-- | :-- | :-- |
   | `twi_init` | None | Initialize TWI unit, enable internal pull-up resistors, and set SCL frequency | `twi_init();` |
   | `twi_start` |  | <br>&nbsp; | `twi_start(addr, TWI_READ);` |
   | `twi_write` |  | <br>&nbsp; |  |
   | `twi_read_ack` | <br>&nbsp; |  |  |
   | `twi_read_nack` | <br>&nbsp; |  |  |
   | `twi_stop` |  |  | `twi_stop();` |
