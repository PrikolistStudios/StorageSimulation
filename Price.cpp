#include "Price.h"


Price::Price(double real_cost) : default_price(real_cost) {}
Price::Price() { default_price = 0; }

double Price::getFinalPrice() { return default_price * modificator; }

void Price::setModificator(double mod) { modificator = mod; }
double Price::getModificator() { return modificator; }