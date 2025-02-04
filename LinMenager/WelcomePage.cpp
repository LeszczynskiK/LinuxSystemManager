#include "WelcomePage.h"
#include "NetMonitor.h"
#include "Schedule.h"
#include "StickyNotes.h"
#include "SystemMonitor.h"
#include "TaskManager.h"

WelcomePage::WelcomePage(QWidget *parent) : QWidget(parent) {

    setWindowTitle("Client Window");

    const int x =1280;//x window size
    const int y=720;//y window size

    setFixedSize(x, y);//Set window size
    //Background image
    background = QPixmap("/home/krzysiek89/Desktop/QT_aplikacje/LinuxManager/LinMenager/ChooseMan.png").scaled(x, y);


    QFont font;
    font.setPointSize(19);//Font size

    int x_pos=30;
    int x_size=425;
    int y_pos=70;
    int y_size=80;
    int gap=20;

    systemMonitorDisplayButton = new QPushButton("System monitor", this);
    systemMonitorDisplayButton->setGeometry(x_pos, y_pos+0*gap+0*y_size, x_size, y_size);
    systemMonitorDisplayButton->setFont(font);
    connect(systemMonitorDisplayButton, &QPushButton::clicked, this, &WelcomePage::systemMonitor);

    netMonitorDisplayButton = new QPushButton("Net monitor", this);
    netMonitorDisplayButton->setGeometry(x_pos, y_pos+1*gap+1*y_size, x_size, y_size);
    netMonitorDisplayButton->setFont(font);
    connect(netMonitorDisplayButton, &QPushButton::clicked, this, &WelcomePage::netMonitoring);

    taskManagerButton = new QPushButton("Task manager", this);
    taskManagerButton->setGeometry(x_pos, y_pos+2*gap+2*y_size ,x_size, y_size);
    taskManagerButton->setFont(font);
    connect(taskManagerButton, &QPushButton::clicked, this, &WelcomePage::taskManager);

    calendarTimeRemindersButton = new QPushButton("Notifications, calendar and time", this);
    calendarTimeRemindersButton->setGeometry(x_pos, y_pos+3*gap+3*y_size, x_size, y_size);
    calendarTimeRemindersButton->setFont(font);
    connect(calendarTimeRemindersButton, &QPushButton::clicked, this, &WelcomePage::calendarTimeReminders);

    stickyNotesBoardButton = new QPushButton("Sticky notes", this);
    stickyNotesBoardButton->setGeometry(x_pos, y_pos+4*gap+4*y_size, x_size, y_size);
    stickyNotesBoardButton->setFont(font);
    connect(stickyNotesBoardButton, &QPushButton::clicked, this, &WelcomePage::stickyNotes);

    exitAppButton = new QPushButton("Exit app", this);
    exitAppButton->setGeometry(x_pos, y_pos+5*gap+5*y_size, x_size, y_size);
    exitAppButton->setFont(font);
    connect(exitAppButton, &QPushButton::clicked, this, &WelcomePage::exitApp);
}

void WelcomePage::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, background);//Background
    QWidget::paintEvent(event);
}


void WelcomePage::systemMonitor()//System Monitor Display CPU, RAM, and disk usage
{
    SystemMonitor *SysMon = new SystemMonitor();//create object of
    SysMon->show();//show system monitor page
    this->close();//close this

}

void WelcomePage::netMonitoring()//Monitor network activity (download/upload speed)
{
    NetMonitor *NetMon = new NetMonitor();//create object of
    NetMon->show();//show net monitoring page
    this->close();//close this
}


void WelcomePage::taskManager()//Task Manager - display and end running process
{
    TaskManager *TaskMan = new TaskManager();//create object of
    TaskMan->show();//show task manager page
    this->close();//close this
}


void WelcomePage::calendarTimeReminders()//Show calendar,time and enable do do reminders on any term
{
    Schedule *schedule = new Schedule();//create object of
    schedule->show();//show diary, time and schedule page
    this->close();//close this
}


void WelcomePage::stickyNotes()//Board with stcky notes(add and delete them from view and display)
{
    StickyNotes *stickNot = new StickyNotes();//create object of
    stickNot->show();//show sticky note page
    this->close();//close this
}


void WelcomePage::exitApp()//Quit linux manager app
{
    this->close();
}
