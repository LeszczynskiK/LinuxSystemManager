#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QTextEdit>
#include <QPainter>
#include <QPaintEvent>
#include <QProcess>//linux proces library acces


class TaskManager : public QWidget {
    Q_OBJECT

private slots:
    void paintEvent(QPaintEvent *event);//background setter
    void exitApp();
    void backToMenu();//go back to welcome page
    void refreshProcessList();//refresh the process list
    void killSelectedProcess();//kill the selected process

public:
    TaskManager(QWidget *parent = nullptr);

private:
    QPixmap background;//Background txt
    QPushButton *exitAppButton;
    QPushButton *menuButton;//go to welcome page button
    QPushButton *refreshButton;//button to refresh process list
    QPushButton *killProcessButton;//button to kill the selected process
    QTextEdit *processList;//textEdit to display process list
    QLineEdit *pidInput;//field to type PID number
};

#endif // TASKMANAGER_H
