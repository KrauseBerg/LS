#include "ui_quest_2.h"
#include "quest_2.h"
#include <quest.h>
#include <fstream>
#include <QDebug>

using namespace std;

QWidget *butt;

string number_to_string_oqu(int x){
    if(!x) return "0";
    string s,s2;
    while(x){
        s.push_back(x%10 + '0');
        x/=10;
    }
    reverse(s.begin(),s.end());
    return s;
}

quest_2::quest_2(QWidget *parent) :
    QMainWindow(parent),perk(1),
    ui(new Ui::quest_2){
    ui->setupUi(this);
    connect(ui->add,SIGNAL(clicked(bool)),this,SLOT(add_button()));
    connect(ui->del,SIGNAL(clicked(bool)),this,SLOT(delete_button()));
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint|
                   //Qt::WindowMinimizeButtonHint |// кнопка сворачивания
                   //Qt::WindowMaximizeButtonHint |// кнопка разворачивания
                   Qt::WindowCloseButtonHint);// |//кнопка красный крестик
    quest_2::setFixedSize(788,592);
}

quest_2::~quest_2()
{
    delete ui;
}

void quest_2::add_text_1(QString id){
    ui->label->setText(id);
}

void quest_2::add_bb(QString &ide){
    for(int i=perk;i<10;i++){
        string ph="./"+ide.toStdString()+'/'+number_to_string_oqu(i)+".txt";
        fstream f(ph.c_str());
        if(f.is_open()){
            add_button();
            qDebug() << "str";
        }
        f.close();
    }
    id=ide;
}

void quest_2::add_button(){
    butt=new QPushButton(QString::number(perk));
    butt->setObjectName(QString::number(perk));
    butt->setStyleSheet("background-image: url(:/bg_image/images/White);");
    butt->setSizePolicy(sizePolicy().Minimum,sizePolicy().Minimum);
    ui->scrollArea->setWidgetResizable(true);
    ui->verticalLayout->addWidget(butt);
    string ph="./"+id.toStdString()+'/'+number_to_string_oqu(perk)+".txt";
//    qDebug() << QString::fromStdString(ph);
    ofstream p(ph.c_str(),ios_base::app);
    p.close();
    perk++;
}

void quest_2::delete_button(){
    qDebug() << perk;
}
