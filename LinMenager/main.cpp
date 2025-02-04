#include "LoginWindow.h"
#include "WelcomePage.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //LoginWindow LogWin;
    //LogWin.show();

    WelcomePage *WelPage = new WelcomePage();
    WelPage->show();//display Welcome Page

    return a.exec();
}
