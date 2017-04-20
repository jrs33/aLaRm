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

int main(void)
{
    volatile unsigned int half_period=50000;
    volatile unsigned int countdown;

    /* Halting the Watchdog */
    MAP_WDT_A_holdTimer();

    /* Configuring P2.4 as output */
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN4);

    while (1)
    {
        MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN4);

        /* Delay Loop */
        for (countdown=half_period;countdown>0;--countdown){
        }

     }
}


