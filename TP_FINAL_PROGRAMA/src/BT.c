/*=============================================================================
 * Author: Juan Pablo Menditto <jpmenditto@gmail.com>
 * Date: 2019/07/20
 * Version: 1.0
 *===========================================================================*/

/*==================[inlcusiones]============================================*/

// Includes de FreeRTOS
#include "BT.h"   //Motor del OS

#include "task.h"		//Api de control de tareas y temporización
#include "semphr.h"		//Api de sincronización (sem y mutex)

// sAPI header
#include "sapi.h"
#include <string.h>


/*==================[definiciones y macros]==================================*/

#define UART_PC        UART_USB
#define UART_BLUETOOTH UART_232


/*==================[definiciones de datos internos]=========================*/
SemaphoreHandle_t Evento_pulsado, Mutex_t_pulsado, Mutex_UART; //Para el uso de semaforos
portTickType TiempoPulsado;  //Para la periodicidad
extern uint8_t control; //variable que indica la instruccion a seguir en el switch
/*==================[definiciones de datos externos]=========================*/

DEBUG_PRINT_ENABLE;  //Para configurar los mensajes por monitor


/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/


/*==================[funcion principal]======================================*/


/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/


// Implementacion de funcion de la tarea ReceiveBT

void ReceiveBT ( void* taskParmPtr )
{
	   uint8_t data = 0; //variable para registrar la entrada desde el celular por BT
	   // ---------- REPETIR POR SIEMPRE --------------------------
 while( TRUE )
	  {
     // Si leo un dato de una UART lo envio a al otra (bridge)
     if( uartReadByte( UART_PC, &data ) )   //para ver lo que envia el BT
       {
	    uartWriteByte( UART_BLUETOOTH, data );
       }

   if( uartReadByte( UART_BLUETOOTH, &data ) ) //Si se Reciben de datos por BT en cada caso utilizo el semaforo
	    //para modificar la variable y luego lo libero.
     {
      if( data == 'C' )
      {
         xSemaphoreTake(Mutex_UART,portMAX_DELAY);
         control = 1;
         xSemaphoreGive(Mutex_UART);
      }

      if( data == 'A' )
      {
          xSemaphoreTake(Mutex_UART,portMAX_DELAY);
          control = 2;
          xSemaphoreGive(Mutex_UART);
      }

      if( data == 'B' )
      {
      	  xSemaphoreTake(Mutex_UART,portMAX_DELAY);
          control = 3;
          xSemaphoreGive(Mutex_UART);
      }

      if( data == 'D' )
      {
          xSemaphoreTake(Mutex_UART,portMAX_DELAY);
          control = 4;
          xSemaphoreGive(Mutex_UART);
      }
      uartWriteByte( UART_PC, data );


	  //  vTaskDelayUntil( &xLastWakeTime, xPeriodicity ); Lo iba autilizar a aca pero no es necesario,
      //Son instantaneas cada recepcion de BT
      }
	}
}


/*
uint8_t ControlValue (void)
{
	uint8_t control;
	while(1)
		control = control0;
	return control;

}
*/
/*==================[fin del archivo]========================================*/
