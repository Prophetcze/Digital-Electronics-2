/***********************************************************************
 * 
 * The I2C (TWI) bus scanner tests all addresses and detects chips and
 * modules that are connected to the SDA and SCL signals.
 * 
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2017 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
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
#include <twi.h>            // I2C/TWI library for AVR-GCC
#include <uart.h>           // Peter Fleury's UART library
#include <stdlib.h>         // C library. Needed for number conversions


/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Use Timer/Counter1, send one I2C (TWI) address every 33 ms,
 *           and test all combinations. Send information about scanning
 *           process to UART.
 * Returns:  none
 **********************************************************************/


/* Global variables --------------------------------------------------*/
   // Declaration of "air" variable with structure "Air_parameters_structure"
   struct Air_parameters_structure {
       uint8_t humid_int;
       uint8_t humid_dec;
       uint8_t temp_int;
       uint8_t temp_dec;
       uint8_t checksum;
   } air;

   // Declaration of "rtc" variable with structure "RTC_parameters_structure"
   struct RTC_parameters_structure {
       uint8_t sec;
       uint8_t min;
       uint8_t hour;
   } rtc;


int main(void)
{
    // Initialize I2C (TWI)
    twi_init();

    // Initialize USART to asynchronous, 8N1, 9600
    uart_init(UART_BAUD_SELECT(9600, F_CPU));

    // Configure 16-bit Timer/Counter1 to test one I2C address
    // Set prescaler to 33 ms and enable interrupt
    TIM1_overflow_1s();
    TIM1_overflow_interrupt_enable();

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Put strings to ringbuffer for transmitting via UART
    uart_puts("Scan I2C bus for devices:\r\n");

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
 * Purpose:  Test one I2C Slave address from the range 8 to 119.
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{
    static uint8_t addr = 8;  // I2C Slave address
    uint8_t ack;              // ACK response from Slave
    char string[3];           // String for converting numbers by itoa()

    // Read temperature and humidity, addr = 0x5c
    addr = 0x5c;
    ack = twi_start(addr, TWI_WRITE);
    if(ack == 0)
    {
        twi_write(0x00);
        twi_stop();
        twi_start(addr, TWI_READ);

        air.humid_int = twi_read_ack();
        air.humid_dec = twi_read_ack();
        air.temp_int = twi_read_ack();
        air.temp_dec = twi_read_nack();
        twi_stop();

        // Print Humidity
        itoa(air.temp_int, string, 10);
        uart_puts(string);
        uart_puts(".");
        itoa(air.temp_dec, string, 10);
        uart_puts(string);
        uart_puts("  °C\t");

        // Print Temperature
        itoa(air.humid_int, string, 10);
        uart_puts(string);
        uart_puts(".");
        itoa(air.humid_dec, string, 10);
        uart_puts(string);
        uart_puts("  %\t"); 
    }

    // Read RTC, addr = 0x68
    addr = 0x68;
    ack = twi_start(addr, TWI_WRITE);
    if(ack == 0)
    {
        twi_write(0x00);
        twi_stop();
        twi_start(addr, TWI_READ);

        rtc.sec = twi_read_ack();
        rtc.min = twi_read_ack();
        rtc.hour = twi_read_ack();
        twi_stop();

        // Print Hours
        itoa(rtc.hour, string, 16);
        uart_puts(string);
        uart_puts(":"); 

        // Print Minutes
        itoa(rtc.min, string, 16);
        uart_puts(string);
        uart_puts(":");

        // Print Seconds
        itoa(rtc.sec, string, 16);
        uart_puts(string);
        uart_puts("\r\n");
    }

/*   
    // I2C Scanner
    if(addr < 120)
    {
        // Start communication, transmit I2C Slave address, get result,
        // and Stop communication
        ack = twi_start(addr, TWI_WRITE);
        twi_stop();

        itoa(addr, string, 10);
        uart_puts(string);

        itoa(addr, string, 16);
        uart_puts("\tHex: ");
        uart_puts(string);

        if(ack == 0)
        {
            uart_puts("\t");
            uart_puts("OK");
        }
        
        addr++;
        uart_puts("\r\n");
    } 
*/
}
