#include "user_form.h"
#include "ui_user_form.h"
#include "QSerialPort"      //串口
#include "QSerialPortInfo"  //串口信息
#include "QMessageBox"      //弹窗提示
#include "QDebug"           //调试信息
#include "QTabWidget"
#include "QSettings"
#include "QCloseEvent"
#include "QSet"
User_Form::User_Form(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::User_Form)
{
    ui->setupUi(this);
    // 修改标签名称
    UI_init();
    loadGoodsFromLocal();


}

User_Form::~User_Form()
{
    delete ui;
}



//刷新界面
void User_Form::on_Btn_Scan_clicked()
{
    ui->comboBox_available_COM->clear();//先清除项目
    foreach( const QSerialPortInfo &info,QSerialPortInfo::availablePorts() )
    {
        ui->comboBox_available_COM->addItem(info.portName());
    }
}


//保存表格商品到本地
void User_Form::saveGoodsToLocal()
{
    // 创建QSettings，数据保存到程序目录下的config.ini文件
    QSettings settings("./config.ini", QSettings::IniFormat);
    settings.clear(); // 先清空旧数据

    int rowCount = ui->tab_goods->rowCount();
    settings.setValue("goods/count", rowCount); // 保存商品行数

    // 遍历表格，逐行保存商品信息
    for (int i = 0; i < rowCount; ++i) {
        QString id = ui->tab_goods->item(i, 0)->text();
        QString name = ui->tab_goods->item(i, 1)->text();
        QString price = ui->tab_goods->item(i, 2)->text();
        QString brand = ui->tab_goods->item(i, 3)->text();

        // 按行号存储，格式：goods/行号/字段名 = 值
        settings.setValue(QString("goods/%1/id").arg(i), id);
        settings.setValue(QString("goods/%1/name").arg(i), name);
        settings.setValue(QString("goods/%1/price").arg(i), price);
        settings.setValue(QString("goods/%1/brand").arg(i), brand);
    }
}

//从本地加载商品到表格
void User_Form::loadGoodsFromLocal()
{
    QSettings settings("./config.ini", QSettings::IniFormat);
    int rowCount = settings.value("goods/count", 0).toInt(); // 读取行数，默认0

    // 清空表格原有数据（避免重复）
    ui->tab_goods->setRowCount(0);

    // 逐行加载商品到表格
    for (int i = 0; i < rowCount; ++i) 
    {
        QString id = settings.value(QString("goods/%1/id").arg(i)).toString();
        QString name = settings.value(QString("goods/%1/name").arg(i)).toString();
        QString price = settings.value(QString("goods/%1/price").arg(i)).toString();
        QString brand = settings.value(QString("goods/%1/brand").arg(i)).toString();

        // 跳过空数据（防止配置文件异常）
        if (id.isEmpty()) continue;

        // 添加到表格
        int newRow = ui->tab_goods->rowCount();
        ui->tab_goods->insertRow(newRow);
        ui->tab_goods->setItem(newRow, 0, new QTableWidgetItem(id));
        ui->tab_goods->setItem(newRow, 1, new QTableWidgetItem(name));
        ui->tab_goods->setItem(newRow, 2, new QTableWidgetItem(price));
        ui->tab_goods->setItem(newRow, 3, new QTableWidgetItem(brand));
    }
}
void User_Form::closeEvent(QCloseEvent* event)
{
    // 关闭窗口时自动保存商品数据
    saveGoodsToLocal();
    event->accept(); // 允许窗口关闭
}
void User_Form::UI_init()
{
    ui->tabWidget->setTabText(0, "读卡器管理");    // 修改第一个标签
    ui->tabWidget->setTabText(1, "购物结算");      // 修改第二个标签
    ui->tab_goods->setColumnCount(4); // 设置4列
    goodsData["1001"] = { {"name", "可乐"}, {"price", "3.50"}, {"brand", "可口可乐"} };
    goodsData["1002"] = { {"name", "薯片"}, {"price", "5.00"}, {"brand", "乐事"} };
    goodsData["1003"] = { {"name", "面包"}, {"price", "4.00"}, {"brand", "桃李"} };
    // 设置列标题
    QStringList headers = { "编号", "名称", "价格（元）", "品牌" };
    ui->tab_goods->setHorizontalHeaderLabels(headers);
    // 让4列平均分布（占满表格宽度）
    ui->tab_goods->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // 隐藏行号
    ui->tab_goods->verticalHeader()->setVisible(false);
    // 设置界面初始状态
    ui->lineEdit_goods->setPlaceholderText("等待扫描商品编号...");
}
//打开读卡器
void User_Form::on_Btn_Open_Card_clicked()
{
    COM->setPortName(ui->comboBox_available_COM->currentText()); //端口名字
    if(ui->Btn_Open_Card->text() == "打开读卡器" )
    {
        if(COM->open(QIODevice::ReadWrite) == true)//判断串口打开成功
        {
            ui->Btn_Open_Card->setText("关闭读卡器");//按键文字变成 关闭串口
        }
        else//串口打开不成功
        {
            QMessageBox::critical(this,"错误提示","打开串口失败！或其他错误。\r\n请选择正确的串口或该串口被占用");
        }
    }
    else if(ui->Btn_Open_Card->text() == "关闭读卡器" )
    {
        COM->close();//关闭串口
        ui->Btn_Open_Card->setText("打开读卡器");//按键文字变成 打开串口
    }
}


