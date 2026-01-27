/********************************************************************************
** Form generated from reading UI file 'login_main_form.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_MAIN_FORM_H
#define UI_LOGIN_MAIN_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login_main_Form
{
public:
    QPushButton *Btn_client;
    QPushButton *Btn_manager;
    QLabel *label_main_title;

    void setupUi(QWidget *Login_main_Form)
    {
        if (Login_main_Form->objectName().isEmpty())
            Login_main_Form->setObjectName("Login_main_Form");
        Login_main_Form->resize(800, 600);
        Btn_client = new QPushButton(Login_main_Form);
        Btn_client->setObjectName("Btn_client");
        Btn_client->setGeometry(QRect(60, 440, 271, 41));
        Btn_manager = new QPushButton(Login_main_Form);
        Btn_manager->setObjectName("Btn_manager");
        Btn_manager->setGeometry(QRect(460, 440, 271, 41));
        label_main_title = new QLabel(Login_main_Form);
        label_main_title->setObjectName("label_main_title");
        label_main_title->setGeometry(QRect(250, 100, 291, 61));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setItalic(false);
        font.setKerning(true);
        label_main_title->setFont(font);
        label_main_title->setAlignment(Qt::AlignmentFlag::AlignCenter);

        retranslateUi(Login_main_Form);

        QMetaObject::connectSlotsByName(Login_main_Form);
    } // setupUi

    void retranslateUi(QWidget *Login_main_Form)
    {
        Login_main_Form->setWindowTitle(QCoreApplication::translate("Login_main_Form", "Login_main_Form", nullptr));
        Btn_client->setText(QCoreApplication::translate("Login_main_Form", "\351\241\276\345\256\242\345\205\245\345\217\243", nullptr));
        Btn_manager->setText(QCoreApplication::translate("Login_main_Form", "\347\256\241\347\220\206\345\221\230\345\205\245\345\217\243", nullptr));
        label_main_title->setText(QCoreApplication::translate("Login_main_Form", "\350\266\205\345\270\202\347\256\241\347\220\206\347\263\273\347\273\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login_main_Form: public Ui_Login_main_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_MAIN_FORM_H
