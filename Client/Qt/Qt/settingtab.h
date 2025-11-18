#ifndef SETTINGTAB_H
#define SETTINGTAB_H

#include <QObject>
#include <QWidget>

class SettingTab : public QWidget
{
    Q_OBJECT
public:
    SettingTab(QWidget* widget);

private:
    QWidget* widget_;
};

#endif // SETTINGTAB_H
