#pragma once
#include "MTime.h"
#include "Product.h"
#include <vector>
#include <random>


class Manager {
 private:
  // -1 = full price
  // 0 = +(5-4) days before expiring - 10%
  // 1 = +(3-2) days before expiring - 15%
  // 2 = +(1) days before expiring - 25%
  std::vector<double> expiring_date_coefficents = {0.1, 0.15, 0.25};

  std::mt19937 generator;
  std::uniform_real_distribution<> daily_ds;
  std::uniform_int_distribution<size_t> type_ds;

  std::vector<ProductType> all_types;
  ProductType daily_type;

 public:
  Manager(std::vector<ProductType>& types, double least_daily_coeff, 
          double greatest_daily_coeff);

  void setNextDayDiscount(); // randomly generator
  void setDiscountOnProduct(Product* prod);
};