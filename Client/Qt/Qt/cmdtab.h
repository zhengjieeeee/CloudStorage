#ifndef CMDTAB_H
#define CMDTAB_H

#include <QObject>
#include <QWidget>
#include <QTextEdit>
#include <QEvent>
#include <QKeyEvent>
#include <QColor>
#include <QString>
#include <QTextCursor>

class CmdTab : public QWidget
{
    Q_OBJECT
public:
    CmdTab(QWidget* widget);
    ~CmdTab();

    void handle(char* data, size_t);

private:
    void init();

    bool eventFilter(QObject* watched, QEvent* event) override;

    void insertText(const QColor& textColor, const QString& text);

    void removeLimit();
    void parse();

private:
    const QColor Color_Normal = QColor(255, 255, 255);   // 输入内容：白色
    const QColor Color_Warning = QColor(255, 100, 100);  // 警告内容：红色
    const QColor Color_Success = QColor(0, 150, 0);      // header：绿色
    const QColor COlor_Response = QColor(100, 100, 255); // 返回内容

    QWidget*        widget_;
    QTextEdit*      cmdTextEdit_;

    size_t          fixedPos_;
};

#endif // CMDTAB_H
