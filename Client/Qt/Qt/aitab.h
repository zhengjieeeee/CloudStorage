#ifndef AITAB_H
#define AITAB_H

#include <QObject>
#include <QWidget>

class AITab : public QWidget
{
    Q_OBJECT
public:
    AITab(QWidget* widget);

private:
    QWidget* widget_;
};

#endif // AITAB_H
