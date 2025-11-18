/********************************************************************************
** Form generated from reading UI file 'friendbox.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDBOX_H
#define UI_FRIENDBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_friendBox
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *friendBox)
    {
        if (friendBox->objectName().isEmpty())
            friendBox->setObjectName(QString::fromUtf8("friendBox"));
        friendBox->resize(378, 57);
        horizontalLayout = new QHBoxLayout(friendBox);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(friendBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(friendBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(30, 30));
        label_2->setMaximumSize(QSize(30, 30));

        horizontalLayout->addWidget(label_2);

        horizontalLayout->setStretch(0, 10);
        horizontalLayout->setStretch(1, 1);

        retranslateUi(friendBox);

        QMetaObject::connectSlotsByName(friendBox);
    } // setupUi

    void retranslateUi(QWidget *friendBox)
    {
        friendBox->setWindowTitle(QCoreApplication::translate("friendBox", "Form", nullptr));
        label->setText(QCoreApplication::translate("friendBox", "\345\220\215\345\255\227", nullptr));
        label_2->setText(QCoreApplication::translate("friendBox", "\346\217\220\351\206\222", nullptr));
    } // retranslateUi

};

namespace Ui {
    class friendBox: public Ui_friendBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDBOX_H
