#include "Building.h"


IBuilding::IBuilding(std::vector<ProductType>& new_types) {
    for (const auto& i : new_types) {
        all_types.push_back(i);
    }

    std::random_device dev;
    generator.seed(dev());
}

Storage::Storage(std::vector<ProductType>& new_types,
                 std::vector<size_t>& min_boards, double least_daily_coeff,
                 double greatest_daily_coeff)
    : IBuilding(new_types) {
    min_count.resize(all_types.size(), 0);
    all_time_amount.resize(all_types.size(), 0);
    refill_queries.resize(all_types.size(), nullptr);
    stock.resize(all_types.size(), nullptr);

    for (size_t i = 0; i < min_boards.size(); ++i) {
        min_count[i] = min_boards[i];

        stock[i] = new Package(all_types[i], true);
        stock[i]->autoFill(min_boards[i]);
    }

    manager = new Manager(all_types, least_daily_coeff, greatest_daily_coeff);
}

void Storage::makeQuery() {
    for (size_t i = 0; i < stock.size(); ++i) {
        if (stock[i]->getAmount() < min_count[i]) {
            if (refill_queries[i] == nullptr) {
                std::uniform_int_distribution<size_t> seller_time_ds(1, 5);

                size_t package_amount = std::ceil((min_count[i] - stock[i]->getAmount()) * 1.0 / stock[i]->getCapacity());
                Time delivery_time(seller_time_ds(generator));

                refill_queries[i] = new SellerQuery(delivery_time, all_types[i], package_amount);
                refill_queries[i]->setState(CREATED);
            }
        }
    }
}

std::vector<SellerQuery*> Storage::getListOfQueries() {
    return refill_queries;
}

void Storage::takeGoods() {
    for (size_t i = 0; i < refill_queries.size(); ++i) {
        if (refill_queries[i]!=nullptr) {
            if (refill_queries[i]->getState() == SHIPPED) {
                for (auto& package : refill_queries[i]->getList()) {
                    while (auto product = package->dequeue()) {
                        stock[i]->enqueue(product);

                        ++all_time_amount[i];
                        income -= product->getRealCost();
                    }

                    delete package;
                }

                delete refill_queries[i];
                refill_queries[i] = nullptr;
            }
        }
    }
}

void Storage::assembleShopQuery(ShopQuery*& another) {
    bool operated = false;
    ++all_queries;

    for (auto& typed_query : another->getList()) {
        size_t index = *typed_query.type;
        std::vector<Product*> postponed;
        double cost_of_postponed_prods = 0.0;

        if (stock[index]->getAmount() >= typed_query.amount) {
            while (typed_query.amount != postponed.size()) {
                auto product = stock[index]->dequeue();

                if (product->getRemainingTime() > 0) {
                    postponed.push_back(product);
                }

                if (!stock[index]->getAmount()) {
                    break;
                }
            }

            if (postponed.size() == typed_query.amount) {
                for (auto& prod : postponed) {
                    manager->setDiscountOnProduct(prod);
                    income += prod->getRealCost();
                }

                another->fill(postponed);
                operated = true;
            } else {
                while (!postponed.empty()) {
                    stock[index]->enqueue(postponed.back());
                    postponed.pop_back();
                }
            }
        }
    }

    if (operated) {
        another->setState(FILLED);
        ++completed_queries;
    } else {
        another->setState(FAILED);
    }
}

std::vector<Package*> Storage::getStock() { return stock; }
void Storage::cleanTrash() {
    for (auto& type : stock) {
        std::set<Product*> prods;

        while (auto product = type->dequeue()) {
            if (product->getRemainingTime() < 1) {
                delete product;
            } else {
                prods.insert(product);
            }
        }

        while (!prods.empty()) {
            type->enqueue(*prods.begin());
            prods.erase(prods.begin());
        }
    }
}

void Storage::openStorage() {
    income = completed_queries = all_queries = 0;
    manager->setNextDayDiscount();
}

DailyInfo Storage::closeStorage() {
    return {income, completed_queries, all_queries};
}

Seller::Seller(std::vector<ProductType>& new_types) : IBuilding(new_types) {
    queries.resize(new_types.size(), nullptr);
}

void Seller::updateQueries(std::vector<SellerQuery*>& list) {
    for (size_t i = 0; i < all_types.size(); ++i) {
        if (list[i]) {
            if (list[i]->getState() == CREATED) {
                queries[i] = list[i];

                queries[i]->setState(FILLED);
            }

            if (queries[i]->getState() == FILLED) {
                if (queries[i]->isReady()) {
                    queries[i]->setState(SHIPPED);
                }
            }
        }
    }
}

void Seller::tryShip() {
    for (size_t i = 0; i < all_types.size(); ++i) {
        if (queries[i]) {
            if (queries[i]->isReady()) {
                queries[i]->setState(SHIPPED);
            }
        }
    }
}

Shop::Shop(std::vector<ProductType>& new_types, size_t req_max)
    : IBuilding(new_types), max_amount_of_requested_prods(req_max)
{}

void Shop::generateQuery() {
    query = new ShopQuery(Time(1));

    std::uniform_int_distribution<size_t> types_ds(1, 5);
    size_t type_counts = types_ds(generator);

    std::uniform_int_distribution<size_t> type_qual_ds(0, all_types.size() - 1),
        amount_ds(1, max_amount_of_requested_prods);
    for (size_t i = 0; i < type_counts; ++i) {
        ProductType itype = all_types[type_qual_ds(generator)];
        query->enqueue(itype, amount_ds(generator));
    }

    query->setState(CREATED);
}

ShopQuery* Shop::getQuery() { return query; }

void Shop::shipQuery() {
    delete query;
    query = nullptr;
}

void Shop::sortByAmount() {
    if (query) {
        query->sortByAmount();
    }
}
