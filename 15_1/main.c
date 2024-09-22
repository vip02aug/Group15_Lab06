#include <stdint.h>
#include "tm4c123gh6pm.h"

volatile uint32_t dutyCycle = 50;  /* Starting duty cycle set to 50% */
volatile uint32_t count = 160;     /* Count value for generating 100 kHz using 16MHz clock */

void init(void);                   /* Declaration for the initialization function */
void Systick_Init(void);            /* Declaration for SysTick timer setup */
void GPIO_Handler(void);          /* Declaration for GPIO interrupt function */
void Systick_Handler(void);        /* Declaration for SysTick interrupt handler */

int main(void) {
    init();   /* Initialize GPIO for the buttons and LED */
    Systick_Init(); /* Set up SysTick timer for PWM generation */

    while (1) {
        /* Main loop does nothing, PWM and duty cycle are controlled by interrupts */
    }
}





