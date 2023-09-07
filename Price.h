#pragma once


class Price {
 private:
  double default_price;
  double modificator = 1;

 public:
  Price();
  Price(double);

  void setModificator(double);
  double getFinalPrice();
  double getModificator();
};