#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_flowWidget(new FlowGraphWidget(this))
{
    this->setCentralWidget(m_flowWidget); //takes ownership

}

MainWindow::~MainWindow()
{

}
