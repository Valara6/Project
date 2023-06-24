#include "second.h"
#include "ui_second.h"
#include "teachermod.h"
#include "ui_teachermod.h"
#include <QTimer>

teachermod* teachermod::m_instance = nullptr;

teachermod::teachermod(QWidget *parent) :
    QMainWindow(parent),
    ui4(new Ui::teachermod)
{
    ui4->setupUi(this);
    ui4->label->setText(second::instance()->ui2->nameoremail->text());
    connect(SingletonSocket::instance(), &SingletonSocket::messageReceived, this, &teachermod::on_readyRead);
    connect(ui4->getstat, &QPushButton::clicked, this, &teachermod::on_getstat_clicked);
    connect(ui4->pushButton_2, &QPushButton::clicked, this, &teachermod::on_pushButton_2_clicked);
    connect(ui4->pushButton_5, &QPushButton::clicked, this, &teachermod::onButtonClicked);
    connect(ui4->pushButton, &QPushButton::clicked, this, &teachermod::onButtonClicked);
    connect(ui4->pushButton_6, &QPushButton::clicked, this, &teachermod::onButtonClicked);
    connect(ui4->pushButton_7, &QPushButton::clicked, this, &teachermod::onButtonClicked);
    connect(ui4->pushButton_3, &QPushButton::clicked, this, &teachermod::onButtonClicked);
    connect(ui4->pushButton_4, &QPushButton::clicked, this, &teachermod::on_pushButton_4_clicked);
    connect(ui4->pushButton_9, &QPushButton::clicked, this, &teachermod::on_pushButton_9_clicked);
}

void teachermod::on_readyRead(const QString& message, const QString& windowName)
{
    if(windowName=="settask")
    {
        qDebug() << message;
        ui4->label_9->setText(message);
        QTimer::singleShot(5000, [=]() {
                ui4->label_9->setText("");
            });
    }
    else if(windowName=="uptdes"){
        qDebug() << message;
        ui4->infoinsert->setText(message);
        QTimer::singleShot(5000, [=]() {
                ui4->infoinsert->setText("");
            });

    }
    else if(windowName=="uptans")
    {
        qDebug() << message;
        ui4->infoinsert->setText(message);
        QTimer::singleShot(5000, [=]() {
                ui4->infoinsert->setText("");
            });

    }
    else if(windowName=="deltask")
    {
        qDebug() << message;
        ui4->infopage2->setText(message);
        QTimer::singleShot(5000, [=]() {
                ui4->infopage2->setText("");
            });

    }
}
teachermod::~teachermod()
{
    delete ui4;
}

teachermod* teachermod::instance()
{
    if (!m_instance)
        m_instance = new teachermod;
    return m_instance;
}

void teachermod::resetInstance()
{
    if (m_instance) {
                delete m_instance;
                m_instance = nullptr;
            }
}




void teachermod::onButtonClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button)
    {
        if (button == ui4->pushButton) // Проверяем, какая кнопка была нажата
        {
            QString name = ui4->label->text();
            QString nameexer = ui4->lineEdit->text();
            QString descrip = ui4->lineEdit_2->text();
            QString answer = ui4->lineEdit_3->text();
            QString message = "settask$"+name+"$"+nameexer +"$"+descrip+"$"+answer + "\r\n";
            SingletonSocket::instance()->getSocket()->write(message.toUtf8());
        }
        else if (button == ui4->pushButton_6)
        {
            QString name = ui4->label->text();
            QString nameexer = ui4->lineEdit_5->text();
            QString des = ui4->lineEdit_6->text();
            QString message = "uptdes$"+name+"$"+nameexer+"$"+des+"\r\n";
            SingletonSocket::instance()->getSocket()->write(message.toUtf8());
        }
        else if (button == ui4->pushButton_7)
        {
            QString name = ui4->label->text();
            QString nameexer = ui4->lineEdit_5->text();
            QString ans = ui4->lineEdit_7->text();
            QString message = "uptans$"+name+"$"+nameexer+"$"+ans+"\r\n";
            SingletonSocket::instance()->getSocket()->write(message.toUtf8());
        }
        else if (button == ui4->pushButton_5)
        {
            QString name = ui4->label->text();
            QString nameexer = ui4->lineEdit_4->text();
            QString message = "deltask$" +nameexer+"\r\n";
            SingletonSocket::instance()->getSocket()->write(message.toUtf8());
        }
        if (button == ui4->pushButton_3) // Проверяем, какая кнопка была нажата
        {
            ui4->stackedWidget->setCurrentIndex(2);
        }

    }
}


void teachermod::on_getstat_clicked()
{
    ui4->stackedWidget->setCurrentIndex(0);
}


void teachermod::on_pushButton_2_clicked()
{
    ui4->stackedWidget->setCurrentIndex(1);
}


void teachermod::on_pushButton_4_clicked()
{
    ui4->stackedWidget->setCurrentIndex(3);
}


void teachermod::on_pushButton_9_clicked()
{
    teachermod::resetInstance();
    second::instance()->show();
}

