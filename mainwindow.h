#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString ot;//строка-ответ
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots://функции вызываемые сигналами
    void on_pushButton_clicked(); //запускает необходимые действия при нажатии на кнопку "Ввод"
    void fnd(QString s); //подбор ответов (s-введённая пользователем строка) 
    void ots();//подбор "универсальных фраз"
    void okt(QString str);//делает кнопку ввода активной для нажатия(str-вводимая пользователем строка)
    void okt1(QString str);//делает кнопку ввода кнопкой по умолчанию(str-вводимая пользователем строка)
    
private:
    Ui::MainWindow *ui;/*класс, хранящий параметры пользовательского интерфейса(формируется автоматически)*/

};

#endif // MAINWINDOW_H
