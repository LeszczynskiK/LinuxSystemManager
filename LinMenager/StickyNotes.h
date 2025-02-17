#ifndef STICKYNOTES_H
#define STICKYNOTES_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QTextEdit>
#include <QPainter>
#include <QPaintEvent>
#include <QVector>

class StickyNotes : public QWidget {
    Q_OBJECT

private slots:
    void paintEvent(QPaintEvent *event);//background setter
    void exitApp();
    void backToMenu();//go back to welcome page
    void addStickyNote();//add new sticky note
    void removeStickyNote(QWidget *noteToRemove);//delete sticky note(the exact one)

public:
    StickyNotes(QWidget *parent = nullptr);

private:
    QPixmap background;//Background txt
    QPushButton *exitAppButton;
    QPushButton *menuButton;//go to welcome page button
    QPushButton *addStickyNoteButton;//add sticky note button
    QVector<QWidget*> stickyNotes;//vector to hold sticky notes widgets
};

#endif // STICKYNOTES_H
