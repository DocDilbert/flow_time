#include <stdio.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

     connect(ui->start_button_, SIGNAL (released()), this, SLOT (HandleButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::HandleButton() {
    printf("HALLO\n");
}