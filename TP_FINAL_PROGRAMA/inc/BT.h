/*
 * BT.h
 *
 *  Created on: 27 ago. 2019
 *      Author: jpm
 */

#ifndef MIS_PROGRAMAS_TP_SOLO_BT_INC_BT_H_
#define MIS_PROGRAMAS_TP_SOLO_BT_INC_BT_H_


#include "FreeRTOS.h"
#include "task.h"
#include "sapi.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/

/*=====[Prototypes (declarations) of public functions]=======================*/

void ReceiveBT( void* taskParmPtr );  // Task declaration
//uint8_t ControlValue (void);
extern uint8_t control;

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/


#endif /* MIS_PROGRAMAS_TP_SOLO_BT_INC_BT_H_ */
