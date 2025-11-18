QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../../Util/MemoryPool/CentralCache.cpp \
    ../../../Util/MemoryPool/PageCache.cpp \
    ../../../Util/MemoryPool/ThreadCache.cpp \
    ../../../Util/ThreadPool/Thread.cpp \
    ../../../Util/ThreadPool/ThreadPool.cpp \
    ../../Command/Command.cpp \
    ../../NetWork/Channel.cpp \
    ../../NetWork/Connection.cpp \
    ../../NetWork/MessageQueue.cpp \
    aitab.cpp \
    chatview.cpp \
    cmdtab.cpp \
    controller.cpp \
    friendbox.cpp \
    main.cpp \
    messagetab.cpp \
    settingtab.cpp \
    transtab.cpp \
    widget.cpp  \

HEADERS += \
    ../../../Util/MemoryPool/CentralCache.h \
    ../../../Util/MemoryPool/Common.h \
    ../../../Util/MemoryPool/MemoryPool.h \
    ../../../Util/MemoryPool/PageCache.h \
    ../../../Util/MemoryPool/ThreadCache.h \
    ../../../Util/ThreadPool/Thread.h \
    ../../../Util/ThreadPool/ThreadPool.h \
    ../../../Util/tools/CPython.h \
    ../../../Util/tools/Configure.h \
    ../../../Util/tools/File.h \
    ../../../Util/tools/MessageType.h \
    ../../../Util/tools/Time.h \
    ../../Command/Command.h \
    ../../Command/Format.h \
    ../../NetWork/Channel.h \
    ../../NetWork/Connection.h \
    ../../NetWork/MessageQueue.h \
    aitab.h \
    chatview.h \
    cmdtab.h \
    controller.h \
    friendbox.h \
    messagetab.h \
    settingtab.h \
    transtab.h \
    widget.h

FORMS += \
    chatview.ui \
    friendbox.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
