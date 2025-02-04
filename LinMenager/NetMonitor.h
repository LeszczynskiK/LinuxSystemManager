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

class NetMonitor : public QWidget {
    Q_OBJECT

private slots:
    void paintEvent(QPaintEvent *event);//background setter
    void exitApp();
    void backToMenu();//go back to welcome page
    void updateNetworkStats();//update network statistics

public:
    NetMonitor(QWidget *parent = nullptr);
private:
    QPixmap background;//Background txt
    QPushButton *exitAppButton;
    QPushButton *menuButton;//go to welcome page button
    QLabel *netSpeedLabel;// label to for network speed
    QTimer *timerNet;//timer connected do updateNetworkStats

};

#endif // NETMONITOR_H
