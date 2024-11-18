#include "signup.h"
#include "ui_signup.h"
#include "login.h"
#include <QSqlError>

signup::signup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::signup)
{
    ui->setupUi(this);

    //设置图片
    QPixmap *pix = new QPixmap(":/image/Hat.jpg");
    QSize sz = ui->Hat->size();
    ui->Hat->setPixmap(pix->scaled(sz));
    connect(ui->back_btn, &QPushButton::clicked, this, &signup::backClicked);
    connect(ui->sure_btn, &QPushButton::clicked, this, &signup::sureClicked);
}

signup::~signup()
{
    delete ui;
}

void signup::backClicked()
{
    Login *l=new Login;
    this->close();
    l->show();
}

void signup::sureClicked()
{
    sqlite_Init();

    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_passwd->text();
    QString surepass = ui->lineEdit_surepasswd->text();
    //判断密码是否一致
    if(password == surepass){
        QString sql=QString("insert into user(username,password) values('%1','%2');")
                          .arg(username).arg(password);
        //创建执行语句对象
        QSqlQuery query;
        //判断执行结果
        if(!query.exec(sql)){
            qDebug()<<"insert into error";
            QMessageBox::information(this,"Sign up","注册失败！");
        }else{
            qDebug()<<"insert into success";
            QMessageBox::information(this,"Sign up","注册成功！");
            Login *l = new Login;
            this->close();
            l->show();
        }
        qDebug()<<query.lastError();
    }else{
        QMessageBox::information(this,"Sign up","两次密码输入不一致");
    }
}
