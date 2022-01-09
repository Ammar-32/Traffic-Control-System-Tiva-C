# include "PedestrianTrafficLight.h"
#include "fsm.h"
#include "gptm.h"
# include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "tm4c123gh6pm.h"
#include <stdbool.h>
#include "driverlib/timer.h"
# include "driverlib/interrupt.h"
#include "led.h"
# include "buttons.h"
# include "uart.h"

//Pedestrian Traffic Light Initialization
void PedestrianTrafficLight_Init(void)
{


    
    //Enable clock for ports and check whether peripheral is ready
    SysCtlPeripheralEnable(LIGHT_PNS_GPIO_PERIPH);
    SysCtlPeripheralEnable(LIGHT_PEW_GPIO_PERIPH);
    while(!SysCtlPeripheralReady(LIGHT_PNS_GPIO_PERIPH));
    while(!SysCtlPeripheralReady(LIGHT_PEW_GPIO_PERIPH));

    
    //Set Pedestrian Traffic Light LIGHT pins as output
    GPIOPinTypeGPIOOutput(LIGHT_PNS_PORT_BASE,LIGHT_PNS_ALL);
    GPIOPinTypeGPIOOutput(LIGHT_PEW_PORT_BASE,LIGHT_PEW_ALL);

    
    //Initialize the Pedestrian Traffic Light Timer
    GPTM_PedestrianTrafficLight_Init();
    GPTM_PedestrianTrafficLight_IntRegister(PedestrianTrafficLight_ISR1);
    GPTM_PedestrianTrafficLight_IntEnable();

    
    //Write the PedestrianTrafficLight to initial condition
    GPIOPinWrite(LIGHT_PNS_PORT_BASE, LIGHT_PNS_ALL, LIGHT_PNS_RED);
    GPIOPinWrite(LIGHT_PEW_PORT_BASE, LIGHT_PEW_ALL, LIGHT_PEW_RED);

    
    //Initialize Buttons
    Btn_Init();

}


//Car Traffic Light Interrupt Service Routine when gptm PedestrianTrafficLight timer Time out first time
void PedestrianTrafficLight_ISR1(void)
{
    //Disable the timer and Clear Interrupt
    GPTM_PedestrianTrafficLight_Disable();
    GPTM_PedestrianTrafficLight_IntClear();
    GPTM_PedestrianTrafficLight_SetPeriodInMS(1000); // 1 seconds

    //Fsm state change
    FSM_Ped_State=FSM_PedestrianTrafficLight[FSM_Ped_State].Next;

    //Change The System State and send it UART
    if(FSM_Car_State==FSM_CAR_GO_NS|FSM_CAR_WAIT_NS|FSM_CAR_STOP_NS)
    {
        FSM_Sys_State=FSM_SYS_CAR_NS;
    }
    else
    {
    	FSM_Sys_State=FSM_SYS_CAR_EW;
    }
    UART_PrintSystemState(FSM_Sys_State,FSM_Car_State);

    //Write All traffic Light LIGHTs
    GPIOPinWrite(LIGHT_CNS_PORT_BASE, LIGHT_CNS_ALL,FSM_PedestrianTrafficLight[FSM_Ped_State].CarOut[FSM_Car_State]);
    GPIOPinWrite(LIGHT_CEW_PORT_BASE, LIGHT_CEW_ALL,FSM_PedestrianTrafficLight[FSM_Ped_State].CarOut[FSM_Car_State]);

    GPIOPinWrite(LIGHT_PNS_PORT_BASE, LIGHT_PNS_ALL, FSM_PedestrianTrafficLight[FSM_Ped_State].PedOut);
    GPIOPinWrite(LIGHT_PEW_PORT_BASE, LIGHT_PEW_ALL, FSM_PedestrianTrafficLight[FSM_Ped_State].PedOut);

    //Set and enable the CarTrafficLight timer
    GPTM_CarTrafficLight_Enable();

    //Timer IntRegister to ISR2
    GPTM_PedestrianTrafficLight_IntRegister(PedestrianTrafficLight_ISR2);

    //Enable the PedestrianTrafficLight Timer
    GPTM_PedestrianTrafficLight_Enable();

    //Clear the btn interrupt requests due to switch bouncing
    // or user press many time when the pedestrian light is green
    if(FSM_Ped_State == FSM_PED_STOP_NS)
    {
    	GPIOIntClear(BUTTON_PNS_PORT_BASE, BUTTON_PNS);
    }
    else
    {
      	GPIOIntClear(BUTTON_PEW_PORT_BASE, BUTTON_PEW);
    }


}
//Car Traffic Light Interrupt Service Routine when gptm PedestrianTrafficLight timer Time out for second time
void PedestrianTrafficLight_ISR2(void)
{
    //Disable the timer and Clear Interrupt
    GPTM_PedestrianTrafficLight_Disable();
    GPTM_PedestrianTrafficLight_IntClear();

    //Timer IntRegister to ISR1
    GPTM_PedestrianTrafficLight_IntRegister(PedestrianTrafficLight_ISR1);


    //Enable buttons Interrupt
    GPIOIntEnable(BUTTON_PNS_PORT_BASE, BUTTON_PNS);
    GPIOIntEnable(BUTTON_PEW_PORT_BASE, BUTTON_PEW);
}
