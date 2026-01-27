/********************************************************************************
** Form generated from reading UI file 'user_form.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USER_FORM_H
#define UI_USER_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_User_Form
{
public:
    QTabWidget *tabWidget;
    QWidget *tab_1;
    QLineEdit *lineEdit_goods;
    QLabel *label_goods;
    QComboBox *comboBox_available_COM;
    QPushButton *Btn_Open_Card;
    QPushButton *Btn_add_goods;
    QPushButton *Btn_SC;
    QPushButton *Btn_Scan;
    QWidget *tab_2;
    QLabel *label;
    QPushButton *Btn_delete_item;
    QPushButton *Btn_delete_items;
    QPushButton *Btn_Settle;
    QTableWidget *tab_goods;

    void setupUi(QWidget *User_Form)
    {
        if (User_Form->objectName().isEmpty())
            User_Form->setObjectName("User_Form");
        User_Form->resize(863, 561);
        QFont font;
        font.setPointSize(20);
        User_Form->setFont(font);
        tabWidget = new QTabWidget(User_Form);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 861, 561));
        tabWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(126,190,247)"));
        tab_1 = new QWidget();
        tab_1->setObjectName("tab_1");
        lineEdit_goods = new QLineEdit(tab_1);
        lineEdit_goods->setObjectName("lineEdit_goods");
        lineEdit_goods->setGeometry(QRect(320, 230, 501, 41));
        label_goods = new QLabel(tab_1);
        label_goods->setObjectName("label_goods");
        label_goods->setGeometry(QRect(70, 220, 241, 41));
        label_goods->setFont(font);
        comboBox_available_COM = new QComboBox(tab_1);
        comboBox_available_COM->setObjectName("comboBox_available_COM");
        comboBox_available_COM->setGeometry(QRect(450, 110, 351, 41));
        Btn_Open_Card = new QPushButton(tab_1);
        Btn_Open_Card->setObjectName("Btn_Open_Card");
        Btn_Open_Card->setGeometry(QRect(60, 170, 741, 31));
        Btn_Open_Card->setFont(font);
        Btn_add_goods = new QPushButton(tab_1);
        Btn_add_goods->setObjectName("Btn_add_goods");
        Btn_add_goods->setGeometry(QRect(50, 300, 741, 81));
        Btn_SC = new QPushButton(tab_1);
        Btn_SC->setObjectName("Btn_SC");
        Btn_SC->setGeometry(QRect(50, 400, 741, 81));
        Btn_Scan = new QPushButton(tab_1);
        Btn_Scan->setObjectName("Btn_Scan");
        Btn_Scan->setGeometry(QRect(60, 110, 371, 41));
        Btn_Scan->setFont(font);
        tabWidget->addTab(tab_1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        label = new QLabel(tab_2);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 10, 821, 41));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(240,10,10)"));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        Btn_delete_item = new QPushButton(tab_2);
        Btn_delete_item->setObjectName("Btn_delete_item");
        Btn_delete_item->setGeometry(QRect(200, 470, 141, 31));
        QFont font1;
        font1.setPointSize(15);
        Btn_delete_item->setFont(font1);
        Btn_delete_items = new QPushButton(tab_2);
        Btn_delete_items->setObjectName("Btn_delete_items");
        Btn_delete_items->setGeometry(QRect(350, 470, 141, 31));
        Btn_delete_items->setFont(font1);
        Btn_Settle = new QPushButton(tab_2);
        Btn_Settle->setObjectName("Btn_Settle");
        Btn_Settle->setGeometry(QRect(500, 470, 141, 31));
        Btn_Settle->setFont(font1);
        tab_goods = new QTableWidget(tab_2);
        tab_goods->setObjectName("tab_goods");
        tab_goods->setEnabled(true);
        tab_goods->setGeometry(QRect(20, 70, 821, 351));
        tabWidget->addTab(tab_2, QString());

        retranslateUi(User_Form);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(User_Form);
    } // setupUi

    void retranslateUi(QWidget *User_Form)
    {
        User_Form->setWindowTitle(QCoreApplication::translate("User_Form", "Form", nullptr));
        lineEdit_goods->setText(QString());
        label_goods->setText(QCoreApplication::translate("User_Form", "\350\257\273\345\217\226\347\232\204\345\225\206\345\223\201\347\274\226\345\217\267:", nullptr));
        Btn_Open_Card->setText(QCoreApplication::translate("User_Form", "\346\211\223\345\274\200\350\257\273\345\215\241\345\231\250", nullptr));
        Btn_add_goods->setText(QCoreApplication::translate("User_Form", "\346\267\273\345\212\240\345\225\206\345\223\201", nullptr));
        Btn_SC->setText(QCoreApplication::translate("User_Form", "\347\273\223\350\264\246\347\241\256\350\256\244", nullptr));
        Btn_Scan->setText(QCoreApplication::translate("User_Form", "\346\211\253\346\217\217\350\257\273\345\215\241\345\231\250", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QCoreApplication::translate("User_Form", "Tab 1", nullptr));
        label->setText(QCoreApplication::translate("User_Form", "\346\217\220\347\244\272:\350\257\267\346\211\253\346\217\217\345\225\206\345\223\201\347\224\265\345\255\220\346\240\207\347\255\276", nullptr));
        Btn_delete_item->setText(QCoreApplication::translate("User_Form", "\345\210\240\351\231\244\351\200\211\344\270\255\345\225\206\345\223\201", nullptr));
        Btn_delete_items->setText(QCoreApplication::translate("User_Form", "\345\210\240\351\231\244\345\205\250\351\203\250\345\225\206\345\223\201", nullptr));
        Btn_Settle->setText(QCoreApplication::translate("User_Form", "\347\273\223\347\256\227", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("User_Form", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class User_Form: public Ui_User_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USER_FORM_H
