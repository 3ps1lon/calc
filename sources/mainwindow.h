#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QStack>
#include <string>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void number();
    void on_pushButton_dot_clicked();
    void chang();

    void on_pushButton_AC_clicked();
    void on_pushButton_ec_clicked();

    void clk();

    void math_operations( );
    void on_pushButton_bin_clicked();
    void on_pushButton_sin_clicked();
    void on_pushButton_cos_clicked();

    void skobki();
};
#endif // MAINWINDOW_H
