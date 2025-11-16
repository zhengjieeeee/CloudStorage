#ifndef CHATVIEW_H
#define CHATVIEW_H

#include <QWidget>

namespace Ui {
class chatView;
}

class chatView : public QWidget
{
    Q_OBJECT

public:
    explicit chatView(QWidget *parent = nullptr);
    ~chatView();

private:
    Ui::chatView *ui;
};

#endif // CHATVIEW_H
