/********************************************************************************
** Form generated from reading UI file 'chatview.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATVIEW_H
#define UI_CHATVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chatView
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *name_label;
    QTextBrowser *textBrowser;
    QTextEdit *textEdit;
    QPushButton *pushButton;

    void setupUi(QWidget *chatView)
    {
        if (chatView->objectName().isEmpty())
            chatView->setObjectName(QString::fromUtf8("chatView"));
        chatView->resize(790, 747);
        verticalLayout = new QVBoxLayout(chatView);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 5);
        name_label = new QLabel(chatView);
        name_label->setObjectName(QString::fromUtf8("name_label"));

        verticalLayout->addWidget(name_label);

        textBrowser = new QTextBrowser(chatView);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout->addWidget(textBrowser);

        textEdit = new QTextEdit(chatView);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        verticalLayout->addWidget(textEdit);

        pushButton = new QPushButton(chatView);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setLayoutDirection(Qt::RightToLeft);

        verticalLayout->addWidget(pushButton);

        verticalLayout->setStretch(0, 3);
        verticalLayout->setStretch(1, 40);
        verticalLayout->setStretch(2, 10);

        retranslateUi(chatView);

        QMetaObject::connectSlotsByName(chatView);
    } // setupUi

    void retranslateUi(QWidget *chatView)
    {
        chatView->setWindowTitle(QCoreApplication::translate("chatView", "Form", nullptr));
        name_label->setText(QCoreApplication::translate("chatView", "\345\220\215\345\255\227", nullptr));
        pushButton->setText(QCoreApplication::translate("chatView", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class chatView: public Ui_chatView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATVIEW_H
