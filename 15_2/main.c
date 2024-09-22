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

/* To initialize GPIO: Set up Port F for the switch (PF4) and LED (PF1) */
void init(void) {
    SYSCTL_RCGCGPIO_R |= 0x020;    /* Enable the clock for Port F */
    GPIO_PORTF_LOCK_R = 0x4C4F434B; /* Unlock Port F for changes */
    GPIO_PORTF_CR_R = 0x10;        /* Allow changes to PF4 (Switch) */
    GPIO_PORTF_DIR_R = 0x02;       /* Set PF1 as output for the LED */
    GPIO_PORTF_DEN_R = 0x12;       /* Enable digital functionality for PF1 and PF4 */
    GPIO_PORTF_PUR_R |= 0x01;      /* Enable pull-up resistor for the switch */

    /* Set up interrupt for PF4 */
    GPIO_PORTF_IS_R = 0x00;        /* Configure for edge sensitivity */
    GPIO_PORTF_IBE_R = 0x00;       /* Interrupt triggered by the condition set by IEV */
    GPIO_PORTF_IEV_R = 0x00;       /* Falling edge trigger (button press) */
    GPIO_PORTF_ICR_R = 0x10;       /* Clear any previous interrupt */
    GPIO_PORTF_IM_R = 0x10;        /* Unmask the interrupt for PF4 */

    NVIC_EN0_R = 0x40000000;       /* Enable the interrupt for Port F in NVIC */
}

/* To set up the SysTick timer */
void Systick_Init(void) {
    NVIC_ST_RELOAD_R = count - 1;  /* Load the reload value for SysTick timer */
    NVIC_ST_CTRL_R = 0x07;         /* Enable SysTick with system clock and interrupt */
}
