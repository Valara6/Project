#include "ui_second.h"
#include "second.h"
#include "mainwindow.h"
#include "task_window.h"
#include "teachermod.h"
#include <QComboBox>
#include <QString>
#include <QStringList>
#include <QDesktopServices>
#include <QUrl>
#include <QGuiApplication>
#include <QScreen>
#include "singletonsocket.h"
#include <QTimer>

second* second::m_instance = nullptr;

second::second(QWidget *parent) :
    QMainWindow(parent),
    ui2(new Ui::second)

{
    ui2->setupUi(this);
    QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();

    SingletonSocket::instance();
    // вычисляем координаты центра экрана
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
    connect(SingletonSocket::instance()->getSocket(), &QTcpSocket::connected, this, &second::on_connected);
    connect(SingletonSocket::instance()->getSocket(), &QTcpSocket::disconnected, this, &second::on_disconnected);
    connect(SingletonSocket::instance(), &SingletonSocket::messageReceived, this, &second::on_readyRead);
    // Connect to the server


    setWindowFlags(Qt::FramelessWindowHint);
    setStyleSheet("background-color: transparent;");
    setAttribute(Qt::WA_TranslucentBackground);
    show();
}

second::~second()
{
    delete ui2;
}

second* second::instance()
{
    if (m_instance == nullptr)
        m_instance = new second();
    return m_instance;
}

void second::on_pushButton_clicked()
{
    if (ui2->nameoremail->text().simplified().isEmpty())
    {
        ui2->message->setStyleSheet("color: red;");
        ui2->message->setText("Заполните поля логина");
        QTimer::singleShot(5000, [=]() {
                ui2->message->setText("");
            });
        return;
    }
    if (ui2->password->text().simplified().isEmpty())
    {
        ui2->message->setStyleSheet("color: red;");
        ui2->message->setText("Заполните поля пароля");
        QTimer::singleShot(5000, [=]() {
                ui2->message->setText("");
            });
        return;
    }
    QString nameoremail = ui2->nameoremail->text();
    QString password = ui2->password->text();


    QString message = "login$" + nameoremail + "$" + password + "\r\n";
    SingletonSocket::instance()->getSocket()->write(message.toUtf8());
}

void second::on_connected()
{
    qDebug() << "Connected";
}

void second::on_disconnected()
{
    qDebug() << "Disconnected";
}

void second::on_readyRead(const QString& message, const QString& windowName)
{

    if(windowName=="log"){
    QList<QString> parts = message.split('$');
    if(parts[0]=="User exists in database.")
    {
        if (parts[1]=="Teacher")
        {
            this->hide();
            teachermod::instance()->show();
            ui2->message->clear();
        }
        else if(parts[1]=="Student"){
        this->hide();
            task_window::instance()->show();
            ui2->message->clear();
        }
    }
    else{
        ui2->nameoremail->clear();
        ui2->password->clear();
        ui2->message->setStyleSheet("color: red;");
        ui2->message->setText(message);
        QTimer::singleShot(5000, [=]() {
                ui2->message->setText("");
            });
    }
    }
}



void second::on_vkbutton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.vk.com/"));
}

void second::on_youtubebutton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.youtube.com/"));
}

void second::on_gitbutton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.github.com/"));
}

void second::on_tgbutton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.telegram.org/"));
}

void second::on_twitterbutton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.twitter.com/"));
}

void second::on_clicktoregister_clicked()
{
    this->hide();
    MainWindow::instance()->show();
}

