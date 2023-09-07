#include "simwindow.h"
#include "QTreeWidget"
#include "simresultdialogue.h"
#include "ui_simwindow.h"
#include "Product.h"
#include "MTime.h"
SimWindow::SimWindow(int days, int products, int shops,
                     std::vector<ProductType> products_types,
                     double min_daily_discount, double max_daily_discount,
                     std::vector<size_t> min_in_storage, QWidget *parent)
    : QWidget(parent), ui(new Ui::SimWindow), days_(days), products_(products),
      shops_(shops), products_types_(products_types) {
    weight_limit=15.0;
  Wrapper wrapper(products_types, min_in_storage, min_daily_discount,max_daily_discount, shops_,17);
  for(int i = 2;i<=days_;++i){
      wrapper.nextDay();
  }
  days_info_=wrapper.returnDailyInformation();
  ui->setupUi(this);
  FillInUi(current_day_);
  UpdateDateCounter();
}

SimWindow::~SimWindow() { delete ui; }

void SimWindow::on_NextDayButton_clicked() {
  if (current_day_ == days_) {
    //    SimResultDialogue res;
    //    res.exec();
  } else {
    current_day_++;
    UpdateDateCounter();
    FillInUi(current_day_);
  }
}

void SimWindow::on_PreviousDayButton_clicked() {
  if (current_day_ == 1)
    return;
  current_day_--;
  UpdateDateCounter();
  FillInUi(current_day_);
}

void SimWindow::UpdateDateCounter() {
  QString text =
      "День " + QString::number(current_day_) + " из " + QString::number(days_);
  ui->DayCounterText->setText(text);
}

void SimWindow::FillInUi(int day) {
  auto day_info = days_info_[day - 1];
  ui->IncomeLabel->setText(QString::number(day_info.income));
  ui->CompletedOrderLabel->setText(QString::number(day_info.completed_queries));
  ui->AllQueriesQLabel->setText(QString::number(day_info.all_queries));

  ui->ShopsOrder->clear();
  for (auto &query : day_info.shop_queries) {
    QTreeWidgetItem *shop_item = new QTreeWidgetItem(ui->ShopsOrder);
      shop_item->setText(0, "Магазин " + QString::number(query.shop+1));
    for (auto query_info : query.products) {
      QTreeWidgetItem *item = new QTreeWidgetItem(shop_item);
      item->setText(1, QString::fromStdString(query_info.tp.getName()));
      item->setText(2, QString::number(query_info.amount));
    }
  }

  int query_num=1;
  ui->ProviderOrders->clear();
  for (auto &query : day_info.seller_queries) {
    QTreeWidgetItem *query_item = new QTreeWidgetItem(ui->ProviderOrders);
    query_item->setText(0, "Заказ " + QString::number(query_num++));
    query_item->setText(1, QString::number(query.deadline));
    query_item->setText(3, QString::number(query.query_size));
    query_item->setText(2, QString::fromStdString(query.type.getName()));
  }

  ui->StorageItems->clear();
  for (auto &prod : day_info.storage_products) {
    QTreeWidgetItem *pack_item = new QTreeWidgetItem(ui->StorageItems);
    pack_item->setText(0, QString::fromStdString(prod.getType().getName()));
    pack_item->setText(1, QString::number(prod.getCreationTime().get_day()+1));
    pack_item->setText(2, QString::number(
                              prod.getType().getExpDate().get_day()+1));
    pack_item->setText(3, QString::number(prod.getRealCost()));
  }

  ui->MadeUpOrders->clear();
  for (auto &val : day_info.sending_products) {
      if(val.products.empty())continue;
    QTreeWidgetItem *shop_item = new QTreeWidgetItem(ui->MadeUpOrders);
    shop_item->setText(0, "Магазин " + QString::number(val.shop+1));
    for (auto prod : val.products) {
      QTreeWidgetItem *pack_item = new QTreeWidgetItem(shop_item);
      pack_item->setText(1, QString::fromStdString(prod.getType().getName()));
      pack_item->setText(2, QString::number(prod.getRealCost()));
      pack_item->setText(3, QString::number(prod.getCreationTime().get_day()+1));
      pack_item->setText(4, QString::number(
                                prod.getType().getExpDate().get_day()+1));
    }
  }
}
