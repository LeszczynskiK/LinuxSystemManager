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
#include <QScrollArea>
#include <QHBoxLayout>
#include <QFile>
#include <QTextStream>


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
    QHBoxLayout *layout;//scrollable layout for notes
    QWidget *scrollWidget;//scroll widget object
    void saveNotes();//save notes to .txt file
    void loadNotes();//load saved notes from txt files

    QString notesFilePath = "sticky_notes.txt";//name of .txt file where notes body will be saved
    //if not exist, it will be created in directory where app is being runned
};

#endif // STICKYNOTES_H
