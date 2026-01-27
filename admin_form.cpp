#include "admin_form.h"
#include "ui_admin_form.h"
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QSqlError>
#include <QFile>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QSqlQuery>
SerialWorker::SerialWorker(QObject* parent)
    : QObject(parent)
{
}

void SerialWorker::openPort(const QString& portName)
{
    if (!m_serial) {
        m_serial = new QSerialPort(this);   // ✅ 子线程创建
        connect(m_serial, &QSerialPort::readyRead,
                this, &SerialWorker::readSerialData);
    }

    if (m_serial->isOpen()) {
        emit portOpened(true, "");
        return;
    }

    m_serial->setPortName(portName);
    m_serial->setBaudRate(QSerialPort::Baud115200);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);

    bool ok = m_serial->open(QIODevice::ReadWrite);
    emit portOpened(ok, ok ? "" : m_serial->errorString());
}

void SerialWorker::closePort()
{
    if (m_serial && m_serial->isOpen())
        m_serial->close();

    emit portClosed();
}

//读取串口数据
void SerialWorker::readSerialData()
{
    m_buffer.append(m_serial->readAll());

    while (m_buffer.contains('\n'))
    {
        int idx = m_buffer.indexOf('\n');
        QByteArray line = m_buffer.left(idx);
        m_buffer.remove(0, idx + 1);

        QString text = QString::fromLocal8Bit(line).trimmed();
        qDebug() << "串口整行:" << text;

        // 示例：卡的类型:40 卡序列号:B260526
        int pos = text.indexOf("卡序列号:");  // 英文冒号
        if (pos != -1)
        {
            QString cardNo = text.mid(pos + QString("卡序列号:").length()).trimmed();
            emit cardRead(cardNo);  // ✅ 发射信号，而不是调用槽函数
        }
    }
}

// 初始化数据库
void Admin_Form::initDatabase()
{
    // 创建SQLite数据库连接
    m_database = QSqlDatabase::addDatabase("QSQLITE", "member_connection");
    m_database.setDatabaseName("member_cards.db");

    if (!m_database.open()) {
        QMessageBox::critical(this, "数据库错误",
                              QString("无法打开数据库: %1").arg(m_database.lastError().text()));
        return;
    }

    // 创建会员表
    QSqlQuery query(m_database);
    QString createTable =
        "CREATE TABLE IF NOT EXISTS members ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "card_no VARCHAR(50) UNIQUE NOT NULL,"
        "name VARCHAR(50) NOT NULL,"
        "phone VARCHAR(20),"
        "balance DECIMAL(10,2) DEFAULT 0.00,"
        "register_time DATETIME DEFAULT CURRENT_TIMESTAMP,"
        "last_recharge_time DATETIME"
        ")";

    if (!query.exec(createTable)) {
        QMessageBox::critical(this, "数据库错误",
                              QString("创建表失败: %1").arg(query.lastError().text()));
    } else {
        qDebug() << "数据库初始化成功";
    }
}


// 在 admin_form.h 中添加声明：
// void refreshMemberTable();

// 在 admin_form.cpp 中实现：
void Admin_Form::refreshMemberTable()
{
    // 清空表格
    ui->tableWidget2->setRowCount(0);

    // 从数据库查询所有会员
    QSqlQuery query(m_database);
    if (query.exec("SELECT card_no, name, phone, balance FROM members ORDER BY register_time DESC")) {
        while (query.next()) {
            int row = ui->tableWidget2->rowCount();
            ui->tableWidget2->insertRow(row);

            ui->tableWidget2->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget2->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget2->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidget2->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
        }
    } else {
        qDebug() << "查询所有会员失败:" << query.lastError().text();
    }
}

