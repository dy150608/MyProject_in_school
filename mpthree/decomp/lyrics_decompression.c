#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lyrics_decompression.h"

char lrc_head[4][256];

void __insert(ListNode *curr, ListNode *tmpnode)
{
	while(curr->next != NULL)
		curr = curr->next;
	while(curr->prev != NULL && (curr->m*60 + curr->s) > (tmpnode->m*60 + tmpnode->s))
		curr = curr->prev;
	ListNode *curr_next = curr->next;
	tmpnode->next = curr->next;
	tmpnode->prev = curr;
	curr->next = tmpnode;
	if(curr_next != NULL)
		curr_next->prev = tmpnode;
}
ListNode* create_lyrics_list()
{
	FILE *fp = fopen("./music/断桥残雪.lrc", "r");
	if(fp == NULL)
	{
		perror("lyrics.");
		return NULL;
	}
	ListNode *header, *curr, *tmpnode;
	curr = header = (ListNode*)malloc(sizeof(struct listnode));
	if(!header)
	{
		perror("header.");
		return NULL;
	}
	header->prev = NULL;
	header->next = NULL;

	int f = 0;
	while(!feof(fp))
	{
		char line[256];// 保存一行的内容
		char _lyrics[256] = "";// 保存歌词
		fgets(line, sizeof(_lyrics), fp);// 读取一行
		if(f < 4)// 解包前四行
		{
			sscanf(line,"%*[^:]%*c%[^]]",&lrc_head[f++]);
			continue;
		}

		int time[5][3] = {0};
		int i = 0;
		char *tmpline = line;
		while(*tmpline != '\0')// 进行解包
		{
			if(*tmpline == '[')
				sscanf(tmpline, "[%d:%d.%d]", &time[i][0], &time[i][1], &time[i][2]);// 将解包得到的时间保存到二维数组中
			else
				break;
			while(*tmpline != ']' && *tmpline != '\0')
				tmpline ++;
			i ++;
			tmpline ++;
		}
		
		if(tmpline != NULL && *tmpline != '\0')// 如果最后一个']'后面不为空，则将歌词保存
			strcpy(_lyrics, tmpline);
		for(i = i-1; i >= 0; i --)// 每一行一共有i-1个节点
		{
			if(*_lyrics != '\0')// 如果歌词数组不为空则插入节点
			{
				tmpnode = (ListNode*)malloc(sizeof(ListNode));
				tmpnode->m = time[i][0];
				tmpnode->s = time[i][1];
				tmpnode->ms = time[i][2];
				strcpy(tmpnode->lyrics, _lyrics);
				tmpnode->prev = NULL;
				tmpnode->next = NULL;
				
				__insert(curr, tmpnode);
				/*
				while(curr->next != NULL)
					curr = curr->next;
				while(curr->prev != NULL && (curr->m*60 + curr->s) > (tmpnode->m*60 + tmpnode->s))
					curr = curr->prev;
				ListNode *curr_next = curr->next;
				tmpnode->next = curr->next;
				tmpnode->prev = curr;
				curr->next = tmpnode;
				if(curr_next != NULL)
					curr_next->prev = tmpnode;
				*/
			}
		}
	}
	return header;
}
