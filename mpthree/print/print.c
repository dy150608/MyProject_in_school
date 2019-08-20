#include <unistd.h>
#include <stdio.h>
#include "../decomp/lyrics_decompression.h"
#include "../pos/console.h"

extern char lrc_head[4][256];
int minutes = 0, seconds = 0, mseconds = 0;

void color_bf(int b,int f,char *str)
{
	printf("\033[%d;%dm%s\033[0m",b,f,str);//b:背景色 f:字体颜色 str:要渲染的字符串
	return;
}

void time(ListNode *head, void (*print)(ListNode *p))
{
	ListNode *tmp, *play;
	tmp = play = head;

	while(1)
	{
		if(tmp->next == NULL)
			break;
		sleep(1);
		seconds ++;
		if(seconds >= 60)
		{
			minutes ++;
			seconds %= 60;
		}

		print(play);
		while(minutes >= tmp->m && seconds >= tmp->s && tmp != NULL)
		{
			play = tmp;
			tmp = tmp->next;
		}
	}
}

void print_lyrics(ListNode *curr)
{
	int i;
	clear_screen();
	for(i = 0; i < 4; i ++)
	{
		printf("%s\n", lrc_head[i]);
	}
	printf("%02d:%02d\n",minutes,seconds);
	
	i=0;
	color_bf(0, 31, curr->lyrics);
	ListNode *tmp = curr->next;
	while(i<4 && tmp!=NULL)
	{
		printf("%s", tmp->lyrics);
		tmp=tmp->next;
		i++;
	}
}

