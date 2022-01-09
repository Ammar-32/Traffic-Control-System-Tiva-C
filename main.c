#include "CarTrafficLight.h"
#include "PedestrianTrafficLight.h"
#include "uart.h"
#include <stdint.h>
#include "driverlib/sysctl.h"


int main(void)
{
    //UART Initialization
    UART_Init();

    
    //Initialize the Car Traffic Light
    CarTrafficLight_Init();

    //Initialize the Pedestrian Traffic Light
    PedestrianTrafficLight_Init();



    while(1)
    {
        
       //Enter Sleep mode until an interrupt occurs
       SysCtlSleep();

    }
}