// Admin_Form 实现
Admin_Form::Admin_Form(QWidget* parent)
    : QWidget(parent),
    ui(new Ui::Form),
    m_serialThread(nullptr),
    m_serialWorker(nullptr)  // 初始化指针
{
    ui->setupUi(this);
    UI_Init();
    initDatabase();
    // 初始化时加载所有会员到表格
    refreshMemberTable();
    // 创建线程
    m_serialThread = new QThread(this);
    m_serialWorker = new SerialWorker;
    // 重要：先将 worker 移动到线程，再进行其他设置
    m_serialWorker->moveToThread(m_serialThread);

    // 连接信号槽 - 注意使用 Qt::QueuedConnection
    connect(m_serialWorker, &SerialWorker::portOpened,
            this, &Admin_Form::onPortOpened,
            Qt::QueuedConnection);

    connect(m_serialWorker, &SerialWorker::portClosed,
            this, &Admin_Form::onPortClosed,
            Qt::QueuedConnection);

    // ⭐ 连接刷卡信号到槽函数
    connect(m_serialWorker, &SerialWorker::cardRead,
            this, &Admin_Form::onCardRead,
            Qt::QueuedConnection);

    // 连接线程结束信号清理worker
    connect(m_serialThread, &QThread::finished,
            m_serialWorker, &QObject::deleteLater);



    // 连接按钮信号
    connect(ui->Btn_reg, &QPushButton::clicked,
            this, &Admin_Form::on_pushButton_register_clicked);

    connect(ui->Btn_find, &QPushButton::clicked,
            this, &Admin_Form::on_Btn_find_clicked);

    connect(ui->Btn_recharge, &QPushButton::clicked,
            this, &Admin_Form::on_pushButton_recharge_clicked);

    // 启动线程
    m_serialThread->start();
}

Admin_Form::~Admin_Form()
{
    // 先请求关闭串口
    if (m_serialWorker) {
        QMetaObject::invokeMethod(m_serialWorker, "closePort",
                                  Qt::BlockingQueuedConnection);
    }

    // 清理线程
    if (m_serialThread) {
        m_serialThread->quit();
        m_serialThread->wait();
        delete m_serialThread;
    }

    // worker 会被线程的 finished 信号自动删除
    // 不需要手动 delete m_serialWorker;

    delete ui;
}

// ✅ 这是 Admin_Form 的槽函数，不是 SerialWorker 的方法
void Admin_Form::onCardRead(const QString& cardNo)
{
    qInfo() << "UI显示卡号:" << cardNo;
    ui->lineEdit_read_card->setText(cardNo);
    ui->lineEdit_Card->setText(cardNo);
}
//版本1.0
// void Admin_Form::UI_Init()
// {
//     ui->tabWidget3->setTabText(0, "读卡器设备管理");    // 修改第一个标签
//     ui->tabWidget3->setTabText(1, "顾客会员卡管理");    // 修改第二个标签
//     ui->tabWidget3->setTabText(2, "在售商品查询");     //修改第一个标签
//     ui->tabWidget3->setTabText(3, "添加新商品");      // 修改第二个标签
//     ui->tabWidget3->setTabText(4, "销售记录");       // 修改第一个标签
//     ui->tabWidget3->setTabText(5, "日志");          // 修改第二个标签

//     ui->tableWidget2->setColumnCount(4);  // 设置为4列
//     QStringList headers = { "卡号", "姓名", "电话", "余额(元)" };
//     ui->tableWidget2->setHorizontalHeaderLabels(headers);
//     // 让4列平均分布（占满表格宽度）
//     ui->tableWidget2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//     // 隐藏行号
//     ui->tableWidget2->verticalHeader()->setVisible(false);

