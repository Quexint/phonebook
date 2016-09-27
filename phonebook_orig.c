#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_orig.h"

/* original version */
entry *init_struct()
{
    entry *pHead = (entry *) malloc(sizeof(entry));
    pHead->pNext = NULL;
    return pHead;
}

entry *findName(char lastName[], entry *pHead)
{
    while (pHead != NULL) {
        if (strcasecmp(lastName, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    /* allocate memory for the new entry and put lastName */
    e->pNext = (entry *) malloc(sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;

    return e;
}

void free_struct(entry *pHead)
{
    if (pHead->pNext) free(pHead->pNext);
    free(pHead);
}
