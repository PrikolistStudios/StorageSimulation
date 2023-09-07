#include "Identificator.h"


ProductType::ProductType(int new_id, int start_price, size_t exp_date_abs, 
                         std::string& new_name, double new_weight) : index(new_id), 
  name(new_name), weight(new_weight), cost(start_price), expiration_date(exp_date_abs) {}
ProductType::ProductType() { index = -1, name = "", weight = -1.0; }

ProductType::~ProductType(){}

std::string ProductType::getLabel() { return name; }
int ProductType::operator*() { return index; }
double ProductType::getWeight() { return weight; }
double ProductType::getCost() { return cost; }
Time ProductType::getExpDate() { return expiration_date; }
std::string ProductType::getName() { return name; }