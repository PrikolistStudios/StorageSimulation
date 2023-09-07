#include "Query.h"
#include <algorithm>


IQuery::IQuery(Time new_deadline)
    : start_time(global_timer.getTime()), deadline(new_deadline) {}
IQuery::~IQuery() {}

void IQuery::setState(QUERY_STATE new_state) { current_state = new_state; }
QUERY_STATE IQuery::getState() { return current_state; }

bool IQuery::isReady() {
    return start_time + deadline == global_timer.getTime();
}

Time IQuery::getProductionTime() { return deadline; }

void QueryInfo::ship(std::vector<Product*>& prods) {
    while (amount != list.size()) {
        list.push_back(prods.back());
        prods.pop_back();
    }
}

QueryInfo::QueryInfo(ProductType new_type, size_t size) : type(new_type), amount(size) {}

QueryInfo::~QueryInfo() {
    list.clear();
}

ShopQuery::ShopQuery(Time new_deadline) : IQuery(new_deadline) {}

void ShopQuery::eraseList() {
    query_list.clear();
}

ShopQuery::~ShopQuery() { eraseList(); }

void ShopQuery::enqueue(ProductType another_type, size_t another_amount) {
    query_list.emplace_back(another_type, another_amount);
}

void ShopQuery::fill(std::vector<Product*>& outcome_products) {
    ProductType fill_type = outcome_products[0]->getType();

    for (auto& i : query_list) {
        if (*i.type == *fill_type && i.amount == outcome_products.size()) {
            i.ship(outcome_products);
        }

        if (outcome_products.empty()) {
            break;
        }
    }
}

std::vector<QueryInfo> ShopQuery::getList() {
    return query_list;
}

void ShopQuery::sortByAmount() {
    std::sort(query_list.begin(), query_list.end(),
              [](QueryInfo a, QueryInfo b) {
                  if (a.type == b.type) {
                      return a.amount > b.amount;
                  }

                  return a.type < b.type;
              });
}

SellerQuery::SellerQuery(Time new_deadline, ProductType new_fill, size_t amount)
    : fill_type(new_fill), IQuery(new_deadline) {
    for (size_t i = 0; i < amount; ++i) {
        query_list.push_back(new Package(new_fill));
        query_list.back()->autoFill();
    }
}

std::vector<Package*> SellerQuery::getList() { return query_list; }

void SellerQuery::eraseList() {
    for (auto& i : query_list) {
        i = nullptr;
    }

    query_list.clear();
}

SellerQuery::~SellerQuery() { eraseList(); }

ProductType SellerQuery::getFillType() { return fill_type; }
size_t SellerQuery::getListSize() { return query_list.size(); }
