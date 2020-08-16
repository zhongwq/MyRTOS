#ifndef PORT_H
#define PORT_H

#include "portmacro.h"
#include "task.h"

#define portINITIAL_XPSR       (0x01000000)
#define portSTART_ADDRESS_MASK ((StackType_t)0xfffffffeUL)

StackType_t* pxPortInitialiseStack(StackType_t* pxTopOfStack,
                                   TaskFunction_t pxCode,
                                   void* pvParameters);

#endif