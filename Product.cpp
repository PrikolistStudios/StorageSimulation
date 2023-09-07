#include "Product.h"


double weight_limit = 0;

Product::Product() {}

Product::Product(ProductType new_type)
    : type(new_type), dynamic_cost(new_type.getCost()) {
  creation_time = global_timer.getTime();
}

Product::Product(const Product& prod) : dynamic_cost(prod.dynamic_cost), type(prod.type), creation_time(prod.creation_time) {}

void Product::setDiscount(double value) { dynamic_cost.setModificator(std::max(0.25, dynamic_cost.getModificator() * value)); }

bool Product::operator==(Product other) { return *other.type == *type; }

double Product::getRealCost() { return dynamic_cost.getFinalPrice(); }

ProductType Product::getType() { return type; }

Time Product::getCreationTime() { return creation_time; }

Time Product::getRemainingTime() {
  Time create_time = getCreationTime();
  Time end_time = create_time + type.getExpDate();
  Time time_left = end_time - global_timer.getTime();

  return time_left;
}

Product::~Product(){}

Package::Package(bool status_elong) : elongable(status_elong) {}
Package::Package(ProductType new_type, bool status_elong)
    : default_type(new_type), elongable(status_elong) {
  capacity = weight_limit / new_type.getWeight();
}

bool Package::enqueue(Product* another) {
  if (capacity == product_list.size() && !elongable) {
    return false;
  }

  product_list.insert(another);
  //++capacity;

  return true;
}

Product* Package::dequeue() {
  if (!product_list.size()) {
    return nullptr;
  }

  auto newest = *product_list.begin();
  product_list.erase(product_list.begin());

  //--capacity;

  return newest;
}

Price Product::getPrice() { return dynamic_cost; }

double Package::getAggregatedCost() {
  double cost = 0.0;

  for (const auto& prod : product_list) {
    cost += prod->getRealCost();
  }

  return cost;
}

void Package::autoFill(size_t amount) {
  while (!product_list.empty()) {
    auto prod = product_list.begin();
    product_list.erase(product_list.begin());

    delete *prod;
    //*prod = nullptr;
  }

  for (size_t i = 0; i < std::min(capacity, amount); ++i) {
    product_list.insert(new Product(default_type));
  }
}

size_t Package::getAmount() { return product_list.size(); }
size_t Package::getCapacity() { return capacity; }
