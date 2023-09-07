#include "Wrapper.h"


Wrapper::Wrapper(std::vector<ProductType>& new_types,
                 std::vector<size_t>& min_boards, double least_daily_coeff,
                 double greatest_daily_coeff, size_t shops_count, size_t shop_max) {
  storage = new Storage(new_types, min_boards, least_daily_coeff,
                        greatest_daily_coeff);

  seller = new Seller(new_types);

  for (size_t i = 0; i < shops_count; ++i) {
    Shop* next_shop = new Shop(new_types, shop_max);
    shops.push_back(next_shop);
  }

  // toggling first day
  global_timer.addDay();
  nextDay();
}

void Wrapper::nextDay() {
  daily_data.emplace_back();

  storage->openStorage();
  storage->cleanTrash(); // убираем испортившиеся продукты

  // отгружаем вчерашние заказы магазинам
  for (size_t i = 0; i < shops.size(); ++i) {
    auto cur_shop = shops[i];

    SendingProducts cur_shop_prods;
    cur_shop_prods.shop = i;

    if (cur_shop->getQuery()) {
      for (const auto& shipped_type : cur_shop->getQuery()->getList()) {
        for (const auto& shipped_prod : shipped_type.list) {
          cur_shop_prods.products.emplace_back(*shipped_prod);
        }
      }

      daily_data.back().sending_products.push_back(cur_shop_prods);

      cur_shop->shipQuery();
    }
  }

  // поставщик отсылает готовые заказы
  seller->tryShip();
  
  // забираем заказы y поставщика 
  storage->takeGoods();

  // получаем от магазинов заказы на следующий день
  for (size_t i = 0; i < shops.size(); ++i) {
    auto cur_shop = shops[i];

    cur_shop->generateQuery();
    cur_shop->sortByAmount(); // сначала самые крупные заказы [[внутри 1 типа]]

    ShopQueryInfo query_info;
    query_info.shop = i;

    auto cur_shop_query = cur_shop->getQuery();

    storage->assembleShopQuery(cur_shop_query);

    for (const auto& typed_info : cur_shop->getQuery()->getList()) {
      query_info.products.emplace_back(typed_info.type, typed_info.amount);
      int x = 1;
    }

    // filled если есть ХОТЯ БЫ 1 позиция по которой заказ принят в обработку \
       иначе failed
    int y = 1;
    query_info.state = cur_shop->getQuery()->getState();

    daily_data.back().shop_queries.push_back(query_info);
  }

  // заказываем у поставщика новые заказы если нужно

  storage->makeQuery();

  auto updated_list = storage->getListOfQueries();

  for (const auto& q : updated_list) {
    if (q) {
      if (q->getState() == CREATED) {
        SellerQueryInfo info;

        info.deadline = q->getProductionTime().get_day();
        info.query_size = q->getListSize();
        info.type = q->getFillType();

        daily_data.back().seller_queries.push_back(info);
      }
    }
  }

  // передаем поставщику заказы
  seller->updateQueries(updated_list);
//  updated_list.clear();

  auto stock_snapshot = storage->getStock();

  for (const auto& type : stock_snapshot) {
    std::vector<Product*> prods;

    while (auto prod = type->dequeue()) {
      prods.push_back(prod);
    }

    while (prods.size()) {
      daily_data.back().storage_products.emplace_back(*prods.back());
      type->enqueue(prods.back());
      prods.pop_back();
    }
  }

  auto storage_outcome = storage->closeStorage();

  daily_data.back().income = storage_outcome.day_income + daily_data[daily_data.size()-2].income;
  daily_data.back().completed_queries = storage_outcome.completed_queries;
  daily_data.back().all_queries = storage_outcome.all_queries;

  global_timer.addDay();
}

std::vector<DayData> Wrapper::returnDailyInformation() { return daily_data; }
