#pragma once
#include <set>
#include <vector>
#include "MTime.h"
#include "Identificator.h"
#include "Price.h"
#include "Product.h"


enum QUERY_STATE {
  FAILED = -2,
  UNDEFINED = -1,
  CREATED,
  FILLED,
  SHIPPED
};

class IQuery {
 protected:
  QUERY_STATE current_state = UNDEFINED;
  Time start_time, deadline;
 public:
  IQuery(Time new_deadline);

  void setState(QUERY_STATE new_state);
  QUERY_STATE getState();

  bool isReady();
  Time getProductionTime();

  virtual void eraseList() = 0;  // вызвать перед деструктом
  virtual ~IQuery();
};

class QueryInfo {
 public:
  ProductType type;
  size_t amount;

  QueryInfo(ProductType new_type, size_t size);

  std::vector<Product*> list;

  void ship(std::vector<Product*>& prods);

  ~QueryInfo();
};

class ShopQuery : public IQuery {
 private:
  std::vector<QueryInfo> query_list;
 public:
  ShopQuery(Time new_deadline);

  void enqueue(ProductType another_type, size_t another_amount);
  void fill(std::vector<Product*>& outcome_products);

  std::vector<QueryInfo> getList();
  void sortByAmount();  

  void eraseList();

  ~ShopQuery();
};

class SellerQuery : public IQuery {
 private:
  std::vector<Package*> query_list;
  ProductType fill_type;

 public:
  SellerQuery(Time new_deadline, ProductType new_fill, size_t amount);

  std::vector<Package*> getList();
  void eraseList();

  ProductType getFillType();
  size_t getListSize();

  ~SellerQuery();
};
