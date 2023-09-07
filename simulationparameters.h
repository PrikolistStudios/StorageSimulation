#ifndef SIMULATIONPARAMETERS_H
#define SIMULATIONPARAMETERS_H

#include <QDialog>

namespace Ui {
class SimulationParameters;
}

class SimulationParameters : public QDialog {
  Q_OBJECT

public:
  explicit SimulationParameters(QWidget *parent = nullptr);
  ~SimulationParameters();
  int days() const { return days_; }
  int products() const { return products_; }
  int shops()const{return shops_;}
  double min_daily_discount()const{return min_daily_discount_;}
  double max_daily_discount()const{return max_daily_discount_;}

private slots:
  void on_OkButton_accepted();

private:
  Ui::SimulationParameters *ui;
  int days_, products_, shops_;
  double min_daily_discount_, max_daily_discount_;
};

#endif // SIMULATIONPARAMETERS_H
