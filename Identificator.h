#pragma once
#include <string>
#include "MTime.h"


class ProductType {
 private:
  int index;
  std::string name;
  double weight;

  double cost;
  Time expiration_date;
 public:
  ProductType();
  ProductType(int, int, size_t, std::string&, double);

  std::string getLabel();

  int operator*();
  friend bool operator==(ProductType, ProductType);
  friend bool operator<(ProductType, ProductType);

  double getWeight();
  Time getExpDate();
  double getCost();

  std::string getName();

  ~ProductType();
};

inline bool operator==(ProductType first, ProductType second) {
  return *first == *second;
}

inline bool operator<(ProductType first, ProductType second) {
  return *first < *second;
}