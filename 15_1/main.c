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

/* Function to initialize Port F: Configure buttons and the LED */
void init(void) {
    SYSCTL_RCGCGPIO_R |= 0x20;               /* Turn on clock for Port F */
    GPIO_PORTF_LOCK_R = 0x4C4F434B;          /* Unlock Port F to allow changes */
    GPIO_PORTF_CR_R |= 0x11;                 /* Allow modifications to PF4 and PF0 */

    /* Set PF1 as output (for LED), and PF4, PF0 as input (for buttons) */
    GPIO_PORTF_DIR_R = 0x02;                 /* PF1 output for the LED, PF0, PF4 input for the buttons */
    GPIO_PORTF_DEN_R = 0x13;                 /* Enable digital functionality for PF1, PF4, and PF0 */
    GPIO_PORTF_PUR_R = 0x11;                 /* Enable pull-up resistors on PF4 and PF0 */

    /* Configure interrupt for PF4 (SW1) and PF0 (SW2) */
    GPIO_PORTF_IS_R &= ~0x11;                /* Set to detect edges */
    GPIO_PORTF_IBE_R &= ~0x11;               /* Interrupt triggered based on IEV */
    GPIO_PORTF_IEV_R &= ~0x11;               /* Set to trigger on the falling edge */
    GPIO_PORTF_ICR_R |= 0x11;                /* Clear any previous interrupts */
    GPIO_PORTF_IM_R |= 0x11;                 /* Enable interrupts for PF4 and PF0 */

    NVIC_EN0_R |= 0x40000000;                /* Enable interrupt for GPIO Port F in NVIC (interrupt 30) */
}





