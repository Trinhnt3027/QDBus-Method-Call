#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QMainWindow>
#include <memory>

namespace Ui {
    class MainWindow;
}

class ChatClient : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChatClient(QWidget *parent = nullptr);
    ~ChatClient();

    void initialize();

public slots:
    void messageFromServerNoReturn(const QString& message);
    QString messageFromServerWithReturn(const QString& message);

private:
    void initUI();
    void intDbusConnection();

private:
    std::unique_ptr<Ui::MainWindow> m_UIPtr;

};

#endif // CHATCLIENT_H
