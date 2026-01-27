#ifndef LOGIN_MAIN_FORM_H
#define LOGIN_MAIN_FORM_H

#include <QWidget>

namespace Ui {
class Login_main_Form;
}

class Login_main_Form : public QWidget
{
    Q_OBJECT

public:
    explicit Login_main_Form(QWidget *parent = nullptr);
    ~Login_main_Form();

private slots:
    void on_Btn_client_clicked();       // 顾客入口按钮
    void on_Btn_manager_clicked();      //管理员入口按钮
private:
    Ui::Login_main_Form *ui;
};

#endif // LOGIN_MAIN_FORM_H
