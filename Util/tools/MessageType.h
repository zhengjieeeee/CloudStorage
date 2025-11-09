// 消息类型
enum class MessageType{
    Login,      // 登录
    Register,   // 注册

    Chat,       // 聊天
    Friend,     // 添加好友
    BreakUp,    // 删除好友
    Permission, // 给予权限
    Ban,        // 删除权限

    Mkdir,      // 创造文件夹
    Rmdir,      // 删除文件夹
    Mv,         // 移动文件
    Rm,         // 删除文件

    Pull,       // 下载
    Push,       // 上传

    Preview,    // 预览文本

    /*********警告消息*********/
                // 上传同名文件
                // 未响应消息
                // 上传失败
                // 下载失败
                // 违法访问或文件不存在
};  

