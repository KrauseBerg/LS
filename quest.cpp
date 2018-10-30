#include "ui_quest.h"
#include "quest.h"
#include "redactor.h"
//#include "w_setting.h"
#include <QDir>

#include <cstring>
#include <QVBoxLayout>
#include <QDynamicPropertyChangeEvent>
#include <fstream>
#include <QDebug>
#include <QSignalMapper>
#include "quest_2.h"
#include "mainwindow.h"

using namespace std;

Redactor *rd;
quest_2 *que_2;
QWidget *but;

int i=1;
int *mas[200];

quest::quest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::quest)
{
    ui->setupUi(this);
    rd=new Redactor();
    que_2=new quest_2();
    // ws=new w_setting();
    connect(ui->add,SIGNAL(clicked(bool)),this,SLOT(add_but()));
    connect(ui->del,SIGNAL(clicked(bool)),this,SLOT(delet()));

    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint|
                   //Qt::WindowMinimizeButtonHint |// кнопка сворачивания
                   //Qt::WindowMaximizeButtonHint |// кнопка разворачивания
                   Qt::WindowCloseButtonHint);// |//кнопка красный крестик
    //Qt::WindowSystemMenuHint); // системное меню(правая кнопка мыши)
}

quest::~quest()
{
    delete ui->scrollAreaWidgetContents;
    delete ui;
}

bool quest::add_bb(){
    int ch=0;
    fstream kat("katalog.txt");
    if(kat.peek()!=EOF){
        string str="";
        while((ch = kat.get()) != EOF){
            if(char(ch)!='$')
                str=str+char(ch);
            else{
                QString s=QString::fromStdString(str);
                but=new QPushButton(s);
                but->setObjectName(s);
                but->setStyleSheet("background-image: url(:/bg_image/images/White);");
                but->setSizePolicy(sizePolicy().Minimum,sizePolicy().Minimum);
                mas[i]=(int*)but;i++;
                ui->scrollArea->setWidgetResizable(true);
                if(ui->gridLayout->isEmpty()==true)
                    ui->gridLayout->addWidget(but);
                str="";
            }
            connect(but,SIGNAL(clicked(bool)),this,SLOT(show_rd()));
        }
    }
    return true;
}

void quest::add_but(){
    if(ui->inputpapka->text()!=""){
        fstream file("katalog.txt");
        string new_str;
        getline(file,new_str);
        string stroka=ui->inputpapka->text().toStdString();
        stroka+='$';
        int jop=new_str.find(stroka);
        if(jop!=-1 && new_str[jop-1]==' '){
            ui->inputpapka->setText("Тема уже существует!");
        }
        else{
            but=new QPushButton(ui->inputpapka->text());
            but->setObjectName(ui->inputpapka->text());
            but->setStyleSheet("background-image: url(:/bg_image/images/White);");
            but->setSizePolicy(sizePolicy().Minimum,sizePolicy().Minimum);
            mas[i]=(int*)but; i++;
            ui->scrollArea->setWidgetResizable(true);
            ui->gridLayout->addWidget(but);
            QDir().mkpath(ui->inputpapka->text());
            ofstream p("katalog.txt",ios_base::app);
            p<<" "<<ui->inputpapka->text().toStdString().c_str()<<"$";
            p.close();
            ui->inputpapka->clear();
        }
        file.close();
    }
    else{

    }
    connect(but,SIGNAL(clicked(bool)),this,SLOT(show_rd()));


}

void quest::delet(){
    if(ui->deletepapka->text()!=""){
        fstream kat("katalog.txt");
        string text;
        getline(kat,text);
        string str=' '+ui->deletepapka->text().toStdString();
        string str1=str+'$';
        int pos=text.find(str1);
        if ( pos == (int) std::string::npos ){
            ui->deletepapka->setText("Нет такой темы!");
        }
        else{
            text.erase(pos,str1.size());
            kat.close();
            kat.open("katalog.txt",ios::out);
            kat<<text;
            kat.close();
            i=1;
            while(true){
                but=(QPushButton*)mas[i];
                text=but->objectName().toStdString();
                if(text[0]!=' '){
                    str1=' ';
                    str1+=but->objectName().toStdString();
                }
                else str1=but->objectName().toStdString();
                if(str1==str){
                    but->hide();
                    QDir().rmpath(ui->deletepapka->text());
                    ui->deletepapka-> clear();
                    i--;
                    qDebug() << QString::number(i);
                    break;
                }
                else{
                    i++;
                }
            }
        }
    }
}
void quest::show_rd(){
    QString id;
    id=sender()->objectName();
    id.remove(0,1);
    que_2->show();
    que_2->add_text_1(id);
    que_2->add_bb(id);
}

void quest::closeEvent(QCloseEvent *event){
    MainWindow *mw=new MainWindow();
    mw->zap();
    mw->show();
}


