#include "SystemMonitor.h"

#include "WelcomePage.h"

SystemMonitor::SystemMonitor(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("System monitor window");

    const int x =1280;//x window size
    const int y=720;//y window size

    setFixedSize(x, y);//Set window size
    //Background image
    background = QPixmap("/home/krzysiek89/Desktop/QT_aplikacje/LinuxManager/LinMenager/AllPages.png").scaled(x, y);


    QFont font;
    font.setPointSize(19);//Font size - beginning initialization

    QFont font_status;
    font_status.setPointSize(25);


    //Initialize buttons
    int x_pos=20;
    int y_pos = 560;
    int y_siz =80;
    exitAppButton = new QPushButton("Exit app...", this);//exit app
    exitAppButton->setFont(font);
    exitAppButton->setGeometry(x_pos, y_pos+y_siz, 300, 60);
    connect(exitAppButton, &QPushButton::clicked, this, &SystemMonitor::exitApp);

    menuButton = new QPushButton("Go back to menu..", this);//go back to welcome page
    menuButton->setFont(font);
    menuButton->setGeometry(x_pos, y_pos, 300, 60);
    connect(menuButton, &QPushButton::clicked, this, &SystemMonitor::backToMenu);
}

void SystemMonitor::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, background);//Background
    QWidget::paintEvent(event);
}

void SystemMonitor::exitApp()
{
    this->close();
}
void SystemMonitor::backToMenu()//go back to welcome page
{
    WelcomePage *WelPage = new WelcomePage();
    WelPage->show();//display Welcome Page
    this->close();//close this
}
