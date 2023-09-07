#ifndef SIMRESULTDIALOGUE_H
#define SIMRESULTDIALOGUE_H

#include <QDialog>

namespace Ui {
class SimResultDialogue;
}

class SimResultDialogue : public QDialog
{
  Q_OBJECT

public:
  explicit SimResultDialogue(QWidget *parent = nullptr);
  ~SimResultDialogue();

  private slots:
  void on_buttonBox_accepted();

  private:
  Ui::SimResultDialogue *ui;
};

#endif // SIMRESULTDIALOGUE_H
