#include "LoginWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow LogWin;
    LogWin.show();

    return a.exec();
}
