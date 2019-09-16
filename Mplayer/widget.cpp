#include "widget.h"
#include "ui_widget.h"

#include <time.h>

pthread_mutex_t mutex;
sem_t sem, sem2;
int CUR_TIME;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    pthread_mutex_init(&mutex, NULL);
    sem_init(&sem, 0, 1);
    sem_init(&sem2, 0, 1);
    ui->listWidget->setViewMode(QListView::ListMode);
    ui->listWidget->setStyleSheet("background-color:transparent");
    ui->listWidget->setFrameShape(QListWidget::NoFrame);

    connect(&timer, SIGNAL(timeout()), this, SLOT(set_prog()));
    timer.start(500);

    only_one_init();
    status_init();
    this->first = true;
}

Widget::~Widget()
{
    ending();
    collect();
    pthread_mutex_destroy(&mutex);
    sem_destroy(&sem);
    sem_destroy(&sem2);
    delete ui;
}

int get_time(char *buffer)
{
    int pos = 0;
    sscanf(buffer, "%*[^=]=%d", &pos);
    return pos;
}

void* get_info(void *arg)// 获取一个总时间
{
    char buf[1024] = "";
    Widget *wid = (Widget*)arg;
    while(1)
    {
        if(!sem_wait(&sem))
        {
            for(int i = 0; i < 4; i ++)
            {
                read(wid->fd_info[0], buf, sizeof(buf));
                if(strstr(buf, "ANS_LENGTH") != NULL)
                {
                     wid->tot_time = get_time(strstr(buf, "ANS_LENGTH"));
                     wid->ui->progressBar->setMaximum(wid->tot_time);
                     sem_post(&sem2);
                }
                memset(buf, 0, sizeof(buf));
            }
        }
    }
}

void* start_player(void *arg)
{
    Widget *wid = (Widget*)arg;
    while(1)
    {
        wid->status_init();
        pthread_mutex_lock(&mutex);
        write(wid->fd_cmd[1], "get_time_length\n", 16);
        sem_post(&sem);// 为了与另一个线程同步
        pthread_mutex_unlock(&mutex);

        while(sem_wait(&sem2));// 等另一个线程先完成
        wid->load_lyric(wid->music_list[wid->music_cur-1]);
        wid->print_list();
        wid->print_lrc();

        if(wid->first == true)// 如果是第一次打开， 设置为暂停状态
        {
            write(wid->fd_cmd[1], "seek -3\n", 8);
            write(wid->fd_cmd[1], "pause\n", 6);
        }
        else
            write(wid->fd_cmd[1], "seek -5\n", 8);
        for( ; CUR_TIME < wid->tot_time-10; CUR_TIME ++)
        {
            if(wid->load == true)
                break;
            while(wid->play == false)
                usleep(20000);
            wid->print_lrc();
            wid->update();
            sleep(1);
        }
        wid->lyric_free();
        wid->auto_load();
    }
}

void Widget::chplstat()
{
    if(this->play == false)
    {
        this->play = true;
        ui->pushButton_2->setText(this->p_stat[1]);
    }
}

void Widget::staystat()
{
    if(this->play == false)
    {
        pthread_mutex_lock(&mutex);
        write(this->fd_cmd[1], "pause\n", 6);
        ui->pushButton_2->setText(this->p_stat[0]);
        pthread_mutex_unlock(&mutex);
    }
}

void Widget::status_init()
{
    if(this->first == false)
        this->play = true;
    else
        this->play = false;
    this->load = false;
    CUR_TIME = 0;
}

