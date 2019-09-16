#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lyric_decom.h"

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
ListNode* create_lyrics_list(char *lrc_path)
{
    FILE *fp = fopen(lrc_path, "r");
    if(fp == NULL)
    {
        perror("lyric");
        return NULL;
    }
    ListNode *header, *curr, *tmpnode;
    curr = header = (ListNode*)malloc(sizeof(struct listnode));
    if(!header)
    {
        perror("header");
        return NULL;
    }
    memset(header, 0, sizeof(ListNode));

    while(!feof(fp))
    {
        char line[256] = "";// 保存一行的内容
        char _lyrics[256] = "";// 保存歌词
        fgets(line, sizeof(line), fp);// 读取一行
        if(strlen(line) == 0)
            continue;
        char tmp[256] = "";
        sscanf(line, "%*[^]]%*c%s", tmp);
        if(strlen(tmp) == 0)// 跳过不含歌词的部分
            continue;

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
        {
            char _tmp_[256] = "";
            strcpy(_tmp_, tmpline);
            str_to_utf8(_tmp_, _lyrics);// 将歌词以utf-8的格式保存
        }
        for(i = i-1; i >= 0; i --)// 每一行一共有i-1个节点
        {
            if(*_lyrics != '\0')// 如果歌词数组不为空则插入节点
            {
                tmpnode = (ListNode*)malloc(sizeof(ListNode));
                memset(tmpnode, 0, sizeof(ListNode));

                tmpnode->m = time[i][0];
                tmpnode->s = time[i][1];
                tmpnode->ms = time[i][2];
                strcpy(tmpnode->lyrics, _lyrics);
                tmpnode->prev = NULL;
                tmpnode->next = NULL;

                __insert(curr, tmpnode);
            }
        }
    }
    return header;
}
