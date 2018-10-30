#include "otvet.h"
#include "ui_otvet.h"
#include "mainwindow.h"
#include "rezz.h"

#include <fstream>
#include <iostream>

#include <QDebug>


using namespace std;

rezz *rz;



string number_to_string_o(int x){
    if(!x) return "0";
    string s,s2;
    while(x){
        s.push_back(x%10 + '0');
        x/=10;
    }
    reverse(s.begin(),s.end());
    return s;
}
int num=0;


otvet::otvet(QWidget *parent) :
    QDialog(parent),

    ui(new Ui::otvet){
    ui->setupUi(this);
    rz=new rezz();
    rz->mas=0;

    key=new QShortcut(this);
    key->setKey(Qt::CTRL+Qt::Key_F10);

    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    //Qt::WindowMinimizeButtonHint |// кнопка сворачивания
    //Qt::WindowMaximizeButtonHint |// кнопка разворачивания
    // Qt::WindowCloseButtonHint);// |//кнопка красный крестик
    //Qt::WindowSystemMenuHint); // системное меню(правая кнопка мыши)

    connect(ui->start,SIGNAL(clicked(bool)),this,SLOT(show_1()));
    connect(ui->Next,SIGNAL(clicked(bool)),this,SLOT(show_1()));

    connect(ui->otvet1,SIGNAL(clicked(bool)),this,SLOT(check_o()));
    connect(ui->otvet2,SIGNAL(clicked(bool)),this,SLOT(check_o()));
    connect(ui->otvet3,SIGNAL(clicked(bool)),this,SLOT(check_o()));
    connect(ui->otvet4,SIGNAL(clicked(bool)),this,SLOT(check_o()));

    connect(key,SIGNAL(activated()),this,SLOT(on_pod_triggered()));
    //ui->lineEdit->text(QTime::currentTime().toString("hh:mm:ss"));
}


otvet::~otvet(){
    delete ui;
}

void otvet::show_1(){
    int ch=0;
    QString vopr=QString::fromStdString(number_to_string_o(num+1)+"-ый Вопрос");
    ui->Vopros->setText(vopr);
    
    ui->start->close();
    ui->area->close();
    ui->Next->setDisabled(true);
    ui->otvet1->setStyleSheet("background-image: url(:/bg_image/images/White)");
    ui->otvet2->setStyleSheet("background-image: url(:/bg_image/images/White)");
    ui->otvet3->setStyleSheet("background-image: url(:/bg_image/images/White)");
    ui->otvet4->setStyleSheet("background-image: url(:/bg_image/images/White)");

    ui->otvet1->setDisabled(false);
    ui->otvet2->setDisabled(false);
    ui->otvet3->setDisabled(false);
    ui->otvet4->setDisabled(false);

    if(num==25)
    {

        this->close();
        rz->show();
        rz->show_col();
        num=0;
        ui->area->show();
        ui->start->show();
        num-=1;

    }

    string path =number_to_string_o(rand_f[num])+".txt";
    num++;

    //    QString u;
    //    u=QString::fromStdString(number_to_string_o(num));
    //    qDebug()<<u;

    // ////////////////////////////&&&
    ui->textEdit->clear();
    ui->otvet1->setText("");
    ui->otvet2->setText("");
    ui->otvet3->setText("");
    ui->otvet4->setText("");
    fstream fileo(path.c_str());
    // fileo.open(path.c_str());
    string str="";
    QString s="";
    int sc=0;
    while((ch = fileo.get()) != EOF){
        if(char(ch)!='$'){
            str=str+char(ch);
            if(sc==5)
            {
                otv=str;
                //qDebug()<<QString::fromStdString(otv);
            }
        }
        else{
            sc++;
            s=QString::fromStdString(str);
            
            if(ui->textEdit->toPlainText()==""){
                ui->textEdit->setText(s);
            }
            else if(ui->otvet1->text()==""){
                ui->otvet1->setText(s);
            }
            else if(ui->otvet2->text()==""){
                ui->otvet2->setText(s);
            }
            else if(ui->otvet3->text()==""){
                ui->otvet3->setText(s);
            }
            else if(ui->otvet4->text()==""){
                ui->otvet4->setText(s);
            }
            str="";
            s="";
        }
        
    }
    fileo.close();
    
}


