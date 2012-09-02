#include <enginegl.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    glwidget = new opengl_test_widget_t(this);
    ui->centralLayout->addWidget(glwidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
