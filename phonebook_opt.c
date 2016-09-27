#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "phonebook_opt.h"

#define DECODE(x) (x - 'a')

entry *init_struct()
{
    entry *pHead = (entry *) malloc(sizeof(entry));
    pHead->content = NULL;
    memset(pHead->pNext, 0, sizeof(entry*) * 26);
    return pHead;
}

entry *findName(char lastName[], entry *pHead)
{
    entry *pItr;
    int l;
    for(pItr = pHead, l = 0; lastName[l] != '\0' && pItr != NULL; l++)
        pItr = pItr->pNext[DECODE(lastName[l])];
    return pItr;
}

entry *append(char lastName[], entry *pHead)
{
    int l;
    entry *pItr;
    for(pItr = pHead, l = 0; lastName[l] != '\0'; pItr = pItr->pNext[DECODE(lastName[l])], l++)
        if(pItr->pNext[DECODE(lastName[l])] == NULL)
            pItr->pNext[DECODE(lastName[l])] = init_struct();

    pItr->content = (content *)malloc(sizeof(content));
    return pHead;
}

void free_struct(entry *pHead)
{
    int i;
    if(pHead) {
        free(pHead->content);
        for(i = 0; i < 26; i++)
            free_struct(pHead->pNext[i]);
    }
    free(pHead);
}
