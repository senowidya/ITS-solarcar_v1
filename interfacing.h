#ifndef INTERFACING_H
#define INTERFACING_H

#include <QMainWindow>
#include <QSerialPort>
#include <QMessageBox>
#include <QTimer>
#include <QTime>


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

private slots:

};

#endif // INTERFACING_H
