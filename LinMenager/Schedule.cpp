#include "Schedule.h"

#include "WelcomePage.h"

Schedule::Schedule(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Time, diary, notification  window");

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
    connect(exitAppButton, &QPushButton::clicked, this, &Schedule::exitApp);

    menuButton = new QPushButton("Go back to menu..", this);//go to welcome page
    menuButton->setFont(font);
    menuButton->setGeometry(x_pos, y_pos, 300, 60);
    connect(menuButton, &QPushButton::clicked, this, &Schedule::backToMenu);//if clicked, go back to welcome page

    //Etiquette to show date and time
    dateTimeLabel = new QLabel(this);
    dateTimeLabel->setFont(font_status);
    dateTimeLabel->setGeometry(20, 20, 350, 50);
    dateTimeLabel->setStyleSheet("color: white; background-color: rgba(0, 0, 0, 150); border-radius: 10px;");
    dateTimeLabel->setAlignment(Qt::AlignCenter);

    //Time rto actualise hour
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Schedule::updateDateTime);
    timer->start(1000);//refresh by each 1 sec
    updateDateTime();//set beginning data

    //dairy initialisation
    calendar = new QCalendarWidget(this);
    calendar->setGeometry(20, 100, 350, 350);
    calendar->setStyleSheet("background-color: white; border-radius: 10px;");
    calendar->setGridVisible(true);//turn on grid between days
    calendar->setNavigationBarVisible(true);//navigation bar in months changing
    calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);//hide weeks numbers
    calendar->setHorizontalHeaderFormat(QCalendarWidget::NoHorizontalHeader);//hide weeks numbers
}

void Schedule::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, background);//Background
    QWidget::paintEvent(event);
}

void Schedule::exitApp()
{
    this->close();
}
void Schedule::backToMenu()//go back to welcome page
{
    WelcomePage *WelPage = new WelcomePage();
    WelPage->show();//display Welcome Page
    this->close();//close this page
}

void Schedule::updateDateTime()//actualise by each 1 sec
{
    dateTimeLabel->setText(QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss"));
}
