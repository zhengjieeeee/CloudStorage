#include "cmdtab.h"

CmdTab::CmdTab(QWidget* widget) : widget_(widget)
{
    init();
}

CmdTab::~CmdTab(){
    // 不用析构指针，最后由ui析构
}

void CmdTab::init(){
    cmdTextEdit_ = widget_ -> findChild<QTextEdit*>("cmd_textEdit");
    cmdTextEdit_ -> installEventFilter(this);

    fixedPos_ = -1;
}

bool CmdTab::eventFilter(QObject* watched, QEvent* event){
    if (watched != cmdTextEdit_){
        return QWidget::eventFilter(watched, event);
    }

    if (event -> type() == QEvent::KeyPress){
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        int key = keyEvent -> key();
        if (key == Qt::Key_Enter){
            // 解析命令
            parse();
        }

        if (key == Qt::Key_Backspace){
            // 删除限制
            removeLimit();
        }
    }
}

void CmdTab::handle(char* data, size_t size){

}

void CmdTab::insertText(const QColor& textColor, QString& text){
    text += '\n';
    QTextCursor cursor = cmdTextEdit_ -> textCursor();
    cursor.movePosition(QTextCursor::End);

    QTextCharFormat format;
    format.setForeground(QBrush(textColor));
    cursor.setCharFormat(format);
    cursor.insertText(text);
    cmdTextEdit_->setTextCursor(cursor);

    fixedPos_ += text.size();
}
