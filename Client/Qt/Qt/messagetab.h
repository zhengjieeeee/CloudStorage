#ifndef MESSAGETAB_H
#define MESSAGETAB_H

#include <QObject>
#include <QWidget>

class MessageTab : public QWidget
{
    Q_OBJECT
public:
    MessageTab(QWidget* widget);

private:
    QWidget* widget_;
};

#endif // MESSAGETAB_H
