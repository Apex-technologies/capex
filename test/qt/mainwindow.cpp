#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../../src/capex.h"

capex::array<float> Xa;
capex::array<float> Ya;

capex::array<capex::array<float>> T2D;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->YAxis_Bt->setChecked(false);
    ui->Cursor_Bt->setChecked(false);
    ui->XAxis_Bt->setChecked(false);
    ui->Tracer_Bt->setChecked(false);

    QDesktopWidget Dw;
    this->showMaximized();

    int Npts = 100000;

    Xa.linspace(0.0, 100.0, Npts);
    Ya.random(-0.05, 0.05, Npts);
    Ya = Ya + sin(Xa);

    QVector<double> x, y;

    for(unsigned int i = 0; i < Xa.size(); i++)
    {
        x.append(Xa[i]);
        y.append(Ya[i]);
    }

    // create graph and assign data to it:
    ui->qplot->addGraph();
    ui->qplot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->qplot->xAxis->setLabel("X Data");
    ui->qplot->yAxis->setLabel("Y Data");
    // set axes ranges, so we see all data:
    ui->qplot->xAxis->setRange(0.0, 100.0);
    ui->qplot->yAxis->setRange(-1.25, 1.25);

    ui->qplot->xAxis->ticker()->setTickCount(10);
    ui->qplot->yAxis->ticker()->setTickCount(10);
    ui->qplot->xAxis->setTicks(false);
    ui->qplot->yAxis->setTicks(false);
    ui->qplot->xAxis->setTickLabels(true);
    ui->qplot->yAxis->setTickLabels(false);

    ui->qplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    ui->dial->setMaximum(150 * Xa.max());
    ui->dial->setValue(10000);

    ui->qplot->addGraph();
    ui->qplot->addGraph();

    this->HC = 0.0;

    this->cursor = new QCPItemTracer(ui->qplot);
    this->cursor->setGraph(ui->qplot->graph(0));
    this->cursor->setGraphKey(0);
    this->cursor->setInterpolating(true);
    this->cursor->setStyle(QCPItemTracer::tsNone);
    this->cursor->setPen(QPen(Qt::magenta));
    this->cursor->setBrush(Qt::red);
    this->cursor->setSize(7);

}

MainWindow::~MainWindow()
{
    delete this->cursor;
    delete ui;
}

void MainWindow::on_Quit_Bt_clicked()
{
    quick_exit(0);
}

void MainWindow::on_dial_valueChanged(int value)
{
    if(ui->XAxis_Bt->isChecked())
    {
        ui->qplot->xAxis->setRange(0.0, (float)(value) / 100.0);
    }
    if(ui->YAxis_Bt->isChecked())
    {
        ui->qplot->yAxis->setRange(-(float)(value) / 100.0, (float)(value) / 100.0);
    }
    if(ui->Cursor_Bt->isChecked())
    {
        QVector<double> Hx, Hy, Vx, Vy;
        this->HC = (float)(value) / 100.0;
        Hx.append(this->HC); Hx.append(this->HC);
        Hy.append(-20.0); Hy.append(20.0);
        ui->qplot->graph(1)->setData(Hx, Hy);
        ui->qplot->graph(1)->setPen(QColor(50, 50, 50, 255));
        ui->qplot->graph(1)->setLineStyle(QCPGraph::lsImpulse);

        int I = Xa.near(Hx[0]);
        float VC = Ya[I];

        ui->label->setText(QString::number(VC));

        Vx.append(0.0); Vx.append(150.0);
        Vy.append(VC); Vy.append(VC);
        ui->qplot->graph(2)->setData(Vx, Vy);
        ui->qplot->graph(2)->setPen(QColor(50, 50, 50, 255));
        //ui->qplot->graph(2)->setLineStyle(QCPGraph::lsImpulse);
    }
    if(ui->Tracer_Bt->isChecked())
    {
        this->cursor->setGraphKey((float)(value) / 100.0);
    }
    ui->qplot->replot();
}

void MainWindow::on_XAxis_Bt_clicked()
{
    ui->YAxis_Bt->setChecked(false);
    ui->Cursor_Bt->setChecked(false);
    ui->XAxis_Bt->setChecked(true);
    ui->Tracer_Bt->setChecked(false);
    this->cursor->setStyle(QCPItemTracer::tsNone);

    QFont qf = ui->XAxis_Bt->font();
    qf.setBold(true);
    ui->XAxis_Bt->setFont(qf);
    qf.setBold(false);
    ui->YAxis_Bt->setFont(qf);
    ui->Cursor_Bt->setFont(qf);

    ui->dial->setMaximum(150 * Xa.max());
    ui->dial->setValue((int)(ui->qplot->xAxis->range().upper * 100));

}

void MainWindow::on_YAxis_Bt_clicked()
{
    ui->XAxis_Bt->setChecked(false);
    ui->Cursor_Bt->setChecked(false);
    ui->YAxis_Bt->setChecked(true);
    ui->Tracer_Bt->setChecked(false);
    this->cursor->setStyle(QCPItemTracer::tsNone);

    QFont qf = ui->XAxis_Bt->font();
    qf.setBold(true);
    ui->YAxis_Bt->setFont(qf);
    qf.setBold(false);
    ui->XAxis_Bt->setFont(qf);
    ui->Cursor_Bt->setFont(qf);

    ui->dial->setMaximum(150 * Ya.max());
    float Ymax = ui->qplot->yAxis->range().upper;
    ui->label->setText(QString::number(Ymax));
    ui->dial->setValue((int)(Ymax * 100));
}

void MainWindow::on_Cursor_Bt_clicked()
{
    ui->XAxis_Bt->setChecked(false);
    ui->YAxis_Bt->setChecked(false);
    ui->Cursor_Bt->setChecked(true);
    ui->Tracer_Bt->setChecked(false);
    this->cursor->setStyle(QCPItemTracer::tsNone);

    QFont qf = ui->XAxis_Bt->font();
    qf.setBold(true);
    ui->Cursor_Bt->setFont(qf);
    qf.setBold(false);
    ui->XAxis_Bt->setFont(qf);
    ui->YAxis_Bt->setFont(qf);

    ui->dial->setMaximum((int)(ui->qplot->xAxis->range().upper) * 100);
    if(this->HC > ui->qplot->xAxis->range().upper)
        this->HC = ui->qplot->xAxis->range().upper;
    ui->label->setText(QString::number(ui->qplot->xAxis->range().upper));
    ui->dial->setValue((int)(this->HC * 100));
}

void MainWindow::on_Tracer_Bt_clicked()
{
    ui->XAxis_Bt->setChecked(false);
    ui->YAxis_Bt->setChecked(false);
    ui->Cursor_Bt->setChecked(false);
    ui->Tracer_Bt->setChecked(true);

    ui->dial->setMaximum((int)(ui->qplot->xAxis->range().upper) * 100);
    ui->dial->setValue((int)(this->cursor->graphKey() * 100));
    this->cursor->setStyle(QCPItemTracer::tsCrosshair);
    ui->qplot->replot();
}
