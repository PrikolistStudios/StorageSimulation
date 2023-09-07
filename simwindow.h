#ifndef SIMWINDOW_H
#define SIMWINDOW_H

#include "Product.h"
#include "Building.h"
#include "Wrapper.h"
#include "qwidget.h"
#include <vector>

namespace Ui {
class SimWindow;
}

class SimWindow : public QWidget {
  Q_OBJECT

public:
  explicit SimWindow(int days, int products, int shops,
                     std::vector<ProductType> products_types, double min_daily_discount, double max_daily_discount, std::vector<size_t> min_in_storage,
                     QWidget *parent = nullptr);
  ~SimWindow();

private slots:
  void on_NextDayButton_clicked();

  void on_PreviousDayButton_clicked();

private:
//  struct SellerQueryInfo{
//      int query_num, deadline;
//      ProductType type;
//      int num;
//  };

//  struct ShopQueryInfo{
//      int shop_num;
//      std::vector<std::pair<ProductType, int>> products;
//  };

//  struct SendingProducts{
//      int shop;
//      std::vector<Product> products;
//  };

//  struct DayData {
//    double income;
//    int completed_queries;
//    std::vector<Product> storage_products;
//    std::vector<SendingProducts> sending_products;
//    std::vector<ShopQueryInfo> shop_queries;
//    std::vector<SellerQueryInfo> seller_queries;
//  };
  void UpdateDateCounter();
  void CacheDay();
  void FillInUi(int day);

  Ui::SimWindow *ui;
  int days_, products_, shops_, current_day_=1;
  std::vector<ProductType> products_types_;
  Storage *storage_;
  Seller *seller_;
  std::vector<Shop *> shops_mas_;
  std::vector<DayData> days_info_;
};

#endif // SIMWINDOW_H
