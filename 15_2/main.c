#include <stdint.h>
#include "tm4c123gh6pm.h"

volatile uint32_t dutyCycle = 50;  /* Initial duty cycle is set to 50% */
volatile uint32_t count = 160;     /* Count value calculated using the 16MHz clock */
volatile uint32_t pressTime = 0;   /* Stores how long the button has been held down */
volatile uint8_t bp = 0;           /* Flag to detect if the button has been pressed */

void init(void);
void Systick_Init(void);
void GPIO_Handler(void);
void Systick_Handler(void);

int main(void) {
    init();   /* Set up GPIO for the switches and LED */
    Systick_Init(); /* Set up SysTick timer */

    while (1) {
        /* Main loop does nothing, interrupts handle the logic */
    }
}
