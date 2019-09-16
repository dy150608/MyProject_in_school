#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <QTimer>
#include <QListWidgetItem>
#include <QListView>
#include <QModelIndex>
#include <QMouseEvent>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <pthread.h>
#include <semaphore.h>

#include "lyric_decom.h"

void* get_info(void*);
void* start_player(void*);

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    friend void* get_info(void*);
    friend void* start_player(void*);
    void chplstat();
    void staystat();

    void status_init();
    void only_one_init();
    void print_lrc();
    void print_list();
    void load_lyric(char*);// 传入歌曲路径， 成功返回0, 失败返回-1
    void lyric_free()
    {
        ListNode *curr = this->lyrics->next;
        while(curr != NULL)
        {
            free(this->lyrics);
            this->lyrics = curr;
            curr = curr->next;
        }
    }
    void auto_load();

    void collect();
    void ending();// 保存播放记录

    int music_num;
    int lyric_num;
    int music_cur;
    char* music_list[100];// 歌曲路径
    char* lyric_list[100];// 歌词路径
    int fd_cmd[2];// before read, lock
    int fd_info[2];

    int tot_time;

    ~Widget();
public slots:
    void set_prog();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_listWidget_clicked(const QModelIndex &index);

    void on_pushButton_9_clicked();

private:
    Ui::Widget *ui;
    QTimer timer;
    bool play;// before read, lock
    bool mute;
    bool first;
    bool load;
    int play_mode;
    QString p_stat[2];
    QString m_stat[2];
    QString p_mode[5];
    ListNode *lyrics;// 一首歌的歌词链表
};

#endif // WIDGET_H
