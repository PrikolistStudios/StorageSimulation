#include "simresultdialogue.h"
#include "ui_simresultdialogue.h"

SimResultDialogue::SimResultDialogue(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::SimResultDialogue)
{
  ui->setupUi(this);
}

SimResultDialogue::~SimResultDialogue()
{
  delete ui;
}

void SimResultDialogue::on_buttonBox_accepted()
{
    close();
}

