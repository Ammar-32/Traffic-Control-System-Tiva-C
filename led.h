#include "driverlib/gpio.h"


//Define macros for Car Traffic Light Leds

//Define macros for Car North South traffic light led pins
#define LIGHT_CNS_RED    (GPIO_PIN_0)
#define LIGHT_CNS_YELLOW (GPIO_PIN_1)
#define LIGHT_CNS_GREEN  (GPIO_PIN_2)
#define LIGHT_CNS_ALL    (GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2)
#define LIGHT_CNS_PORT_BASE   (GPIO_PORTE_BASE)
#define LIGHT_CNS_GPIO_PERIPH (SYSCTL_PERIPH_GPIOE)


//Define macros for Car East West traffic light led pins
#define LIGHT_CEW_RED    (GPIO_PIN_3)
#define LIGHT_CEW_YELLOW (GPIO_PIN_4)
#define LIGHT_CEW_GREEN  (GPIO_PIN_5)
#define LIGHT_CEW_ALL    (GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5)
#define LIGHT_CEW_PORT_BASE   (GPIO_PORTE_BASE)
#define LIGHT_CEW_GPIO_PERIPH (SYSCTL_PERIPH_GPIOE)


//Define the car traffic light leds output for each state
//note: all the 6 leds must be assigned to different bits
# define LIGHT_CAR_GO_NS      (LIGHT_CNS_GREEN|LIGHT_CEW_RED)
# define LIGHT_CAR_WAIT_NS    (LIGHT_CNS_YELLOW|LIGHT_CEW_RED)
# define LIGHT_CAR_STOP_NS    (LIGHT_CNS_RED|LIGHT_CEW_RED)
# define LIGHT_CAR_GO_EW      (LIGHT_CNS_RED|LIGHT_CEW_GREEN)
# define LIGHT_CAR_WAIT_EW    (LIGHT_CNS_RED|LIGHT_CEW_YELLOW)
# define LIGHT_CAR_STOP_EW    (LIGHT_CNS_RED|LIGHT_CEW_RED)


//Define macros for Pedestrian Traffic Light Leds

//Define macros for Pedestrian North South traffic light led pins
#define LIGHT_PNS_RED    (GPIO_PIN_0)
#define LIGHT_PNS_GREEN (GPIO_PIN_1)
#define LIGHT_PNS_ALL    (GPIO_PIN_0|GPIO_PIN_1)
#define LIGHT_PNS_PORT_BASE   (GPIO_PORTD_BASE)
#define LIGHT_PNS_GPIO_PERIPH (SYSCTL_PERIPH_GPIOD)


//Define macros for Pedestrian East West traffic light led pins
#define LIGHT_PEW_RED    (GPIO_PIN_2)
#define LIGHT_PEW_GREEN  (GPIO_PIN_3)
#define LIGHT_PEW_ALL    (GPIO_PIN_2|GPIO_PIN_3)
#define LIGHT_PEW_PORT_BASE   (GPIO_PORTD_BASE)
#define LIGHT_PEW_GPIO_PERIPH (SYSCTL_PERIPH_GPIOD)


//Define the car traffic light leds output for each state
//note: all the 4 leds must be assigned to different bits
# define LIGHT_PED_GO_NS      (LIGHT_PNS_GREEN|LIGHT_PEW_RED)
# define LIGHT_PED_STOP_NS    (LIGHT_PNS_RED|LIGHT_PEW_RED)
# define LIGHT_PED_GO_EW      (LIGHT_PNS_RED|LIGHT_PEW_GREEN)
# define LIGHT_PED_STOP_EW    (LIGHT_PNS_RED|LIGHT_PEW_RED)
