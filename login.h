#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QtSql/QSqlDatabase>//数据驱动
#include <QtSql/QSqlQuery> //数据库执行语句
#include <QMessageBox>//消息盒子
#include <QSqlError>
#include <QDebug>

void sqlite_Init();

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
private slots:
    void signupClicked();
    void signinClicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