void Widget::only_one_init()// 初始化没问题
{
    this->p_stat[0] = "|>";// 暂停
    this->p_stat[1] = "||";// 播放
    this->m_stat[0] = "))";// 有声
    this->m_stat[1] = "X"; // 静音
    this->p_mode[0] = "=>";// 循环播放
    this->p_mode[1] = "X>";// 随机播放
    this->p_mode[2] = ">1";// 单曲循环

    FILE *fp = fopen("./stat.txt", "r");
    if(fp == NULL)
    {
        this->music_cur = 1;
        CUR_TIME = 0;
        this->play_mode = 0;
        this->mute = false;
    }
    else
    {
        char buf[16] = "";
        fgets(buf, sizeof(buf), fp);
        sscanf(buf, "%d", &this->music_cur);
        memset(buf, 0, sizeof(buf));

        fgets(buf, sizeof(buf), fp);
        sscanf(buf, "%d", &CUR_TIME);
        memset(buf, 0, sizeof(buf));

        int tmp;
        fgets(buf, sizeof(buf), fp);
        sscanf(buf, "%d", &tmp);
        this->play_mode = tmp % 3;
        memset(buf, 0, sizeof(buf));

        fgets(buf, sizeof(buf), fp);
        if(strcmp(buf, "true") == 0)
        {
            this->mute = true;
            write(this->fd_cmd[1], "mute 1\n", 7);
        }
        else if(strcmp(buf, "false") == 0)
        {
            this->mute = false;
            write(this->fd_cmd[1], "mute 0\n", 7);
        }
    }
    ui->pushButton_2->setText(this->p_stat[0]);
    if(this->mute == false)
        ui->pushButton_8->setText(this->m_stat[0]);
    else
        ui->pushButton_8->setText(this->m_stat[1]);

    ui->pushButton_9->setText(this->p_mode[0]);

    // 命名管道： 用来收发命令
    unlink("./fifo_cmd");
    if(mkfifo("./fifo_cmd", 0664) < 0)
        perror("fifo");

    pipe(this->fd_info);
    dup2(this->fd_info[1], 1);

    this->fd_cmd[0] = open("fifo_cmd", O_RDONLY | O_NONBLOCK);
    if(this->fd_cmd[0] < 0)
        perror("read open");
    this->fd_cmd[1] = open("fifo_cmd", O_WRONLY | O_NONBLOCK);
    if(this->fd_cmd[1] < 0)
        perror("write open");

    // 读取歌曲目录
    this->music_num = 0;
    DIR *_music = opendir("./music");
    if(_music == NULL)
        perror("");
    struct dirent *_dir = NULL;
    while(1)
    {
        _dir = readdir(_music);
        if(_dir == NULL)
            break;
        if(_dir->d_type == DT_REG)
        {
            this->music_list[this->music_num] = (char*)malloc(sizeof(_dir->d_name)*sizeof(char)+10);
            sprintf(this->music_list[this->music_num], "%s%s", "./music/", _dir->d_name);
            this->music_num ++;
        }
    }
    closedir(_music);

    // 读取歌词目录
    this->lyric_num = 0;
    DIR *_lyric = opendir("./lyric");
    if(_lyric == NULL)
        perror("");
    _dir = NULL;
    while(1)
    {
        _dir = readdir(_lyric);
        if(_dir == NULL)
            break;
        if(_dir->d_type == DT_REG)
        {
            this->lyric_list[this->lyric_num] = (char*)malloc(sizeof(_dir->d_name)*sizeof(char)+10);
            sprintf(this->lyric_list[this->lyric_num], "%s%s", "./lyric/", _dir->d_name);
            this->lyric_num ++;
        }
    }// 这里已经没问题了
}

void Widget::print_lrc()// 打印歌词
{
    char buf[2048] = "";
    ListNode *curr = this->lyrics;
    while(curr != NULL)
    {
        if(CUR_TIME >= (curr->m*60 + curr->s))
            curr = curr->next;
        else
            break;
    }

    if(curr->prev != NULL)// 比如有一句在 32s -> 44s显示， 则在35s时还不能跳过这句词
        curr = curr->prev;
    int i = 0;
    while(i < 8 && curr != NULL)
    {
        strcat(buf, curr->lyrics);
        curr = curr->next;
        i ++;
    }
    this->ui->label->setText(buf);
}

void Widget::print_list()// 打印歌曲列表
{
    char buf[256] = "";
    int i = 0;
    while(i < 8 && i < this->music_num)
    {
        sscanf(this->music_list[(this->music_cur+i-1)%this->music_num], "./music/%s", buf);
        ui->listWidget->item(i)->setText(buf);
        i ++;
    }
}

