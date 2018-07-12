#include "GPIO_Pin.h"

static bool Called = false;
bool GPIO_PinInit_Error = true;


bool GPIO_Pin_Initialize( void )
{
  if( Called )
    return GPIO_PinInit_Error;
  
  Called = true;
  
  return GPIO_PinInit_Error;
}

void Wireless_ResetPin_Set( int NewVal )
{
}
