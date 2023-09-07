#include "Manager.h"


Manager::Manager(std::vector<ProductType>& types, double least_daily_coeff,
                 double greatest_daily_coeff)
    : all_types(types), daily_ds(least_daily_coeff, greatest_daily_coeff),
      type_ds(0, types.size() - 1) {
  std::random_device dev;
  generator.seed(dev());
}

void Manager::setNextDayDiscount() {
  size_t new_type = type_ds(generator);
  daily_type = all_types[new_type];
}

void Manager::setDiscountOnProduct(Product* prod) {
  Time time_left = prod->getRemainingTime();

  if (time_left == 5 || time_left == 4) {
    prod->setDiscount(expiring_date_coefficents[0]);
  } else if (time_left == 3 || time_left == 2) {
    prod->setDiscount(expiring_date_coefficents[1]);
  } else if (time_left == 1) {
    prod->setDiscount(expiring_date_coefficents[2]);
  }

  if (prod->getType() == daily_type) {
    prod->setDiscount(daily_ds(generator));
  }
}