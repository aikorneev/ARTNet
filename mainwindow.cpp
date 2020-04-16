#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;

    ARTnet = new net(10);
    qDebug() << "shownet";
    ARTnet->show_net();

    double x1[10]={1,1,0,1,1,1,0,1,0,1};
    ARTnet->new_input(x1, 10);
    double x2[10]={0,0,1,0,0,1,1,1,1,1};
    ARTnet->new_input(x2, 10);
    double x3[10]={1,1,1,1,1,1,0,1,0,1};
    ARTnet->new_input(x3, 10);
    double x4[10]={0,0,1,0,0,0,1,1,1,1};
    ARTnet->new_input(x4, 10);
    double x5[10]={1,0,1,0,0,1,1,1,1,1};
    ARTnet->new_input(x5, 10);

    qDebug() << "shownet";
    ARTnet->show_net();

}

