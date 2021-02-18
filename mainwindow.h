#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "qcustomplot/qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void insertValue();
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QVector<double> vec_x,vec_y;
    QCPItemText* m_ItemText;
    int nIndex;
    QTimer timer;

public slots:
    void Slot_clickGraph(QCPAbstractPlottable*, int, QMouseEvent*);
    void Slot_addData();
};

#endif // MAINWINDOW_H
