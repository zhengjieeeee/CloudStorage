#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    init();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init(){
    cmdTab_ = new CmdTab(ui -> command_tab);
    transTab_ = new TransTab(ui -> transmission_tab);
    msgTab_ = new MessageTab(ui -> message_tab);
    aiTab_ = new AITab(ui -> ai_tab);
    settingTab_ = new SettingTab(ui -> setting_tab);

    conn_ = Connection::getInstance();
}

void Widget::distribute(MessageInfo msgInfo){
    // 解析protobuf，判断在哪个模块
}
