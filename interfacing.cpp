#include "interfacing.h"
#include "ui_interfacing.h"

interfacing::interfacing(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::interfacing)
{
    ui->setupUi(this);
    ui->txt_Terminal->installEventFilter(this);
    obj_port= new QSerialPort(this);
    connect(obj_port,SIGNAL(readyRead()),SLOT(readData()));
    obj_timer= new QTimer(this);
}

interfacing::~interfacing()
{
    delete ui;
}

void interfacing::on_actionQuit_triggered()
{
    if(obj_port->isOpen()){obj_port->close();}
    QApplication::quit();
}

void interfacing::on_actionAboutQt_triggered()
{
    QApplication::aboutQt();
}

void interfacing::readData(){
    QByteArray rawdata=obj_port->readAll();
    ui->txt_Terminal->insertPlainText(rawdata);
}

void interfacing::on_btn_Open_clicked()
{
    QString dev_name="/dev/";

    dev_name += ui->cmb_Port->currentText();

    QSerialPort::BaudRate dev_baud;
    QSerialPort::DataBits dev_DataBits;

    int baud_index=ui->cmb_Baud->currentIndex();
    int DataBits_index= ui->cmb_DataBits->currentIndex();

    switch(baud_index){
    case 0: dev_baud=QSerialPort::Baud9600;break;
    case 1: dev_baud=QSerialPort::Baud38400;break;
    case 2: dev_baud=QSerialPort::Baud57600;break;
    case 3: dev_baud=QSerialPort::Baud115200;break;
    }
    switch(DataBits_index){
    case 0: dev_DataBits=QSerialPort::Data5;break;
    case 1: dev_DataBits=QSerialPort::Data6;break;
    case 2: dev_DataBits=QSerialPort::Data7;break;
    case 3: dev_DataBits=QSerialPort::Data8;break;
    }


    if(ui->btn_Open->text()=="Open"){

       obj_port->setPortName(dev_name);

       if(obj_port->open(QIODevice::ReadWrite)){
//           obj_port->setBaudRate(dev_baud,QSerialPort::AllDirections);
           obj_port->setBaudRate(dev_baud);
           obj_port->setDataBits(dev_DataBits);
           obj_port->setStopBits(QSerialPort::OneStop);
           obj_port->setFlowControl(QSerialPort::NoFlowControl);
           obj_port->setParity(QSerialPort::NoParity);
           QMessageBox::information(this,"success","port success on "+dev_name );
           ui->btn_Open->setText("Close");
           ui->txt_portname->setText(dev_name);
                }
       else{
       QMessageBox::critical(this,"Failed","port failed on "+dev_name);

       ui->btn_Open->setText("Open");
       ui->txt_portname->clear();
       }

           }else{if(obj_port->isOpen()){obj_port->close();
               }
               ui->btn_Open->setText("Open");
               ui->txt_portname->clear();
           }
    }

bool interfacing::eventFilter(QObject *obj, QEvent *event){
    if(event->type()== QEvent::KeyPress){
        QKeyEvent* keyEvent = static_cast<QKeyEvent* >(event);
        if(obj_port->isOpen()){
            QString s = keyEvent->text();
            if(s.length()){
                char ch = s.at(0).toLatin1();
                QByteArray chb= QByteArray::fromRawData(&ch,1);
                obj_port->write(chb);

                if(ui->chk_LocalEcho->isChecked()){
                    ui->txt_Terminal->insertPlainText(chb);
                }
            }
        }
        return true;
    }
    else{
        return QObject::eventFilter(obj, event);
    }
}

void interfacing::on_btn_Clear_clicked()
{
    ui->txt_Terminal->clear();
}
