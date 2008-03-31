/*
             MyUSB Library
     Copyright (C) Dean Camera, 2008.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com

 Released under the LGPL Licence, Version 3
*/

#ifndef _USB_SERIAL_H_
#define _USB_SERIAL_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/interrupt.h>

		#include "Descriptors.h"
		#include "RingBuff.h"

		#include <MyUSB/Version.h>                         // Library Version Information
		#include <MyUSB/Common/ButtLoadTag.h>              // PROGMEM tags readable by the ButtLoad project
		#include <MyUSB/Drivers/USB/USB.h>                 // USB Functionality
		#include <MyUSB/Drivers/AT90USBXXX/Serial.h>       // USART driver
		#include <MyUSB/Drivers/Board/LEDs.h>              // LEDs driver
		#include <MyUSB/Scheduler/Scheduler.h>             // Simple scheduler for task management

	/* Macros: */
		#define GET_LINE_CODING              0x21
		#define SET_LINE_CODING              0x20
		#define SET_CONTROL_LINE_STATE       0x22

	/* Event Handlers: */
		HANDLES_EVENT(USB_Connect);
		HANDLES_EVENT(USB_Disconnect);
		HANDLES_EVENT(USB_CreateEndpoints);
		HANDLES_EVENT(USB_UnhandledControlPacket);
		
	/* Type Defines: */
		typedef struct
		{
			uint32_t BaudRateBPS;
			uint8_t  CharFormat;
			uint8_t  ParityType;
			uint8_t  DataBits;
		} CDC_Line_Coding_t;
		
	/* Enums: */
		enum CDC_Line_Coding_Format_t
		{
			OneStopBit          = 0,
			OneAndAHalfStopBits = 1,
			TwoStopBits         = 2,
		};
		
		enum CDC_Line_Codeing_Parity_t
		{
			Parity_None         = 0,
			Parity_Odd          = 1,
			Parity_Even         = 2,
			Parity_Mark         = 3,
			Parity_Space        = 4,
		};

	/* Function Prototypes: */
		void ReconfigureUSART(void);

	/* Tasks: */
		TASK(CDC_Task);

#endif
