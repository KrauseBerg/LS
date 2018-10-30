#ifndef REZZ_H
#define REZZ_H

#include <QDialog>

namespace Ui {
class rezz;
}

class rezz : public QDialog
{
    Q_OBJECT

public:
    explicit rezz(QWidget *parent = 0);
    ~rezz();
    int mas;
public slots:
    void show_col();

private:
    Ui::rezz *ui;
};

#endif // REZZ_H
