#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QTextEdit>
#include <QPainter>
#include <QPaintEvent>
#include <QDateTime>
#include <QTimer>
#include <QCalendarWidget>
#include <QTimeEdit>
#include <QMessageBox>

class Schedule: public QWidget {
    Q_OBJECT

private slots:
    void paintEvent(QPaintEvent *event);//background setter
    void exitApp();
    void backToMenu();//go back to welcome page
    void updateDateTime();//to actualise data and time
    void addNotification();//add notifiction method

public:
    Schedule(QWidget *parent = nullptr);

private:
    QPixmap background;//Background txt
    QPushButton *exitAppButton;
    QPushButton *menuButton;//go to welcome page button
    QLabel *dateTimeLabel;//Etiquete to display time and data
    QCalendarWidget *calendar;//Calendar widget

    QTimeEdit *timeEdit;//to keep time of notifiction display
    QTextEdit *notificationText;//to put text of notification
    QPushButton *addNotificationButton;//button to add notification
    QList<QPair<QTime, QString>> notifications;//list of notification(pair of time and notification text)
};

#endif // SCHEDULE_H