void Widget::load_lyric(char *muc_path)
{
    char muc_name[128] = "";
    sscanf(muc_path, "./music/%[^.]", muc_name);
    for(int i = 0; i < this->lyric_num; i ++)
    {
        char tmp_name[128] = "";
        sscanf(this->lyric_list[i], "./lyric/%[^.]", tmp_name);
        if(strcmp(muc_name, tmp_name) == 0)
        {
            this->lyrics = create_lyrics_list(this->lyric_list[i]);
            return;
        }
    }
    this->lyrics = (ListNode*)malloc(sizeof(ListNode));
    memset(this->lyrics, 0, sizeof(ListNode));
    memset(this->lyrics->lyrics, 0, sizeof(this->lyrics->lyrics));

    this->lyrics->m = this->tot_time / 60;
    this->lyrics->s = this->tot_time % 60;
    strcpy(this->lyrics->lyrics, "找不到歌词");
}

void Widget::auto_load()
{
    if(this->load == true)
        return;
    switch(this->play_mode)
    {
    case 0:// 循环播放
        if(this->music_cur >= this->music_num)
            this->music_cur = 1;
        else
            this->music_cur ++;
        break;
    case 1:// 随机播放
        srand(time(NULL));
        this->music_cur = rand() % this->music_num + 1;
        break;
    case 2:// 单曲循环
        break;
    default:
        break;
    }

    char buf[128] = "";
    sprintf(buf, "%s\"%s\"\n", "loadfile ", this->music_list[this->music_cur-1]);
    pthread_mutex_lock(&mutex);
    int ret = write(this->fd_cmd[1], buf, strlen(buf));
    this->first = false;
    pthread_mutex_unlock(&mutex);
    this->chplstat();
    if(ret < 0)
        perror("");
}

void Widget::collect()
{
    for(int i = 0; i < this->music_num; i ++)
        free(this->music_list[i]);
    for(int i = 0; i < this->lyric_num; i ++)
        free(this->lyric_list[i]);

    ::close(this->fd_cmd[0]);
    ::close(this->fd_cmd[1]);
    ::close(this->fd_info[0]);
    ::close(this->fd_info[1]);
}

void Widget::ending()
{
    char buf[16] = "";
    int fd = open("./stat.txt", O_WRONLY | O_CREAT, 0664);
    sprintf(buf, "%d\n", this->music_cur);
    write(fd, buf, sizeof(buf));
    memset(buf, 0, sizeof(buf));

    sprintf(buf, "%d\n", CUR_TIME);
    write(fd, buf, sizeof(buf));
    memset(buf, 0, sizeof(buf));

    sprintf(buf, "%d\n", this->play_mode);
    write(fd, buf, sizeof(buf));
    memset(buf, 0, sizeof(buf));

    if(this->mute == true)
        strcpy(buf, "true");
    else
        strcpy(buf, "false");
    write(fd, buf, sizeof(buf));
    ::close(fd);
}

/*
 * 以下为槽函数， 请留步
 * ×××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××
 */

void Widget::set_prog()// 设置进度条
{
    if(this->play == true)
        this->ui->progressBar->setValue(CUR_TIME);
}

void Widget::on_pushButton_2_clicked()// 暂停/播放
{
    pthread_mutex_lock(&mutex);
    if(this->play == true)
    {
        this->play = false;
        ui->pushButton_2->setText(this->p_stat[0]);
    }
    else
    {
        this->play = true;
        ui->pushButton_2->setText(this->p_stat[1]);
    }
    int ret = write(this->fd_cmd[1], "pause\n", 6);
    pthread_mutex_unlock(&mutex);
    if(ret < 0)
        perror("");
}

