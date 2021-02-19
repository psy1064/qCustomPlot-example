#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    nIndex = 0;

    ui->plot->addGraph();

    ui->plot->xAxis->setLabel("x");
    ui->plot->yAxis->setLabel("y");     // 축 이름 설정

    ui->plot->xAxis->setRange(0,30);
    ui->plot->yAxis->setRange(0,20);    // 축 범위 설정

    ui->plot->graph(0)->setLineStyle(QCPGraph::lsLine);         // 그래프 종류
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,10));     // 그래프 좌표 데이터 포인트 설정

    QPen pen;
    pen.setColor(QColor(255,0,0));
    pen.setWidth(2);
    ui->plot->graph(0)->setPen(pen);            // 그래프 색, 굵기 설정

    ui->plot->graph(0)->setName("linear function");
    ui->plot->legend->setVisible(true);         // 범례

    QCPItemText* itemText = new QCPItemText(ui->plot);
    itemText->setLayer("overlay");
    itemText->setPositionAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
    itemText->position->setType(QCPItemPosition::ptAxisRectRatio);
    itemText->position->setCoords(0.5,0.1);
    itemText->setText("Point Information\n");
    itemText->setPadding(QMargins(5,5,5,5));
    itemText->setPen(QPen(Qt::black));
    itemText->setBrush(QColor(255,255,255));        // 데이터 정보 창
    m_ItemText = itemText;
//    m_ItemText->setVisible(false);
    ui->plot->layer("overlay")->setVisible(false);

    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iSelectAxes | QCP::iSelectLegend);
    // 그래프 상호작용 설정

    connect(ui->plot, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(Slot_clickGraph(QCPAbstractPlottable*,int, QMouseEvent*)));
    // 그래프 클릭 signal / slot
    connect(ui->pbStop, SIGNAL(clicked()), this, SLOT(Slot_finAddData()));

    qsrand(QTime::currentTime().msec());
    connect(&timer, SIGNAL(timeout()),this,SLOT(Slot_addData()));
    timer.start(100);


    ui->plot->replot();
}

void MainWindow::insertValue()
{
    vec_x.clear();
    vec_y.clear();

    qsrand(QTime::currentTime().msec());
    for(int i = 0; i <= 10 ; i++) {
        int nRand = qrand() % 11;
        vec_x.append(i);
        vec_y.append(nRand);
        nIndex = i;
    }

}

void MainWindow::Slot_clickGraph(QCPAbstractPlottable* potItem, int num, QMouseEvent* event)
{
    double dX = potItem->interface1D()->dataMainKey(num);
    double dY = potItem->interface1D()->dataMainValue(num);
//    m_ItemText->setVisible(true);
    ui->plot->layer("overlay")->setVisible(true);

    m_ItemText->setText(QString("Point Information\nX = %1\nY = %2").arg(QString::number(dX)).arg(QString::number(dY)));

    ui->plot->replot();
}

void MainWindow::Slot_addData()
{
    int nRand = qrand() % 11;
    ui->plot->graph(0)->addData(nIndex++, nRand);
    if ( nIndex >= 20 ) {
        ui->plot->xAxis->moveRange(1);
    }
    ui->plot->replot();
}

void MainWindow::Slot_finAddData()
{
    timer.stop();

    QFile file;
    file.setFileName("C:/Users/psy10/Desktop/work/test.csv");
    if( !file.open(QIODevice::ReadWrite)) qDebug() << "fail";

    QString data = "";
    data += ui->plot->xAxis->label();
    data += ",";
    data += ui->plot->yAxis->label();
    data += "\n";

    for (int i = 0 ; i < ui->plot->graph(0)->dataCount(); i++) {
        QString xValue = QString::number(ui->plot->graph(0)->dataMainKey(i));
        QString yValue = QString::number(ui->plot->graph(0)->dataMainValue(i));
        data += xValue + "," + yValue + "\n";
    }

    qDebug() << data;
    file.write(data.toLocal8Bit());

    file.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}
