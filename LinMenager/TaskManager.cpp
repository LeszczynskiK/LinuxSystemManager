#include "TaskManager.h"

#include "WelcomePage.h"

TaskManager::TaskManager(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Task manager window");

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
    connect(exitAppButton, &QPushButton::clicked, this, &TaskManager::exitApp);

    menuButton = new QPushButton("Go back to menu..", this);//go back to welcome page
    menuButton->setFont(font);
    menuButton->setGeometry(x_pos, y_pos, 300, 60);
    connect(menuButton, &QPushButton::clicked, this, &TaskManager::backToMenu);//if clicked, go back to welcome page


    //Text display to show the list of processes
    processList = new QTextEdit(this);
    processList->setGeometry(20, 100, 1240, 400);
    processList->setReadOnly(true);
    processList->setFont(font);

    //Button to refresh the process list
    refreshButton = new QPushButton("Refresh process list", this);
    refreshButton->setFont(font);
    refreshButton->setGeometry(330, y_pos+y_siz, 300, 60);
    connect(refreshButton, &QPushButton::clicked, this, &TaskManager::refreshProcessList);

    //Field to type PID number
    pidInput = new QLineEdit(this);
    pidInput->setFont(font);
    pidInput->setGeometry(950, y_pos+y_siz, 200, 60);
    pidInput->setPlaceholderText("Enter PID...");

    //Button to kill the selected process
    killProcessButton = new QPushButton("Kill selected process", this);
    killProcessButton->setFont(font);
    killProcessButton->setGeometry(640, y_pos+y_siz, 300, 60);
    connect(killProcessButton, &QPushButton::clicked, this, &TaskManager::killSelectedProcess);

    refreshProcessList();
}

void TaskManager::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, background);//Background
    QWidget::paintEvent(event);
}

void TaskManager::exitApp()
{
    this->close();
}
void TaskManager::backToMenu()//go back to welcome page
{
    WelcomePage *WelPage = new WelcomePage();
    WelPage->show();//display Welcome Page
    this->close();//close this
}

void TaskManager::refreshProcessList() {

    processList->clear();//clear text list


    QProcess process;//qprocess to execute linux command
    process.start("/bin/sh", QStringList() << "-c" << "ps aux");


    if (!process.waitForFinished()) {
        processList->setText("Failes to run ps aux");
        return;
    }

    QString output(process.readAllStandardOutput());//read output of called command to show tasks


    if (output.isEmpty()) {//show data from ps aux result
        processList->setText("No data from ps aux..");
    } else {
        processList->setPlainText(output);
    }
}

void TaskManager::killSelectedProcess() {
    bool ok;
    int processId = pidInput->text().toInt(&ok);//get number from PID field of QLineType

    if (!ok || processId <= 0) {//if transformation to int failed or PID id <0
        processList->setText("Invalid PID! Enter a correct number.");
        return;
    }

    QProcess::execute("kill", QStringList() << QString::number(processId));
    processList->setText("Process " + QString::number(processId) + " killed.");
}


