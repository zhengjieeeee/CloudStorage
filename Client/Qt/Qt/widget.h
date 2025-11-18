#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTabWidget>

#include "cmdtab.h"
#include "transtab.h"
#include "messagetab.h"
#include "aitab.h"
#include "settingtab.h"
#include "../../NetWork/Connection.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    void init();

    void distribute(MessageInfo msgInfo);
private:
    Ui::Widget  *ui;

    CmdTab*     cmdTab_;
    TransTab*   transTab_;
    MessageTab* msgTab_;
    AITab*      aiTab_;
    SettingTab* settingTab_;

    Connection*  conn_;
};
#endif // WIDGET_H