//添加商品
void User_Form::on_Btn_add_goods_clicked()
{
    // 1. 读取输入的商品编号
    QString goodsId = ui->lineEdit_goods->text().trimmed(); // 假设读取商品编号的输入框是lineEdit_goods
    if (goodsId.isEmpty()) 
    {
        QMessageBox::warning(this, "提示", "请输入商品编号！");
        return;
    }

    // 2. 检查商品编号是否存在于商品数据中
    if (!goodsData.contains(goodsId)) 
    {
        QMessageBox::warning(this, "提示", "该商品编号不存在！");
        ui->lineEdit_goods->clear();
        return;
    }

    // 3. 检查表格中是否已存在该商品（去重）
    bool isDuplicate = false;
    int rowCount = ui->tab_goods->rowCount(); // 表格名以实际UI中的objectName为准
    for (int i = 0; i < rowCount; ++i) {
        QTableWidgetItem* item = ui->tab_goods->item(i, 0); // 第0列是“编号”
        if (item && item->text() == goodsId) {
            isDuplicate = true;
            break;
        }
    }
    if (isDuplicate) {
        QMessageBox::information(this, "提示", "该商品已存在，请勿重复添加！");
        ui->lineEdit_goods->clear();
        return;
    }

    // 4. 从商品数据中获取名称、价格、品牌
    QMap<QString, QString> info = goodsData[goodsId];
    QString name = info["name"];
    QString price = info["price"];
    QString brand = info["brand"];

    // 5. 添加到表格
    int newRow = ui->tab_goods->rowCount();
    ui->tab_goods->insertRow(newRow);
    ui->tab_goods->setItem(newRow, 0, new QTableWidgetItem(goodsId));
    ui->tab_goods->setItem(newRow, 1, new QTableWidgetItem(name));
    ui->tab_goods->setItem(newRow, 2, new QTableWidgetItem(price));
    ui->tab_goods->setItem(newRow, 3, new QTableWidgetItem(brand));

    // 清空输入框
    ui->lineEdit_goods->clear();
}

// 结算功能
void User_Form::on_Btn_SC_clicked()
{
    int rowCount = ui->tab_goods->rowCount();
    if (rowCount == 0) {
        QMessageBox::information(this, "提示", "购物车为空，无法结账！");
        return;
    }

    double totalPrice = 0.0;
    QString goodsList;
    for (int i = 0; i < rowCount; ++i) {
        QString id = ui->tab_goods->item(i, 0)->text();
        QString name = ui->tab_goods->item(i, 1)->text();
        QString priceStr = ui->tab_goods->item(i, 2)->text();
        // （如果priceStr带“元”，先去掉：priceStr = priceStr.remove("元");）
        double price = priceStr.toDouble();

        totalPrice += price;
        goodsList += QString("%1. %2（%3）：%4元\n").arg(i + 1).arg(name).arg(id).arg(priceStr);
    }

    // 关键修正：Qt中用arg()按顺序传参，先传goodsList，再传保留2位小数的totalPrice
    QString msg = QString("您的购物明细：\n%1\n合计：%2元\n是否确认结账？")
        .arg(goodsList)
        .arg(totalPrice, 0, 'f', 2); // 0=宽度，'f'=浮点数，2=保留2位小数

    QMessageBox::StandardButton result = QMessageBox::question(
        this,
        "结账确认",
        msg,
        QMessageBox::Yes | QMessageBox::No
    );

    if (result == QMessageBox::Yes) {
        ui->tab_goods->setRowCount(0);
        // 清空本地配置（结账后重置）
        QSettings settings("./config.ini", QSettings::IniFormat);
        settings.clear();
        QMessageBox::information(this, "成功", "结账完成！欢迎下次光临~");
    }
    else {
        QMessageBox::information(this, "提示", "已取消结账");
    }
}

