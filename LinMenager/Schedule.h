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

class Schedule: public QWidget {
    Q_OBJECT

private slots:
    void paintEvent(QPaintEvent *event);//background setter
    void exitApp();
    void backToMenu();//go back to welcome page

public:
    Schedule(QWidget *parent = nullptr);

private:
    QPixmap background;//Background txt
    QPushButton *exitAppButton;
    QPushButton *menuButton;//go to welcome page button
};

#endif // SCHEDULE_H
