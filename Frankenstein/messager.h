#ifndef MESSAGER_H_
#define MESSAGER_H_
#include <QObject>

class Messager : public QObject //Showing messages to create an interface
{
    Q_OBJECT
private:
    int former_percentage;

public slots:
    void reset_percentage() {former_percentage = 0; emit percentage_changed(0);}
    void print_info(const std::string& info) {emit info_printed(QString::fromStdString(info));}
    void show_percentage(int percentage);

signals:
    void info_printed(const QString& info);
    void percentage_changed(int value);
};

extern Messager *msg;

#endif
