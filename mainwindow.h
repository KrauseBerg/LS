#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCodec>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void zap();
    ~MainWindow();

private slots:
    void showSetting();
    void showOtvet();
public slots:
    void fil_f(int j);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
