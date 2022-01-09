#include <stdbool.h>
#include <stdint.h>


// GPTM Car Traffic Light prototypes
void GPTM_CarTrafficLight_Init(void);
void GPTM_CarTrafficLight_SetPeriodInMS(uint32_t tms);
void GPTM_CarTrafficLight_Disable(void);
void GPTM_CarTrafficLight_Enable(void);
void GPTM_CarTrafficLight_IntEnable(void);
void GPTM_CarTrafficLight_IntDisable(void);
void GPTM_CarTrafficLight_IntClear(void);
void GPTM_CarTrafficLight_IntRegister(void(*pfnHandeler)(void));


// GPTM Pedestrian Traffic Light prototypes
void GPTM_PedestrianTrafficLight_Init(void);
void GPTM_PedestrianTrafficLight_SetPeriodInMS(uint32_t tms);
void GPTM_PedestrianTrafficLight_Disable(void);
void GPTM_PedestrianTrafficLight_Enable(void);
void GPTM_PedestrianTrafficLight_IntEnable(void);
void GPTM_PedestrianTrafficLight_IntDisable(void);
void GPTM_PedestrianTrafficLight_IntClear(void);
void GPTM_PedestrianTrafficLight_IntRegister(void(*pfnHandeler)(void));