//     ui->lineEdit_read_card->setPlaceholderText("请刷RFID卡...");
//     ui->lineEdit_read_card->setReadOnly(true);
//     ui->lineEdit_read_card->setClearButtonEnabled(true);
// }
void Admin_Form::UI_Init()
{
    // 设置标签页文本
    ui->tabWidget3->setTabText(0, "读卡器设备管理");
    ui->tabWidget3->setTabText(1, "顾客会员卡管理");
    ui->tabWidget3->setTabText(2, "在售商品查询");
    ui->tabWidget3->setTabText(3, "添加新商品");
    ui->tabWidget3->setTabText(4, "销售记录");
    ui->tabWidget3->setTabText(5, "日志");

    // 读卡器管理标签页
    ui->lineEdit_read_card->setPlaceholderText("请刷RFID卡...");
    ui->lineEdit_read_card->setReadOnly(true);
    ui->lineEdit_read_card->setClearButtonEnabled(true);

    // 设置充值金额验证
    ui->lineEdit_scan_money->setValidator(new QDoubleValidator(0.0, 10000.0, 2, this));

    // 设置表格属性 - 使用 tableWidget2
    ui->tableWidget2->setColumnCount(4);  // 设置为4列
    QStringList headers = { "卡号", "姓名", "电话", "余额" };
    ui->tableWidget2->setHorizontalHeaderLabels(headers);

    // 让列平均分布（占满表格宽度）
    ui->tableWidget2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // 隐藏行号
    ui->tableWidget2->verticalHeader()->setVisible(false);

    // 设置选择行为为选择整行
    ui->tableWidget2->setSelectionBehavior(QAbstractItemView::SelectRows);

    // 设置表格为只读
    ui->tableWidget2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 初始时清空表格内容
    ui->tableWidget2->setRowCount(0);

    // 设置表格样式
    ui->tableWidget2->setAlternatingRowColors(true); // 交替行颜色
    ui->tableWidget2->setStyleSheet(
        "QTableWidget {"
        "  gridline-color: #e0e0e0;"
        "}"
        "QTableWidget::item {"
        "  padding: 5px;"
        "}"
        "QTableWidget::item:selected {"
        "  background-color: #e0e0e0;"
        "  color: black;"
        "}"
        );

    // 设置表格支持排序
    ui->tableWidget2->setSortingEnabled(true);

    // 添加清除表格的按钮（可选）
    // QPushButton *clearTableBtn = new QPushButton("清空表格", this);
    // connect(clearTableBtn, &QPushButton::clicked, this, [this]() {
    //     ui->tableWidget2->setRowCount(0);
    // });
    // 可以将按钮添加到某个布局中
}

