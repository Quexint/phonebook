#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

/* TODO: After modifying the original version, uncomment the following
 * line to set OPT properly */
#define OPT 1

struct __PHONE_BOOK_ENTRY;
struct __CONTENT_ENTRY;

typedef struct __PHONE_BOOK_ENTRY {
    struct __CONTENT_ENTRY *content;
    struct __PHONE_BOOK_ENTRY *pNext[26];
} entry;

typedef struct __CONTENT_ENTRY {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
} content;

void free_struct(entry *pHead);
entry *append(char lastName[], entry *e);
entry *findName(char lastName[], entry *pHead);
entry *init_struct();

#endif
