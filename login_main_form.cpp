#include "login_main_form.h"
#include "ui_login_main_form.h"
#include "user_form.h"
#include "admin_form.h"
#include "QPushButton"
Login_main_Form::Login_main_Form(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login_main_Form)
{
    ui->setupUi(this);
}

Login_main_Form::~Login_main_Form()
{
    delete ui;
}

void Login_main_Form::on_Btn_manager_clicked()
{
    Admin_Form* admin = new Admin_Form();
    admin->show();
    this->hide();
}

void Login_main_Form::on_Btn_client_clicked()
{
    User_Form* user = new User_Form();
    user->show();
    this->hide();
}
