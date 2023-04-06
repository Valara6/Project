#include "ui_second.h"
#include "second.h"
#include "mainwindow.h"
#include <QComboBox>
#include <QString>
#include <QStringList>
#include <QDesktopServices>
#include <QUrl>
#include <QGuiApplication>
#include <QScreen>
second* second::m_instance = nullptr;

second::second(QWidget *parent) :
    QMainWindow(parent),
    ui2(new Ui::second),
    m_socket2(new QTcpSocket(this))
{
    ui2->setupUi(this);
    QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();


    // вычисляем координаты центра экрана
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
    connect(m_socket2, &QTcpSocket::connected, this, &second::on_connected);
    connect(m_socket2, &QTcpSocket::disconnected, this, &second::on_disconnected);
    connect(m_socket2, &QTcpSocket::readyRead, this, &second::on_readyRead);

    // Connect to the server
    m_socket2->connectToHost("127.0.0.1", 33333);

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
    QString nameoremail = ui2->nameoremail->text();
    QString password = ui2->password->text();

    QString message = "login$" + nameoremail + "$" + password + "\r\n";
    m_socket2->write(message.toUtf8());
}

void second::on_connected()
{
    qDebug() << "Connected";
}

void second::on_disconnected()
{
    qDebug() << "Disconnected";
}

void second::on_readyRead()
{
    qDebug() << "ReadyRead: " << m_socket2->readAll();
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

