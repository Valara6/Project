#ifndef SECOND_H
#define SECOND_H

#include <QMainWindow>
#include <QTcpSocket>
#include "singletonsocket.h"
#include "task_window.h"
#include "teachermod.h"
QT_BEGIN_NAMESPACE
namespace Ui { class second; }
QT_END_NAMESPACE

class second : public QMainWindow
{
Q_OBJECT
    friend class task_window;
    friend class teachermod;
public:
    static second* instance();
    ~second();

private slots:
    void on_pushButton_clicked();
    void on_connected();
    void on_disconnected();
    void on_readyRead(const QString &message, const QString &windowName);

    void on_vkbutton_clicked();
    void on_youtubebutton_clicked();
    void on_gitbutton_clicked();
    void on_tgbutton_clicked();
    void on_twitterbutton_clicked();

    void on_clicktoregister_clicked();
private:
    explicit second(QWidget *parent = nullptr);
    Ui::second *ui2;
    static second* m_instance;
};

#endif // SECOND_H