void otvet::check_o(){
    int n_ot;
    n_ot=atoi(otv.c_str());
    if(sender()->objectName()=="otvet1" && n_ot==1){
        ui->otvet1->setStyleSheet("*{background-image: url(:/bg_image/images/White); background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 255, 255, 255), stop:0.353234 rgba(189, 255, 189, 255), stop:0.621891 rgba(153, 255, 153, 255), stop:1 rgba(86, 220, 86, 255));}");
        ui->otvet1->setDisabled(true);
        ui->otvet2->setDisabled(true);
        ui->otvet3->setDisabled(true);
        ui->otvet4->setDisabled(true);
        ui->Next->setDisabled(false);
        rz->mas++;
    }
    else if(sender()->objectName()=="otvet2" && n_ot==2){
        ui->otvet2->setStyleSheet("*{background-image: url(:/bg_image/images/White);background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 255, 255, 255), stop:0.353234 rgba(189, 255, 189, 255), stop:0.621891 rgba(153, 255, 153, 255), stop:1 rgba(86, 220, 86, 255));}");
        ui->otvet1->setDisabled(true);
        ui->otvet2->setDisabled(true);
        ui->otvet3->setDisabled(true);
        ui->otvet4->setDisabled(true);
        ui->Next->setDisabled(false);
        rz->mas++;
    }
    else if(sender()->objectName()=="otvet3" && n_ot==3){
        ui->otvet3->setStyleSheet("*{background-image: url(:/bg_image/images/White);background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 255, 255, 255), stop:0.353234 rgba(189, 255, 189, 255), stop:0.621891 rgba(153, 255, 153, 255), stop:1 rgba(86, 220, 86, 255));}");
        ui->otvet1->setDisabled(true);
        ui->otvet2->setDisabled(true);
        ui->otvet3->setDisabled(true);
        ui->otvet4->setDisabled(true);
        ui->Next->setDisabled(false);
        rz->mas++;
    }
    else if(sender()->objectName()=="otvet4" && n_ot==4){
        ui->otvet4->setStyleSheet("*{background-image: url(:/bg_image/images/White);background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 255, 255, 255), stop:0.353234 rgba(189, 255, 189, 255), stop:0.621891 rgba(153, 255, 153, 255), stop:1 rgba(86, 220, 86, 255));}");
        ui->otvet1->setDisabled(true);
        ui->otvet2->setDisabled(true);
        ui->otvet3->setDisabled(true);
        ui->otvet4->setDisabled(true);
        ui->Next->setDisabled(false);
        rz->mas++;
    }
    else {
        ui->otvet1->setDisabled(true);
        ui->otvet2->setDisabled(true);
        ui->otvet3->setDisabled(true);
        ui->otvet4->setDisabled(true);
        ui->Next->setDisabled(false);

        QString on=sender()->objectName();
        if(on=="otvet1")
            ui->otvet1->setStyleSheet("*{background-image: url(:/bg_image/images/White);background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 255, 255, 255), stop:0.283582 rgba(255, 189, 189, 255), stop:0.547264 rgba(255, 153, 153, 255), stop:0.791045 rgba(255, 72, 72, 255), stop:1 rgba(220, 0, 0, 255));}");
        else if(on=="otvet2")
            ui->otvet2->setStyleSheet("*{background-image: url(:/bg_image/images/White);background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 255, 255, 255), stop:0.283582 rgba(255, 189, 189, 255), stop:0.547264 rgba(255, 153, 153, 255), stop:0.791045 rgba(255, 72, 72, 255), stop:1 rgba(220, 0, 0, 255));}");
        else if(on=="otvet3")
            ui->otvet3->setStyleSheet("*{background-image: url(:/bg_image/images/White);background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 255, 255, 255), stop:0.283582 rgba(255, 189, 189, 255), stop:0.547264 rgba(255, 153, 153, 255), stop:0.791045 rgba(255, 72, 72, 255), stop:1 rgba(220, 0, 0, 255));}");
        else if(on=="otvet4")
            ui->otvet4->setStyleSheet("*{background-image: url(:/bg_image/images/White);background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 255, 255, 255), stop:0.283582 rgba(255, 189, 189, 255), stop:0.547264 rgba(255, 153, 153, 255), stop:0.791045 rgba(255, 72, 72, 255), stop:1 rgba(220, 0, 0, 255));}");

    }


}

void otvet::on_pod_triggered()
{
    int ot;
    ot=atoi(otv.c_str());
    if(ot==1){
        ui->otvet1->setStyleSheet("*{background-image: url(:/bg_image/images/White); background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 255, 255, 255), stop:0.353234 rgba(189, 255, 189, 255), stop:0.621891 rgba(153, 255, 153, 255), stop:1 rgba(86, 220, 86, 255));}");

    }
    else if(ot==2){
        ui->otvet2->setStyleSheet("*{background-image: url(:/bg_image/images/White);background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 255, 255, 255), stop:0.353234 rgba(189, 255, 189, 255), stop:0.621891 rgba(153, 255, 153, 255), stop:1 rgba(86, 220, 86, 255));}");

    }
    else if(ot==3){
        ui->otvet3->setStyleSheet("*{background-image: url(:/bg_image/images/White);background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 255, 255, 255), stop:0.353234 rgba(189, 255, 189, 255), stop:0.621891 rgba(153, 255, 153, 255), stop:1 rgba(86, 220, 86, 255));}");

    }
    else if(ot==4){
        ui->otvet4->setStyleSheet("*{background-image: url(:/bg_image/images/White); background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 255, 255, 255), stop:0.353234 rgba(189, 255, 189, 255), stop:0.621891 rgba(153, 255, 153, 255), stop:1 rgba(86, 220, 86, 255));}");

    }
}

