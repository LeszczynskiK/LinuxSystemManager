#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QTextEdit>
#include <QPainter>
#include <QPaintEvent>


class WelcomePage : public QWidget {
    Q_OBJECT

public:
    WelcomePage(QWidget *parent = nullptr);

private slots:
    void systemMonitor();//System Monitor Display CPU, RAM, and disk usage
    void netMonitoring();//Monitor network activity (download/upload speed)
    void taskManager();//Task Manager - display and end running process
    void calendarTimeReminders();//Show calendar,time and enable do do reminders on any term
    void stickyNotes();//Board with stcky notes(add and delete them from view and display)
    void exitApp();//Quit linux manager app

private:
    void paintEvent(QPaintEvent *event);//background setter
    QPixmap background;//Background txt

    //buttons to methods collocated to its name
    QPushButton *systemMonitorDisplayButton;
    QPushButton *netMonitorDisplayButton;
    QPushButton *taskManagerButton;
    QPushButton *calendarTimeRemindersButton;
    QPushButton *stickyNotesBoardButton;
    QPushButton *exitAppButton;

};

#endif // WELCOMEPAGE_H
