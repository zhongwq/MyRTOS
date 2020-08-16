#include "port.h"

static void prvTaskExitError(void)
{
    for (;;) {}
}

StackType_t* pxPortInitialiseStack(StackType_t* pxTopOfStack,
                                   TaskFunction_t pxCode,
                                   void* pvParameters)
{
    pxTopOfStack--;
    *pxTopOfStack = portINITIAL_XPSR;
    pxTopOfStack--;
    *pxTopOfStack = ((StackType_t)pxCode) & portSTART_ADDRESS_MASK;
    pxTopOfStack--;
    *pxTopOfStack = (StackType_t)prvTaskExitError;
    pxTopOfStack -= 5;
    *pxTopOfStack = (StackType_t)pvParameters;
    pxTopOfStack -= 8;
    return pxTopOfStack;
}