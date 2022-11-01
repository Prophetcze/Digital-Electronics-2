1. Use online manual of UART library and add the input parameters and description of the following functions.

   | **Function name** | **Function parameter(s)** | **Description** | **Example** |
   | :-- | :-- | :-- | :-- |
   | `uart_init` | `UART_BAUD_SELECT(9600, F_CPU)` | Initialize UART to 8N1 and set baudrate to 9600&nbsp;Bd | `uart_init(UART_BAUD_SELECT(9600, F_CPU));` |
   | `uart_getc` | -- | Returns data from UART comunication |
   | `uart_putc` | `data` | Put byte to ringbuffer for Tx |
   | `uart_puts` | `s` | String is buffered bz the UART library |