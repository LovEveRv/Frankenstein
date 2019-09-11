#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controller.h"
#include "messager.h"
#include "dialog_process.h"
#include <QFileDialog>
#include <QThread>

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
    ui->resource_dir->setText(QFileDialog::getExistingDirectory(this, "Select a directory", "/"));
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->target_path->setText(QFileDialog::getOpenFileName(this, "Select a picture"));
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->save_path->setText(QFileDialog::getSaveFileName(this, "Save as"));
}

void MainWindow::on_pushButton_3_clicked()
{
    Settings::PROCESSING_WIDTH = ui->spin_width->value();
    Settings::PROCESSING_HEIGHT = ui->spin_height->value();
    switch(ui->comboBox->currentIndex())
    {
    case 0:
        Settings::ALIGN = Settings::ALIGN_LEFT_TOP;
        break;
    case 1:
        Settings::ALIGN = Settings::ALIGN_CENTER;
        break;
    case 2:
        Settings::ALIGN = Settings::ALIGN_RIGHT_BOTTOM;
        break;
    }
    switch(ui->quality_choice->currentIndex())
    {
    case 0:
        Settings::OUTPUT_QUALITY = Settings::QUALITY_MAXIMUM;
        break;
    case 1:
        Settings::OUTPUT_QUALITY = Settings::QUALITY_MINIMUM;
        break;
    case 2:
        Settings::OUTPUT_QUALITY = Settings::QUALITY_SUITABLE;
        break;
    }
    Settings::BLOCKS_PER_ROW = ui->spin_bprow->value();
    QThread *thread = new QThread;
    Main_Controller *controller = new Main_Controller(nullptr, ui->resource_dir->text().toStdString(), ui->target_path->text().toStdString(), ui->save_path->text().toStdString());
    controller->moveToThread(thread);
    msg = new Messager;
    msg->moveToThread(thread);
    connect(thread, &QThread::started, controller, &Main_Controller::execute);
    connect(controller, &Main_Controller::finished, thread, &QThread::quit);
    connect(thread, &QThread::finished, controller, &QObject::deleteLater);
    connect(thread, &QThread::finished, msg, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    Dialog_Process dia(this);
    connect(controller, &Main_Controller::finished, &dia, &Dialog_Process::finish);
    connect(msg, &Messager::info_printed, &dia, &Dialog_Process::print_info);
    connect(msg, &Messager::percentage_changed, &dia, &Dialog_Process::change_percentage);
    thread->start();
    if(dia.exec() != QDialog::Accepted)
    {
        thread->quit();
    }
}
