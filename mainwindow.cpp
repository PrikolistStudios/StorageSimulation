#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qformlayout.h"
#include "qspinbox.h"
#include "simwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_OkButton_accepted()
{
    SimWindow sim(ui->DaysSpinBox->value(), ui->ProductsSpinBox->value(), ui->ShopsSpinBox->value());
    close();
    sim.show();
}

