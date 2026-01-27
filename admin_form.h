#ifndef ADMIN_FORM_H
#define ADMIN_FORM_H

#include <QWidget>
#include <QThread>
#include <QSerialPort>
#include <QtSql/QSqlDatabase>
#include <QMap>
#include <QVariant>
#include <QSqlQuery>


QT_BEGIN_NAMESPACE
namespace Ui {
class Form;
}
QT_END_NAMESPACE

class SerialWorker : public QObject
{
    Q_OBJECT
public:
    explicit SerialWorker(QObject* parent = nullptr);

public slots:
    void openPort(const QString& portName);
    void closePort();
    void readSerialData();
    // 删除这行: void cardRead(const QString& cardNo);   // ❌ 错误：这应该是信号，不是槽

signals:
    void portOpened(bool ok, const QString& err);
    void portClosed();
    void cardRead(const QString& cardNo);   // ✅ 正确：这是信号，不是槽

private:
    QSerialPort* m_serial = nullptr;
    QByteArray   m_buffer;                  // ⭐ 防粘包
};

class Admin_Form : public QWidget
{
    Q_OBJECT
public:
    explicit Admin_Form(QWidget* parent = nullptr);
    ~Admin_Form();
    void UI_Init();
    void refreshMemberTable();

    // 删除这行: void onCardRead(const QString& cardNo); // 这不是公共方法

private slots:
    void on_Btn_Scan_clicked();
    void on_Btn_Open_card_clicked();
    void onPortOpened(bool success, const QString& error);
    void onPortClosed();
    void onCardRead(const QString& cardNo); // ✅ 这是槽函数


    // 会员卡管理相关槽函数
    void on_pushButton_register_clicked();    // 注册按钮
    void on_Btn_find_clicked();       // 查询按钮
    void on_pushButton_recharge_clicked();    // 充值按钮

    // 数据库操作

    void initDatabase();
    bool registerMember(const QString& cardNo, const QString& name,
                        const QString& phone, double initialBalance = 0.0);
    QMap<QString, QVariant> queryMember(const QString& cardNo);
    bool rechargeMember(const QString& cardNo, double amount);



private:
    Ui::Form* ui;
    QThread* m_serialThread;
    SerialWorker* m_serialWorker;
    QSqlDatabase m_database;
};

#endif // ADMIN_FORM_H
