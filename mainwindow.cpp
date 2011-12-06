#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QGraphicsScene scene;
    scene.addLine(10,-10,20,-20,QPen(QColor(100,100,100,255)));
    scene.addText("Hello world");
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->show();
}
