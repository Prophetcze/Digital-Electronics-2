/***********************************************************************
 * 
 * Blink a LED in Arduino-style and use function from the delay library.
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2022 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/


/* Defines -----------------------------------------------------------*/
#define LED_GREEN PB5   // PB5 is AVR pin where green on-board LED 
                        // is connected
#define DOT_DELAY   200 // Delay in milliseconds for dot
#define DASH_DELAY  600 // Delay in milliseconds for dash
#define SPACE_DELAY 200 // Delay in milliseconds for space between symbols
#define LET_DELAY   600 // Delay in milliseconds for space between letters
#define WORDS_DELAY 1400// Delay in milliseconds for space between words

#ifndef F_CPU
# define F_CPU 16000000 // CPU frequency in Hz required for delay funcs
#endif

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>     // AVR device-specific IO definitions
#include <util/delay.h> // Functions for busy-wait delay loops


// -----
// This part is needed to use Arduino functions but also physical pin
// names. We are using Arduino-style just to simplify the first lab.
#include "Arduino.h"
#define PB5 13          // In Arduino world, PB5 is called "13"
// -----


/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Toggle one LED and use delay library.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    uint8_t led_value = LOW;  // Local variable to keep LED status

    // Set pin where on-board LED is connected as output
    pinMode(LED_GREEN, OUTPUT);

    // Infinite loop
    while (1)
    {
        led_value = LOW;
        digitalWrite(LED_GREEN, led_value);
        _delay_ms(LET_DELAY);

        if (led_value == LOW)
        {   
            led_value = HIGH;
            digitalWrite(LED_GREEN, led_value);
            _delay_ms(DOT_DELAY);

            if (led_value == HIGH)
            {   
                led_value = LOW;
                digitalWrite(LED_GREEN, led_value);
                _delay_ms(SPACE_DELAY);

                if (led_value == LOW)
                {   
                    led_value = HIGH;
                    digitalWrite(LED_GREEN, led_value);
                    _delay_ms(DASH_DELAY);

                    if (led_value == HIGH)
                    {   
                        led_value = LOW;
                        digitalWrite(LED_GREEN, led_value);
                        _delay_ms(SPACE_DELAY);
                    }
                }
            }
        }

        else
            led_value = LOW;

    }

    // Will never reach this
    return 0;
}
