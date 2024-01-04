#ifndef REPAIR_PROCESS_ADMIN_H
#define REPAIR_PROCESS_ADMIN_H

#include <QMainWindow>

namespace Ui {
class Repair_Process_Admin;
}

class Repair_Process_Admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit Repair_Process_Admin(QWidget *parent = nullptr);
    ~Repair_Process_Admin();

private:
    Ui::Repair_Process_Admin *ui;
};

#endif // REPAIR_PROCESS_ADMIN_H
