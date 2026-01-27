#ifndef USER_FORM_H
#define USER_FORM_H

#include <QWidget>
#include "QSerialPort"      //串口
#include <QTableWidget>
namespace Ui {
class User_Form;
}

class User_Form : public QWidget
{
    Q_OBJECT
public:
    explicit User_Form(QWidget *parent = nullptr);
    ~User_Form();


private:
    Ui::User_Form *ui;
    QTableWidget* tableGoods;  // 商品表格
    QMap<QString, QMap<QString, QString>> goodsData;
    //定义一个串口指针
    QSerialPort *COM = new QSerialPort();//定义串口指针，实例化串口
    // 保存表格商品到本地
    void saveGoodsToLocal();
    // 从本地加载商品到表格
    void loadGoodsFromLocal();
    // 重写关闭事件（程序关闭时自动保存）
    void closeEvent(QCloseEvent* event) override;

    void UI_init();
private slots:
    void on_Btn_Scan_clicked();
    void on_Btn_Open_Card_clicked();
    void on_Btn_add_goods_clicked();
    void on_Btn_SC_clicked();

/*****************************************************/
/*****************************************************/
    void on_Btn_Settle_clicked();
    void on_Btn_delete_item_clicked();
    void on_Btn_delete_items_clicked();
};

#endif // USER_FORM_H
