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

// Sets up the state machine
// We have 00 = 10-5 under, 01 = 5-0 under, 10 = 0-5 over, 11 = 5-10 over
volatile int MSB = 0;
volatile int LSB = 0;

// PIR IRQ used to trigger the traffic light
void PORT6_IRQHandler(){
    volatile unsigned int half_period=10000000;
    volatile unsigned int countdown;
    uint32_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P6);
    GPIO_clearInterruptFlag(GPIO_PORT_P6, status);

    // Replace this logic with triggering the GREEN light for a bit and then set back to default RED
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN4);
    for (countdown=half_period;countdown>0;--countdown){
    }
    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN4);

    MAP_GPIO_enableInterrupt(GPIO_PORT_P6, GPIO_PIN7);
}

// Proof of concept of changing each light based on speed (1 for fast 0 for slow)
void PORT5_IRQHandler(){
    volatile unsigned int half_period=2500000;
    volatile unsigned int countdown;
    uint32_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);
    GPIO_clearInterruptFlag(GPIO_PORT_P5, status);

    if(LSB == 1) {
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN4);
        for (countdown=half_period;countdown>0;--countdown){
        }
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN4);
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN5);
        for (countdown=half_period;countdown>0;--countdown){
        }
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN5);
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN7);
        for (countdown=half_period;countdown>0;--countdown){
        }
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN7);
    }
    else if(LSB == 0){
        half_period *= 2;

        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN4);
        for (countdown=half_period;countdown>0;--countdown){
        }
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN4);
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN5);
        for (countdown=half_period;countdown>0;--countdown){
        }
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN5);
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN7);
        for (countdown=half_period;countdown>0;--countdown){
        }
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN7);
    }
}

int main(void)
{
    volatile unsigned int half_period=50000;
    volatile unsigned int countdown;

    /* Halting the Watchdog */
    MAP_WDT_A_holdTimer();

    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_24);

    /* Configuring the PIR sensor */
    MAP_Interrupt_disableSleepOnIsrExit();
    MAP_Interrupt_enableMaster();

    MAP_Interrupt_enableInterrupt(INT_PORT6);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P6, GPIO_PIN7);
    MAP_GPIO_setAsInputPin(GPIO_PORT_P6, GPIO_PIN7);

    /* Configuring the GPIO to take interrupts from the bluetooth HIGH signals
     * Triggered distance sensor --> speed read from bluetooth --> appropriate signal
     * to board to adjust speed properly
     */
    // MIMICKING THRESHOLD IDEA OF THE BLUETOOTH BOARD
    double speed = 2;
    if(speed < 20) {
        LSB = 0;
    }
    else if(speed >= 20) {
        LSB = 1;
    }

    MAP_Interrupt_enableInterrupt(INT_PORT5);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN1);
    MAP_GPIO_setAsInputPin(GPIO_PORT_P5, GPIO_PIN1);

    // Configuring street light GPIOs
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN4);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN5);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN7);

    // Default the street lights to OFF
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN4);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN5);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN7);

    while (1)
    {
        /* Delay Loop */
        //for (countdown=half_period;countdown>0;--countdown){
        //}
    }
}
