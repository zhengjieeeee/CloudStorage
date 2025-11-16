#ifndef FRIENDBOX_H
#define FRIENDBOX_H

#include <QWidget>

namespace Ui {
class friendBox;
}

class friendBox : public QWidget
{
    Q_OBJECT

public:
    explicit friendBox(QWidget *parent = nullptr);
    ~friendBox();

private:
    Ui::friendBox *ui;
};

#endif // FRIENDBOX_H
