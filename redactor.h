#ifndef REDACTOR_H
#define REDACTOR_H

#include <QDialog>

namespace Ui {
class Redactor;
}

class Redactor : public QDialog
{
    Q_OBJECT

public:
    explicit Redactor(QWidget *parent = 0);
    ~Redactor();
    QStringList list;
    //int i=1;
    int i_f;


private slots:
    void zapis();
    void undis();
public slots:
    void add_text(int id);

private:
    Ui::Redactor *ui;
    virtual void closeEvent (QCloseEvent *event);
};

#endif // REDACTOR_H
