#ifndef TRANSTAB_H
#define TRANSTAB_H

#include <QObject>
#include <QWidget>

class TransTab : public QWidget
{
    Q_OBJECT
public:
    TransTab(QWidget* widget);

private:
    QWidget* widget_;
};

#endif // TRANSTAB_H
