/********************************************************************************
** Form generated from reading UI file 'admin_form.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMIN_FORM_H
#define UI_ADMIN_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QTabWidget *tabWidget3;
    QWidget *tab;
    QPushButton *Btn_Scan;
    QComboBox *comboBox;
    QPushButton *Btn_Open_card;
    QLabel *label_Rd_card;
    QLineEdit *lineEdit_read_card;
    QWidget *tab_2;
    QLabel *label_card;
    QLabel *label_name;
    QLabel *label_phone;
    QPushButton *Btn_reg;
    QLineEdit *lineEdit_Card;
    QLineEdit *lineEdit_name;
    QLineEdit *lineEdit_phone;
    QPushButton *Btn_find;
    QPushButton *Btn_recharge;
    QLineEdit *lineEdit_scan_money;
    QTableWidget *tableWidget2;
    QPushButton *Btn_refresh;
    QPushButton *Btn_destroy;
    QWidget *tab_3;
    QTableWidget *tableWidget;
    QPushButton *Btn_Tab3_refrash;
    QPushButton *Btn_tab_delete_item;
    QWidget *tab_4;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_shopid;
    QLabel *label_shopname;
    QLabel *label_sellprice;
    QLabel *label_shopbrand;
    QPushButton *Btn_tab4_addshop;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit_shopid;
    QLineEdit *lineEdit_shopname;
    QLineEdit *lineEdit_sellprice;
    QLineEdit *lineEdit_shopbrand;
    QWidget *tab_5;
    QWidget *tab_6;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(1096, 669);
        tabWidget3 = new QTabWidget(Form);
        tabWidget3->setObjectName("tabWidget3");
        tabWidget3->setGeometry(QRect(10, 0, 981, 591));
        QFont font;
        font.setPointSize(15);
        tabWidget3->setFont(font);
        tab = new QWidget();
        tab->setObjectName("tab");
        Btn_Scan = new QPushButton(tab);
        Btn_Scan->setObjectName("Btn_Scan");
        Btn_Scan->setGeometry(QRect(20, 220, 431, 41));
        comboBox = new QComboBox(tab);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(470, 220, 441, 41));
        Btn_Open_card = new QPushButton(tab);
        Btn_Open_card->setObjectName("Btn_Open_card");
        Btn_Open_card->setGeometry(QRect(20, 280, 891, 51));
        label_Rd_card = new QLabel(tab);
        label_Rd_card->setObjectName("label_Rd_card");
        label_Rd_card->setGeometry(QRect(30, 360, 131, 41));
        lineEdit_read_card = new QLineEdit(tab);
        lineEdit_read_card->setObjectName("lineEdit_read_card");
        lineEdit_read_card->setGeometry(QRect(160, 360, 751, 41));
        tabWidget3->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        label_card = new QLabel(tab_2);
        label_card->setObjectName("label_card");
        label_card->setGeometry(QRect(30, 30, 81, 31));
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(true);
        label_card->setFont(font1);
        label_name = new QLabel(tab_2);
        label_name->setObjectName("label_name");
        label_name->setGeometry(QRect(30, 70, 71, 31));
        label_name->setFont(font1);
        label_phone = new QLabel(tab_2);
        label_phone->setObjectName("label_phone");
        label_phone->setGeometry(QRect(30, 110, 71, 31));
        label_phone->setFont(font1);
        Btn_reg = new QPushButton(tab_2);
        Btn_reg->setObjectName("Btn_reg");
        Btn_reg->setGeometry(QRect(250, 150, 311, 31));
        lineEdit_Card = new QLineEdit(tab_2);
        lineEdit_Card->setObjectName("lineEdit_Card");
        lineEdit_Card->setGeometry(QRect(110, 30, 671, 31));
        lineEdit_name = new QLineEdit(tab_2);
        lineEdit_name->setObjectName("lineEdit_name");
        lineEdit_name->setGeometry(QRect(110, 70, 671, 31));
        lineEdit_phone = new QLineEdit(tab_2);
        lineEdit_phone->setObjectName("lineEdit_phone");
        lineEdit_phone->setGeometry(QRect(110, 110, 671, 31));
        Btn_find = new QPushButton(tab_2);
        Btn_find->setObjectName("Btn_find");
        Btn_find->setGeometry(QRect(20, 220, 91, 31));
        Btn_recharge = new QPushButton(tab_2);
        Btn_recharge->setObjectName("Btn_recharge");
        Btn_recharge->setGeometry(QRect(130, 220, 101, 31));
        lineEdit_scan_money = new QLineEdit(tab_2);
        lineEdit_scan_money->setObjectName("lineEdit_scan_money");
        lineEdit_scan_money->setGeometry(QRect(240, 220, 661, 41));
        tableWidget2 = new QTableWidget(tab_2);
        tableWidget2->setObjectName("tableWidget2");
        tableWidget2->setGeometry(QRect(20, 270, 941, 271));
        Btn_refresh = new QPushButton(tab_2);
        Btn_refresh->setObjectName("Btn_refresh");
        Btn_refresh->setGeometry(QRect(90, 550, 331, 41));
        Btn_destroy = new QPushButton(tab_2);
        Btn_destroy->setObjectName("Btn_destroy");
        Btn_destroy->setGeometry(QRect(460, 550, 211, 41));
        tabWidget3->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        tableWidget = new QTableWidget(tab_3);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 20, 951, 561));
        Btn_Tab3_refrash = new QPushButton(tab_3);
        Btn_Tab3_refrash->setObjectName("Btn_Tab3_refrash");
        Btn_Tab3_refrash->setGeometry(QRect(210, 480, 211, 41));
        QFont font2;
        font2.setPointSize(20);
        Btn_Tab3_refrash->setFont(font2);
        Btn_tab_delete_item = new QPushButton(tab_3);
        Btn_tab_delete_item->setObjectName("Btn_tab_delete_item");
        Btn_tab_delete_item->setGeometry(QRect(450, 480, 241, 41));
        Btn_tab_delete_item->setFont(font2);
        tabWidget3->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        layoutWidget = new QWidget(tab_4);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(300, 190, 127, 151));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_shopid = new QLabel(layoutWidget);
        label_shopid->setObjectName("label_shopid");

        verticalLayout_2->addWidget(label_shopid);

        label_shopname = new QLabel(layoutWidget);
        label_shopname->setObjectName("label_shopname");

        verticalLayout_2->addWidget(label_shopname);

        label_sellprice = new QLabel(layoutWidget);
        label_sellprice->setObjectName("label_sellprice");

        verticalLayout_2->addWidget(label_sellprice);

        label_shopbrand = new QLabel(layoutWidget);
        label_shopbrand->setObjectName("label_shopbrand");

        verticalLayout_2->addWidget(label_shopbrand);

        Btn_tab4_addshop = new QPushButton(tab_4);
        Btn_tab4_addshop->setObjectName("Btn_tab4_addshop");
        Btn_tab4_addshop->setGeometry(QRect(360, 360, 231, 41));
        layoutWidget1 = new QWidget(tab_4);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(410, 190, 391, 179));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_shopid = new QLineEdit(layoutWidget1);
        lineEdit_shopid->setObjectName("lineEdit_shopid");

        verticalLayout->addWidget(lineEdit_shopid);

        lineEdit_shopname = new QLineEdit(layoutWidget1);
        lineEdit_shopname->setObjectName("lineEdit_shopname");

        verticalLayout->addWidget(lineEdit_shopname);

        lineEdit_sellprice = new QLineEdit(layoutWidget1);
        lineEdit_sellprice->setObjectName("lineEdit_sellprice");

        verticalLayout->addWidget(lineEdit_sellprice);

        lineEdit_shopbrand = new QLineEdit(layoutWidget1);
        lineEdit_shopbrand->setObjectName("lineEdit_shopbrand");

        verticalLayout->addWidget(lineEdit_shopbrand);

        tabWidget3->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        tabWidget3->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName("tab_6");
        tabWidget3->addTab(tab_6, QString());

        retranslateUi(Form);

        tabWidget3->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        Btn_Scan->setText(QCoreApplication::translate("Form", "\346\211\253\346\217\217\350\257\273\345\215\241\345\231\250", nullptr));
        Btn_Open_card->setText(QCoreApplication::translate("Form", "\346\211\223\345\274\200\350\257\273\345\215\241\345\231\250", nullptr));
        label_Rd_card->setText(QCoreApplication::translate("Form", "\350\257\273\345\217\226\347\232\204\345\215\241\345\217\267\357\274\232", nullptr));
        tabWidget3->setTabText(tabWidget3->indexOf(tab), QCoreApplication::translate("Form", "Tab 1", nullptr));
        label_card->setText(QCoreApplication::translate("Form", "\345\215\241\345\217\267\357\274\232", nullptr));
        label_name->setText(QCoreApplication::translate("Form", "\345\247\223\345\220\215:", nullptr));
        label_phone->setText(QCoreApplication::translate("Form", "\347\224\265\350\257\235:", nullptr));
        Btn_reg->setText(QCoreApplication::translate("Form", "\346\263\250\345\206\214", nullptr));
        Btn_find->setText(QCoreApplication::translate("Form", "\346\237\245\350\257\242", nullptr));
        Btn_recharge->setText(QCoreApplication::translate("Form", "\345\205\205\345\200\274", nullptr));
        Btn_refresh->setText(QCoreApplication::translate("Form", "\345\210\267\346\226\260\345\205\250\351\203\250\351\241\276\345\256\242\344\274\232\345\221\230\345\215\241\344\277\241\346\201\257", nullptr));
        Btn_destroy->setText(QCoreApplication::translate("Form", "\346\263\250\351\224\200\345\215\241", nullptr));
        tabWidget3->setTabText(tabWidget3->indexOf(tab_2), QCoreApplication::translate("Form", "Tab 2", nullptr));
        Btn_Tab3_refrash->setText(QCoreApplication::translate("Form", "\346\233\264\346\226\260\344\277\241\346\201\257", nullptr));
        Btn_tab_delete_item->setText(QCoreApplication::translate("Form", "\345\210\240\351\231\244\351\200\211\344\270\255\345\225\206\345\223\201", nullptr));
        tabWidget3->setTabText(tabWidget3->indexOf(tab_3), QCoreApplication::translate("Form", "\351\241\265", nullptr));
        label_shopid->setText(QCoreApplication::translate("Form", "\345\225\206\345\223\201\347\274\226\345\217\267:", nullptr));
        label_shopname->setText(QCoreApplication::translate("Form", "\345\225\206\345\223\201\345\220\215\347\247\260\357\274\232", nullptr));
        label_sellprice->setText(QCoreApplication::translate("Form", "\345\224\256\345\215\226\344\273\267\346\240\274:", nullptr));
        label_shopbrand->setText(QCoreApplication::translate("Form", "\345\225\206\345\223\201\345\223\201\347\211\214\357\274\232", nullptr));
        Btn_tab4_addshop->setText(QCoreApplication::translate("Form", "\346\267\273\345\212\240\345\225\206\345\223\201", nullptr));
        tabWidget3->setTabText(tabWidget3->indexOf(tab_4), QCoreApplication::translate("Form", "\351\241\265", nullptr));
        tabWidget3->setTabText(tabWidget3->indexOf(tab_5), QCoreApplication::translate("Form", "\351\241\265", nullptr));
        tabWidget3->setTabText(tabWidget3->indexOf(tab_6), QCoreApplication::translate("Form", "\351\241\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMIN_FORM_H
