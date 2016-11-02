#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "driverlib/interrupt.h"
#include "driverlib/debug.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/rom.h"

void
InitConsole(void)
{
    //
    // Enable GPIO port A which is used for UART0 pins.
    // TODO: change this to whichever GPIO port you are using.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    //
    // Enable UART0 so that we can configure the clock.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Select the alternate (UART) function for these pins.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}


int main(void)
{

volatile uint8_t ui8Var;
ui8Var=16; //2=0x04; 3=0x08; 4= 0x10; 5=0x20
int status=0;
char c;
//char *receive;
//uint32_t ui32RecLen;
//ui8Adjust = 20;
SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4| GPIO_PIN_5| GPIO_PIN_6| GPIO_PIN_7);
//2345-> clockwise ; 5432->Anticlockwise
InitConsole();
IntMasterEnable();
while(1)
{
	a:
UARTprintf(" Stepper motor ");
UARTprintf("\n Enter 'C' for clockwise and 'A' for anti clockwise direction :");
while(1)
{
	c=UARTgetc();
	if(c=='C')
	{
		status=0;
		ui8Var=16;
		UARTCharPut(UART0_BASE,'C');
		UARTprintf("\n Press Enter to go to menu. ");
//UARTCharPut(UART0_BASE,'\n');
		while(1)
		{

			GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4,GPIO_PIN_4);
			GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5,0);
			GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6,0);
			GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7,0);
			SysCtlDelay(200000);
			SysCtlDelay(200000);
			GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5,0x20);
			GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4,0);
					GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6,0);
					GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7,0);
						SysCtlDelay(200000);
						SysCtlDelay(200000);
						GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6,0x40);
						GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5,0);
								GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4,0);
								GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7,0);
									SysCtlDelay(200000);
									SysCtlDelay(200000);
									GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7,0x80);
									GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5,0);
											GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6,0);
											GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4,0);
												SysCtlDelay(200000);
												SysCtlDelay(200000);
												if(UARTCharsAvail(UART0_BASE))
													goto a;

		}

	}

	if(c=='A')
	{
		UARTCharPut(UART0_BASE,'A');
	//	UARTCharPut(UART0_BASE,'\n');
		UARTprintf("\n Press Enter to go to menu. ");
		while(1)
		{
			GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7,GPIO_PIN_7);
			GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5,0);
			GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6,0);
			GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4,0);
			SysCtlDelay(200000);
			SysCtlDelay(200000);
			GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6,GPIO_PIN_6);
			GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4,0);
					GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5,0);
					GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7,0);
						SysCtlDelay(200000);
						SysCtlDelay(200000);
						GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5,GPIO_PIN_5);
						GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6,0);
								GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4,0);
								GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7,0);
									SysCtlDelay(200000);
									SysCtlDelay(200000);
									GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4,GPIO_PIN_4);
									GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5,0);
											GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6,0);
											GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7,0);
												SysCtlDelay(200000);
												SysCtlDelay(200000);
												if(UARTCharsAvail(UART0_BASE))
													goto a;
		}


	}


}//end of while(1)



}
}//End of main
