#include <QApplication>
#include "ChatClient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatClient client;
    client.initialize();
    client.show();

    return a.exec();
}
