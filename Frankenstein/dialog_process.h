#ifndef DIALOG_PROCESS_H
#define DIALOG_PROCESS_H

#include <QDialog>

namespace Ui {
class Dialog_Process;
}

class Dialog_Process : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Process(QWidget *parent = nullptr);
    ~Dialog_Process();

private:
    Ui::Dialog_Process *ui;

public slots:
    void change_percentage(int value);
    void print_info(const QString& info);
    void finish();
};

#endif // DIALOG_PROCESS_H
