#include "login.h"
#include "ui_login.h"
#include "signup.h"
#include "restroom.h"
#include <QSqlError>

void sqlite_Init()
{
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
    }
    db.setDatabaseName("user.db");
    if (!db.open()){
        qDebug()<<"open error";
    }

    //创建一个user表,标题分别为id、username、password
    //" PRIMARY KEY AUTOINCREMENT,":表示该列为整数递增,如果为空时则自动填入1,然后在下面的每一行都会自动+1
    QString createsql=QString("CREATE TABLE if not exists user(id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                "username ntext unique not NULL,"
                                "password ntext not NULL)");
    QSqlQuery query;
    if(!query.exec(createsql)){
        qDebug()<<"table create error";
    }
    else{
        qDebug()<<"table create success";
    }
}
Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    //设置图片
    QPixmap *pix1 = new QPixmap(":/image/Background1.jpg");
    QSize sz1 = ui->label->size();
    ui->label->setPixmap(pix1->scaled(sz1));
    QPixmap *pix2 = new QPixmap(":/image/title.png");
    QSize sz2 = ui->Login_Title->size();
    ui->Login_Title->setPixmap(pix2->scaled(sz2));

    connect(ui->signup_btn, &QPushButton::clicked, this, &Login::signupClicked);
    connect(ui->signin_btn, &QPushButton::clicked, this, &Login::signinClicked);

}

Login::~Login()
{
    delete ui;
}

void Login::signupClicked()
{
    signup *s=new signup;
    s->show();
    this->close();
}

void Login::signinClicked()
{
    sqlite_Init();
    QString username = ui->lineEdit_username->text();  //读取输入的用户姓名
    QString password = ui->lineEdit_password->text();  //读取输入的密码
    QString sql=QString("select * from user where username='%1' and password='%2'")  //在数据库中查找是否有相对应的用户和密码
                      .arg(username).arg(password);
    //创建执行语句对象
    QSqlQuery query(sql);
    //判断执行结果
    if(!query.next()){
        qDebug()<<"Login error";
        QMessageBox::information(this,"Login","登录失败,账户或者密码错误");
    }else{
        qDebug()<<"Login success";
        QMessageBox::information(this,"Login","登录成功");
        //登录成功后可以跳转到其他页面
        RestRoom *r = new RestRoom;
        r->show();
        this->close();
    }
}

