#include "ChatServer.h"
#include <QDebug>
#include <QThread>
#include <QCoreApplication>
#include <ui_MainWindow.h>
#include <QDBusInterface>
#include <QDBusReply>

#define LOG  qDebug() << "[" << QCoreApplication::applicationPid() << ":" << QThread::currentThreadId() << "] "

#define OPTION_1    "No return"
#define OPTION_2    "With return"

#define SERVICE_NAME    "chat.client"
#define PATH_NAME       "/chat/client"
#define INTERFACE_NAME  "local.ChatClient"

ChatServer::ChatServer(QWidget *parent) : QMainWindow(parent)
{

}

ChatServer::~ChatServer()
{

}

void ChatServer::initialize()
{
    LOG << "initialize";
    initUI();
}

void ChatServer::initUI()
{
    LOG << "initUI";
    m_UIPtr = std::make_unique<Ui::MainWindow>();
    m_UIPtr->setupUi(this);
    setWindowTitle("ChatServer");

    m_UIPtr->options->addItems({OPTION_1, OPTION_2});

    connect(m_UIPtr->sendBtn, &QPushButton::clicked, this, &ChatServer::onBtnSendClicked);
    connect(m_UIPtr->message, &QLineEdit::textChanged, this, &ChatServer::onMessageChanged);
}

void ChatServer::onBtnSendClicked()
{
    LOG << "onBtnSendClicked";
    QString curOption = m_UIPtr->options->currentText();
    QString message = m_UIPtr->message->text();
    QString resultCall("");
    QDBusInterface inface(SERVICE_NAME, PATH_NAME, INTERFACE_NAME);
    inface.setTimeout(2000);
    if (curOption == OPTION_1) {
        // No return
        LOG << "call without return, message: " << message;
        QDBusMessage mess = inface.call("messageFromServerNoReturn", message);
        resultCall = mess.errorMessage().isEmpty() ? "messageFromServerNoReturn Ok"
                                                   : QString("messageFromServerNoReturn Error: %1").arg(mess.errorMessage());
    }
    else {
        // Return
        LOG << "call with return, message: " << message;
        QDBusReply<QString> reply = inface.call("messageFromServerWithReturn", message);
        resultCall = reply.isValid() ? QString("messageFromServerWithReturn Ok >> return: %1").arg(reply.value())
                                     : QString("messageFromServerWithReturn Error: %1").arg(reply.error().message());
    }
    m_UIPtr->history->append(resultCall);
}

void ChatServer::onMessageChanged(const QString &message)
{
    m_UIPtr->sendBtn->setEnabled(!message.trimmed().isEmpty());
}
