#pragma once
#include <vector>
#include <set>
#include "MTime.h"
#include "Identificator.h"
#include "Price.h"


//extern Timer global_timer;
extern double weight_limit;

class Product {
 private:
  Time creation_time;

  ProductType type;
  Price dynamic_cost;
 public:
  Product();
  Product(ProductType);

  Product(const Product&);

  // from (0.0, 1]
  void setDiscount(double value);
  double getRealCost();
  Price getPrice();

  ProductType getType();
  Time getCreationTime();
  Time getRemainingTime();

  ~Product();

  bool operator==(Product other);

  friend bool operator<(Product&, Product&);
};

inline bool operator<(Product& first, Product& second) {
  return first.creation_time > second.creation_time;
}

class Package {
 private:
  std::set<Product*> product_list;
  ProductType default_type;

  size_t capacity;
  //double weight_limit = 5000; // in kg

  bool elongable;
 public:
  Package(bool status_elong = false);
  Package(ProductType new_def, bool status_elong = false);

  bool enqueue(Product* another);
  Product* dequeue();
  void autoFill(size_t amount = 1e10);

  double getAggregatedCost();
  size_t getAmount();
  size_t getCapacity();
};