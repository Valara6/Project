#ifndef TASK_WINDOW_H
#define TASK_WINDOW_H

#include <QMainWindow>
#include "second.h"
//#include "first.h"
namespace Ui {
class task_window;
}

class task_window : public QMainWindow
{
    Q_OBJECT
    friend class second;
public:
    static task_window* instance(); // Статический метод для получения единственного экземпляра класса
    static void resetInstance();
    ~task_window();


private slots:
    void onButtonClicked();
    void on_readyRead(const QString& message, const QString& windowName);

    void on_pushButton_6_clicked();

    void on_logout_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    //void on_pushButton_8_clicked();

    void on_generatebutton_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

private:
    explicit task_window(QWidget *parent = nullptr);
    Ui::task_window *ui3;
    static task_window* m_instance; // Статический указатель на экземпляр класса

};

#endif // TASK_WINDOW_H