//购物结算里面的结算
void User_Form::on_Btn_Settle_clicked()
{
    // 1. 找到当前界面的商品表格（替换为你实际的表格名）
    QTableWidget* goodsTable = ui->tab_goods;
    if (goodsTable->rowCount() == 0) {
        QMessageBox::information(this, "提示", "购物车为空，无法结算！");
        return;
    }

    // 2. 统计总价+商品明细
    double total = 0.0;
    QString detail;
    for (int i = 0; i < goodsTable->rowCount(); ++i) {
        // 读取当前行的4列数据（编号、名称、价格、品牌）
        QString id = goodsTable->item(i, 0)->text();
        QString name = goodsTable->item(i, 1)->text();
        QString priceStr = goodsTable->item(i, 2)->text();
        // 注意：如果价格带“元”，要先去掉（比如priceStr = priceStr.remove("元");）
        double price = priceStr.toDouble();

        total += price;
        detail += QString("%1. %2（编号：%3） 价格：%4元\n").arg(i + 1).arg(name).arg(id).arg(priceStr);
    }

    // 3. 弹出结算确认框
    QString msg = QString("商品明细：\n%1\n合计金额：%2元\n是否确认结算？")
        .arg(detail)
        .arg(total, 0, 'f', 2); // 总价保留2位小数

    QMessageBox::StandardButton res = QMessageBox::question(
        this, "结算确认", msg, QMessageBox::Yes | QMessageBox::No
    );

    // 4. 确认结算后的操作
    if (res == QMessageBox::Yes) {
        // 清空表格
        goodsTable->setRowCount(0);
        // （可选）清空本地保存（如果之前做了持久化）
        QSettings settings("./config.ini", QSettings::IniFormat);
        settings.clear();
        QMessageBox::information(this, "成功", "结算完成！");
    }
}

void User_Form::on_Btn_delete_item_clicked()
{
    QTableWidget* goodsTable = ui->tab_goods; // 替换为你实际的表格名
    // 1. 检查是否有选中行
    QList<QTableWidgetItem*> selectedItems = goodsTable->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先选中要删除的商品！");
        return;
    }

    // 2. 获取选中行的行号（用QList+去重，替代QSet::toList()）
    QList<int> selectedRows;
    foreach(QTableWidgetItem * item, selectedItems) {
        int row = item->row();
        // 去重：如果行号不在列表中，才添加
        if (!selectedRows.contains(row)) {
            selectedRows.append(row);
        }
    }

    // 3. 倒序删除行（从最后一行开始删，防止行号混乱）
    std::sort(selectedRows.begin(), selectedRows.end(), std::greater<int>()); // 降序排列
    foreach(int row, selectedRows) {
        goodsTable->removeRow(row);
    }

    // 4. 提示删除成功
    QMessageBox::information(this, "成功", QString("已删除%1件选中商品！").arg(selectedRows.size()));
}

void User_Form::on_Btn_delete_items_clicked()
{
    QTableWidget* goodsTable = ui->tab_goods; // 替换为你实际的表格名
    if (goodsTable->rowCount() == 0) {
        QMessageBox::information(this, "提示", "购物车已为空！");
        return;
    }

    // 1. 二次确认（防止误操作）
    QMessageBox::StandardButton res = QMessageBox::question(
        this, "确认删除", "是否要删除所有商品？",
        QMessageBox::Yes | QMessageBox::No
    );
    if (res != QMessageBox::Yes) {
        return;
    }

    // 2. 清空表格
    goodsTable->setRowCount(0);
    QMessageBox::information(this, "成功", "所有商品已删除！");
}




