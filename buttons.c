# include <stdint.h>
# include <stdbool.h>
# include "gptm.h"
# include "fsm.h"
# include "buttons.h"
# include "driverlib/sysctl.h"
# include "driverlib/gpio.h"
# include "driverlib/interrupt.h"
# include "inc/hw_memmap.h"
# include "uart.h"
void Btn_Init(void)
{
    
    //Enable clock for ports and check whether peripheral is ready
    SysCtlPeripheralEnable(BUTTON_PNS_GPIO_PERIPH);
    SysCtlPeripheralEnable(BUTTON_PEW_GPIO_PERIPH);
    while(!SysCtlPeripheralReady(BUTTON_PNS_GPIO_PERIPH));
    while(!SysCtlPeripheralReady(BUTTON_PEW_GPIO_PERIPH));

    
    //Set Pedestrian Traffic Light Buttons pins as input
    GPIOPinTypeGPIOInput(BUTTON_PNS_PORT_BASE,BUTTON_PNS);
    GPIOPinTypeGPIOInput(BUTTON_PEW_PORT_BASE,BUTTON_PEW);

    //Pull up resistor
    GPIOPadConfigSet(BUTTON_PNS_PORT_BASE, BUTTON_PNS, GPIO_STRENGTH_2MA , GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(BUTTON_PEW_PORT_BASE, BUTTON_PEW, GPIO_STRENGTH_2MA , GPIO_PIN_TYPE_STD_WPU);

    
    //GPIO interrupt configuration
    GPIOIntDisable(BUTTON_PNS_PORT_BASE, BUTTON_PNS);
    GPIOIntDisable(BUTTON_PEW_PORT_BASE, BUTTON_PEW);

    GPIOIntTypeSet(BUTTON_PNS_PORT_BASE, BUTTON_PNS, GPIO_FALLING_EDGE);
    GPIOIntTypeSet(BUTTON_PEW_PORT_BASE, BUTTON_PEW, GPIO_FALLING_EDGE);

    GPIOIntRegister(BUTTON_PNS_PORT_BASE, Btn_NS_ISR);
    GPIOIntRegister(BUTTON_PEW_PORT_BASE, Btn_EW_ISR);

    //Set highest priority
    //IntPrioritySet(BUTTON_PNS_PORT_INT, 0);

    GPIOIntEnable(BUTTON_PNS_PORT_BASE, BUTTON_PNS);
    GPIOIntEnable(BUTTON_PEW_PORT_BASE, BUTTON_PEW);
}

void Btn_NS_ISR(void)
{
    //Clear Interrupt
    GPIOIntClear(BUTTON_PNS_PORT_BASE, BUTTON_PNS);

    //Disable both buttons Interrupt
    GPIOIntDisable(BUTTON_PNS_PORT_BASE, BUTTON_PNS);
    GPIOIntDisable(BUTTON_PEW_PORT_BASE, BUTTON_PEW);

    //Disable CarTrafficLight timer
    GPTM_CarTrafficLight_Disable();


    //Set and enable the pedestrian timer
    GPTM_PedestrianTrafficLight_Disable();
    GPTM_PedestrianTrafficLight_SetPeriodInMS(2000); // 2 seconds
    GPTM_PedestrianTrafficLight_Enable();

    //Change The FSM state of pedestrian
    FSM_Ped_State=FSM_PED_GO_NS;

    //Change The System State and send it UART
    FSM_Sys_State=FSM_SYS_PED_NS;
    UART_PrintSystemState(FSM_Sys_State,FSM_Car_State);

    //Write All the Traffic Lights LIGHT
    GPIOPinWrite(LIGHT_CNS_PORT_BASE, LIGHT_CNS_ALL, FSM_PedestrianTrafficLight[FSM_Ped_State].CarOut[FSM_Car_State]);
    GPIOPinWrite(LIGHT_CEW_PORT_BASE, LIGHT_CEW_ALL, FSM_PedestrianTrafficLight[FSM_Ped_State].CarOut[FSM_Car_State]);

    GPIOPinWrite(LIGHT_PNS_PORT_BASE, LIGHT_PNS_ALL, FSM_PedestrianTrafficLight[FSM_Ped_State].PedOut);
    GPIOPinWrite(LIGHT_PEW_PORT_BASE, LIGHT_PEW_ALL, FSM_PedestrianTrafficLight[FSM_Ped_State].PedOut);
}
void Btn_EW_ISR(void)
{
    //Clear Interrupt
    GPIOIntClear(BUTTON_PEW_PORT_BASE, BUTTON_PEW);

    //Disable both buttons Interrupt
    GPIOIntDisable(BUTTON_PNS_PORT_BASE, BUTTON_PNS);
    GPIOIntDisable(BUTTON_PEW_PORT_BASE, BUTTON_PEW);

    //Disable CarTrafficLight timer
    GPTM_CarTrafficLight_Disable();



    //Set and enable the pedestrian timer
    GPTM_PedestrianTrafficLight_Disable();
    GPTM_PedestrianTrafficLight_SetPeriodInMS(2000); // 2 seconds
    GPTM_PedestrianTrafficLight_Enable();

    //Change The FSM state of pedestrian
    FSM_Ped_State=FSM_PED_GO_EW;

    //Change The System State and send it UART
     FSM_Sys_State=FSM_SYS_PED_EW;
     UART_PrintSystemState(FSM_Sys_State,FSM_Car_State);

    //Write All the Traffic Lights LIGHT
    GPIOPinWrite(LIGHT_CNS_PORT_BASE, LIGHT_CNS_ALL, FSM_PedestrianTrafficLight[FSM_Ped_State].CarOut[FSM_Car_State]);
    GPIOPinWrite(LIGHT_CEW_PORT_BASE, LIGHT_CEW_ALL, FSM_PedestrianTrafficLight[FSM_Ped_State].CarOut[FSM_Car_State]);

    GPIOPinWrite(LIGHT_PNS_PORT_BASE, LIGHT_PNS_ALL, FSM_PedestrianTrafficLight[FSM_Ped_State].PedOut);
    GPIOPinWrite(LIGHT_PEW_PORT_BASE, LIGHT_PEW_ALL, FSM_PedestrianTrafficLight[FSM_Ped_State].PedOut);

}
