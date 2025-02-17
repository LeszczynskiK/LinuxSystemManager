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
    int x_size=360;

    exitAppButton = new QPushButton("Exit app...", this);//exit app
    exitAppButton->setFont(font);
    exitAppButton->setGeometry(x_pos, y_pos+y_siz, x_size, 60);
    connect(exitAppButton, &QPushButton::clicked, this, &NetMonitor::exitApp);

    menuButton = new QPushButton("Go back to menu..", this);//go to welcome page
    menuButton->setFont(font);
    menuButton->setGeometry(x_pos, y_pos, x_size, 60);
    connect(menuButton, &QPushButton::clicked, this, &NetMonitor::backToMenu);//if clicked, go back to welcome page

    refreshButton = new QPushButton("Refresh network stats..", this);//go to welcome page
    refreshButton->setFont(font);
    refreshButton->setGeometry(x_pos, y_pos-y_siz, x_size, 60);
    connect(refreshButton, &QPushButton::clicked, this, &NetMonitor::updateNetworkStats);//if clicked, go back to welcome page

    //network speed label
    netSpeedLabel = new QLabel(this);
    netSpeedLabel->setFont(font_status);
    netSpeedLabel->setStyleSheet("color: yellow;");
    netSpeedLabel->setGeometry(20,1,900,200);
    netSpeedLabel->setText("Click the button to check...");//if button is not clicked, show this, and later on it will be replaced
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

void NetMonitor::updateNetworkStats()
{
    netSpeedLabel->setText("Waiting for measurement to finish...");//information about the process(measuring is progressing)

    qDebug() << "Wait for result...";

    QProcess *updateProcess = new QProcess(this);//create process object
    connect(updateProcess, &QProcess::finished, this, [this, updateProcess]() {//lambda function - if proces finished

        qDebug() << "Speedtest-cli updated, starting network stats...";//run speedtest-cli

        //Create process for speedtest
        QProcess *process = new QProcess(this);

        //Connect signals for process execution
        connect(process, &QProcess::started, this, []() {//if proces started, inform
            qDebug() << "Process started.";
        });

        connect(process, &QProcess::errorOccurred, this, [](QProcess::ProcessError error) {//if error ocured-inform
            qDebug() << "Process error: " << error;
        });

        connect(process, &QProcess::finished, this, [this, process]() {//if proces finishedd
            QString output = process->readAllStandardOutput();//Read output from process
            qDebug() << "Output: " << output;

            QJsonDocument jsonDoc = QJsonDocument::fromJson(output.toUtf8());//parse data from json format file
            if (!jsonDoc.isNull() && jsonDoc.isObject()) {//if json exist
                QJsonObject jsonObj = jsonDoc.object();//put this to json type object

                //Check if expected data is available
                if (jsonObj.contains("download") && jsonObj.contains("upload") && jsonObj.contains("ping")) {//contain needed values?

                    //put to variable and convert
                    double downloadSpeed = jsonObj["download"].toDouble() / 1000000; //Mbps (bit/s to Mbit/s)
                    double uploadSpeed = jsonObj["upload"].toDouble() / 1000000; //Mbps
                    double ping = jsonObj["ping"].toDouble(); // ms

                    //update label with network speed
                    netSpeedLabel->setText(QString("Download: %1 Mbps\nUpload: %2 Mbps\nPing: %3 ms")
                                               .arg(downloadSpeed, 0, 'f', 2)
                                               .arg(uploadSpeed, 0, 'f', 2)
                                               .arg(ping, 0, 'f', 2));
                } else {
                    netSpeedLabel->setText("Error: No speed or ping data.");//if any data not exist, put status to label
                }
            } else {
                netSpeedLabel->setText("Error: Invalid data format.");//put status to label if error
            }

            process->deleteLater();//delete current process after finishing(to make possible check net stats again)
        });

        //Execute speedtest-cli
        process->start("sh", QStringList() << "-c" << "speedtest-cli --json");//execute in sh - shell
        //with -c -> give single line to execute(full command as argument given without this it would wait for input)
        //run speedtest-cli and show in json file extention

        // Clean up the update process
        updateProcess->deleteLater();
    });

    // Run the update process
    updateProcess->start("sh", QStringList() << "-c" << "sudo apt update speedtest-cli");//update library to avoid errors with
    // older version of net stats checking - need the newest one!
}








