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

   //scrollable area to see all sticky notes added
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setGeometry(0, 100, 1280, 320);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//horisontal scroll on for notes scrolling area
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//vertical scroll off for notes scrolling area

    scrollWidget = new QWidget();//create widget to keep all notes inside to make it scrollable
    scrollWidget->setFixedHeight(320);//constant height for notes

    //set layout for notes
    layout = new QHBoxLayout(scrollWidget);//make organised layout to keep notes
    layout->setSpacing(10);//space between notes

    scrollWidget->setLayout(layout);//scrollwidget is based on QHBoxLayout
    scrollArea->setWidget(scrollWidget);//scrollable area is made of scrollDidgets(aka notes)
    scrollArea->setWidgetResizable(false);//const size of notes


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

    loadNotes();//load saved in .txt file notes
}

void StickyNotes::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, background);//Background
    QWidget::paintEvent(event);
}

void StickyNotes::exitApp()
{
    saveNotes();//save notes before closing app
    this->close();
}
void StickyNotes::backToMenu()//go back to welcome page
{
    saveNotes();//save notes before goint back to main menu
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
            QWidget *note = new QWidget(scrollWidget); //create a new sticky note
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

            layout->addWidget(note);//add card to scrollable layout
            note->show();
            stickyNotes.append(note);//keep the new note in the vector
            found=true;

            //actualise size of scrollable area (based on notes amount and its sizes) -> only for increasing amount of notes
            int totalWidth = (stickyNotes.size() * (250 + layout->spacing())) + layout->spacing();
            scrollWidget->setFixedWidth(totalWidth);
        }
        index++;//change number of currently checked position(index is number of card)
    }
}

void StickyNotes::removeStickyNote(QWidget *noteToRemove) {
    stickyNotes.removeOne(noteToRemove); // remove note from the vector
    layout->removeWidget(noteToRemove);//delete note from scrollable area
    noteToRemove->deleteLater(); // delete the note safely


    //actualise size-> is notes deletes, actualise size of scrollable area..
    int totalWidth = (stickyNotes.size() * (250 + layout->spacing())) + layout->spacing();
    scrollWidget->setFixedWidth(totalWidth);
}

void StickyNotes::loadNotes() {
    QFile file(notesFilePath);//create file object with the url of notesFilePath
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {//file open in read only mode in text type
        QTextStream in(&file);//make qtextstream object called in, with the argument of file(reference becouse want to work on original file)
        while (!in.atEnd()) {//while file is not over
            QString content = in.readLine();//get line(one line is one note body)

            if (!content.isEmpty()) {//if loaded line is not empty
                QWidget *note = new QWidget(scrollWidget);//create new note with classic settings(like below note->)
                note->setStyleSheet("background-color: yellow; border: 1px solid black;");
                note->setGeometry(50 + stickyNotes.size() * 250, 50, 250, 250);

                QTextEdit *textEdit = new QTextEdit(note);//if we want full note, we need to create empty rectangle with no messahe so far
                textEdit->setGeometry(10, 10, 230, 230);
                textEdit->setStyleSheet("Color: black;");
                textEdit->setText(content);//we write downloaded message(line) to empty (so far) textEdit place

                QPushButton *closeButton = new QPushButton("Close", note);//add close button to make note(text place + button)
                closeButton->setStyleSheet("Color: black;");
                closeButton->setGeometry(10, 205, 230, 35);

                connect(closeButton, &QPushButton::clicked, this, [=]() {
                    removeStickyNote(note);
                });//connect functionality (removing note) to button closeButtn

                layout->addWidget(note);//add to scrollable layout out fully created note(buton, text etc)
                note->show();//show note
                stickyNotes.append(note);//add to vector collecting notes

                //to count total lenght of widget: stickyNotes.size() is amount of notes in vector, 20 is width of note,
                //layout->spacing is space between notes(here is equal to 10), and to leave small gap at the end
                //we add last space to the totalWidth
                int totalWidth = (stickyNotes.size() * (250 + layout->spacing())) + layout->spacing();

                scrollWidget->setFixedWidth(totalWidth);//if any next note is added, change size of scrollable widget
            }
        }
        file.close();//if we are on the end of file with notes text, close file
    }
}

void StickyNotes::saveNotes() {
    QFile file(notesFilePath);//create QFile instance with the url to .txt file as argument
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {//open .txt file in write and text mode
        QTextStream out(&file);//create QTextStream called out, with the reference to file
        for (QWidget *note : stickyNotes) {//iterate throw all of the stickyNotes (type is QWidget)
            QTextEdit *textEdit = note->findChild<QTextEdit *>();//look for child-> note is QWidget which has QTextEdit as child,
            //so is QTextEdit is child of note here, it will find QTextEdit and will save it as textEdit variable(pointer type)

            if (textEdit) {//if textEdit exist
                out << textEdit->toPlainText() << "\n";//save text to .txt file and separate each note's text by new line
            }
        }
        file.close();//if there are no more notes, close file
    }
}


