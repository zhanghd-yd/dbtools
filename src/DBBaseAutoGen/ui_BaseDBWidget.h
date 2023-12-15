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

class Ui_Form
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

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(1011, 754);
        horizontalLayout_3 = new QHBoxLayout(Form);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        searchDataBtn = new QPushButton(Form);
        searchDataBtn->setObjectName(QString::fromUtf8("searchDataBtn"));

        horizontalLayout_2->addWidget(searchDataBtn);

        delDataBtn = new QPushButton(Form);
        delDataBtn->setObjectName(QString::fromUtf8("delDataBtn"));

        horizontalLayout_2->addWidget(delDataBtn);


        verticalLayout->addLayout(horizontalLayout_2);

        tableWidget = new QTableWidget(Form);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout->addWidget(tableWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        allSelectBtn = new QPushButton(Form);
        allSelectBtn->setObjectName(QString::fromUtf8("allSelectBtn"));

        horizontalLayout->addWidget(allSelectBtn);

        notAllSelectBtn = new QPushButton(Form);
        notAllSelectBtn->setObjectName(QString::fromUtf8("notAllSelectBtn"));

        horizontalLayout->addWidget(notAllSelectBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        prePageBtn = new QPushButton(Form);
        prePageBtn->setObjectName(QString::fromUtf8("prePageBtn"));

        horizontalLayout->addWidget(prePageBtn);

        nextPageBtn = new QPushButton(Form);
        nextPageBtn->setObjectName(QString::fromUtf8("nextPageBtn"));

        horizontalLayout->addWidget(nextPageBtn);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_3->addLayout(verticalLayout);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", nullptr));
        searchDataBtn->setText(QApplication::translate("Form", "\346\237\245\350\257\242", nullptr));
        delDataBtn->setText(QApplication::translate("Form", "\345\210\240\351\231\244", nullptr));
        allSelectBtn->setText(QApplication::translate("Form", "\345\205\250\351\200\211", nullptr));
        notAllSelectBtn->setText(QApplication::translate("Form", "\351\235\236\345\205\250\351\200\211", nullptr));
        prePageBtn->setText(QApplication::translate("Form", "\344\270\212\344\270\200\351\241\265", nullptr));
        nextPageBtn->setText(QApplication::translate("Form", "\344\270\213\344\270\200\351\241\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASEDBWIDGET_H
