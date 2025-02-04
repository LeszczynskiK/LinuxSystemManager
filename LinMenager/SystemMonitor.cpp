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
    font_status.setPointSize(32);


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


    //Initialise etiquere for CPU, RAM and DISK usage
    cpuLabel = new QLabel("CPU: --%", this);
    cpuLabel->setFont(font_status);
    cpuLabel->setStyleSheet("color: yellow;");
    cpuLabel->setGeometry(50, 50, 400, 50);

    ramLabel = new QLabel("RAM: -- MB", this);
    ramLabel->setFont(font_status);
    ramLabel->setStyleSheet("color: yellow;");
    ramLabel->setGeometry(50, 120, 400, 50);

    diskLabel = new QLabel("Disk: --%", this);
    diskLabel->setFont(font_status);
    diskLabel->setStyleSheet("color: yellow;");
    diskLabel->setGeometry(50, 190, 400, 50);

    //Timer to actualise system data(RAM,DISC and CPU)
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &SystemMonitor::updateSystemInfo);
    updateTimer->start(2000);//catt updateSystemInfo function after each 2 sec

    updateSystemInfo();//download data for start display
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

void SystemMonitor::updateSystemInfo() {
    QProcess process;//System proces object

    //Download CPU usage
    process.start("bash", QStringList() << "-c" << "top -bn1 | grep 'Cpu(s)' | awk '{print $2}'");
    //"bash" start bash to execute code of instruction
    //-c pass this command as a string for bash to execute only onece and informt to execute rest of code
    //top - tasks manager, -b bash mode, -n update the top 1 times,
    //grep is to look for 'Cpu(s) phrase,
    //awk will print 2nd variable from line of top
    //this is all based on linux command

    process.waitForFinished();//wait for process.start.... command finish
    QString cpuUsage = process.readAllStandardOutput().trimmed();//read all of the output from the process and delete white chars
    cpuLabel->setText("CPU: " + cpuUsage + "%");//put this as a text(label format)

    //Download RAM usage
    process.start("bash", QStringList() << "-c" << "free -m | awk 'NR==2{printf \"%s/%s MB\", $3,$2}'");
    //-c pass this command as a string for bash to execute only onece and informt to execute rest of code
    //-free is usage of memory , -b bash mode, -n update the top 1 times,
    //awk will print this in ' '
    //%s is string type
    //&3 and %2 means 3rd and 2nd column in free command result line

    process.waitForFinished();//wait for process.start.... command finish
    QString ramUsage = process.readAllStandardOutput().trimmed();//read all of the output from the process and delete white chars
    ramLabel->setText("RAM: " + ramUsage);//put this as a text(label format)

    //Download disc usage
    process.start("bash", QStringList() << "-c" << "df -h | grep '/$' | awk '{print $5}'");
    //"bash" start bash to execute code of instruction
     //-c pass this command as a string for bash to execute only onece and informt to execute rest of code
    //df - disc free display, h means in human friendly format display
    // grep '/$" means that we are looking for row ending with /
    //and tren print 5th value of this row(5th argument)

    process.waitForFinished();//wait for process.start.... command finish
    QString diskUsage = process.readAllStandardOutput().trimmed();//read all of the output from the process and delete white chars
    diskLabel->setText("Disk: " + diskUsage);//put this as a text(label format)
}
