QT       += core gui dbus widgets
CONFIG += c++14



FORMS += MainWindow.ui

HEADERS += \
    ChatClient.h

SOURCES += \
    ChatClient.cpp \
    main.cpp

DBUS_ADAPTORS   += local.chat.client.xml
DBUS_INTERFACES += local.chat.client.xml

DISTFILES += \
    local.chat.client.xml
