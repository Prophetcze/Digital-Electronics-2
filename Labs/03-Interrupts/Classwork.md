1. The timer modules can be configured with several special purpose registers. According to the [ATmega328P datasheet](https://www.microchip.com/wwwproducts/en/ATmega328p) (eg in the **8-bit Timer/Counter0 with PWM > Register Description** section), which I/O registers and which bits configure the timer operations?

   | **Module** | **Operation** | **I/O register(s)** | **Bit(s)** |
   | :-: | :-- | :-: | :-- |
   | Timer/Counter0 | Prescaler<br><br>8-bit data value<br>Overflow interrupt enable | TCCR0B<br><br>TCNT0<br>TIMSK0 | CS02, CS01, CS00<br>(000: stopped, 001: 1, 010: 8, 011: 64, 100: 256, 101: 1024)<br>TCNT0[7:0]<br>TOIE1 (1: enable, 0: disable)  |
   | Timer/Counter1 | Prescaler<br><br>16-bit data value<br>Overflow interrupt enable | TCCR1B<br><br>TCNT1H, TCNT1L<br>TIMSK1 | CS12, CS11, CS10<br>(000: stopped, 001: 1, 010: 8, 011: 64, 100: 256, 101: 1024)<br>TCNT1[15:0]<br>TOIE1 (1: enable, 0: disable) |
   | Timer/Counter2 | Prescaler<br><br>8-bit data value<br>Overflow interrupt enable | TCCR2B<br><br>TCNT2<br>TIMSK2 | CS22, CS21, CS20<br>(000: stopped, 001: 1, 010: 8, 011: 32, 100: 64, 101: 128, 110: 256, 111: 1024)<br>TCNT2[7:0]<br>TOIE2 (1: enable, 0: disable)   |

See the [ATmega328P datasheet](https://www.microchip.com/wwwproducts/en/ATmega328p) (section **Interrupts > Interrupt Vectors in ATmega328 and ATmega328P**) for sources of interruptions that can occur on ATmega328P. Complete the selected interrupt sources in the following table. The names of the interrupt vectors in C can be found in [C library manual](https://www.nongnu.org/avr-libc/user-manual/group__avr__interrupts.html).

   | **Program address** | **Source** | **Vector name** | **Description** |
   | :-: | :-- | :-- | :-- |
   | 0x0000 | RESET | -- | Reset of the system |
   | 0x0002 | INT0  | `INT0_vect` | External interrupt request number 0 |
   |  | INT1 | `INT1_vect` | External interrupt request number 1 |
   |  | PCINT0 | `PCINT0_vect` | Pin change nterrupt request 0 |
   |  | PCINT1 | `PCINT1_vect` | Pin change nterrupt request 1 |
   |  | PCINT2 | `PCINT2_vect` | Pin change nterrupt request 2 |
   |  | WDT | `WDT_vect` | Watchdog timeout interrupt |
   |  | TIMER2_OVF | `TIMER2_OVF_vect` | Overflow of Timer/Counter2 value |
   | 0x0018 | TIMER1_COMPB | `TIMER1_COMPB_vect` | Compare match between Timer/Counter1 value and channel B compare value |
   | 0x001A | TIMER1_OVF | `TIMER1_OVF_vect` | Overflow of Timer/Counter1 value |
   |  | TIMER0_OVF | `TIMER0_OVF_vect` | Overflow of Timer/Counter0 value |
   |  | USART_RX | `USART_RX_vect` | USART, Rx complete |
   |  | ADC | `ADC_vect` | ADC Conversion complete |
   |  | TWI | `TWI_vect` | 2-wire Serial interface |