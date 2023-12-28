#ifndef STUDENT_INFO_QUERY_H
#define STUDENT_INFO_QUERY_H

#include <QMainWindow>
#include "dialog.h"
namespace Ui {
class Student_Info_Query;
}

class Student_Info_Query : public QMainWindow
{
    Q_OBJECT

public:
    explicit Student_Info_Query(QWidget *parent = nullptr);
    ~Student_Info_Query();
    bool connect(const QString &dbName);

private slots:
    void on_ReturnBtn_clicked();

    void on_ShowAllBtn_clicked();

private:
    Ui::Student_Info_Query *ui;
    QSqlTableModel *model;

};

#endif // STUDENT_INFO_QUERY_H