#include <QApplication>
#include "widget.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);

    Widget w;

    pid_t pid = vfork();
    if(pid < 0)
        perror("");
    else if(pid == 0)
    {
        execlp("mplayer", " mplayer ", "-ac", "mad",
               "-slave", "-idle", "-quiet",
               "-input", "file=./fifo_cmd",
               w.music_list[w.music_cur-1], NULL);
    }
    else
    {
        sleep(1);// 这个不能少
        pthread_t _read, _play;
        pthread_create(&_read, NULL, get_info, (void*)&w);
        pthread_detach(_read);
        pthread_create(&_play, NULL, start_player, (void*)&w);
        pthread_detach(_play);
        w.show();
    }
    return a.exec();
}
