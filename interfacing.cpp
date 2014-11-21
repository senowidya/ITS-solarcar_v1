#include "interfacing.h"
#include "ui_interfacing.h"

interfacing::interfacing(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::interfacing)
{
    ui->setupUi(this);
}

interfacing::~interfacing()
{
    delete ui;
}
