#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "./decomp/lyrics_decompression.h"
#include "./print/print.h"
#include "./mplayerfile/start_mplayer.h"
#include "./pos/console.h"

// extern ListNode* create_lyrics_list();

int main(void)
{
	ListNode *header, *curr;
	curr = header = create_lyrics_list();
	mplayer_play("./music/断桥残雪.mp3");
	time(header->next, print_lyrics);

	while(curr != NULL)
	{
		free(header);
		header = curr;
		curr = curr->next;
	}
	return 0;
}
// gcc -g main.c ./decomp/lyrics_decompression.c ./print/print.c ./mplayerfile/start_mplayer.c ./pos/console.c
