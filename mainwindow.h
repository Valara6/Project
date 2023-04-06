#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include "second.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    static MainWindow* instance();
    void checkPasswordMatch();
    void onPasswordEditingFinished();
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_vkbutton_clicked();
    void on_twitterbutton_clicked();
    void on_telegrambutton_clicked();
    void on_youtubebutton_clicked();
    void on_gitbutton_clicked();
    void on_connected();
    void on_disconnected();
    void on_readyRead();
    void on_clicktologin_clicked();

private:
    explicit MainWindow(QWidget *parent = nullptr);
    Ui::MainWindow *ui;
    QTcpSocket *m_socket;
    static MainWindow* m_instance;
};

#endif // MAINWINDOW_H
