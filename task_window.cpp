#include "task_window.h"
#include "ui_task_window.h"
#include "second.h"
#include "ui_second.h"
//#include "first.h"
#include <QString>
// Инициализация статического указателя на экземпляр класса
task_window* task_window::m_instance = nullptr;

task_window::task_window(QWidget *parent) :
    QMainWindow(parent),
    ui3(new Ui::task_window)
{
    ui3->setupUi(this);

    ui3->username->setText(second::instance()->ui2->nameoremail->text());
    connect(ui3->pushButton_1, &QPushButton::clicked, this, &task_window::onButtonClicked);
    connect(ui3->pushButton_22, &QPushButton::clicked, this, &task_window::onButtonClicked);
    connect(ui3->pushButton_33, &QPushButton::clicked, this, &task_window::onButtonClicked);
    connect(ui3->pushButton, &QPushButton::clicked, this, &task_window::on_pushButton_clicked);
    connect(ui3->pushButton_2, &QPushButton::clicked, this, &task_window::on_pushButton_2_clicked);
    connect(ui3->pushButton_4, &QPushButton::clicked, this, &task_window::on_pushButton_4_clicked);
    connect(ui3->pushButton_5, &QPushButton::clicked, this, &task_window::on_pushButton_6_clicked);
    connect(ui3->pushButton_7, &QPushButton::clicked, this, &task_window::on_pushButton_7_clicked);
    //connect(ui3->pushButton_8, &QPushButton::clicked, this, &task_window::on_pushButton_8_clicked);
    connect(SingletonSocket::instance(), &SingletonSocket::messageReceived, this, &task_window::on_readyRead);


}

task_window::~task_window()
{
    delete ui3;
}

task_window* task_window::instance()
{
    if (!m_instance)
        m_instance = new task_window;
    return m_instance;
}

void task_window::resetInstance()
{
    if (m_instance) {
                delete m_instance;
                m_instance = nullptr;
            }
}

void task_window::onButtonClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button)
    {
        if (button == ui3->pushButton_1) // Проверяем, какая кнопка была нажата
        {
            QString name = ui3->pushButton_1->text();
            ui3->exnum->clear();
            ui3->exnum->setText(name);
            QString message = "gettask$" + name + "\r\n";
            SingletonSocket::instance()->getSocket()->write(message.toUtf8());
        }
        else if (button == ui3->pushButton_22)
        {
            QString name = ui3->pushButton_22->text();
            ui3->exnum->clear();
            ui3->exnum->setText(name);
            QString message = "gettask$" + name + "\r\n";
            SingletonSocket::instance()->getSocket()->write(message.toUtf8());
        }
        else if (button == ui3->pushButton_33)
        {
            QString name = ui3->pushButton_33->text();

            ui3->exnum->clear();
            ui3->exnum->setText(name);
            QString message = "gettask$" + name + "\r\n";
            SingletonSocket::instance()->getSocket()->write(message.toUtf8());
        }

    }
}
void task_window::on_readyRead(const QString& message, const QString& windowName)
{
    if(windowName=="getstat")
    {
        qDebug() << message;
        QList<QString> parts = message.split('$');
        ui3->st1->clear();
        ui3->st2->clear();
        ui3->st3->clear();
        ui3->st1->setText(parts[0]);
        ui3->st2->setText(parts[1]);
        ui3->st3->setText(parts[2]);
    }
    else if(windowName=="gettask"){
     ui3->label_3->clear();
     ui3->label_3->setText(message);

    }
    else if(windowName=="chkres")
    {
        if(message=="Correct answer.")
        {
            ui3->message->clear();
            ui3->message->setStyleSheet("color: green;");
            ui3->message->setText(message);
        }
        else
        {
            ui3->message->clear();
            ui3->message->setStyleSheet("color: red;");
            ui3->message->setText(message);
        }
    }
}

void task_window::on_pushButton_6_clicked()
{
    QLineEdit* answerLineEdit = ui3->lineEdit;
    if(ui3->label_3->text()=="")
    {
        answerLineEdit->setStyleSheet("QLineEdit { border-bottom:2px solid rgba(255,0,0,1); }");
        ui3->message->setStyleSheet("color: red;");
        ui3->message->setText("не выбран задача ");
    }
    else if (ui3->label_3->text()!="")
    {
        ui3->message->clear();
        QString name = ui3->exnum->text();
        QString answer=ui3->lineEdit->text();
        QString username=ui3->username->text();
        if(answer=="")
        {
            answerLineEdit->setStyleSheet("QLineEdit { border-bottom:2px solid rgba(255,0,0,1); }");
            ui3->message->setStyleSheet("color: red;");
            ui3->message->setText("нету ответа");
            return;
        }

        QString message = "chkres$" + name +"$"+answer+"$"+username+ "\r\n";
        SingletonSocket::instance()->getSocket()->write(message.toUtf8());
    }

}


void task_window::on_logout_clicked()
{
    task_window::resetInstance();
    second::instance()->show();
}


void task_window::on_pushButton_3_clicked()
{
    QString name = ui3->username->text();
    QString message = "getstat$" + name + "\r\n";
    SingletonSocket::instance()->getSocket()->write(message.toUtf8());
}


void task_window::on_pushButton_clicked()
{
    ui3->stackedWidget->setCurrentIndex(0);
}


void task_window::on_pushButton_2_clicked()
{
    ui3->stackedWidget->setCurrentIndex(1);
}


void task_window::on_pushButton_4_clicked()
{
    ui3->stackedWidget_2->setCurrentIndex(0);
}


void task_window::on_pushButton_5_clicked()
{
    ui3->stackedWidget_2->setCurrentIndex(1);
}


void task_window::on_pushButton_7_clicked()
{
    ui3->stackedWidget_2->setCurrentIndex(2);
}


//void task_window::on_pushButton_8_clicked()
//{
//    QString vertices1=ui3->lineEdit_2->text();
//    QString text1 = ui3->lineEdit_3->text();
//    int line1 = text1.toInt();
//    QString str1=ui3->lineEdit_4->text();
//    QString result;
//    result= maint(vertices1,line1,str1);
//    ui3->label_15->setText(result);

//}

