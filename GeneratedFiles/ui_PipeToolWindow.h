/********************************************************************************
** Form generated from reading UI file 'PipeToolWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PIPETOOLWINDOW_H
#define UI_PIPETOOLWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pipeToolWindow
{
public:
    QWidget *page0;
    QGroupBox *groupBox;
    QPushButton *choosePipeDataBtn;
    QGroupBox *groupBox_2;
    QListWidget *modelListWidget;
    QPushButton *deleteModelBtn;
    QPushButton *selectAllModelBtn;
    QPushButton *chooseFolderModelBtn;
    QPushButton *chooseSingleModelBtn;
    QPushButton *chooseSaveBtn;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *datasetEdit;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *savePathLineEdit;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *vectorDataEdit;
    QPushButton *prePushButton;
    QPushButton *nextPushButton;
    QPushButton *okPushButton;
    QWidget *page1;
    QGroupBox *groupBox_3;
    QTableWidget *colorTableWidget;
    QPushButton *addColorBtn;
    QPushButton *seleAllColorBtn;
    QPushButton *deleteColor;
    QPushButton *defaultColor;
    QWidget *page2;
    QGroupBox *groupBox_4;
    QTableWidget *lineTableWidget;
    QWidget *page3;
    QGroupBox *groupBox_5;
    QTableWidget *pointTableWidget;

    void setupUi(QWidget *pipeToolWindow)
    {
        if (pipeToolWindow->objectName().isEmpty())
            pipeToolWindow->setObjectName(QStringLiteral("pipeToolWindow"));
        pipeToolWindow->setEnabled(true);
        pipeToolWindow->resize(650, 377);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pipeToolWindow->sizePolicy().hasHeightForWidth());
        pipeToolWindow->setSizePolicy(sizePolicy);
        pipeToolWindow->setMinimumSize(QSize(650, 377));
        pipeToolWindow->setMaximumSize(QSize(650, 377));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/SynBuilder.ico"), QSize(), QIcon::Normal, QIcon::On);
        pipeToolWindow->setWindowIcon(icon);
        pipeToolWindow->setStyleSheet(QStringLiteral(""));
        page0 = new QWidget(pipeToolWindow);
        page0->setObjectName(QStringLiteral("page0"));
        page0->setGeometry(QRect(0, 10, 641, 331));
        page0->setStyleSheet(QStringLiteral(""));
        groupBox = new QGroupBox(page0);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 631, 321));
        choosePipeDataBtn = new QPushButton(groupBox);
        choosePipeDataBtn->setObjectName(QStringLiteral("choosePipeDataBtn"));
        choosePipeDataBtn->setGeometry(QRect(540, 20, 75, 23));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 50, 611, 231));
        modelListWidget = new QListWidget(groupBox_2);
        modelListWidget->setObjectName(QStringLiteral("modelListWidget"));
        modelListWidget->setGeometry(QRect(10, 20, 501, 201));
        modelListWidget->setStyleSheet(QStringLiteral(""));
        deleteModelBtn = new QPushButton(groupBox_2);
        deleteModelBtn->setObjectName(QStringLiteral("deleteModelBtn"));
        deleteModelBtn->setGeometry(QRect(530, 180, 75, 23));
        selectAllModelBtn = new QPushButton(groupBox_2);
        selectAllModelBtn->setObjectName(QStringLiteral("selectAllModelBtn"));
        selectAllModelBtn->setGeometry(QRect(530, 130, 75, 23));
        chooseFolderModelBtn = new QPushButton(groupBox_2);
        chooseFolderModelBtn->setObjectName(QStringLiteral("chooseFolderModelBtn"));
        chooseFolderModelBtn->setGeometry(QRect(530, 80, 75, 23));
        chooseSingleModelBtn = new QPushButton(groupBox_2);
        chooseSingleModelBtn->setObjectName(QStringLiteral("chooseSingleModelBtn"));
        chooseSingleModelBtn->setGeometry(QRect(530, 30, 75, 23));
        chooseSaveBtn = new QPushButton(groupBox);
        chooseSaveBtn->setObjectName(QStringLiteral("chooseSaveBtn"));
        chooseSaveBtn->setGeometry(QRect(540, 290, 75, 23));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 290, 213, 22));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);

        datasetEdit = new QLineEdit(layoutWidget);
        datasetEdit->setObjectName(QStringLiteral("datasetEdit"));

        horizontalLayout_4->addWidget(datasetEdit);

        layoutWidget1 = new QWidget(groupBox);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(261, 290, 261, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        savePathLineEdit = new QLineEdit(layoutWidget1);
        savePathLineEdit->setObjectName(QStringLiteral("savePathLineEdit"));

        horizontalLayout->addWidget(savePathLineEdit);

        layoutWidget2 = new QWidget(groupBox);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(11, 20, 511, 22));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        vectorDataEdit = new QLineEdit(layoutWidget2);
        vectorDataEdit->setObjectName(QStringLiteral("vectorDataEdit"));

        horizontalLayout_3->addWidget(vectorDataEdit);

        prePushButton = new QPushButton(pipeToolWindow);
        prePushButton->setObjectName(QStringLiteral("prePushButton"));
        prePushButton->setGeometry(QRect(360, 340, 75, 23));
        nextPushButton = new QPushButton(pipeToolWindow);
        nextPushButton->setObjectName(QStringLiteral("nextPushButton"));
        nextPushButton->setGeometry(QRect(450, 340, 75, 23));
        okPushButton = new QPushButton(pipeToolWindow);
        okPushButton->setObjectName(QStringLiteral("okPushButton"));
        okPushButton->setGeometry(QRect(540, 341, 75, 23));
        page1 = new QWidget(pipeToolWindow);
        page1->setObjectName(QStringLiteral("page1"));
        page1->setGeometry(QRect(0, 10, 641, 321));
        page1->setStyleSheet(QStringLiteral(""));
        groupBox_3 = new QGroupBox(page1);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 0, 631, 321));
        colorTableWidget = new QTableWidget(groupBox_3);
        if (colorTableWidget->columnCount() < 6)
            colorTableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        colorTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        colorTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        colorTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        colorTableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        colorTableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        colorTableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        colorTableWidget->setObjectName(QStringLiteral("colorTableWidget"));
        colorTableWidget->setGeometry(QRect(10, 20, 511, 281));
        colorTableWidget->setStyleSheet(QStringLiteral(""));
        colorTableWidget->setAlternatingRowColors(true);
        colorTableWidget->setShowGrid(true);
        colorTableWidget->setGridStyle(Qt::SolidLine);
        colorTableWidget->setSortingEnabled(false);
        colorTableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        colorTableWidget->horizontalHeader()->setDefaultSectionSize(80);
        colorTableWidget->horizontalHeader()->setStretchLastSection(true);
        colorTableWidget->verticalHeader()->setCascadingSectionResizes(false);
        addColorBtn = new QPushButton(groupBox_3);
        addColorBtn->setObjectName(QStringLiteral("addColorBtn"));
        addColorBtn->setGeometry(QRect(540, 50, 75, 23));
        seleAllColorBtn = new QPushButton(groupBox_3);
        seleAllColorBtn->setObjectName(QStringLiteral("seleAllColorBtn"));
        seleAllColorBtn->setGeometry(QRect(540, 110, 75, 23));
        deleteColor = new QPushButton(groupBox_3);
        deleteColor->setObjectName(QStringLiteral("deleteColor"));
        deleteColor->setGeometry(QRect(540, 170, 75, 23));
        defaultColor = new QPushButton(groupBox_3);
        defaultColor->setObjectName(QStringLiteral("defaultColor"));
        defaultColor->setGeometry(QRect(540, 230, 75, 23));
        page2 = new QWidget(pipeToolWindow);
        page2->setObjectName(QStringLiteral("page2"));
        page2->setGeometry(QRect(0, 10, 641, 331));
        page2->setStyleSheet(QStringLiteral(""));
        groupBox_4 = new QGroupBox(page2);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(0, 0, 631, 321));
        lineTableWidget = new QTableWidget(groupBox_4);
        if (lineTableWidget->columnCount() < 2)
            lineTableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        lineTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        lineTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        lineTableWidget->setObjectName(QStringLiteral("lineTableWidget"));
        lineTableWidget->setGeometry(QRect(10, 20, 591, 281));
        lineTableWidget->horizontalHeader()->setDefaultSectionSize(250);
        page3 = new QWidget(pipeToolWindow);
        page3->setObjectName(QStringLiteral("page3"));
        page3->setGeometry(QRect(0, 10, 641, 331));
        page3->setStyleSheet(QStringLiteral(""));
        groupBox_5 = new QGroupBox(page3);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(0, 0, 631, 321));
        pointTableWidget = new QTableWidget(groupBox_5);
        if (pointTableWidget->columnCount() < 2)
            pointTableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        pointTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        pointTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem9);
        pointTableWidget->setObjectName(QStringLiteral("pointTableWidget"));
        pointTableWidget->setGeometry(QRect(10, 20, 591, 281));
        pointTableWidget->horizontalHeader()->setDefaultSectionSize(250);
        page1->raise();
        page2->raise();
        page3->raise();
        prePushButton->raise();
        nextPushButton->raise();
        okPushButton->raise();
        page0->raise();

        retranslateUi(pipeToolWindow);

        QMetaObject::connectSlotsByName(pipeToolWindow);
    } // setupUi

    void retranslateUi(QWidget *pipeToolWindow)
    {
        pipeToolWindow->setWindowTitle(QApplication::translate("pipeToolWindow", "\347\256\241\347\272\277\347\224\237\344\272\247\345\267\245\345\205\267", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("pipeToolWindow", "\345\257\274\345\205\245\345\257\274\345\207\272", Q_NULLPTR));
        choosePipeDataBtn->setText(QApplication::translate("pipeToolWindow", "\346\265\217\350\247\210", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("pipeToolWindow", "\345\257\274\345\205\245\347\256\241\347\202\271\346\250\241\345\236\213\346\226\207\344\273\266", Q_NULLPTR));
        deleteModelBtn->setText(QApplication::translate("pipeToolWindow", "\345\210\240\351\231\244", Q_NULLPTR));
        selectAllModelBtn->setText(QApplication::translate("pipeToolWindow", "\345\205\250\351\200\211/\345\217\215\351\200\211", Q_NULLPTR));
        chooseFolderModelBtn->setText(QApplication::translate("pipeToolWindow", "\346\211\223\345\274\200\346\226\207\344\273\266\345\244\271", Q_NULLPTR));
        chooseSingleModelBtn->setText(QApplication::translate("pipeToolWindow", "\346\211\223\345\274\200", Q_NULLPTR));
        chooseSaveBtn->setText(QApplication::translate("pipeToolWindow", "\346\265\217\350\247\210", Q_NULLPTR));
        label_3->setText(QApplication::translate("pipeToolWindow", "\346\225\260\346\215\256\351\233\206\345\220\215\347\247\260\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("pipeToolWindow", "\345\257\274\345\207\272\350\267\257\345\276\204\357\274\232", Q_NULLPTR));
        label->setText(QApplication::translate("pipeToolWindow", "\351\200\211\346\213\251\347\256\241\347\272\277\346\225\260\346\215\256\357\274\232", Q_NULLPTR));
        prePushButton->setText(QApplication::translate("pipeToolWindow", "\344\270\212\344\270\200\346\255\245", Q_NULLPTR));
        nextPushButton->setText(QApplication::translate("pipeToolWindow", "\344\270\213\344\270\200\346\255\245", Q_NULLPTR));
        okPushButton->setText(QApplication::translate("pipeToolWindow", "\345\256\214\346\210\220", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("pipeToolWindow", "\347\256\241\347\272\277\351\242\234\350\211\262\351\205\215\347\275\256", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = colorTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("pipeToolWindow", "\351\200\211\344\270\255", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = colorTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("pipeToolWindow", "\347\210\266\347\261\273\345\236\213", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = colorTableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("pipeToolWindow", "\347\210\266\345\220\215\347\247\260", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = colorTableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("pipeToolWindow", "\345\255\220\347\261\273\345\236\213", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = colorTableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("pipeToolWindow", "\345\255\220\345\220\215\347\247\260", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = colorTableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("pipeToolWindow", "\350\256\276\347\275\256\351\242\234\350\211\262", Q_NULLPTR));
        addColorBtn->setText(QApplication::translate("pipeToolWindow", "\346\267\273\345\212\240", Q_NULLPTR));
        seleAllColorBtn->setText(QApplication::translate("pipeToolWindow", "\345\205\250\351\200\211/\345\217\215\351\200\211", Q_NULLPTR));
        deleteColor->setText(QApplication::translate("pipeToolWindow", "\345\210\240\351\231\244", Q_NULLPTR));
        defaultColor->setText(QApplication::translate("pipeToolWindow", "\351\273\230\350\256\244", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("pipeToolWindow", "\347\256\241\347\272\277\345\255\227\346\256\265\346\230\240\345\260\204", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = lineTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QApplication::translate("pipeToolWindow", "\347\233\256\346\240\207\350\241\250\345\205\263\350\201\224\345\255\227\346\256\265\345\220\215", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = lineTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QApplication::translate("pipeToolWindow", "\345\257\274\345\205\245\350\241\250\345\205\263\350\201\224\345\255\227\346\256\265\345\220\215", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("pipeToolWindow", "\347\256\241\347\202\271\345\255\227\346\256\265\346\230\240\345\260\204", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem8 = pointTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem8->setText(QApplication::translate("pipeToolWindow", "\347\233\256\346\240\207\350\241\250\345\205\263\350\201\224\345\255\227\346\256\265\345\220\215", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem9 = pointTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem9->setText(QApplication::translate("pipeToolWindow", "\345\257\274\345\205\245\350\241\250\345\205\263\350\201\224\345\255\227\346\256\265\345\220\215", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class pipeToolWindow: public Ui_pipeToolWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PIPETOOLWINDOW_H
