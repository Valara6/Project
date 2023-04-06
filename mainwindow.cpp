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
MainWindow* MainWindow::m_instance = nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_socket(new QTcpSocket(this))
{
    ui->setupUi(this);
    QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();


    // вычисляем координаты центра экрана
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
    connect(m_socket, &QTcpSocket::connected, this, &MainWindow::on_connected);
    connect(m_socket, &QTcpSocket::disconnected, this, &MainWindow::on_disconnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &MainWindow::on_readyRead);
    connect(ui->password, &QLineEdit::editingFinished, this, &MainWindow::onPasswordEditingFinished);
    connect(ui->password, &QLineEdit::textChanged, this, &MainWindow::checkPasswordMatch);
    connect(ui->verpassword, &QLineEdit::textChanged, this, &MainWindow::checkPasswordMatch);


    // Connect to the server
    m_socket->connectToHost("127.0.0.1", 33333);

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
    m_socket->write(message.toUtf8());
    QMessageBox::information(this, tr("Обновлено"), tr("Данные успешно обновлены."));

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

void MainWindow::on_readyRead()
{
qDebug() << "ReadyRead: " << m_socket->readAll();
}



void MainWindow::on_clicktologin_clicked()
{
         // Скрыть MainWindow


        // Скрываем MainWindow
    this->hide();
    second::instance()->show();
}

