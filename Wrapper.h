#pragma once
#include "MTime.h"
#include "Product.h"
#include "Building.h"
#include <vector>


struct SellerQueryInfo {
  size_t query_size, deadline;
  ProductType type;
};

struct DetailInfo {
  ProductType tp;
  size_t amount;

  DetailInfo(ProductType type, size_t new_amount) {
    tp = type;
    amount = new_amount;
  }
};

struct ShopQueryInfo {
  size_t shop;
  std::vector<DetailInfo> products;

  QUERY_STATE state;
};

struct SendingProducts {
  size_t shop;
  std::vector<Product> products;
};

struct DayData {
  double income=0;
  size_t completed_queries=0, all_queries=0;

  // скопированные продукты НЕ указатели =>
  // => предоставляют только информацию о состоянии а не реальное состояние

  std::vector<Product> storage_products;
  std::vector<SendingProducts> sending_products;

  std::vector<ShopQueryInfo> shop_queries;
  std::vector<SellerQueryInfo> seller_queries;
};

class Wrapper {
 private:
  std::vector<DayData> daily_data;
  Storage* storage = nullptr;
  Seller* seller = nullptr;

  std::vector<ProductType> types;
  std::vector<Shop*> shops;
 public:
  Wrapper(std::vector<ProductType>& new_types, std::vector<size_t>& min_boards,
          double least_daily_coeff, double greatest_daily_coeff, size_t shop_count, size_t shop_maximum);
  void nextDay();
  std::vector<DayData> returnDailyInformation();
};
