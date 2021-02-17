#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    insertValue();

    ui->plot->addGraph();
    ui->plot->graph(0)->setData(vec_x, vec_y);
    ui->plot->xAxis->setLabel("x");
    ui->plot->yAxis->setLabel("y");

    ui->plot->xAxis->setRange(0,10);
    ui->plot->yAxis->setRange(0,20);

    ui->plot->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,10));

    QPen pen;
    pen.setColor(QColor(255,0,0));
    pen.setWidth(2);
    ui->plot->graph(0)->setPen(pen);

    ui->plot->graph(0)->setName("linear function");
    ui->plot->legend->setVisible(true);

    QCPItemText* itemText = new QCPItemText(ui->plot);
    itemText->setLayer("overlay");
    itemText->setPositionAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
    itemText->position->setType(QCPItemPosition::ptAxisRectRatio);
    itemText->position->setCoords(0.5,0.1);
    itemText->setText("Point Information\n");
    itemText->setPadding(QMargins(5,5,5,5));
    itemText->setPen(QPen(Qt::black)); // show black border around text
    itemText->setBrush(QColor(255,255,255));

    m_ItemText = itemText;
    connect(ui->plot, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(Slot_clickGraph(QCPAbstractPlottable*,int, QMouseEvent*)));

    ui->plot->replot();
}

void MainWindow::insertValue()
{
    vec_x.clear();
    vec_y.clear();

    qsrand(QTime::currentTime().msec());
    for(int i = 0; i < 10 ; i++) {
        int nRand = qrand() % 11;
        vec_x.append(i);
        vec_y.append(nRand);
    }
}

void MainWindow::Slot_clickGraph(QCPAbstractPlottable* potItem, int num, QMouseEvent* event)
{
    double dX = potItem->interface1D()->dataMainKey(num);
    double dY = potItem->interface1D()->dataMainValue(num);

    m_ItemText->setText(QString("Point Information\nX = %1\nY = %2").arg(QString::number(dX)).arg(QString::number(dY)));
    ui->plot->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}
