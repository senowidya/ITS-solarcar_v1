#ifndef INTERFACING_H
#define INTERFACING_H

#include <QMainWindow>

namespace Ui {
class interfacing;
}

class interfacing : public QMainWindow
{
    Q_OBJECT

public:
    explicit interfacing(QWidget *parent = 0);
    ~interfacing();

private:
    Ui::interfacing *ui;
};

#endif // INTERFACING_H
