#ifndef NETMONITOR_H
#define NETMONITOR_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QTextEdit>
#include <QPainter>
#include <QPaintEvent>
#include <QProcess>
#include <QTimer>


//to net stats values getting from process results
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

class NetMonitor : public QWidget {
    Q_OBJECT

private slots:
    void paintEvent(QPaintEvent *event);//background setter
    void exitApp();
    void backToMenu();//go back to welcome page
    void updateNetworkStats();//test speed of internet with speedtest-cli

public:
    NetMonitor(QWidget *parent = nullptr);
private:
    QPixmap background;//Background txt
    QPushButton *exitAppButton;
    QPushButton *menuButton;//go to welcome page button
    QPushButton *refreshButton;//refresh net stats button
    QLabel *netSpeedLabel;// label to for network speed

};

#endif // NETMONITOR_H
