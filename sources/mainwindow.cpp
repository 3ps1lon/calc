#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>


double num_first;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(number()));
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(number()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(number()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(number()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(number()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(number()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(number()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(number()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(number()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(number()));

    connect(ui->pushButton_plusminus,SIGNAL(clicked()),this,SLOT(chang()));
    connect(ui->pushButton_procent,SIGNAL(clicked()),this,SLOT(chang()));

    connect(ui->pushButton_plus,SIGNAL(clicked()),this,SLOT(clk()));
    connect(ui->pushButton_minus,SIGNAL(clicked()),this,SLOT(clk()));
    connect(ui->pushButton_divide,SIGNAL(clicked()),this,SLOT(clk()));
    connect(ui->pushButton_star,SIGNAL(clicked()),this,SLOT(clk()));

    connect(ui->pushButton_leftskob,SIGNAL(clicked()),this,SLOT(skobki()));
    connect(ui->pushButton_rightskob,SIGNAL(clicked()),this,SLOT(skobki()));

    ui->pushButton_leftskob->setCheckable(true);
    ui->pushButton_rightskob->setCheckable(true);

    ui->pushButton_star->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);
    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
}

struct Leks{
    char type;
    double value;
};

QStack<Leks> Stack_n;
QStack<Leks> Stack_o;

QStack <Leks> Stack_n_2;
QStack <Leks> Stack_o_2;
Leks item;

std::string vir = "";
char oper;

MainWindow::~MainWindow()
{


    delete ui;
}


bool Math(QStack <Leks> & Stack_n,QStack <Leks> & Stack_o,Leks& item ){
    double a,b,c;
    char oper;
    std::cout<<"MATh"<<std::endl;
    a = Stack_n.top().value;

    if (Stack_n.size()==1){
        return false;
    }


    Stack_n.pop();


    switch (Stack_o.top().type) {
        case '+':
            b = Stack_n.top().value;
            Stack_n.pop();


            c = b+a;

            item.type = '0';
            item.value = c;
            Stack_o.pop();
            Stack_n.push(item);

            break;
    case '-':
        b = Stack_n.top().value;

        Stack_n.pop();



        c = b-a;

        item.type = '0';
        item.value = c;
        Stack_o.pop();
        Stack_n.push(item);
        break;
    case '*':
        b = Stack_n.top().value;
        Stack_n.pop();



        c = b*a;

        item.type = '0';
        item.value = c;
        Stack_o.pop();
        Stack_n.push(item);

        break;
    case '/':
            b = Stack_n.top().value;


            if (a == 0) {

                    return false;
                }
            else {

                Stack_n.pop();
                c = (b / a);
                item.type = '0';
                item.value = c;

                Stack_o.pop();
                Stack_n.push(item);
                break;
            }
    default:

        return false;

}

    return true;
}

int getRang(char Ch) { //Функция возвращает приоритет операции: "1" для сложения и вычитания, "2" для умножения и деления и т.д.
    if (Ch == '+' || Ch == '-')return 2;
    if (Ch == '*' || Ch == '/')return 3;
    else return 0;
}

void MainWindow::skobki(){
    QPushButton *button = (QPushButton *) sender();

    QString label_l;


    if (ui->pushButton_leftskob->isChecked()){
            oper = '(';
            item.type = oper;
            item.value = 0;
            Stack_o.push(item);
            std::cout<<"("<<std::endl;
           ui->pushButton_leftskob->setChecked(false);
        }
    if (ui->pushButton_rightskob->isChecked()){
    std::cout<<")"<<std::endl;
        while (Stack_o.top().type != '(') {
                            if (Math(Stack_n, Stack_o, item) == false) {
                            }

            }
           ui->pushButton_rightskob->setChecked(false);
        }
    Stack_o.pop();
    ui->resualt->setText(label_l);
    button->setChecked(true);

}

  double num;
void MainWindow::number(){
    QPushButton *button = (QPushButton *) sender();


    QString label_l;

    num = (ui->resualt->text()+button->text()).toDouble();
    label_l = QString::number(num, 'g', 16);


    ui->resualt->setText(label_l);

}

void MainWindow::on_pushButton_dot_clicked()
{
    if(!ui->resualt->text().contains('.')){
         ui->resualt->setText(ui->resualt->text()+".");
    }

}

void MainWindow::chang(){
    QPushButton *button = (QPushButton *) sender();

    double num;
    QString label_l;

    if (button->text() == "+/-"){
        num = (ui->resualt->text()).toDouble();
        num *=(-1);
        Stack_n.pop();
        item.type = '0';
        item.value = num;
        Stack_n.push(item);
        label_l = QString::number(num, 'g', 16);
        ui->resualt->setText(label_l);
    }
    else if (button->text() == "%"){
        num = (ui->resualt->text()).toDouble();
        num *= 0.01;
        label_l = QString::number(num, 'g', 16);
        ui->resualt->setText(label_l);
    }

}




void MainWindow::clk(){

    QPushButton *button = (QPushButton *) sender();
    QString label_l;


    button->setChecked(true);

    math_operations();
    ui->resualt->setText("");



}

void MainWindow::math_operations()
{

     QString label_l;
    std::cout<<"num "<<num<<std::endl;
     if (num!=0){
         vir += ui->resualt->text().toStdString();
         item.type ='0';
         item.value = num;
         Stack_n.push(item);
         num =0;
     }

     if (ui->pushButton_plus->isChecked()){
             oper = '+';

            ui->pushButton_plus->setChecked(false);
         }
         else if (ui->pushButton_minus->isChecked()){
         oper = '-';

             vir +="-";


             ui->pushButton_minus->setChecked(false);

         }
         else if (ui->pushButton_divide->isChecked()){
         oper = '/';
             vir +="/";

             ui->pushButton_divide->setChecked(false);
         }
         else if (ui->pushButton_star->isChecked()){
                         oper = '*';
                         vir +="*";

             ui->pushButton_star->setChecked(false);
         }

     if (Stack_o.size() != 0 && getRang(oper) >
                                getRang(Stack_o.top().type && Stack_o.top().type != '(')) {
         item.type = oper;
         item.value = 0;
         Stack_o.push(item);


     }
     else if (Stack_o.size() != 0 && getRang(oper) <=
                                getRang(Stack_o.top().type) && Stack_o.top().type != '(') {
         if (Math(Stack_n, Stack_o, item) == false) {

         }

     }

     if (Stack_o.size() == 0) {
         item.type = oper;
         item.value = 0;
         Stack_o.push(item);

     }


     std::cout<<"oper "<< oper<<std::endl;


ui->resualt->setText(label_l);


}

void MainWindow::on_pushButton_AC_clicked()
{
         num_first = 0;
         ui->resualt->setText("0");
         Stack_n.clear();
         Stack_o.clear();
}


void MainWindow::on_pushButton_ec_clicked()

{   std::cout<<Stack_n.size()<<" " << Stack_o.size()<<std::endl;
    std::cout<<"EC "<<Stack_n.top().value<<std::endl;
    clk();


    double Num;
    QString label_l;
    while (Stack_o.size()!=0){

         if (Math(Stack_n,Stack_o,item) == false){

             break;

         }
         else  continue;

    }


       ui->resualt->setText(QString::number (Stack_n.top().value));



    while (!Stack_n.empty()){
        Stack_n.pop();
    }
    while (!Stack_o.empty()){
        Stack_o.pop();
    }

}


void MainWindow::on_pushButton_bin_clicked()
{
    QString label_l, tt,res;
    int k;
    num_first = ui->resualt->text().toDouble();
    k = (int) num_first;
    tt = "";
    label_l = QString::number(num_first, 'g', 16);
    if(!ui->resualt->text().contains('.')){
       while (k>0){
           tt = QString::number(k%2)+tt;
           k= k/2;
       }
       ui->resualt->setText(tt);

    }


}


void MainWindow::on_pushButton_sin_clicked()
{
    QString label_l, tt,res;
    int k;
    num_first = ui->resualt->text().toDouble();
    k = (int) num_first;
    tt = "";
    label_l = QString::number(num_first, 'g', 16);
    if(!ui->resualt->text().contains('.')){
       while (k>0){
           tt = QString::number(k%8)+tt;
           k= k/8;
       }
       ui->resualt->setText(tt);
    }


}


void MainWindow::on_pushButton_cos_clicked()
{
    QString label_l, tt,res;
    int k;
    num_first = ui->resualt->text().toDouble();
    k = (int) num_first;
    label_l = QString::number(num_first, 'g', 16);
    if(!ui->resualt->text().contains('.')){
      ui->resualt->setText(tt.setNum(k,16));
    }


}

