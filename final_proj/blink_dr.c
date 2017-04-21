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

volatile int state = 0; // 0 = ON , 1 = OFF
volatile uint8_t receivedValue = 0;
volatile uint8_t checkBluetooth = 0; // 0 means we received 3, 1 means we received 4

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

const eUSCI_UART_Config uartConfig =
{
    EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
    78,                                     // BRDIV = 78
    2,                                       // UCxBRF = 2
    0,                                       // UCxBRS = 0
    EUSCI_A_UART_NO_PARITY,                  // No Parity
    EUSCI_A_UART_LSB_FIRST,                  // MSB First
    EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
    EUSCI_A_UART_MODE,                       // UART mode
    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
};

void EUSCIA2_IRQHandler(void)
{
    uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A2_BASE);

    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG){
        receivedValue = MAP_UART_receiveData(EUSCI_A2_BASE);
        if (receivedValue == 3){
            checkBluetooth = 0;
        }
        else if (receivedValue == 4){
            checkBluetooth = 1;
        }
    }
}

int main(void)
{
    volatile unsigned int half_period=50000;
    volatile unsigned int countdown;

    /* Halting the Watchdog */
    MAP_WDT_A_holdTimer();

    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_24);

    /* Selecting P3.2 and P3.3 in UART mode */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3,
    GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Configuring UART Module */
    MAP_UART_initModule(EUSCI_A2_BASE, &uartConfig);

    /* Enable UART module */
    MAP_UART_enableModule(EUSCI_A2_BASE);
    MAP_UART_enableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);

    // start with Receive Enabled
    MAP_Interrupt_enableInterrupt(INT_EUSCIA2);

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
        //for (countdown=half_period;countdown>0;--countdown){
        //}
    }
}


