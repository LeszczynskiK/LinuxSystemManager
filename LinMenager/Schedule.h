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
#include <QDateEdit>
#include <QTimer>
#include <QCalendarWidget>
#include <QTimeEdit>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

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

    QString notificationFile = "notifications.txt";//url to .txt file where will be saved notifications saved to system
    //if not exist, it will be created in directory where app is being runned

    QTimeEdit *timeEdit;//to keep time of notifiction display
    QDateEdit *dateEdit;//to keep date of notification display
    QTextEdit *notificationText;//to put text of notification
    QPushButton *addNotificationButton;//button to add notification
    QList<QPair<QDateTime, QString>> notifications;//list of notification(pair of time+date and notification text)

    void saveNotificationsToFile();//save notification to .txt
    void loadNotificationsFromFile();//load notification from .txt file

};

#endif // SCHEDULE_H
