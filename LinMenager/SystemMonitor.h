#ifndef SYSTEMMONITOR_H
#define SYSTEMMONITOR_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QTextEdit>
#include <QPainter>
#include <QPaintEvent>
#include <QProcess>//system proces download with it is possible
#include <QTimer>

class SystemMonitor : public QWidget {
    Q_OBJECT

private slots:
    void paintEvent(QPaintEvent *event);//background setter
    void exitApp();
    void backToMenu();//go back to welcome page
    void updateSystemInfo();//to download system data(CPU,Disc and ram usage)


public:
    SystemMonitor(QWidget *parent = nullptr);

private:
    QPixmap background;//Background txt
    QPushButton *exitAppButton;
    QPushButton *menuButton;//go to welcome page button
    QLabel *cpuLabel;//CPU usage label
    QLabel *ramLabel;//RAM usage label
    QLabel *diskLabel;//Disk usage label
    QTimer *updateTimer;//Timer to refresh downloaded data
};

#endif // SYSTEMMONITOR_H
