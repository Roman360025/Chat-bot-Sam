#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <string.h>

//Описание конструктора класса MainWindow
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{ 
    ui->setupUi(this);//код, сгенерированный компилятором
    ui->pushButton->setEnabled(false);//делаем кнопку ввода не доступной к нажатию
    //связывание сигналов от интерфейса с функциями
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(okt(QString)));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(okt1(QString)));
}
//Деструктор класса MainWindow
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::okt(QString str)
{
    ui->pushButton->setEnabled(!str.isEmpty());
}

void MainWindow::okt1(QString str)
{
    ui->pushButton->setDefault(!str.isEmpty());
}

void MainWindow::fnd(QString s)
{int j=0, j1=0;
    QString str1, str2, s2;
    //str1-хранит строку из файла
    //str2-хранит ключевое слово из str1
    //s2-хранит ответ на ключевое слово str2 из строки str1
    QFile fl(tr(":/Document/Sam.txt"));//связываем объект класса с файлом ключесых слов
    fl.open(QFile::ReadOnly);//открываем файл для чтения
    QTextStream stream(&fl);//создаём объект для чтения текста из файла
    s=s.simplified();//удаляем из строки лишние пробелы
    bool flag=false;//flag-проверяет, был ли получен ответ
    //цикл, который подбирает необходимый ответ
    while(j1<=53){
        ot="";
        str1=stream.readLine();//получаем строку из файла
        j=str1.indexOf("|");
        str2=str1.left(j);//получаем ключевое слово
        s2=str1.mid(j+1);//получаем ответ
        //если ключевое слово содержится в строке пользователя, то запоминаем, что ответ был получен
        if(s.contains(str2, Qt::CaseInsensitive)) {
            ot=s2;
            flag=true;
        }
        j1++;
        //при наличие ответной реакции, выводим в поле вывода
        if (!ot.isEmpty()) {
            ui->textEdit->setTextColor(Qt::blue);
            ui->textEdit->append(ot);
        }

    }
    if((!flag)) ots();//при отсутствии ответной реакции вызывается функция, отвечающая за подбор универсальных фраз
    fl.close();//закрываем файл
}

void MainWindow::ots()
{
    int p, i;
    //p-хранит случаеное число
    //i-переменная-счётчик
    QString str1;//str1-хранит ответную реакцию
    QFile fl(tr(":/Document/Sam1.txt"));//связываем объект класса с файлом "универсальных фраз"
    fl.open(QFile::ReadOnly);//открываем файл для чтения
    QTextStream stream(&fl);//создаём объект для чтения текста из файла
    //получаем случайное число
    srand(time(0));
    p=1+rand()%8;
    //цикл, получающий нужную "универсальную фразу"
    for(i=1; i<=p; i++)
        str1=stream.readLine();
    ot=str1;//получаем ответ
    //выводим в поле вывода
    ui->textEdit->setTextColor(Qt::blue);
    ui->textEdit->append(ot);
    fl.close();//закрываем файл
}

void MainWindow::on_pushButton_clicked()
{   
    ot="";//инициализируем строку ответа
    //выводим строку пользователя в поле вывода
    ui->textEdit->setTextColor(Qt::black);
    ui->textEdit->append(ui->lineEdit->text());
    fnd(ui->lineEdit->text());//вызов функции подбора ответов
    ui->lineEdit->clear();//очищаем поле ввода
    ui->pushButton->setEnabled(false);//делаем кнопку ввода неактивной
}