void Widget::on_pushButton_clicked()// 快退10s
{
    pthread_mutex_lock(&mutex);
    int ret = write(this->fd_cmd[1], "seek -10\n", 9);
    if(CUR_TIME <= 10)
        CUR_TIME = 0;
    else
        CUR_TIME -= 10;
    pthread_mutex_unlock(&mutex);
    this->chplstat();
    if(ret < 0)
        perror("");
}

void Widget::on_pushButton_3_clicked()// 快进10s
{
    pthread_mutex_lock(&mutex);
    int ret = write(this->fd_cmd[1], "seek 10\n", 8);
    if(CUR_TIME < (this->tot_time-10))
        CUR_TIME += 10;
    else
        this->on_pushButton_7_clicked();
    pthread_mutex_unlock(&mutex);
    this->chplstat();
    if(ret < 0)
        perror("");
}

void Widget::on_pushButton_6_clicked()// 上一曲
{
    switch(this->play_mode)
    {
    case 0:// 循环播放
        if(this->music_cur <= 1)
            this->music_cur = this->music_num;
        else
            this->music_cur --;
        break;
    case 1:// 随机播放
        srand(time(NULL));
        this->music_cur = rand() % this->music_num + 1;
        break;
    case 2:// 单曲循环
        break;
    default:
        break;
    }
    char buf[128] = "";
    sprintf(buf, "%s\"%s\"\n", "loadfile ", this->music_list[this->music_cur-1]);
    pthread_mutex_lock(&mutex);
    int ret = write(this->fd_cmd[1], buf, strlen(buf));
    this->load = true;
    this->first = false;
    pthread_mutex_unlock(&mutex);
    this->chplstat();
    if(ret < 0)
        perror("");
}

void Widget::on_pushButton_7_clicked()// 下一曲
{
    switch(this->play_mode)
    {
    case 0:// 循环播放
        if(this->music_cur >= this->music_num)
            this->music_cur = 1;
        else
            this->music_cur ++;
        break;
    case 1:// 随机播放
        srand(time(NULL));
        this->music_cur = rand() % this->music_num + 1;
        break;
    case 2:// 单曲循环
        break;
    default:
        break;
    }
    char buf[128] = "";
    sprintf(buf, "%s\"%s\"\n", "loadfile ", this->music_list[this->music_cur-1]);
    pthread_mutex_lock(&mutex);
    int ret = write(this->fd_cmd[1], buf, strlen(buf));
    this->load = true;
    this->first =false;
    pthread_mutex_unlock(&mutex);
    this->chplstat();
    if(ret < 0)
        perror("");
}

void Widget::on_pushButton_8_clicked()// 静音/非静音
{
    if(this->mute == false)
    {
        this->mute = true;
        ui->pushButton_8->setText(this->m_stat[1]);
        pthread_mutex_lock(&mutex);
        int ret = write(this->fd_cmd[1], "mute 1\n", 7);
        pthread_mutex_unlock(&mutex);
        this->chplstat();
        if(ret < 0)
            perror("");
    }
    else
    {
        this->mute = false;
        ui->pushButton_8->setText(this->m_stat[0]);
        pthread_mutex_lock(&mutex);
        int ret = write(this->fd_cmd[1], "mute 0\n", 7);
        pthread_mutex_unlock(&mutex);
        this->chplstat();
        if(ret < 0)
            perror("");
    }
}

void Widget::on_listWidget_clicked(const QModelIndex &index)
{
    int row = this->ui->listWidget->currentRow();
    this->music_cur = ((this->music_cur+row -1) % this->music_num) + 1;// 跳到选定的歌曲
    char buf[128] = "";
    sprintf(buf, "%s\"%s\"\n", "loadfile ", this->music_list[this->music_cur-1]);
    pthread_mutex_lock(&mutex);
    int ret = write(this->fd_cmd[1], buf, strlen(buf));
    this->load = true;
    this->first =false;
    pthread_mutex_unlock(&mutex);
    this->chplstat();
    if(ret < 0)
        perror("");
}

void Widget::on_pushButton_9_clicked()
{
    this->play_mode = (this->play_mode+1) % 3;
    this->ui->pushButton_9->setText(this->p_mode[this->play_mode]);
}