// 在查询按钮点击事件中更新表格
// 在查询按钮点击事件中更新表格 - 保持原有行，只更新匹配的行
void Admin_Form::on_Btn_find_clicked()
{
    QString cardNo = ui->lineEdit_Card->text().trimmed();

    if (cardNo.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入要查询的卡号！");
        return;
    }

    auto memberInfo = queryMember(cardNo);

    if (memberInfo["exists"].toBool()) {
        // 显示会员信息到输入框
        ui->lineEdit_name->setText(memberInfo["name"].toString());
        ui->lineEdit_phone->setText(memberInfo["phone"].toString());

        // 显示余额信息
        double balance = memberInfo["balance"].toDouble();

        // 在表格中查找是否已有该卡号，如果有则更新，否则添加新行
        bool found = false;
        int rowCount = ui->tableWidget2->rowCount();

        for (int i = 0; i < rowCount; i++) {
            QTableWidgetItem* item = ui->tableWidget2->item(i, 0);
            if (item && item->text() == cardNo) {
                // 更新现有行
                ui->tableWidget2->setItem(i, 1, new QTableWidgetItem(memberInfo["name"].toString()));
                ui->tableWidget2->setItem(i, 2, new QTableWidgetItem(memberInfo["phone"].toString()));
                ui->tableWidget2->setItem(i, 3, new QTableWidgetItem(QString::number(balance, 'f', 2)));
                found = true;
                // 滚动到该行并选中
                ui->tableWidget2->selectRow(i);
                break;
            }
        }

        // 如果没有找到，添加新行
        if (!found) {
            int newRow = ui->tableWidget2->rowCount();
            ui->tableWidget2->insertRow(newRow);
            ui->tableWidget2->setItem(newRow, 0, new QTableWidgetItem(cardNo));
            ui->tableWidget2->setItem(newRow, 1, new QTableWidgetItem(memberInfo["name"].toString()));
            ui->tableWidget2->setItem(newRow, 2, new QTableWidgetItem(memberInfo["phone"].toString()));
            ui->tableWidget2->setItem(newRow, 3, new QTableWidgetItem(QString::number(balance, 'f', 2)));
            // 滚动到最后一行并选中
            ui->tableWidget2->selectRow(newRow);
        }

        // 启用充值功能
        ui->lineEdit_scan_money->setEnabled(true);
        ui->Btn_recharge->setEnabled(true);
    } else {
        // 会员不存在，清空输入框但不清空表格
        ui->lineEdit_name->clear();
        ui->lineEdit_phone->clear();

        QMessageBox::information(this, "查询结果",
                                 QString("卡号 %1 未注册\n"
                                         "可以点击'注册'按钮进行注册")
                                     .arg(cardNo));

        // 禁用充值功能
        ui->lineEdit_scan_money->setEnabled(false);
        ui->Btn_recharge->setEnabled(false);
    }
}
// 在注册成功后更新表格
// 在注册成功后更新表格 - 改为添加行而不是替换
void Admin_Form::on_pushButton_register_clicked()
{
    QString cardNo = ui->lineEdit_Card->text().trimmed();
    QString name = ui->lineEdit_name->text().trimmed();
    QString phone = ui->lineEdit_phone->text().trimmed();

    // 验证输入
    if (cardNo.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "卡号不能为空！");
        ui->lineEdit_Card->setFocus();
        return;
    }

    if (name.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "姓名不能为空！");
        ui->lineEdit_name->setFocus();
        return;
    }

    // 检查是否已注册
    auto memberInfo = queryMember(cardNo);
    if (memberInfo["exists"].toBool()) {
        QMessageBox::warning(this, "注册失败",
                             QString("卡号 %1 已经注册！\n"
                                     "姓名: %2\n"
                                     "余额: %3 元")
                                 .arg(cardNo)
                                 .arg(memberInfo["name"].toString())
                                 .arg(memberInfo["balance"].toDouble()));
        return;
    }

    // 注册会员
    if (registerMember(cardNo, name, phone)) {
        QMessageBox::information(this, "注册成功",
                                 QString("会员注册成功！\n"
                                         "卡号: %1\n"
                                         "姓名: %2\n"
                                         "电话: %3")
                                     .arg(cardNo).arg(name).arg(phone));

        // 在表格中添加新行（而不是替换）
        int rowCount = ui->tableWidget2->rowCount();
        ui->tableWidget2->insertRow(rowCount);

        ui->tableWidget2->setItem(rowCount, 0, new QTableWidgetItem(cardNo));
        ui->tableWidget2->setItem(rowCount, 1, new QTableWidgetItem(name));
        ui->tableWidget2->setItem(rowCount, 2, new QTableWidgetItem(phone));
        ui->tableWidget2->setItem(rowCount, 3, new QTableWidgetItem("0.00"));

        // 清空姓名和电话输入框，保留卡号以便继续操作
        ui->lineEdit_name->clear();
        ui->lineEdit_phone->clear();

        // 启用充值功能
        ui->lineEdit_scan_money->setEnabled(true);
        ui->Btn_recharge->setEnabled(true);
    } else {
        QMessageBox::critical(this, "注册失败", "会员注册失败，请重试！");
    }
}

// 在充值成功后更新表格
// 在充值成功后更新表格
void Admin_Form::on_pushButton_recharge_clicked()
{
    QString cardNo = ui->lineEdit_Card->text().trimmed();
    QString amountStr = ui->lineEdit_scan_money->text().trimmed();

    if (cardNo.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请先查询要充值的卡号！");
        return;
    }

    if (amountStr.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入充值金额！");
        ui->lineEdit_scan_money->setFocus();
        return;
    }

    double amount = amountStr.toDouble();
    if (amount <= 0) {
        QMessageBox::warning(this, "输入错误", "充值金额必须大于0！");
        ui->lineEdit_scan_money->setFocus();
        return;
    }

    // 确认充值
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认充值",
                                  QString("确认给卡号 %1 充值 %2 元吗？")
                                      .arg(cardNo).arg(amount, 0, 'f', 2),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (rechargeMember(cardNo, amount)) {
            QMessageBox::information(this, "充值成功",
                                     QString("充值成功！\n"
                                             "卡号: %1\n"
                                             "充值金额: %2 元")
                                         .arg(cardNo).arg(amount, 0, 'f', 2));

            // 清空充值金额输入框
            ui->lineEdit_scan_money->clear();

            // 重新查询并更新表格
            on_Btn_find_clicked();
        } else {
            QMessageBox::critical(this, "充值失败", "充值失败，请重试！");
        }
    }
}

