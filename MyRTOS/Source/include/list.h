#ifndef LIST_H
#define LIST_H

#include "portmacro.h"

typedef struct xLIST_ITEM {
    TickType_t xItemValue;
    struct xLIST_ITEM *pxNext;
    struct xLIST_ITEM *pxPrevious;
    void *pvOwner;
    void *pvContainer;
} ListItem_t;

typedef struct xMINI_LIST_ITEM {
    TickType_t xItemValue;
    struct xLIST_ITEM *pxNext;
    struct xLIST_ITEM *pxPrevios;
} MiniListItem_t;

typedef struct xLIST {
    UBaseType_t uxNumberOfItems; // count of items in list
    ListItem_t *pxIndex;         // 链表节点索引指针
    MiniListItem_t xListEnd;
} List_t;

 /* 初始化节点的拥有者 */
#define listSET_LIST_ITEM_OWNER(pxListItem, pxOwner) \
    ((pxListItem)->pvOwner = (void*)(pxOwner))

/* 获取节点拥有者 */
#define listGET_LIST_ITEM_OWNER(pxListItem) \
    ((pxListItem)->pvOwner)

/* 初始化节点排序辅助值 */
#define listSET_LIST_ITEM_VALUE(pxListItem, xValue) \
    ((pxListItem)->xItemValue = (xValue))

/* 获取节点排序辅助值 */
#define listGET_LIST_ITEM_VALUE(pxListItem) \
    ((pxListItem)->xItemValue)

/* 获取链表根节点的节点计数器的值 */
#define listGET_ITEM_VALUE_OF_HEAD_ENTRY(pxList) \
    (((pxList)->xListEnd).pxNext->xItemValue)

/* 获取链表的入口节点 */
#define listGET_HEAD_ENTRY(pxList) \
    (((pxList)->xListEnd).pxNext)

/* 获取节点的下一个节点 */
#define listGET_NEXT(pxListItem) \
    ((pxListItem)->pxNext)

/* 获取链表的最后一个节点 */
#define listGET_END_MARKER( pxList ) \
    ((ListItem_t const *)(&((pxList)->xListEnd)))

/* 判断链表是否为空 */
#define listLIST_IS_EMPTY(pxList) \
    ((BaseType_t)((pxList)->uxNumberOfItems == (UBaseType_t)0))

/* 获取链表的节点数 */
#define listCURRENT_LIST_LENGTH(pxList) \
    ((pxList)->uxNumberOfItems)

/* 获取链表第一个节点的 OWNER，即 TCB */
#define listGET_OWNER_OF_NEXT_ENTRY(pxTCB, pxList) { \
    List_t* const pxConstList = (pxList); \
    (pxConstList)->pxIndex = (pxConstList)->pxIndex->pxNext; \
    if ((void*)(pxConstList)->pxIndex == (void*)&((pxConstList)->xListEnd)) { \
        (pxConstList)->pxIndex = (pxConstList)->pxIndex->pxNext; \
    } \
    (pxTCB) = (pxConstList)->pxIndex->pvOwner; \
}

void vListInitialise(List_t* const pxList);
void vListInitialiseItem(ListItem_t* const pxItem);
void vListInsertEnd(List_t* const pxList, ListItem_t* const pxNewListItem);
void vListInsert(List_t* const pxList, ListItem_t* const pxNewListItem);
UBaseType_t uxListRemove(ListItem_t* const pxItemToRemove);

#endif
