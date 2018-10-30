#ifndef OTVET_H
#define OTVET_H

#include <QDialog>
#include <cstring>
#include <QShortcut>

using namespace std;
namespace Ui {
class otvet;
}

class otvet : public QDialog
{
    Q_OBJECT

public:
    explicit otvet(QWidget *parent = 0);
    ~otvet();
    vector <int> rand_f;


private slots:
    void check_o();
    void on_pod_triggered();

public slots:
    void show_1();

private:
    Ui::otvet *ui;
    string otv;
    QShortcut *key;

};

#endif // OTVET_H
