#ifndef PRODUCTSPARAMETERS_H
#define PRODUCTSPARAMETERS_H

#include <QDialog>
#include "Product.h"
#include "Identificator.h"

namespace Ui {
class ProductsParameters;
}

class ProductsParameters : public QDialog
{
    Q_OBJECT

public:
    explicit ProductsParameters(int products_, QWidget *parent = nullptr);
    ~ProductsParameters();

    std::vector<ProductType> GetProducts(){return product_types_;}
    std::vector<size_t> min_in_storage(){return min_in_storage_;}
private slots:
    void on_pushButton_clicked();

private:
    Ui::ProductsParameters *ui;
    int products_, products_made_=0;
    std::vector<ProductType> product_types_;
    std::vector<size_t> min_in_storage_;
};

#endif // PRODUCTSPARAMETERS_H
