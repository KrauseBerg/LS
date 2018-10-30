#include "redactor.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_redactor.h"
#include "quest.h"

#include <fstream>
#include <iostream>
#include <cstring>
#include <QMessageBox>

using namespace std;



string number_to_string(int x){
    if(!x) return "0";
    string s,s2;
    while(x){
        s.push_back(x%10 + '0');
        x/=10;
    }
    reverse(s.begin(),s.end());
    return s;
}

int id2;

Redactor::Redactor(QWidget *parent) :
    QDialog(parent),
    i_f(1),
    ui(new Ui::Redactor){
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint|
                   //Qt::WindowMinimizeButtonHint |// кнопка сворачивания
                   //Qt::WindowMaximizeButtonHint |// кнопка разворачивания
                   Qt::WindowCloseButtonHint);// |//кнопка красный крестик
    //Qt::WindowSystemMenuHint); // системное меню(правая кнопка мыши)
    connect(ui->Gotovo,SIGNAL(clicked(bool)),this,SLOT(zapis()));
    // connect(ui->Gotovo,SIGNAL(clicked(bool)),this,SLOT(close()));


    connect(ui->rb_1,SIGNAL(clicked(bool)),this,SLOT(undis()));
    connect(ui->rb_2,SIGNAL(clicked(bool)),this,SLOT(undis()));
    connect(ui->rb_3,SIGNAL(clicked(bool)),this,SLOT(undis()));
    connect(ui->rb_4,SIGNAL(clicked(bool)),this,SLOT(undis()));


    Redactor::setFixedSize(788,592);
}

Redactor::~Redactor(){
    delete ui;
}

void Redactor::undis(){
    ui->Gotovo->setDisabled(false);
}


void Redactor::zapis(){

    string s =number_to_string(id2)+".txt";
    ofstream file;
    file.open(s.c_str(),ios::trunc);

    QString str=ui->Vopros_1->text();
    file<<str.toStdString()<<"$ ";

    str=ui->Otvet_1->text();
    file<<str.toStdString()<<"$ ";

    str=ui->Otvet_2->text();
    file<<str.toStdString()<<"$ ";

    str=ui->Otvet_3->text();
    file<<str.toStdString()<<"$ ";

    str=ui->Otvet_4->text();
    file<<str.toStdString()<<"$";

    //file.close();
    i_f++;
    ui->Vopros_1->clear();
    ui->Otvet_1->clear();
    ui->Otvet_2->clear();
    ui->Otvet_3->clear();
    ui->Otvet_4->clear();


    if(ui->rb_1->isChecked()==true)
    {
        file<<"1$";
        file.close();

        this->close();
    }
    else if(ui->rb_2->isChecked()==true){
        file<<"2$";
        file.close();

        this->close();
    }
    else if(ui->rb_3->isChecked()==true){
        file<<"3$";
        file.close();

        this->close();
    }
    else if(ui->rb_4->isChecked()==true){
        file<<"4$";
        file.close();
        this->close();
    }

    //file.close();
}

void Redactor::add_text(int id){
    id2=id;
    ui->Vopros_1->clear();
    ui->Otvet_1->clear();
    ui->Otvet_2->clear();
    ui->Otvet_3->clear();
    ui->Otvet_4->clear();

    ui->Gotovo->setDisabled(true);
    ui->rb_1->setChecked(false);
    ui->rb_2->setChecked(false);
    ui->rb_3->setChecked(false);
    ui->rb_4->setChecked(false);

    string ss =number_to_string(id)+".txt";
    fstream file;
    file.open(ss.c_str());
    string str="";
    QString s="";
    int ch=0;
    while((ch = file.get()) != EOF){
        if(char(ch)!='$'){
            str=str+char(ch);
        }
        else{
            s=QString::fromStdString(str);

            if(ui->Vopros_1->text()==""){
                ui->Vopros_1->setText(s);
            }
            else if(ui->Otvet_1->text()==""){
                ui->Otvet_1->setText(s);
            }
            else if(ui->Otvet_2->text()==""){
                ui->Otvet_2->setText(s);
            }
            else if(ui->Otvet_3->text()==""){
                ui->Otvet_3->setText(s);
            }
            else if(ui->Otvet_4->text()==""){
                ui->Otvet_4->setText(s);
            }
            else{
                if(str=="1")
                {
                    ui->rb_1->setChecked(true);
                    ui->rb_2->setChecked(false);
                    ui->rb_3->setChecked(false);
                    ui->rb_4->setChecked(false);
                    ui->Gotovo->setDisabled(false);

                }
                else if(str=="2"){
                    ui->rb_2->setChecked(true);
                    ui->rb_1->setChecked(false);
                    ui->rb_3->setChecked(false);
                    ui->rb_4->setChecked(false);
                    ui->Gotovo->setDisabled(false);
                }
                else if(str=="3"){
                    ui->rb_3->setChecked(true);
                    ui->rb_1->setChecked(false);
                    ui->rb_2->setChecked(false);
                    ui->rb_4->setChecked(false);
                    ui->Gotovo->setDisabled(false);
                }
                else if(str=="4"){
                    ui->rb_4->setChecked(true);
                    ui->rb_1->setChecked(false);
                    ui->rb_2->setChecked(false);
                    ui->rb_3->setChecked(false);
                    ui->Gotovo->setDisabled(false);

                }
            }
            str="";
            s="";
        }

    }
    file.close();



}


void Redactor::closeEvent(QCloseEvent *event)
{
    ui->rb_1->setChecked(false);
    ui->rb_2->setChecked(false);
    ui->rb_3->setChecked(false);
    ui->rb_4->setChecked(false);
}
