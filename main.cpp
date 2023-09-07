#include "mainwindow.h"
#include "productsparameters.h"
#include "simulationparameters.h"
#include "simwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
    SimulationParameters params;
  params.exec();
  ProductsParameters products(params.products());
  products.exec();
  SimWindow sim(params.days(), params.products(), params.shops(),
                products.GetProducts(), params.min_daily_discount(),
                params.max_daily_discount(), products.min_in_storage());
  sim.show();
  return a.exec();
}
