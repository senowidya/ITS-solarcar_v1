#include "interfacing.h"
#include "ui_interfacing.h"

interfacing::interfacing(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::interfacing)
{
    ui->setupUi(this);
    ui->txt_terminal->installEventFilter(this);
}

interfacing::~interfacing()
{
    delete ui;
}
