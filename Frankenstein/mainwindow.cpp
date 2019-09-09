#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

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

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->vague_arg_value->setText(QString::number(value)+"%");
}

void MainWindow::on_pushButton_clicked()
{
    ui->resource_dir->setText(QFileDialog::getExistingDirectory(this, "Select a directory", "/"));
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->target_path->setText(QFileDialog::getOpenFileName(this, "Select a picture", "/", tr("Images (*.jpg *.jpeg *.png *.bmp")));
}
