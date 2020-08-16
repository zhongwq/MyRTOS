#ifndef TASK_H
#define TASK_H

#include "MyRTOSConfig.h"
#include "portmacro.h"
#include "list.h"
#include "projdefs.h"

typedef struct tskTaskControlBlock {
    volatile StackType_t* pxTopOfStack;
    ListItem_t xStateListItem; // 任务节点
    StackType_t* pxStack;
    char pcTaskName[MAX_TASK_NAME_LEN];
} tskTCB, TCB_t;

typedef void* TaskHandle_t;

#if (configSUPPORT_STATIC_ALLOCATION == 1)
TaskHandle_t xTaskCreateStaic(TaskFunction_t pxTaskCode,
                              const char* const pcName,
                              const uint32_t ulStackDepth,
                              void* const pvParameters.
                              StackType_t* const puxStackBuffer,
                              TCB_t* const pxTaskBuffer);
#endif