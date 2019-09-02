/*=============================================================================
 * Copyright (c) 2019, Eric Pernia <ericpernia@gmail.com>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2019/08/23
 *===========================================================================*/

/*=====[Inclusion of own header]=============================================*/

#include "userTasks.h"
 
/*=====[Inclusions of private function dependencies]=========================*/

#include "sapi.h"       // <= sAPI header
#include "ff.h"         // <= Biblioteca FAT FS
#include "fssdc.h"      // API de bajo nivel para unidad "SDC:" en FAT FS
#include "PWM.h"

/*=====[Definition macros of private constants]==============================*/
#define UART_PC        UART_USB
#define UART_BLUETOOTH UART_232
/*=====[Private function-like macros]========================================*/

/*=====[Definitions of private data types]===================================*/

/*=====[Definitions of external public global variables]=====================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

static char buf[100];

static FATFS fs;      // <-- FatFs work area needed for each volume
static FIL fp;        // <-- File object needed for each open file

/*=====[Prototypes (declarations) of private functions]======================*/

/*=====[Implementations of public functions]=================================*/

// Task implementation
void myTask( void* taskParmPtr )
{
   // ----- Task setup -----------------------------------
   uartWriteString( UART_USB, "Blinky with freeRTOS y sAPI.\r\n" );

   // Periodic task every 500 ms
   portTickType xPeriodicity =  500 / portTICK_RATE_MS;
   portTickType xLastWakeTime = xTaskGetTickCount();

   // ----- Task repeat for ever -------------------------
   while(TRUE) {
      gpioToggle( LED );
      uartWriteString( UART_USB, "Blink!\r\n" );

      // Send the task to the locked state during xPeriodicity
      // (periodical delay)
      vTaskDelayUntil( &xLastWakeTime, xPeriodicity );
   }
}

// Task implementation
void disk( void* taskParmPtr )
{
   // ----- Task setup -----------------------------------


   // Periodic task every 10 ms
   portTickType xPeriodicity =  10 / portTICK_RATE_MS;
   portTickType xLastWakeTime = xTaskGetTickCount();

   // ----- Task repeat for ever -------------------------
   while(TRUE) {
      disk_timerproc();   // Disk timer process

      // Send the task to the locked state during xPeriodicity
      // (periodical delay)
      vTaskDelayUntil( &xLastWakeTime, xPeriodicity );
   }
}

// Task implementation
void saveInSd( void* taskParmPtr )
{
   // ----- Task setup -----------------------------------
   // SPI configuration
   spiConfig( SPI0 );

   uartWriteString( UART_USB, "Inicializando\r\n" );
   FSSDC_InitSPI ();
   if( f_mount( &fs, "SDC:", 0 ) != FR_OK ){
      while (1) {
         gpioToggle( LEDR );
         uartWriteString( UART_USB, "SD no disponible\r\n" );
         delay(1000);
      }
   }

   // Periodic task every 1 s
   portTickType xPeriodicity =  500 / portTICK_RATE_MS;
   portTickType xLastWakeTime = xTaskGetTickCount();
   
   uint8_t i = 0;
   int n = 0;
   int nbytes = 0;
   int16_t pwmR;


   // ----- Task repeat for ever -------------------------

   while(TRUE)
   {
	  	 pwmR = pwmRead( PWM6 );
	     for(i = 0; i < 4 ;i++)
	     {
	  	 buf[i] = intToString( pwmR );
	     }
     //	 uartWriteString( UART_PC, "Valor PWM:% \r\n",buf );
         printf( "Valor PWM:%d \r\n",pwmR);
         uartWriteString( UART_BLUETOOTH, ("PWM:%d \r\n",buf) );

         /*
      if( f_open( &fp, "SDC:/log.txt", FA_WRITE | FA_OPEN_APPEND ) == FR_OK )
      {
         n = 24;
         f_write( &fp, buf, n, &nbytes );
         f_close(&fp);

           if( nbytes == n )
           {
            uartWriteString( UART_USB, "Escribio correctamente\r\n ");
            gpioWrite( LEDG, ON );
           }

           else
           {
            gpioWrite( LEDR, ON );
            uartWriteString( UART_USB, "Error al escribir\r\n ");
           }

      }

      else
        {
         uartWriteString( UART_USB, "Error al abrir el archivo\r\n" );
         gpioWrite( LEDR, ON );
        }
*/
      // Send the task to the locked state during xPeriodicity
      // (periodical delay)
      vTaskDelayUntil( &xLastWakeTime, xPeriodicity );
   }
}


/*=====[Implementations of interrupt functions]==============================*/

/*=====[Implementations of private functions]================================*/

