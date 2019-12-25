/********************************************************************************
** Form generated from reading UI file 'ShowPipeWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWPIPEWINDOW_H
#define UI_SHOWPIPEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_showPipeWindow
{
public:

    void setupUi(QWidget *showPipeWindow)
    {
        if (showPipeWindow->objectName().isEmpty())
            showPipeWindow->setObjectName(QStringLiteral("showPipeWindow"));
        showPipeWindow->resize(650, 350);

        retranslateUi(showPipeWindow);

        QMetaObject::connectSlotsByName(showPipeWindow);
    } // setupUi

    void retranslateUi(QWidget *showPipeWindow)
    {
        showPipeWindow->setWindowTitle(QApplication::translate("showPipeWindow", "\346\237\245\347\234\213\347\256\241\347\272\277", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class showPipeWindow: public Ui_showPipeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWPIPEWINDOW_H
