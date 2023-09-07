#include "productsparameters.h"
#include "ui_productsparameters.h"
#include <QMessageBox>

ProductsParameters::ProductsParameters(int products, QWidget *parent)
    : QDialog(parent), ui(new Ui::ProductsParameters), products_(products), min_in_storage_(products) {
  ui->setupUi(this);
}

ProductsParameters::~ProductsParameters() { delete ui; }

void ProductsParameters::on_pushButton_clicked() {
  bool name_correct = true;
  for (auto val : product_types_) {
    if (val.getName() == ui->ProductNameLine->text().toStdString()) {
      name_correct = false;
      break;
    }
  }

  if (!name_correct) {
      QMessageBox msg;
      msg.setText("Продукт с таким названием уже существует");
      msg.exec();
    return;
  }
  products_made_++;
  std::string name = ui->ProductNameLine->text().toStdString();
  int age = ui->AgeSpinBox->value();
  int price = ui->CostSpinBox->value();
  double weight = ui->WeightDoubleSpinBox->value();
  min_in_storage_[products_made_-1]=ui->MinInStorageSpinBox->value();
  product_types_.push_back(
      ProductType(products_made_-1,price,age,name,weight));
  if (products_made_ == products_) {
    close();
  } else {
    ui->CurPruductLabel->setText("Введите информацию о " +
                                 QString::number(products_made_ + 1) +
                                 " продукте");
  }
}
