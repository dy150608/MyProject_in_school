#ifndef LYRIC_DECOM_H
#define LYRIC_DECOM_H

#include "gb2312_ucs2.h"

typedef struct listnode
{
    int m;
    int s;
    int ms;
    char lyrics[256];
    struct listnode *prev;
    struct listnode *next;
}ListNode;

ListNode* create_lyrics_list(char*);

#endif // LYRIC_DECOM_H