void Admin_Form::on_Btn_Scan_clicked()
{
    ui->comboBox->clear();

    // 快速扫描，避免UI阻塞
    QTimer::singleShot(0, [this]() {
        QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

        if (ports.isEmpty())
        {
            ui->comboBox->addItem("未检测到串口");
            ui->comboBox->setEnabled(false);
            ui->Btn_Open_card->setEnabled(false);
        }
        else
        {
            for (const auto& info : ports) {
                QString displayText = info.portName();
                if (!info.description().isEmpty()) {
                    displayText += " - " + info.description();
                }
                ui->comboBox->addItem(displayText, info.portName());
            }
            ui->comboBox->setEnabled(true);
            ui->Btn_Open_card->setEnabled(true);
        }
    });
}

void Admin_Form::on_Btn_Open_card_clicked()
{
    if (ui->comboBox->currentData().toString().isEmpty()) {
        QMessageBox::warning(this, "警告", "请选择有效的串口");
        return;
    }

    QString portName = ui->comboBox->currentData().toString();

    if (ui->Btn_Open_card->text() == "打开读卡器") {
        // 禁用按钮防止重复点击
        ui->Btn_Open_card->setEnabled(false);
        ui->Btn_Open_card->setText("正在打开...");

        // 在线程中打开串口
        QMetaObject::invokeMethod(m_serialWorker, "openPort",
                                  Qt::QueuedConnection, Q_ARG(QString, portName));

    }
    else {
        // 在线程中关闭串口
        QMetaObject::invokeMethod(m_serialWorker, "closePort", Qt::QueuedConnection);
    }
}

void Admin_Form::onPortOpened(bool success, const QString& error)
{
    if (success)
    {
        ui->Btn_Open_card->setText("关闭读卡器");
        QMessageBox::information(this, "成功", "串口打开成功");
    }
    else
    {
        ui->Btn_Open_card->setText("打开读卡器");
        QMessageBox::critical(this, "错误",
                              QString("打开串口失败：%1").arg(error));
    }

    ui->Btn_Open_card->setEnabled(true);
}

void Admin_Form::onPortClosed()
{
    ui->Btn_Open_card->setText("打开读卡器");
    ui->Btn_Open_card->setEnabled(true);
}

// 在 admin_form.cpp 中添加这些函数的实现：

// 注册会员
bool Admin_Form::registerMember(const QString& cardNo, const QString& name,
                                const QString& phone, double initialBalance)
{
    QSqlQuery query(m_database);
    query.prepare(
        "INSERT INTO members (card_no, name, phone, balance) "
        "VALUES (:card_no, :name, :phone, :balance)"
        );
    query.bindValue(":card_no", cardNo);
    query.bindValue(":name", name);
    query.bindValue(":phone", phone);
    query.bindValue(":balance", initialBalance);

    if (!query.exec()) {
        qDebug() << "注册失败:" << query.lastError().text();
        return false;
    }

    return true;
}

// 查询会员信息
QMap<QString, QVariant> Admin_Form::queryMember(const QString& cardNo)
{
    QMap<QString, QVariant> result;

    QSqlQuery query(m_database);
    query.prepare(
        "SELECT card_no, name, phone, balance, register_time "
        "FROM members WHERE card_no = :card_no"
        );
    query.bindValue(":card_no", cardNo);

    if (query.exec() && query.next()) {
        result["card_no"] = query.value(0);
        result["name"] = query.value(1);
        result["phone"] = query.value(2);
        result["balance"] = query.value(3);
        result["register_time"] = query.value(4);
        result["exists"] = true;
    } else {
        result["exists"] = false;
    }

    return result;
}

// 充值会员
bool Admin_Form::rechargeMember(const QString& cardNo, double amount)
{
    QSqlQuery query(m_database);
    query.prepare(
        "UPDATE members SET balance = balance + :amount, "
        "last_recharge_time = CURRENT_TIMESTAMP "
        "WHERE card_no = :card_no"
        );
    query.bindValue(":amount", amount);
    query.bindValue(":card_no", cardNo);

    if (!query.exec()) {
        qDebug() << "充值失败:" << query.lastError().text();
        return false;
    }

    return query.numRowsAffected() > 0;
}

