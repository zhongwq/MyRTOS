#include "list.h"

void vListInitialise(List_t* const pxList)
{
    pxList->pxIndex = (ListItem_t*)(&pxList->xListEnd);
    pxList->xListEnd.xItemValue = portMAX_DELAY;
    pxList->xListEnd.pxNext = (ListItem_t*)(&pxList->xListEnd);
    pxList->xListEnd.pxPrevios = (ListItem_t*)(&pxList->xListEnd);
    pxList->uxNumberOfItems = (UBaseType_t)0U;
}

void vListInitialiseItem(ListItem_t* const pxItem)
{
    pxItem->pvContainer = NULL;
}

void vListInsertEnd(List_t* const pxList, ListItem_t* const pxNewListItem)
{
    ListItem_t* const pxIndex = pxList->pxIndex;
    pxNewListItem->pxNext = pxIndex;
    pxNewListItem->pxPrevious = pxIndex->pxPrevious;
    pxIndex->pxPrevious->pxNext = pxNewListItem;
    pxIndex->pxPrevious = pxNewListItem;

    pxNewListItem->pvContainer = (void*)pxList;

    pxList->uxNumberOfItems++;
}

void vListInsert(List_t* const pxList, ListItem_t* const pxNewListItem)
{
    ListItem_t *pxIterator;

    const TickType_t xValueeOfInsertion = pxNewListItem->xItemValue;

    if (xValueeOfInsertion == portMAX_DELAY) {
        pxIterator = pxList->xListEnd.pxPrevios;
    } else {
        pxIterator = (ListItem_t*)(&pxList->xListEnd);
        while (pxIterator->pxNext->xItemValue <= xValueeOfInsertion) {
            pxIterator = pxIterator->pxNext;
        }
    }
    pxNewListItem->pxNext = pxIterator->pxNext;
    pxNewListItem->pxNext->pxPrevious = pxNewListItem;
    pxNewListItem->pxPrevious = pxIterator;
    pxIterator->pxNext = pxNewListItem;

    pxNewListItem->pvContainer = (void*)pxList;
    pxList->uxNumberOfItems++;
}

UBaseType_t uxListRemove(ListItem_t* const pxItemToRemove)
{
    List_t* const pxList = (List_t*)pxItemToRemove->pvContainer;
    pxItemToRemove->pxNext->pxPrevious = pxItemToRemove->pxPrevious;
    pxItemToRemove->pxPrevious->pxNext = pxItemToRemove->pxNext;

    if (pxList->pxIndex == pxItemToRemove) {
        pxList->pxIndex = pxItemToRemove->pxPrevious;
    }
    pxItemToRemove->pvContainer = NULL;
    pxList->uxNumberOfItems--;
    return pxList->uxNumberOfItems;
}
