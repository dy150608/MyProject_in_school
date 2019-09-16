/********************************************************************************
** Form generated from reading UI file 'probar.ui'
**
** Created: Tue Sep 10 19:25:30 2019
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROBAR_H
#define UI_PROBAR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QProgressBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Probar
{
public:
    QProgressBar *progressBar;

    void setupUi(QWidget *Probar)
    {
        if (Probar->objectName().isEmpty())
            Probar->setObjectName(QString::fromUtf8("Probar"));
        Probar->resize(490, 20);
        progressBar = new QProgressBar(Probar);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(0, 0, 490, 20));
        progressBar->setValue(24);

        retranslateUi(Probar);

        QMetaObject::connectSlotsByName(Probar);
    } // setupUi

    void retranslateUi(QWidget *Probar)
    {
        Probar->setWindowTitle(QApplication::translate("Probar", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Probar: public Ui_Probar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROBAR_H
