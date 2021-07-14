#include "ChatClient.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QThread>
#include <QCoreApplication>
#include <client_adaptor.h>
#include <client_interface.h>

#define LOG  qDebug() << "[" << QCoreApplication::applicationPid() << ":" << QThread::currentThreadId() << "] "

#define SERVICE_NAME    "chat.client"
#define PATH_NAME       "/chat/client"

ChatClient::ChatClient(QWidget *parent) : QMainWindow(parent)
{

}

ChatClient::~ChatClient()
{

}

void ChatClient::initialize()
{
    LOG << "initialize";
    initUI();
    intDbusConnection();
}

void ChatClient::messageFromServerNoReturn(const QString &message)
{
    LOG << "messageFromServerNoReturn: " << message;

//    // Dummy loop
//    while (true) {

//    }

    m_UIPtr->chatHistory->append(message);
}

QString ChatClient::messageFromServerWithReturn(const QString &message)
{
    LOG << "messageFromServerWithReturn: " << message;
    m_UIPtr->chatHistory->append(message);

    return QString("Client received message: %1").arg(message);
}

void ChatClient::initUI()
{
    LOG << "initUI";
    m_UIPtr = std::make_unique<Ui::MainWindow>();
    m_UIPtr->setupUi(this);
    setWindowTitle("ChatClient");
}

void ChatClient::intDbusConnection()
{
    LOG << "intDbusConnection";
    QDBusConnection dbus = QDBusConnection::sessionBus();
//    QDBusConnection dbus = QDBusConnection::systemBus();
    if (!dbus.registerService(SERVICE_NAME)) {
        LOG << "Register service ERROR: " << SERVICE_NAME;
    }
    if (!dbus.registerObject(PATH_NAME, this)) {
        LOG << "Register Object ERROR: " << PATH_NAME;
    }

    new ChatClientAdaptor(this);
}
