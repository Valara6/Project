#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "second.h"
#include <QComboBox>
#include <QString>
#include <QStringList>
#include <QDesktopServices>
#include <QUrl>
#include <QGuiApplication>
#include <QScreen>
#include <QMessageBox>
#include "singletonsocket.h"
#include <QTimer>
MainWindow* MainWindow::m_instance = nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();

    SingletonSocket::instance();
    // вычисляем координаты центра экрана
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
    connect(SingletonSocket::instance()->getSocket(), &QTcpSocket::connected, this, &MainWindow::on_connected);
    connect(SingletonSocket::instance()->getSocket(), &QTcpSocket::disconnected, this, &MainWindow::on_disconnected);
    connect(SingletonSocket::instance(), &SingletonSocket::messageReceived, this, &MainWindow::on_readyRead);
    connect(ui->password, &QLineEdit::editingFinished, this, &MainWindow::onPasswordEditingFinished);
    connect(ui->password, &QLineEdit::textChanged, this, &MainWindow::checkPasswordMatch);
    connect(ui->verpassword, &QLineEdit::textChanged, this, &MainWindow::checkPasswordMatch);


    // Connect to the server


    setWindowFlags(Qt::FramelessWindowHint);
    setStyleSheet("background-color: transparent;");
    setAttribute(Qt::WA_TranslucentBackground);
    show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::checkPasswordMatch()
{
    QLineEdit* passwordLineEdit = ui->password;
    QLineEdit* confirmLineEdit = ui->verpassword;

    if (passwordLineEdit->text() != confirmLineEdit->text()) {

        confirmLineEdit->setStyleSheet("QLineEdit { border-bottom:2px solid rgba(255,0,0,1); }");
    } else {
        passwordLineEdit->setStyleSheet("QLineEdit { border-bottom:2px solid rgba(46,82,101,200); }");
        confirmLineEdit->setStyleSheet("QLineEdit { border-bottom:2px solid rgba(46,82,101,200); }");
    }
}
void MainWindow::onPasswordEditingFinished()
{
    QLineEdit* passwordLineEdit = ui->password;
    QLineEdit* confirmLineEdit = ui->verpassword;

    if (passwordLineEdit->text().isEmpty()) {
        // Если первое поле ввода пустое, вывести сообщение об ошибке
        QMessageBox::warning(this, tr("Ошибка"), tr("Пожалуйста, введите пароль"));
        passwordLineEdit->setFocus(); // Установить фокус на первое поле ввода
        confirmLineEdit->setDisabled(true); // Заблокировать второе поле ввода
    } else {
        confirmLineEdit->setDisabled(false); // Разблокировать второе поле ввода
        confirmLineEdit->setFocus(); // Установить фокус на второе поле ввода
    }
}
MainWindow* MainWindow::instance()
{
    if (m_instance == nullptr)
        m_instance = new MainWindow();
    return m_instance;
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->name->text().simplified().isEmpty())
    {
        ui->message->setStyleSheet("color: red;");
        ui->message->setText("Заполните поля имя");
        QTimer::singleShot(5000, [=]() {
                ui->message->setText("");
            });
        return;
    }
    if (ui->email->text().simplified().isEmpty())
    {
        ui->message->setStyleSheet("color: red;");
        ui->message->setText("Заполните поля логин");
        QTimer::singleShot(5000, [=]() {
                ui->message->setText("");
            });
        return;
    }
    if (ui->password->text().simplified().isEmpty())
    {
        ui->message->setStyleSheet("color: red;");
        ui->message->setText("Заполните поля пароля");
        QTimer::singleShot(5000, [=]() {
                ui->message->setText("");
            });
        return;
    }
    if (ui->verpassword->text().simplified().isEmpty())
    {
        ui->message->setStyleSheet("color: red;");
        ui->message->setText("Заполните поля подтверждения пароля");
        QTimer::singleShot(5000, [=]() {
                ui->message->setText("");
            });
        return;
    }
    if(!ui->srudent->isChecked() and !ui->teacher->isChecked())
    {
        ui->message->setStyleSheet("color: red;");
        ui->message->setText("Не выбран роль");
        QTimer::singleShot(5000, [=]() {
                ui->message->setText("");
            });
        return;
    }
    QString name = ui->name->text();
    QString email = ui->email->text();
    QString password = ui->password->text();
    QString verpassword = ui->verpassword->text();
    QString radioButtonValue;

    if(ui->srudent->isChecked())
    {
        radioButtonValue = "Student";
    }
    else if(ui->teacher->isChecked())
    {
        radioButtonValue = "Teacher";
    }

    QString message = "registration$" + name + "$" + email + "$" + password + "$" + verpassword + "$" + radioButtonValue+"\r\n";
    ui->name->clear();
    ui->email->clear();
    ui->password->clear();
    ui->verpassword->clear();
    ui->srudent->setAutoExclusive(false); // добавить эту строку
    ui->srudent->setChecked(false);
    ui->srudent->setAutoExclusive(true); // добавить эту строку
    ui->teacher->setAutoExclusive(false); // добавить эту строку
    ui->teacher->setChecked(false);
    ui->teacher->setAutoExclusive(true); // добавить эту строку
    SingletonSocket::instance()->getSocket()->write(message.toUtf8());


}

void MainWindow::on_vkbutton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.vk.com/"));
}

void MainWindow::on_twitterbutton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.twitter.com/"));
}

void MainWindow::on_telegrambutton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.telegram.org/"));
}

void MainWindow::on_youtubebutton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.youtube.com/"));
}

void MainWindow::on_gitbutton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.github.com/"));
}

void MainWindow::on_connected()
{
    qDebug() << "Connected";
}

void MainWindow::on_disconnected()
{
    qDebug() << "Disconnected";
}

void MainWindow::on_readyRead(const QString& message, const QString& windowName)
{
    if(windowName=="reg"){
    if(message=="User successfully inserted")
    {
        this->hide();
        second::instance()->show();
        ui->message->clear();
    }
    else{
    ui->message->setStyleSheet("color: red;");
    ui->message->setText(message);
    QTimer::singleShot(5000, [=]() {
            ui->message->setText("");
        });
    }
    }
}



void MainWindow::on_clicktologin_clicked()
{
         // Скрыть MainWindow


        // Скрываем MainWindow
    this->hide();
    second::instance()->show();
}


void MainWindow::on_closebutton_clicked()
{

    this->close();
}

