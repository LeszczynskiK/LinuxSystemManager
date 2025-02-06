#include "NetMonitor.h"
#include "WelcomePage.h"

NetMonitor::NetMonitor(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Net monitor window");

    const int x =1280;//x window size
    const int y=720;//y window size

    setFixedSize(x, y);//Set window size
    //Background image
    background = QPixmap("/home/krzysiek89/Desktop/QT_aplikacje/LinuxManager/LinMenager/AllPages.png").scaled(x, y);


    QFont font;
    font.setPointSize(19);//Font size - beginning initialization

    QFont font_status;
    font_status.setPointSize(32);


    //Initialize buttons
    int x_pos=20;
    int y_pos = 560;
    int y_siz =80;

    exitAppButton = new QPushButton("Exit app...", this);//exit app
    exitAppButton->setFont(font);
    exitAppButton->setGeometry(x_pos, y_pos+y_siz, 300, 60);
    connect(exitAppButton, &QPushButton::clicked, this, &NetMonitor::exitApp);

    menuButton = new QPushButton("Go back to menu..", this);//go to welcome page
    menuButton->setFont(font);
    menuButton->setGeometry(x_pos, y_pos, 300, 60);
    connect(menuButton, &QPushButton::clicked, this, &NetMonitor::backToMenu);//if clicked, go back to welcome page

    //network speed label
    netSpeedLabel = new QLabel(this);
    netSpeedLabel->setFont(font_status);
    netSpeedLabel->setStyleSheet("color: yellow;");
    netSpeedLabel->setGeometry(20, 50, 900, 60);

    //timer connected with net stats actualisation
    timerNet = new QTimer(this);
    connect(timerNet, &QTimer::timeout, this, &NetMonitor::updateNetworkStats);
    timerNet->start(1000);//actualise after each 1sec

    updateNetworkStats();//get begining values
}

void NetMonitor::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, background);//Background
    QWidget::paintEvent(event);
}

void NetMonitor::exitApp()
{
    this->close();
}

void NetMonitor::backToMenu()//go back to welcome page
{
    WelcomePage *WelPage = new WelcomePage();
    WelPage->show();//display Welcome Page
    this->close();//close this page
}

void NetMonitor::updateNetworkStats() {

}

