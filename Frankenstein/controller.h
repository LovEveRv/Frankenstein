#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include "modules.h"
#ifdef USING_QT
#include <QObject>
#endif

class Main_Controller : public QObject //Controlling the whole procedure
{
    Q_OBJECT
private:
    std::string srcdir_path;
    std::string target_path;
    std::string save_path;

public:
    Main_Controller(QObject *parent, const std::string& m_dirpath, const std::string& m_target, const std::string& m_svpath);
    ~Main_Controller() = default;

public slots:
    void execute();

signals:
    void finished();
};

#endif
