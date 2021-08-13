#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    counter = 0;

    QTimer1 = new QTimer(this);
    connect(QTimer1, &QTimer::timeout, this, &MainWindow::onQTimer1);

    QPaintBox1 = new QPaintBox(0, 0, ui->widget);
}

MainWindow::~MainWindow()
{
    delete QTimer1;
    delete QPaintBox1;
    delete ui;
}

void MainWindow::onQTimer1(){
    QDateTime dt;
    float rad;
    int hour, mins, secs, mSecs, xi, yi, xf, yf;
//    int w, h, radius;

    QPen pen;
    QBrush brush;
    QPainter paint(QPaintBox1->getCanvas());

    counter++;
    if(counter==100)
        counter = 0;

    ui->lcdNumber->display(QString("%1").arg(counter, 2, 10, QChar('0')));
    ui->lineEdit->setText(dt.currentDateTime().toString("hh:mm:ss.zzz-dd/MM/yyyy"));

    hour = dt.currentDateTime().time().hour();
    mins = dt.currentDateTime().time().minute();
    secs = dt.currentDateTime().time().second();
    mSecs = dt.currentDateTime().time().msec();

    pen.setWidth(5);
    pen.setColor(Qt::blue);
    paint.setPen(pen);
    brush.setColor(Qt::white);
    brush.setStyle(Qt::SolidPattern);
    paint.setBrush(brush);
    paint.drawEllipse(180, 25, 400, 400);

    pen.setColor(Qt::black);
    pen.setWidth(3);
    paint.setPen(pen);
    for(int i= 0; i<360; i+=6){
        rad = i*M_PI/180;
        if(!(i%30)){
            xi = 380+175*cos(rad);
            yi = 225-175*sin(rad);
        }else{
            xi = 380+185*cos(rad);
            yi = 225-185*sin(rad);
        }
        xf = 380+196*cos(rad);
        yf = 225-196*sin(rad);
        paint.drawLine(xi, yi, xf, yf);
    }

    rad = (90-(6*secs+0.6*mSecs/100))*M_PI/180;
        xf = 380+190*cos(rad);
        yf = 225-190*sin(rad);
        pen.setColor(Qt::darkGray);
        pen.setWidth(2);
        paint.setPen(pen);
        paint.drawLine(380, 225, xf, yf);

        rad = (90-6*mins)*M_PI/180;
        xf = 380+170*cos(rad);
        yf = 225-170*sin(rad);
        pen.setColor(Qt::blue);
        pen.setWidth(2);
        paint.setPen(pen);
        paint.drawLine(380, 225, xf, yf);

        if(hour <12)
            hour -= 12;
        rad = (90-30*hour)*M_PI/180;
        xf = 380+140*cos(rad);
        yf = 225-140*sin(rad);
        pen.setColor(Qt::blue);
        pen.setWidth(4);
        paint.setPen(pen);
        paint.drawLine(380, 225, xf, yf);

    QPaintBox1->update();
}

void MainWindow::on_pushButton_clicked()
{
    if(QTimer1->isActive()){
        QTimer1->stop();
        ui->pushButton->setText("ON");
    }else{
        QTimer1->start(100);
        ui->pushButton->setText("OFF");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
//    ui->lineEdit->clear();
}
