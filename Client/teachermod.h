#ifndef TEACHERMOD_H
#define TEACHERMOD_H

#include <QMainWindow>
#include "second.h"
namespace Ui {
class teachermod;
}

class teachermod : public QMainWindow
{
    Q_OBJECT
    friend class second;
public:
    static teachermod* instance(); // Статический метод для получения единственного экземпляра класса
    static void resetInstance();

    ~teachermod();

private slots:
    void on_readyRead(const QString& message, const QString& windowName);

    void onButtonClicked();


    void on_getstat_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_9_clicked();

private:
    explicit teachermod(QWidget *parent = nullptr);
    Ui::teachermod *ui4;
    static teachermod* m_instance;
    void on_pushButton_4_clicked();
};

#endif // TEACHERMOD_H
