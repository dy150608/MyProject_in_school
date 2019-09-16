/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created: Wed Sep 11 01:47:02 2019
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QStackedWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLabel *label;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *widget;
    QPushButton *pushButton_4;
    QWidget *page_2;
    QWidget *widget_2;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QListWidget *listWidget;
    QWidget *widget_3;
    QProgressBar *progressBar;
    QPushButton *pushButton_9;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->setEnabled(true);
        Widget->resize(800, 450);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Widget->sizePolicy().hasHeightForWidth());
        Widget->setSizePolicy(sizePolicy);
        Widget->setMinimumSize(QSize(800, 450));
        Widget->setMaximumSize(QSize(800, 450));
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(55, 350, 35, 40));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMinimumSize(QSize(35, 40));
        pushButton->setMaximumSize(QSize(40, 40));
        pushButton->setAutoFillBackground(true);
        pushButton->setIconSize(QSize(40, 40));
        pushButton_2 = new QPushButton(Widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(100, 350, 40, 40));
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);
        pushButton_2->setMinimumSize(QSize(40, 40));
        pushButton_2->setMaximumSize(QSize(40, 40));
        pushButton_2->setAutoFillBackground(true);
        pushButton_2->setIconSize(QSize(40, 40));
        pushButton_3 = new QPushButton(Widget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(150, 350, 40, 40));
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);
        pushButton_3->setMinimumSize(QSize(40, 40));
        pushButton_3->setMaximumSize(QSize(40, 40));
        pushButton_3->setAutoFillBackground(true);
        pushButton_3->setIconSize(QSize(40, 40));
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(250, 10, 250, 300));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        stackedWidget = new QStackedWidget(Widget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(520, 10, 260, 300));
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        stackedWidget->setMinimumSize(QSize(260, 300));
        stackedWidget->setMaximumSize(QSize(260, 300));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        widget = new QWidget(page);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 60, 260, 180));
        widget->setAutoFillBackground(true);
        pushButton_4 = new QPushButton(widget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(0, 0, 260, 180));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy1);
        pushButton_4->setMinimumSize(QSize(0, 0));
        pushButton_4->setMaximumSize(QSize(600, 600));
        pushButton_4->setAutoFillBackground(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8("images/53cf03f9-ea42-4a1d-8a92-65f62c039dc0.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_4->setIcon(icon);
        pushButton_4->setIconSize(QSize(260, 180));
        pushButton_4->setAutoRepeat(false);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        widget_2 = new QWidget(page_2);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(0, 60, 260, 180));
        widget_2->setAutoFillBackground(true);
        pushButton_5 = new QPushButton(widget_2);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(0, 0, 260, 180));
        stackedWidget->addWidget(page_2);
        pushButton_6 = new QPushButton(Widget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(10, 350, 40, 40));
        sizePolicy.setHeightForWidth(pushButton_6->sizePolicy().hasHeightForWidth());
        pushButton_6->setSizePolicy(sizePolicy);
        pushButton_6->setMinimumSize(QSize(40, 40));
        pushButton_6->setMaximumSize(QSize(40, 40));
        pushButton_6->setAutoFillBackground(true);
        pushButton_6->setIconSize(QSize(40, 40));
        pushButton_7 = new QPushButton(Widget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(200, 350, 40, 40));
        sizePolicy.setHeightForWidth(pushButton_7->sizePolicy().hasHeightForWidth());
        pushButton_7->setSizePolicy(sizePolicy);
        pushButton_7->setMinimumSize(QSize(40, 40));
        pushButton_7->setMaximumSize(QSize(40, 40));
        pushButton_7->setAutoFillBackground(true);
        pushButton_7->setIconSize(QSize(40, 40));
        pushButton_8 = new QPushButton(Widget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(750, 350, 40, 40));
        listWidget = new QListWidget(Widget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(15, 75, 220, 210));
        widget_3 = new QWidget(Widget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(250, 360, 490, 20));
        progressBar = new QProgressBar(widget_3);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(0, 0, 490, 20));
        progressBar->setMouseTracking(false);
        progressBar->setAcceptDrops(false);
        progressBar->setValue(24);
        progressBar->setTextVisible(false);
        pushButton_9 = new QPushButton(Widget);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(250, 400, 40, 40));
        sizePolicy.setHeightForWidth(pushButton_9->sizePolicy().hasHeightForWidth());
        pushButton_9->setSizePolicy(sizePolicy);
        pushButton_9->setMinimumSize(QSize(40, 40));
        pushButton_9->setMaximumSize(QSize(40, 40));
        pushButton_9->setAutoFillBackground(true);
        pushButton_9->setIconSize(QSize(40, 40));

        retranslateUi(Widget);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Widget", "|<", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Widget", "||", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("Widget", ">|", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        pushButton_4->setText(QString());
        pushButton_5->setText(QString());
        pushButton_6->setText(QApplication::translate("Widget", "|<<", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("Widget", ">>|", 0, QApplication::UnicodeUTF8));
        pushButton_8->setText(QApplication::translate("Widget", "))", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("Widget", "\346\226\260\345\273\272\351\241\271\347\233\256", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("Widget", "\346\226\260\345\273\272\351\241\271\347\233\256", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("Widget", "\346\226\260\345\273\272\351\241\271\347\233\256", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem3 = listWidget->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("Widget", "\346\226\260\345\273\272\351\241\271\347\233\256", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem4 = listWidget->item(4);
        ___qlistwidgetitem4->setText(QApplication::translate("Widget", "\346\226\260\345\273\272\351\241\271\347\233\256", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem5 = listWidget->item(5);
        ___qlistwidgetitem5->setText(QApplication::translate("Widget", "\346\226\260\345\273\272\351\241\271\347\233\256", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem6 = listWidget->item(6);
        ___qlistwidgetitem6->setText(QApplication::translate("Widget", "\346\226\260\345\273\272\351\241\271\347\233\256", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem7 = listWidget->item(7);
        ___qlistwidgetitem7->setText(QApplication::translate("Widget", "\346\226\260\345\273\272\351\241\271\347\233\256", 0, QApplication::UnicodeUTF8));
        listWidget->setSortingEnabled(__sortingEnabled);

        pushButton_9->setText(QApplication::translate("Widget", "=>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
