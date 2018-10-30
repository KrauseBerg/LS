#include "rezz.h"
#include "ui_rezz.h"
#include "otvet.h"

//otvet *tv;
rezz::rezz(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rezz)
{
    ui->setupUi(this);
    //tv=new otvet();
    rezz::setFixedSize(706,407);
    connect(ui->cl,SIGNAL(clicked(bool)),this,SLOT(close()));
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint|
                   //Qt::WindowMinimizeButtonHint |// кнопка сворачивания
                   //Qt::WindowMaximizeButtonHint |// кнопка разворачивания
                   Qt::WindowCloseButtonHint);// |//кнопка красный крестик
    //Qt::WindowSystemMenuHint); // системное меню(правая кнопка мыши)
}

rezz::~rezz()
{
    delete ui;
}

void rezz::show_col(){
    QString cor=QString::number(mas);

    ui->cor->setText(cor);
    //mas=0;

    if(mas>=23){
        ui->cor->setStyleSheet("color: rgb(0, 255, 0);");
        ui->ozenka->setStyleSheet("color: rgb(0, 255, 0);font: 72pt \"Times New Roman\" ;");
        ui->ozenka->setText("5");

    }

    else if(mas<23 && mas>=21){
        ui->cor->setStyleSheet("color: rgb(255, 255, 0);");
        ui->ozenka->setStyleSheet("color: rgb(255, 255, 0);font: 72pt \"Times New Roman\" ;");
        ui->ozenka->setText("4");
    }
    else if(mas<21 && mas>19){
        ui->cor->setStyleSheet("color: rgb(255, 85, 0);");
        ui->ozenka->setStyleSheet("color: rgb(255, 85, 0);font: 72pt \"Times New Roman\" ;");
        ui->ozenka->setText("3");
    }
    else {
        ui->cor->setStyleSheet("color: rgb(255, 0, 0);");
        ui->ozenka->setStyleSheet("color: rgb(255, 0, 0);font: 72pt \"Times New Roman\" ;");
        ui->ozenka->setText("2");
    }

    mas=0;

}



