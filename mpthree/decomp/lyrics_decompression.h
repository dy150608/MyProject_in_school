#ifndef _LYRICS_DECOMPRESSION_H_
#define _LYRICS_DECOMPRESSION_H_

typedef struct listnode
{
	int m;
	int s;
	int ms;
	char lyrics[256];
	struct listnode *prev;
	struct listnode *next;
}ListNode;

ListNode* create_lyrics_list();

#endif
