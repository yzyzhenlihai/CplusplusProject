#ifndef STUDENTINFOADMIN_H
#define STUDENTINFOADMIN_H

#include <QMainWindow>

namespace Ui {
class StudentInfoAdmin;
}

class StudentInfoAdmin : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentInfoAdmin(QWidget *parent = nullptr);
    ~StudentInfoAdmin();

private slots:
    void on_ReturnBtn_clicked();

    void on_QueryBtn_clicked();

private:
    Ui::StudentInfoAdmin *ui;
};

#endif // STUDENTINFOADMIN_H
