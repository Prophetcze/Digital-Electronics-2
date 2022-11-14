/***********************************************************************
 * 
 * Implementation of LFSR-based (Linear Feedback Shift Register) 
 * pseudo-random generator in AVR assembly.
 * 
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2017 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 * NOTE:
 *   To see assembly listing, run the following command in Terminal
 *   after the compilation.
 * 
 *   Windows:
 *   avr-objdump -S -d -m avr .pio/build/uno/firmware.elf > firmware.lst
 * 
 *   Linux:
 *   ~/.platformio/packages/toolchain-atmelavr/bin/avr-objdump -S -d -m avr .pio/build/uno/firmware.elf > firmware.lst
 * 
 * SEE:
 *   https://five-embeddev.com/baremetal/platformio/
 *
 **********************************************************************/


/* Defines -----------------------------------------------------------*/
#ifndef F_CPU
# define F_CPU 16000000  // CPU frequency in Hz required for UART_BAUD_SELECT
#endif


/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <uart.h>           // Peter Fleury's UART library
#include <stdlib.h>         // C library. Needed for number conversions


/* Function prototypes -----------------------------------------------*/
// Function(s) written in Assembly and/or C language
uint8_t multiply_accumulate_asm(uint8_t result, uint8_t a, uint8_t b);
uint8_t lfsr4_fibonacci_asm(uint8_t value);


/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Use Timer/Counter1 and generate a new pseudo-random value 
 *           using 4- and/or 8-bit LFSR structure every 262 ms. Send 
 *           information about LFSR process to UART.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    // Initialize USART to asynchronous, 8N1, 9600
    uart_init(UART_BAUD_SELECT(9600, F_CPU));

    // Configure 16-bit Timer/Counter1 to generate one LFSR state
    // Set prescaler to 262 ms and enable interrupt
    TIM1_overflow_262ms();
    TIM1_overflow_interrupt_enable();

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Put strings to ringbuffer for transmitting via UART
    uart_puts("LFSR-based pseudo-random generator:\r\n");

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}


/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
 * Function: Timer/Counter1 overflow interrupt
 * Purpose:  Generate one pseudo-random value using 4- and/or 8-bit
             LFSR structure.
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{
    static uint8_t value = 0;  // LFSR value
    static uint8_t no_of_values = 0;
    char string[8];            // String for converting numbers by itoa()

    // Multiply-and-accumulate Assembly example
    uint8_t a = 2;
    uint8_t b = 3;
    value = multiply_accumulate_asm(value, a, b);
    itoa(value, string, 10);
    uart_puts(string);
    uart_puts("\r\n");


    // LFSR generator
    // Transmit LFSR value via UART in decimal

    // Generate one LFSR value and increment number of generated LFSR values

    // If LFSR value is equal to 0 then print length info and start again

}
