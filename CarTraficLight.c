#include "CarTrafficLight.h"
#include "fsm.h"
#include "gptm.h"
#include "uart.h"
# include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "tm4c123gh6pm.h"
#include <stdbool.h>
#include "driverlib/timer.h"
# include "driverlib/interrupt.h"
#include "led.h"

//Car Traffic Light Initialization
void CarTrafficLight_Init(void)
{
    
    //Enable clock for ports and check whether peripheral is ready
    SysCtlPeripheralEnable(LIGHT_CNS_GPIO_PERIPH);
    SysCtlPeripheralEnable(LIGHT_CEW_GPIO_PERIPH);
    while(!SysCtlPeripheralReady(LIGHT_CNS_GPIO_PERIPH));
    while(!SysCtlPeripheralReady(LIGHT_CEW_GPIO_PERIPH));

 
    //Set Car Traffic Light LIGHT pins as output
    GPIOPinTypeGPIOOutput(LIGHT_CNS_PORT_BASE,LIGHT_CNS_ALL);
    GPIOPinTypeGPIOOutput(LIGHT_CEW_PORT_BASE,LIGHT_CEW_ALL);

    
    //Initialize the Car Traffic Light Timer
    GPTM_CarTrafficLight_Init();
    GPTM_CarTrafficLight_IntRegister(CarTrafficLight_ISR);
    GPTM_CarTrafficLight_IntEnable();

    
    //Initialize the first CarTrafficLight state
    GPIOPinWrite(LIGHT_CNS_PORT_BASE, LIGHT_CNS_ALL,FSM_CarTrafficLight[FSM_Car_State].Out );
    GPIOPinWrite(LIGHT_CEW_PORT_BASE, LIGHT_CEW_ALL,FSM_CarTrafficLight[FSM_Car_State].Out);
    GPTM_CarTrafficLight_SetPeriodInMS(FSM_CarTrafficLight[FSM_Car_State].Time);
    GPTM_CarTrafficLight_Enable();

    
    //Initialize the system state and send it with UART
    FSM_Sys_State=FSM_SYS_CAR_NS;
    UART_PrintSystemState(FSM_Sys_State,FSM_Car_State);
}


//Car Traffic Light Interrupt Service Routine
void CarTrafficLight_ISR(void)
{
    //Disable the timer
    GPTM_CarTrafficLight_Disable();
    GPTM_CarTrafficLight_IntClear();

    FSM_Car_State=FSM_CarTrafficLight[FSM_Car_State].Next;
    GPTM_CarTrafficLight_SetPeriodInMS(FSM_CarTrafficLight[FSM_Car_State].Time);

    FSM_Sys_State=FSM_CarTrafficLight[FSM_Car_State].SysState;
    UART_PrintSystemState(FSM_Sys_State,FSM_Car_State);

    GPIOPinWrite(LIGHT_CNS_PORT_BASE, LIGHT_CNS_ALL,FSM_CarTrafficLight[FSM_Car_State].Out );
    GPIOPinWrite(LIGHT_CEW_PORT_BASE, LIGHT_CEW_ALL,FSM_CarTrafficLight[FSM_Car_State].Out);

    GPTM_CarTrafficLight_Enable();

}

