#include "debug.h"
#include "pinDictionary.h"
#include "stm32wlxx.h"
#include <stdbool.h>

static uint32_t pin_loc = 0;
static uint32_t pin_msk = 0;
static uint32_t pin_shift = 0;
static uint32_t pin_port_index = 0;
static bool pinSet = false;


void initDebugPin(void)
{
  if(!pinSet)
	{
    pin_port_index = GPIO_GET_INDEX(LED_PORT);

    //find out which pin number is the debug pin
    pin_loc = 0;
    pin_loc = __builtin_ctz(LED_PIN);

    //most of GPIO registers have 2 bit wide fields, so prepare a mask variable
    pin_msk = 0x3 << ((pin_loc) * 2u);
    pin_shift = ((pin_loc) * 2u);
    
    pinSet = true;
  }

	//enable GPIO clock so we can modify the pin
	RCC->AHB2ENR |= (1u << pin_port_index);

  //clear the appropriate field in PUPDR register - no pull-ups or pull-downs
  LED_PORT->PUPDR &= ~(pin_msk);

  //set appropriate field in MODER register - output mode
  LED_PORT->MODER &= ~(pin_msk);
  LED_PORT->MODER |= (0x01 << pin_shift);

  //set the output type - output push-pull
  LED_PORT->OTYPER &= ~(1 << pin_loc);

  //clear the appropriate field in OSPEEDR register - low speed
  LED_PORT->OSPEEDR &= ~(pin_msk);



}

void deinitDebugPin(void)
{

  	//clear the appropriate field in PUPDR register - no pull-ups or pull-downs
		LED_PORT->PUPDR &= ~(pin_msk);

		//set the appropriate field in MODER register - analog
		LED_PORT->MODER |= pin_msk;

}

void DebugPinBlink(void)
{
  if(pinSet)
  {
    uint32_t odr = READ_REG(LED_PORT->ODR);
    WRITE_REG(LED_PORT->BSRR, ((odr & LED_PIN) << 16u) | (~odr & LED_PIN));
  }

}
