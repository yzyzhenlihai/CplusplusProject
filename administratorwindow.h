#ifndef ADMINISTRATORWINDOW_H
#define ADMINISTRATORWINDOW_H

#include <QMainWindow>

namespace Ui {
class AdministratorWindow;
}

class AdministratorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdministratorWindow(QWidget *parent = nullptr);
    ~AdministratorWindow();

private slots:
    //void on_pushButton_4_clicked();

    void on_ReturnLoginBtn_clicked();

    void on_StuInfoAdminBtn_clicked();

    void on_DormitoryInfoAdminBtn_clicked();

private:
    Ui::AdministratorWindow *ui;
};

#endif // ADMINISTRATORWINDOW_H
