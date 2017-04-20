//****************************************************************************
// EC450 Blink Example 0 -DriverLib version
//****************************************************************************
/* This example is identical in spirit to the software Driverlib blink example from TI.
 * The only differences are that:
 *   a) the count between toggles is a variable we can change in the debugger
 *   b) The LED used is connected to P2.4 (Port 2, bit 4) which connects to the
 *      bright green pin in the 3-color LED on the EDU-MKII booster pack
 */
/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>

#include <stdbool.h>

volatile int state = 0;

void PORT6_IRQHandler(){

    uint32_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P6);
    GPIO_clearInterruptFlag(GPIO_PORT_P6, status);

    if(state == 0){
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN4);
        state = 1;
    }
    else if(state == 1) {
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN4);
        state = 0;
    }

    MAP_GPIO_enableInterrupt(GPIO_PORT_P6, GPIO_PIN7);
}

int main(void)
{
    volatile unsigned int half_period=50000;
    volatile unsigned int countdown;

    /* Halting the Watchdog */
    MAP_WDT_A_holdTimer();

    /* Configuring the PIR sensor */
    MAP_Interrupt_disableSleepOnIsrExit();
    MAP_Interrupt_enableMaster();
    MAP_Interrupt_enableInterrupt(INT_PORT6);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P6, GPIO_PIN7);
    MAP_GPIO_setAsInputPin(GPIO_PORT_P6, GPIO_PIN7);

    /* Configuring P2.4 as output */
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN4);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN5);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN7);

    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN4);

    while (1)
    {

        /* Delay Loop */
        for (countdown=half_period;countdown>0;--countdown){
        }

     }
}


