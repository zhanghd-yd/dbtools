/********************************************************************************
** Form generated from reading UI file 'BaseDBWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASEDBWIDGET_H
#define UI_BASEDBWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BaseDBWidget
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *searchDataBtn;
    QPushButton *delDataBtn;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *allSelectBtn;
    QPushButton *notAllSelectBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *prePageBtn;
    QPushButton *nextPageBtn;

    void setupUi(QWidget *BaseDBWidget)
    {
        if (BaseDBWidget->objectName().isEmpty())
            BaseDBWidget->setObjectName(QString::fromUtf8("BaseDBWidget"));
        BaseDBWidget->resize(1011, 754);
        horizontalLayout_3 = new QHBoxLayout(BaseDBWidget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        searchDataBtn = new QPushButton(BaseDBWidget);
        searchDataBtn->setObjectName(QString::fromUtf8("searchDataBtn"));

        horizontalLayout_2->addWidget(searchDataBtn);

        delDataBtn = new QPushButton(BaseDBWidget);
        delDataBtn->setObjectName(QString::fromUtf8("delDataBtn"));

        horizontalLayout_2->addWidget(delDataBtn);


        verticalLayout->addLayout(horizontalLayout_2);

        tableWidget = new QTableWidget(BaseDBWidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout->addWidget(tableWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        allSelectBtn = new QPushButton(BaseDBWidget);
        allSelectBtn->setObjectName(QString::fromUtf8("allSelectBtn"));

        horizontalLayout->addWidget(allSelectBtn);

        notAllSelectBtn = new QPushButton(BaseDBWidget);
        notAllSelectBtn->setObjectName(QString::fromUtf8("notAllSelectBtn"));

        horizontalLayout->addWidget(notAllSelectBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        prePageBtn = new QPushButton(BaseDBWidget);
        prePageBtn->setObjectName(QString::fromUtf8("prePageBtn"));

        horizontalLayout->addWidget(prePageBtn);

        nextPageBtn = new QPushButton(BaseDBWidget);
        nextPageBtn->setObjectName(QString::fromUtf8("nextPageBtn"));

        horizontalLayout->addWidget(nextPageBtn);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_3->addLayout(verticalLayout);


        retranslateUi(BaseDBWidget);

        QMetaObject::connectSlotsByName(BaseDBWidget);
    } // setupUi

    void retranslateUi(QWidget *BaseDBWidget)
    {
        BaseDBWidget->setWindowTitle(QApplication::translate("BaseDBWidget", "Form", nullptr));
        searchDataBtn->setText(QApplication::translate("BaseDBWidget", "\346\237\245\350\257\242", nullptr));
        delDataBtn->setText(QApplication::translate("BaseDBWidget", "\345\210\240\351\231\244", nullptr));
        allSelectBtn->setText(QApplication::translate("BaseDBWidget", "\345\205\250\351\200\211", nullptr));
        notAllSelectBtn->setText(QApplication::translate("BaseDBWidget", "\351\235\236\345\205\250\351\200\211", nullptr));
        prePageBtn->setText(QApplication::translate("BaseDBWidget", "\344\270\212\344\270\200\351\241\265", nullptr));
        nextPageBtn->setText(QApplication::translate("BaseDBWidget", "\344\270\213\344\270\200\351\241\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BaseDBWidget: public Ui_BaseDBWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASEDBWIDGET_H
