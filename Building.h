#pragma once
#include "MTime.h"
#include "Identificator.h"
#include "Query.h"
#include <vector>
#include <random>
#include "Manager.h"


class IBuilding {
 protected:
  std::vector<ProductType> all_types;
  std::mt19937 generator;
 public:

  IBuilding(std::vector<ProductType>& new_types);
};

struct DailyInfo {
  double day_income = 0.0;
  size_t completed_queries = 0, all_queries = 0;
};

class Storage : public IBuilding {
 private:
  std::vector<Package*> stock;
  std::vector<size_t> min_count, all_time_amount;

  double income = 0;
  size_t completed_queries = 0, all_queries = 0;

  std::vector<SellerQuery*> refill_queries;

  Manager* manager = nullptr;
 public:
  Storage(std::vector<ProductType>& new_types, std::vector<size_t>& min_boards,
          double least_daily_coeff, double greatest_daily_coeff);

  DailyInfo closeStorage();
  void openStorage();

  void cleanTrash();
  std::vector<Package*> getStock();

  void makeQuery(); // ������� ������ ����������
  std::vector<SellerQuery*> getListOfQueries(); // �������� ������ ������� ����������
  void takeGoods(); // ������� ������������ ������ �� ����������

  void assembleShopQuery(ShopQuery*& another); // ���������� ����� ��������
};

class Seller : public IBuilding {
 private:
  std::vector<SellerQuery*> queries;
 public:
  Seller(std::vector<ProductType>& new_types);

  void updateQueries(std::vector<SellerQuery*>& list); // ������� ����� ������ �� ������, ���� ����
  void tryShip(); // ��������� �� ������ ������� ������ � ��������
};

class Shop : public IBuilding {
 private:
  ShopQuery* query = nullptr;
  size_t max_amount_of_requested_prods;

 public:
  Shop(std::vector<ProductType>& new_types, size_t req_max);

  void generateQuery(); // ����������� ����� �����
  ShopQuery* getQuery(); // �������� ����� ������

  void shipQuery(); // �������� �� ������ �����

  void sortByAmount();
};
