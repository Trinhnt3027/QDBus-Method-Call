#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QMainWindow>
#include <memory>

namespace Ui {
    class MainWindow;
}

class ChatServer : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChatServer(QWidget *parent = nullptr);
    ~ChatServer();

    void initialize();

private:
    void initUI();

private slots:
    void onBtnSendClicked();
    void onMessageChanged(const QString& message);

private:
    std::unique_ptr<Ui::MainWindow> m_UIPtr;

};

#endif // CHATSERVER_H
