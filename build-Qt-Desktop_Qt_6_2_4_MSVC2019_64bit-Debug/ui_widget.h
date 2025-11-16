/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *title_widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *close_pushButton;
    QWidget *main_widget;
    QHBoxLayout *horizontalLayout_2;
    QTabWidget *tabWidget;
    QWidget *command_tab;
    QVBoxLayout *verticalLayout_3;
    QTextBrowser *textBrowser;
    QWidget *transmission_tab;
    QHBoxLayout *horizontalLayout_3;
    QTabWidget *transmission_tabWidget;
    QWidget *push_tab;
    QVBoxLayout *verticalLayout_6;
    QWidget *pushInfo_widget;
    QHBoxLayout *horizontalLayout_5;
    QTextBrowser *textBrowser_2;
    QTextBrowser *textBrowser_3;
    QTextBrowser *textBrowser_4;
    QTextBrowser *textBrowser_5;
    QListWidget *push_listWidget;
    QWidget *pull_tab;
    QVBoxLayout *verticalLayout_7;
    QWidget *pullInfo_widget;
    QHBoxLayout *horizontalLayout_7;
    QTextBrowser *textBrowser_10;
    QTextBrowser *textBrowser_11;
    QTextBrowser *textBrowser_12;
    QTextBrowser *textBrowser_13;
    QListWidget *pull_listWidget;
    QWidget *message_tab;
    QHBoxLayout *horizontalLayout_4;
    QWidget *friendList_widget;
    QVBoxLayout *verticalLayout_2;
    QListView *friendList_listView;
    QWidget *chat_widget;
    QWidget *ai_tab;
    QVBoxLayout *verticalLayout_4;
    QTextBrowser *ai_textBrowser;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_5;
    QTextEdit *input_textEdit;
    QPushButton *send_pushButton;
    QWidget *setting_tab;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1013, 796);
        Widget->setMinimumSize(QSize(0, 0));
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        title_widget = new QWidget(Widget);
        title_widget->setObjectName(QString::fromUtf8("title_widget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(title_widget->sizePolicy().hasHeightForWidth());
        title_widget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(title_widget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(title_widget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(300, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_3 = new QPushButton(title_widget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        sizePolicy1.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy1);
        pushButton_3->setMinimumSize(QSize(0, 0));
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"        margin: 0px;\n"
"        padding: 0px;\n"
"        border: none;\n"
"        background: white;\n"
"        icon-size: 24px; \n"
"}"));
        pushButton_3->setIconSize(QSize(30, 30));

        horizontalLayout->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(title_widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);
        pushButton_2->setMinimumSize(QSize(0, 0));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"        margin: 0px;\n"
"        padding: 0px;\n"
"        border: none;\n"
"        background: white;\n"
"        icon-size: 24px; \n"
"}"));

        horizontalLayout->addWidget(pushButton_2);

        close_pushButton = new QPushButton(title_widget);
        close_pushButton->setObjectName(QString::fromUtf8("close_pushButton"));
        sizePolicy1.setHeightForWidth(close_pushButton->sizePolicy().hasHeightForWidth());
        close_pushButton->setSizePolicy(sizePolicy1);
        close_pushButton->setMinimumSize(QSize(0, 0));
        close_pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"        margin: 0px;\n"
"        padding: 0px;\n"
"        border: none;\n"
"        background: white;\n"
"        icon-size: 24px; \n"
"}"));

        horizontalLayout->addWidget(close_pushButton);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 20);
        horizontalLayout->setStretch(2, 1);
        horizontalLayout->setStretch(3, 1);
        horizontalLayout->setStretch(4, 1);

        verticalLayout->addWidget(title_widget);

        main_widget = new QWidget(Widget);
        main_widget->setObjectName(QString::fromUtf8("main_widget"));
        main_widget->setMinimumSize(QSize(0, 0));
        horizontalLayout_2 = new QHBoxLayout(main_widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(main_widget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy2);
        tabWidget->setStyleSheet(QString::fromUtf8("QTabBar::tab {\n"
"        height: 80px;   /* \345\233\272\345\256\232\351\253\230\345\272\246 */\n"
"        width: 80px;   /* \346\234\200\345\244\247\345\256\275\345\272\246\351\231\220\345\210\266\357\274\210\351\201\277\345\205\215\350\277\207\345\256\275\357\274\211 */\n"
"    }\n"
"\n"
" QTabWidget {\n"
"            margin: 0px;\n"
"            padding: 0px;\n"
"        }\n"
"\n"
"QTabWidget::pane {\n"
"            border: none; /* \347\247\273\351\231\244\344\270\273\344\275\223\345\214\272\345\237\237\351\273\230\350\256\244\350\276\271\346\241\206\357\274\210\351\201\277\345\205\215\350\247\206\350\247\211\347\251\272\351\232\231\357\274\211 */\n"
"            margin: 0px;  /* \346\266\210\351\231\244\344\270\273\344\275\223\345\214\272\345\237\237\344\270\216 TabBar\343\200\201\347\252\227\345\217\243\350\276\271\347\274\230\347\232\204\346\211\200\346\234\211\350\276\271\350\267\235 */\n"
"            padding: 0px; /* \346\266\210\351\231\244\344\270\273\344\275\223\345\214\272\345\237\237\345\206\205"
                        "\351\203\250\350\276\271\350\267\235 */\n"
"        }"));
        tabWidget->setTabPosition(QTabWidget::West);
        tabWidget->setTabShape(QTabWidget::Rounded);
        command_tab = new QWidget();
        command_tab->setObjectName(QString::fromUtf8("command_tab"));
        verticalLayout_3 = new QVBoxLayout(command_tab);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        textBrowser = new QTextBrowser(command_tab);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout_3->addWidget(textBrowser);

        verticalLayout_3->setStretch(0, 10);
        tabWidget->addTab(command_tab, QString());
        transmission_tab = new QWidget();
        transmission_tab->setObjectName(QString::fromUtf8("transmission_tab"));
        horizontalLayout_3 = new QHBoxLayout(transmission_tab);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        transmission_tabWidget = new QTabWidget(transmission_tab);
        transmission_tabWidget->setObjectName(QString::fromUtf8("transmission_tabWidget"));
        transmission_tabWidget->setStyleSheet(QString::fromUtf8("QTabBar::tab {\n"
"        height: 40px;   /* \345\233\272\345\256\232\351\253\230\345\272\246 */\n"
"        width: 80px;   /* \346\234\200\345\244\247\345\256\275\345\272\246\351\231\220\345\210\266\357\274\210\351\201\277\345\205\215\350\277\207\345\256\275\357\274\211 */\n"
"    }\n"
"\n"
" QTabWidget {\n"
"            margin: 0px;\n"
"            padding: 0px;\n"
"        }\n"
"\n"
"QTabWidget::pane {\n"
"            border: none; /* \347\247\273\351\231\244\344\270\273\344\275\223\345\214\272\345\237\237\351\273\230\350\256\244\350\276\271\346\241\206\357\274\210\351\201\277\345\205\215\350\247\206\350\247\211\347\251\272\351\232\231\357\274\211 */\n"
"            margin: 0px;  /* \346\266\210\351\231\244\344\270\273\344\275\223\345\214\272\345\237\237\344\270\216 TabBar\343\200\201\347\252\227\345\217\243\350\276\271\347\274\230\347\232\204\346\211\200\346\234\211\350\276\271\350\267\235 */\n"
"            padding: 0px; /* \346\266\210\351\231\244\344\270\273\344\275\223\345\214\272\345\237\237\345\206\205"
                        "\351\203\250\350\276\271\350\267\235 */\n"
"        }"));
        push_tab = new QWidget();
        push_tab->setObjectName(QString::fromUtf8("push_tab"));
        verticalLayout_6 = new QVBoxLayout(push_tab);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        pushInfo_widget = new QWidget(push_tab);
        pushInfo_widget->setObjectName(QString::fromUtf8("pushInfo_widget"));
        sizePolicy.setHeightForWidth(pushInfo_widget->sizePolicy().hasHeightForWidth());
        pushInfo_widget->setSizePolicy(sizePolicy);
        pushInfo_widget->setMinimumSize(QSize(0, 30));
        pushInfo_widget->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_5 = new QHBoxLayout(pushInfo_widget);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        textBrowser_2 = new QTextBrowser(pushInfo_widget);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));

        horizontalLayout_5->addWidget(textBrowser_2);

        textBrowser_3 = new QTextBrowser(pushInfo_widget);
        textBrowser_3->setObjectName(QString::fromUtf8("textBrowser_3"));

        horizontalLayout_5->addWidget(textBrowser_3);

        textBrowser_4 = new QTextBrowser(pushInfo_widget);
        textBrowser_4->setObjectName(QString::fromUtf8("textBrowser_4"));

        horizontalLayout_5->addWidget(textBrowser_4);

        textBrowser_5 = new QTextBrowser(pushInfo_widget);
        textBrowser_5->setObjectName(QString::fromUtf8("textBrowser_5"));

        horizontalLayout_5->addWidget(textBrowser_5);


        verticalLayout_6->addWidget(pushInfo_widget);

        push_listWidget = new QListWidget(push_tab);
        push_listWidget->setObjectName(QString::fromUtf8("push_listWidget"));

        verticalLayout_6->addWidget(push_listWidget);

        verticalLayout_6->setStretch(0, 1);
        verticalLayout_6->setStretch(1, 10);
        transmission_tabWidget->addTab(push_tab, QString());
        pull_tab = new QWidget();
        pull_tab->setObjectName(QString::fromUtf8("pull_tab"));
        verticalLayout_7 = new QVBoxLayout(pull_tab);
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        pullInfo_widget = new QWidget(pull_tab);
        pullInfo_widget->setObjectName(QString::fromUtf8("pullInfo_widget"));
        sizePolicy.setHeightForWidth(pullInfo_widget->sizePolicy().hasHeightForWidth());
        pullInfo_widget->setSizePolicy(sizePolicy);
        pullInfo_widget->setMinimumSize(QSize(0, 30));
        pullInfo_widget->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_7 = new QHBoxLayout(pullInfo_widget);
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        textBrowser_10 = new QTextBrowser(pullInfo_widget);
        textBrowser_10->setObjectName(QString::fromUtf8("textBrowser_10"));

        horizontalLayout_7->addWidget(textBrowser_10);

        textBrowser_11 = new QTextBrowser(pullInfo_widget);
        textBrowser_11->setObjectName(QString::fromUtf8("textBrowser_11"));

        horizontalLayout_7->addWidget(textBrowser_11);

        textBrowser_12 = new QTextBrowser(pullInfo_widget);
        textBrowser_12->setObjectName(QString::fromUtf8("textBrowser_12"));

        horizontalLayout_7->addWidget(textBrowser_12);

        textBrowser_13 = new QTextBrowser(pullInfo_widget);
        textBrowser_13->setObjectName(QString::fromUtf8("textBrowser_13"));

        horizontalLayout_7->addWidget(textBrowser_13);


        verticalLayout_7->addWidget(pullInfo_widget);

        pull_listWidget = new QListWidget(pull_tab);
        pull_listWidget->setObjectName(QString::fromUtf8("pull_listWidget"));

        verticalLayout_7->addWidget(pull_listWidget);

        transmission_tabWidget->addTab(pull_tab, QString());

        horizontalLayout_3->addWidget(transmission_tabWidget);

        tabWidget->addTab(transmission_tab, QString());
        message_tab = new QWidget();
        message_tab->setObjectName(QString::fromUtf8("message_tab"));
        horizontalLayout_4 = new QHBoxLayout(message_tab);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        friendList_widget = new QWidget(message_tab);
        friendList_widget->setObjectName(QString::fromUtf8("friendList_widget"));
        verticalLayout_2 = new QVBoxLayout(friendList_widget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        friendList_listView = new QListView(friendList_widget);
        friendList_listView->setObjectName(QString::fromUtf8("friendList_listView"));

        verticalLayout_2->addWidget(friendList_listView);


        horizontalLayout_4->addWidget(friendList_widget);

        chat_widget = new QWidget(message_tab);
        chat_widget->setObjectName(QString::fromUtf8("chat_widget"));

        horizontalLayout_4->addWidget(chat_widget);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 5);
        tabWidget->addTab(message_tab, QString());
        ai_tab = new QWidget();
        ai_tab->setObjectName(QString::fromUtf8("ai_tab"));
        ai_tab->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_4 = new QVBoxLayout(ai_tab);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        ai_textBrowser = new QTextBrowser(ai_tab);
        ai_textBrowser->setObjectName(QString::fromUtf8("ai_textBrowser"));

        verticalLayout_4->addWidget(ai_textBrowser);

        widget_3 = new QWidget(ai_tab);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setLayoutDirection(Qt::RightToLeft);
        verticalLayout_5 = new QVBoxLayout(widget_3);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 10);
        input_textEdit = new QTextEdit(widget_3);
        input_textEdit->setObjectName(QString::fromUtf8("input_textEdit"));

        verticalLayout_5->addWidget(input_textEdit);

        send_pushButton = new QPushButton(widget_3);
        send_pushButton->setObjectName(QString::fromUtf8("send_pushButton"));
        sizePolicy1.setHeightForWidth(send_pushButton->sizePolicy().hasHeightForWidth());
        send_pushButton->setSizePolicy(sizePolicy1);
        send_pushButton->setLayoutDirection(Qt::RightToLeft);

        verticalLayout_5->addWidget(send_pushButton);

        verticalLayout_5->setStretch(0, 10);

        verticalLayout_4->addWidget(widget_3);

        verticalLayout_4->setStretch(0, 3);
        verticalLayout_4->setStretch(1, 1);
        tabWidget->addTab(ai_tab, QString());
        setting_tab = new QWidget();
        setting_tab->setObjectName(QString::fromUtf8("setting_tab"));
        tabWidget->addTab(setting_tab, QString());

        horizontalLayout_2->addWidget(tabWidget);


        verticalLayout->addWidget(main_widget);


        retranslateUi(Widget);

        tabWidget->setCurrentIndex(3);
        transmission_tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        label->setText(QCoreApplication::translate("Widget", "    logo     ", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Widget", "\346\234\200\345\260\217", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Widget", "\346\234\200\345\244\247", nullptr));
        close_pushButton->setText(QCoreApplication::translate("Widget", "\345\205\263\351\227\255", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(command_tab), QCoreApplication::translate("Widget", "\345\221\275\344\273\244\350\241\214", nullptr));
        textBrowser_2->setHtml(QCoreApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">\346\226\207\344\273\266\345\220\215\345\255\227</span></p></body></html>", nullptr));
        textBrowser_3->setHtml(QCoreApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">\344\275\215\347\275\256</span></p></body></html>", nullptr));
        textBrowser_4->setHtml(QCoreApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">\345\244\247\345\260\217</span></p></body></html>", nullptr));
        textBrowser_5->setHtml(QCoreApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">\346\227\266\351\227\264</span></p></body></html>", nullptr));
        transmission_tabWidget->setTabText(transmission_tabWidget->indexOf(push_tab), QCoreApplication::translate("Widget", "\344\270\212\344\274\240", nullptr));
        textBrowser_10->setHtml(QCoreApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">\346\226\207\344\273\266\345\220\215\345\255\227</span></p></body></html>", nullptr));
        textBrowser_11->setHtml(QCoreApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">\344\275\215\347\275\256</span></p></body></html>", nullptr));
        textBrowser_12->setHtml(QCoreApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">\345\244\247\345\260\217</span></p></body></html>", nullptr));
        textBrowser_13->setHtml(QCoreApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">\346\227\266\351\227\264</span></p></body></html>", nullptr));
        transmission_tabWidget->setTabText(transmission_tabWidget->indexOf(pull_tab), QCoreApplication::translate("Widget", "\344\270\213\350\275\275", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(transmission_tab), QCoreApplication::translate("Widget", "\344\274\240\350\276\223", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(message_tab), QCoreApplication::translate("Widget", "\346\266\210\346\201\257", nullptr));
        send_pushButton->setText(QCoreApplication::translate("Widget", "\345\217\221\351\200\201", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(ai_tab), QCoreApplication::translate("Widget", "AI", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(setting_tab), QCoreApplication::translate("Widget", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
