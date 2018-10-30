#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "w_setting.h"
#include "otvet.h"
#include <fstream>
#include <ctime>
#include <QDebug>
#include <QGridLayout>
#include <QPushButton>

w_setting *set;
otvet *otv;

QWidget *thems;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    set=new w_setting();
    otv=new otvet();
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint|
                   //Qt::WindowMinimizeButtonHint |// кнопка сворачивания
                   //Qt::WindowMaximizeButtonHint |// кнопка разворачивания
                   Qt::WindowCloseButtonHint);// |//кнопка красный крестик
    //Qt::WindowSystemMenuHint); // системное меню(правая кнопка мыши)
    ui->mainToolBar->setMovable(false);
    int i,j;
    int ch=0;i=0;j=0;
    fstream kat("katalog.txt");
    if(kat.peek()!=EOF){
        string str="";
        while((ch = kat.get()) != EOF)
        {
            if(char(ch)!='$')
                str=str+char(ch);

            else{
                QString s=QString::fromStdString(str);
                thems=new QPushButton(s);
                thems->setObjectName(s);
                thems->setStyleSheet("background-image: url(:/bg_image/images/White);color: rgb(0, 0, 0);");
                thems->setSizePolicy(sizePolicy().Minimum,sizePolicy().Minimum);
                ui->scrollArea->setWidgetResizable(true);
                //qlay->addWidget(thems);
                ui->gridLayout->addWidget(thems,i,j);
                // QWidget* widget = new QWidget;
                // widget -> setLayout(qlay);
                //ui->scrollArea->setWidget(widget);
                //ui->scrollArea->setLayout(qlay);
                str="";
                if(j==0)
                    j++;
                else{
                    i++;
                    j--;
                }
            }
        }
    }
    MainWindow::setFixedSize(744,588);
    connect(ui->setting,SIGNAL(triggered(bool)),this,SLOT(showSetting()));
    //    connect(ui->var_1,SIGNAL(clicked(bool)),this,SLOT(showOtvet()));
    //    connect(ui->var_2,SIGNAL(clicked(bool)),this,SLOT(showOtvet()));
    //    connect(ui->var_3,SIGNAL(clicked(bool)),this,SLOT(showOtvet()));
    //    connect(ui->var_4,SIGNAL(clicked(bool)),this,SLOT(showOtvet()));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::showSetting(){
    set->show();
    this->close();
}

void MainWindow::showOtvet(){
    //otvet ot;
    if(sender()->objectName()=="var_1")
        fil_f(1);
    if(sender()->objectName()=="var_2")
        fil_f(2);
    if(sender()->objectName()=="var_3")
        fil_f(3);
    if(sender()->objectName()=="var_4")
        fil_f(4);

    otv->show();

}
void MainWindow::fil_f(int j){
    otv->rand_f.clear();
    for(int i=(j-1)*25;i<25*j;i++){
        otv->rand_f.push_back(i+1);
    }

    srand(time(0));
    random_shuffle(otv->rand_f.begin(),otv->rand_f.end());
    for(int i=0;i<7;i++){

        QString a=QString::number(otv->rand_f[i]);
    }

}
void MainWindow::zap(){

    int ch=0;
    fstream kat("katalog.txt");
    if(kat.peek()!=EOF){
        string str="";
        while((ch = kat.get()) != EOF){
            if(char(ch)!='$')
                str=str+char(ch);

            else{
                QString s=QString::fromStdString(str);
                thems=new QPushButton(s);
                thems->setObjectName(s);
                thems->setStyleSheet("background-image: url(:/bg_image/images/White);color: rgb(0, 0, 0);");
                thems->setSizePolicy(sizePolicy().Minimum,sizePolicy().Minimum);
                ui->scrollArea->setWidgetResizable(true);
                str="";
            }
        }
    }
}
