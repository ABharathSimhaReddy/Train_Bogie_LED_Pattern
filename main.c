/*                   ASSIGNMENT - 1

  Program Name : LED Pattern Generator PIC PORTB
  Author       : Bharath Simha Reddy
  Date         : October 23, 2025

  Description:
  This program generates a sequence of LED patterns
  on PORTB of a PIC microcontroller. The sequence
  consists of four phases, each phase taking eight steps.

  Pattern Flow total 32 iterations:
  1. i = 0 to 7   : Set bits from LSB to MSB
  2. i = 8 to 15  : Shift bits left clearing one by one
  3. i = 16 to 23 : Set bits from MSB to LSB
  4. i = 24 to 31 : Shift bits right clearing one by one

  Why compared with 32:
  Each phase uses eight steps.
  Four phases multiplied by eight steps equals 32 steps.
  After 32 iterations the pattern completes and i resets to 0.

  Variable Description:
  i     : Controls the current stage of the LED pattern 0 to 31
  wait  : Delay counter for speed control

  Hardware:
  PORTB is configured as output using TRISB = 0x00
*/

#include <xc.h>                       // Include PIC microcontroller header file

unsigned int i = 0;                   // Variable to track LED pattern steps (0 to 31)
int delay = 50000;                    // Delay counter for timing LED transitions

void main(void)
{
    TRISB = 0x00;                     // Configure PORTB as output for LEDs

    while (1)                         // Infinite loop to run LED pattern continuously
    {
        if (delay-- == 0)             // Check if delay counter has reached zero
        {
            if (i < 8)                // Phase 1: Turn on LEDs from LSB to MSB
            {
                PORTB = (unsigned char)(PORTB | (1 << i));  // Set bit 'i' ON
            }
            else if (i < 16)          // Phase 2: Shift bits left (turn LEDs off one by one)
            {
                PORTB = (unsigned char)(PORTB << 1);        // Shift all bits left by 1
            }
            else if (i < 24)          // Phase 3: Turn on LEDs from MSB to LSB
            {
                PORTB = (unsigned char)(PORTB | (1 << (24 - i))); // Set bits ON from MSB side
            }
            else if (i < 32)          // Phase 4: Shift bits right (turn LEDs off one by one)
            {
                PORTB = (unsigned char)(PORTB >> 1);        // Shift all bits right by 1
            }
            else                      // Reset after 32 steps
            {
                i = 0;                // Restart pattern index
                PORTB = 0x00;         // Clear all LEDs
            }

            i++;                      // Move to next step in sequence
            delay = 50000;            // Reload delay counter
        }
    }
}
