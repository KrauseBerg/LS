#ifndef QUEST_H
#define QUEST_H

#include <QDialog>
#include <QString>

namespace Ui {
class quest;
}

class quest : public QDialog
{
    Q_OBJECT

public:
    explicit quest(QWidget *parent = 0);
    QString p_name;

    ~quest();
private slots:
    void add_but();
    void delet();
    void show_rd();
public slots:
    bool add_bb();

private:
    Ui::quest *ui;
      virtual void closeEvent (QCloseEvent *even);
};

#endif // QUEST_H
