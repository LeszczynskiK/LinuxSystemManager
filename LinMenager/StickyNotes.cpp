#include "StickyNotes.h"

#include "WelcomePage.h"

StickyNotes::StickyNotes(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Sticky notes window");

    const int x =1280;//x window size
    const int y=720;//y window size

    setFixedSize(x, y);//Set window size
    //Background image
    background = QPixmap("/home/krzysiek89/Desktop/QT_aplikacje/LinuxManager/LinMenager/AllPages.png").scaled(x, y);


    QFont font;
    font.setPointSize(19);//Font size - beginning initialization

    QFont font_status;
    font_status.setPointSize(25);


    //Initialize buttons
    int x_pos=20;
    int y_pos = 560;
    int y_siz =80;

    exitAppButton = new QPushButton("Exit app...", this);//exit app
    exitAppButton->setFont(font);
    exitAppButton->setGeometry(x_pos, y_pos+y_siz, 300, 60);
    connect(exitAppButton, &QPushButton::clicked, this, &StickyNotes::exitApp);

    menuButton = new QPushButton("Go back to menu..", this);//go back to welcome page
    menuButton->setFont(font);
    menuButton->setGeometry(x_pos, y_pos, 300, 60);
    connect(menuButton, &QPushButton::clicked, this, &StickyNotes::backToMenu);

    addStickyNoteButton = new QPushButton("Add Sticky Note", this);//button to add a sticky note
    addStickyNoteButton->setFont(font);
    addStickyNoteButton->setGeometry(x_pos + 330, y_pos, 300, 60);
    connect(addStickyNoteButton, &QPushButton::clicked, this, &StickyNotes::addStickyNote);
}

void StickyNotes::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, background);//Background
    QWidget::paintEvent(event);
}

void StickyNotes::exitApp()
{
    this->close();
}
void StickyNotes::backToMenu()//go back to welcome page
{
    WelcomePage *WelPage = new WelcomePage();
    WelPage->show();//display Welcome Page
    this->close();//close this page
}

void StickyNotes::addStickyNote() {

    int baseX = 50;
    int baseY = 50;
    int offsetX = 250;

    int index = 0;//number of note
    bool found = false;//sticky note is found?
    while (!found) {//if not found
        //check if there is a sticky note
        int posX = baseX + index * offsetX;//check position of sticky note number index
        bool isOccupied = false;//is this place taken by sticky note number index?

        for (QWidget *note : stickyNotes) {//iterate throw all of the sticky notes
            if (note->geometry().x() == posX) {//if position counter by posX is equal to real position of cticky note
                //means that there is sticky note
                isOccupied = true;//so change bool variable to true, becouse there is a sticky note
                break;
            }
        }

        if(!isOccupied){//if position not taken by sticky card
            QWidget *note = new QWidget(this); //create a new sticky note
            note->setStyleSheet("background-color: yellow; border: 1px solid black;");
            note->setGeometry(posX, baseY, 250, 250);//positioning new sticky notes dynamically

            QTextEdit *textEdit = new QTextEdit(note);//add QText widget inside sticky note view
            textEdit->setGeometry(10, 10, 230, 230);
            textEdit->setStyleSheet("Color: black;");

            QPushButton *closeButton = new QPushButton("Close", note);//close button to close actual sticky note
            closeButton->setStyleSheet("Color: black;");
            closeButton->setGeometry(10, 205, 230, 35);

            connect(closeButton, &QPushButton::clicked, this, [=]() {//if clicked, run lambda function which will remove sticky note
                // = - with this it will remember copy of note, so even if lambda function is addStickyNote(main function)
                //is over, lambda function will still remember note value, which has to put to removeStickyNote
                //as an argument (this exact note - co = will remember note)
                removeStickyNote(note);
            });

            note->show();
            stickyNotes.append(note);//keep the new note in the vector
            found=true;
        }
        index++;//change number of currently checked position(index is number of card)
    }
}

void StickyNotes::removeStickyNote(QWidget *noteToRemove) {
    stickyNotes.removeOne(noteToRemove); // remove note from the vector
    noteToRemove->deleteLater(); // delete the note safely
}

