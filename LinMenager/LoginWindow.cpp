#include "LoginWindow.h"

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Login window");

    const int x =1280;//x window size
    const int y=720;//y window size

    setFixedSize(x, y);//Set window size
    //Background image
    background = QPixmap("/home/krzysiek89/Desktop/QT_aplikacje/LinuxManager/LinMenager/LoginPage.png").scaled(x, y);


    QFont font;
    font.setPointSize(19);//Font size - beginning initialization

    QFont font_status;
    font_status.setPointSize(25);

    //Text inputs (login and password)
    loginInput = new QLineEdit(this);//login
    loginInput->setGeometry(30, 120, 500, 60);
    loginInput->setFont(font);
    loginInput->setPlaceholderText("Enter login");

    passwordInput = new QLineEdit(this);//password
    passwordInput->setGeometry(30, 200, 500, 60);
    passwordInput->setFont(font);
    passwordInput->setPlaceholderText("Enter password");
    passwordInput->setEchoMode(QLineEdit::Password);//dont show password, show only *****


    //login status(logged or not)
    statusLogin = new QLabel("Not logged...", this);
    statusLogin->setFont(font_status);
    statusLogin->setStyleSheet("color: yellow;");
    statusLogin->setGeometry(10, 30, 650, 70);

    //Initialize buttons
    int x_pos=20;
    int y_pos = 450;
    int y_siz =80;
    login_to_session_button = new QPushButton("Login to app...", this);//login to app
    login_to_session_button->setFont(font);
    login_to_session_button->setGeometry(x_pos, y_pos, 300, 60);
    connect(login_to_session_button, &QPushButton::clicked, this, &LoginWindow::handleLoginAttempt);

    turn_on_button = new QPushButton("Turn on app...", this);//turn on app
    turn_on_button->setFont(font);
    turn_on_button->setGeometry(x_pos, y_pos+y_siz, 300, 60);
    turn_on_button->setVisible(false);//if login and password are not ok, button is not visible
    connect(turn_on_button, &QPushButton::clicked, this, &LoginWindow::openApp);//if clicked, open main page of app

    exit_button = new QPushButton("Exit app...", this);//leave from app
    exit_button->setFont(font);
    exit_button->setGeometry(x_pos, y_pos+2*y_siz, 300, 60);
    connect(exit_button, &QPushButton::clicked, this, &LoginWindow::exitApp);

}

void LoginWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, background);//Background
    QWidget::paintEvent(event);
}

QString LoginWindow::hashPassword(const QString &password) {

    //Hash the password using SHA-256
    return QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
}

QString LoginWindow::hashLogin(const QString &login) {

    //Hash the login using SHA-256
    return QString(QCryptographicHash::hash(login.toUtf8(), QCryptographicHash::Sha256).toHex());
}

void LoginWindow::handleLoginAttempt() {//check correctivity of typped data...
    userLogin = loginInput->text();
    userPassword = passwordInput->text();


    //predefined hashed password
    QString hashedCorrectPassword = hashPassword("123");
    QString hashedCorrectLogin = hashLogin("admin");


    if (hashLogin(userLogin) == hashedCorrectLogin && hashPassword(userPassword) == hashedCorrectPassword) {//check validation of login and password
        isLoggedIn = true;//let login - bool variable
        statusLogin->setText("Login successful! Ready to proceed...");//new status of data
        turn_on_button->setVisible(true);
    } else {
        isLoggedIn = false;//deny login - frong data written
        statusLogin->setText("Incorrect login or password. Try again.");//new status of data
        turn_on_button->setVisible(false);
    }
}

void LoginWindow::exitApp()
{
    this->close();//turn off app...
}

void LoginWindow::openApp()
{
    if (isLoggedIn) {//go to manager window

        WelcomePage *WelPage = new WelcomePage();
        WelPage->show();//display Welcome Page
        this->close();//close authorisation page
    }
}
