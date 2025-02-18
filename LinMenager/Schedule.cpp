#include "Schedule.h"

#include "WelcomePage.h"

Schedule::Schedule(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Time, diary, notification  window");

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
    connect(exitAppButton, &QPushButton::clicked, this, &Schedule::exitApp);

    menuButton = new QPushButton("Go back to menu..", this);//go to welcome page
    menuButton->setFont(font);
    menuButton->setGeometry(x_pos, y_pos, 300, 60);
    connect(menuButton, &QPushButton::clicked, this, &Schedule::backToMenu);//if clicked, go back to welcome page

    //Etiquette to show date and time
    dateTimeLabel = new QLabel(this);
    dateTimeLabel->setFont(font_status);
    dateTimeLabel->setGeometry(20, 20, 350, 50);
    dateTimeLabel->setStyleSheet("color: white; background-color: rgba(0, 0, 0, 150); border-radius: 10px;");
    dateTimeLabel->setAlignment(Qt::AlignCenter);

    //Time rto actualise hour
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Schedule::updateDateTime);
    timer->start(1000);//refresh by each 1 sec
    updateDateTime();//set beginning data

    //dairy initialisation
    calendar = new QCalendarWidget(this);
    calendar->setGeometry(20, 100, 350, 350);
    calendar->setStyleSheet("background-color: white; border-radius: 10px;");
    calendar->setGridVisible(true);//turn on grid between days
    calendar->setNavigationBarVisible(true);//navigation bar in months changing
    calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);//hide weeks numbers
    calendar->setHorizontalHeaderFormat(QCalendarWidget::NoHorizontalHeader);//hide weeks numbers


    //notification values
    int y_start=150;
    int x_start=600;
    int text_y=250;
    int text_x=150+300;
    QFont fontTime;
    fontTime.setPointSize(19);
    QFont fontTextNot;
    fontTextNot.setPointSize(21);

    timeEdit = new QTimeEdit(this);//put time of notification
    timeEdit->setGeometry(x_start+20, y_start-20, 130,60);
    timeEdit->setDisplayFormat("HH:mm");//format of notification time is:Hour,minute
    timeEdit->setFont(fontTime);

    dateEdit = new QDateEdit(QDate::currentDate(), this);
    dateEdit->setGeometry(x_start-150, y_start-20, 170,60);
    dateEdit->setDisplayFormat("dd.MM.yyyy");//format of notification time is:Day,month,year
    dateEdit->setFont(fontTime);
    dateEdit->setCalendarPopup(true);//if clicked in dateEdit field, open calendar immediately to choose date...

    notificationText = new QTextEdit(this);
    notificationText->setGeometry(x_start-150, y_start+40, text_x+150, text_y+200);//field for text of notification
    notificationText->setFont(fontTextNot);

    addNotificationButton = new QPushButton("Add Notification", this);//button to add notification
    addNotificationButton->setGeometry(x_start+150, y_start-20, 300, 60);
    addNotificationButton->setFont(font);
    connect(addNotificationButton, &QPushButton::clicked, this, &Schedule::addNotification);

    loadNotificationsFromFile();//load saved notifications from .txt file
}



void Schedule::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, background);//Background
    QWidget::paintEvent(event);
}

void Schedule::exitApp()
{
    this->close();
}
void Schedule::backToMenu()//go back to welcome page
{
    WelcomePage *WelPage = new WelcomePage();
    WelPage->show();//display Welcome Page
    this->close();//close this page
}

void Schedule::updateDateTime()//actualise by each 1 sec
{
    dateTimeLabel->setText(QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss"));

    //Check if there is any notification connected with current time
    QDateTime currentDateTime = QDateTime::currentDateTime();//Date time value holder...

    for (int i = 0; i < notifications.size(); ++i) {//iterate throw list with notifications
        if (notifications[i].first.date() == currentDateTime.date() &&//if real date is equal to notification one
            notifications[i].first.time().hour() == currentDateTime.time().hour() &&//if current hour is equal to notification one
            notifications[i].first.time().minute() == currentDateTime.time().minute()) {//and the same with minutes..
            QMessageBox::information(this, "Notification", notifications[i].second);//.second part is notification text..
            notifications.removeAt(i);//removeAt - delete element At the position of i

            saveNotificationsToFile();//if notificaton displayed, remove it from .txt file...
            break;
        }
    }
}

void Schedule::addNotification() {
    QTime notificationTime = timeEdit->time();//get time from field
    QDate notificationDate = dateEdit->date();//get date from field
    QString notificationMessage = notificationText->toPlainText();//put to plain text value from notifivationText field and save as QString

    if (notificationMessage.isEmpty()) {//if empty message
        QMessageBox::warning(this, "Error", "Notification message cannot be empty.");//show error
        return;
    }

    //Add notification to list(pair of date+time and text)
    notifications.append(qMakePair(QDateTime(notificationDate, notificationTime), notificationMessage));
    notificationText->clear();//clear text field after adding

    saveNotificationsToFile();//save created notification to .txt file
}

void Schedule::loadNotificationsFromFile() {
    QFile file(notificationFile);//create QFile named file with the argument of url to .txt

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {//if opened in read and text mode
        QTextStream in(&file);//create QTextStream called in with the reference to file as argument
        while (!in.atEnd()) {//if we are not at the end on QTextStream
            QString line = in.readLine();//get line of in
            QStringList parts = line.split("|");//create list of string type and split elements(separator is | char)
            if (parts.size() == 2) {//if we have 2 elements in list(we have to have becouse we separate line on 2 parts)
                QDateTime dateTime = QDateTime::fromString(parts[0], "dd.MM.yyyy HH:mm");//first element is dateTime
                QString message = parts[1];//2nd element is message
                notifications.append(qMakePair(dateTime, message));//add to vector as pair these two separated by | elements
            }
        }
        file.close();//if end of QTextStream(iterated throw all lines), close file
    }
}

void Schedule::saveNotificationsToFile() {
    QFile file(notificationFile);//create QFile called file with the argument of url to .txt file

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {//if opened in write and text mode
        QTextStream out(&file);//create QTextStream variable called out, with the reference to file
        for (const auto &notification : notifications) {//iterate throw notifications vector(pair of dateTime and message)
            out << notification.first.toString("dd.MM.yyyy HH:mm") << "|" << notification.second << "\n";//and add to out file
            //all of the elements of pair , with separator between 1st and 2nd element(| as separator will be recognised in loading
            //to part the line to two fragments(1st is on tthe left of separator, 2nd is on the right of separator)
        }
        file.close();//if we are on the end of QTextStream, close file
    }
}

