#include "simulationparameters.h"
#include "qmessagebox.h"
#include "ui_simulationparameters.h"
#include "QStackedLayout"
#include "qspinbox.h"


SimulationParameters::SimulationParameters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimulationParameters)
{
    ui->setupUi(this);
}

SimulationParameters::~SimulationParameters()
{
    delete ui;
}

void SimulationParameters::on_OkButton_accepted()
{
    if(ui->MinDailySpinBox->value()>=ui->MaxDailySpinBox->value()){
        QMessageBox msg;
        msg.setText("Минимальная дневная скидка должна быть меньше максимальной");
        msg.exec();
        return;
    }

    max_daily_discount_ = ui->MaxDailySpinBox->value();
    min_daily_discount_ = ui->MinDailySpinBox->value();
    days_ = ui->DaysSpinBox->value();
    shops_ = ui->ShopsSpinBox->value();
    products_ = ui->ProductsSpinBox->value();
    close();
}

