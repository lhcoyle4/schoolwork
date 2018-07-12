#include "Timer.h"
#include "driverlib/timer.h"

static bool TimerInitialized = false;
static volatile uint32_t Counter = 0;
static volatile uint32_t NUMBER_OF_INTS = 0;
static bool TimerDone = true;

void TimerInitialize( void )
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

	// The Timer0 peripheral must be enabled for use.
	TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PERIODIC);

	// Set the Timer0B load value to 1ms.
	TimerLoadSet(TIMER0_BASE, TIMER_B, SysCtlClockGet() / 1000);

	// Enable processor interrupts.
	IntMasterEnable();

}

void Timer0BIntHandler(void)
{
    // Clear the timer interrupt flag.
    TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);

    // Update the periodic interrupt counter.
    Counter++;

    // Once NUMBER_OF_INTS interrupts have been received, turn off the
    // TIMER0B interrupt.
    if(Counter >= NUMBER_OF_INTS)
    {
        // Disable the Timer0B interrupt.
        IntDisable(INT_TIMER0B);

        // Turn off Timer0B interrupt.
        TimerIntDisable(TIMER0_BASE, TIMER_TIMB_TIMEOUT);

        // Clear any pending interrupt flag.
        TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);

        TimerDone = true;
    }
}

void BlockingDelay( unsigned int Time )
{
	//if the Timer system isn't initialized then initialize it
	//if( !TimerInitialized )
	//{
		TimerInitialize();
	//	TimerInitialized = true;
	//}

	TimerDone = false;
	NUMBER_OF_INTS = Time;
	Counter = 0;

	//start timer

	// Configure the Timer0B interrupt for timer timeout.
	TimerIntEnable(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
	// Enable the Timer0B interrupt on the processor (NVIC).
	IntEnable(INT_TIMER0B);

	TimerEnable(TIMER0_BASE, TIMER_B);

	while( !TimerDone )
	{}

}

