#include "dialog_process.h"
#include "ui_dialog_process.h"

Dialog_Process::Dialog_Process(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Process)
{
    ui->setupUi(this);
}

Dialog_Process::~Dialog_Process()
{
    delete ui;
}

void Dialog_Process::change_percentage(int value)
{
    ui->progressBar->setValue(value);
    ui->label->setText(QString::number(value) + "%");
}

void Dialog_Process::print_info(const QString &info)
{
    ui->textEdit->append(info);
}

void Dialog_Process::finish()
{
    ui->buttonBox->setStandardButtons(QDialogButtonBox::Ok);
}
