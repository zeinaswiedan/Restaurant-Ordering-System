#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtNetwork/QTcpSocket>
#include <QRegularExpression> 

#include <algorithm>

using json = nlohmann::json;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    statusTimer = new QTimer(this);
    connect(statusTimer, &QTimer::timeout, this, &MainWindow::updateOrderStatus);

    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::connected, this, &MainWindow::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::onReadyRead);

    socket->connectToHost("127.0.0.1", 8080);
    ui->stackedWidget->setCurrentWidget(ui->welcomePage);

}

MainWindow::~MainWindow()
{
    delete ui;
}

// ================= NETWORK =================
void MainWindow::onConnected()
{
    ui->orderTextEdit->append("Connected to server!");
}

void MainWindow::onReadyRead()
{
    static QByteArray buffer;
buffer.append(socket->readAll());

    try {
        json response = json::parse(buffer.toStdString());
        QString status = QString::fromStdString(response["status"]);

        ui->orderTextEdit->append("Server Status: " + status);
buffer.clear();  
  }
    catch (...) {
        
    }
}

// ================= HELPER =================
QString MainWindow::cleanItemName(const QString &item)
{
    QString clean = item;
    clean.remove(QRegularExpression("[^a-zA-Z]"));
    return clean;
}

// ================= ADD TO ORDER =================
void MainWindow::on_addToOrderButton_clicked()
{
    if (!ui->menuListWidget->currentItem()) {
        ui->orderTextEdit->append("Please select an item!");
        return;
    }

    QString item = ui->menuListWidget->currentItem()->text();
    int quantity = ui->quantitySpinBox->value();

    ui->orderTextEdit->append(item + " x " + QString::number(quantity));
}

// ================= SUBMIT ORDER =================
void MainWindow::on_submitOrderButton_clicked()
{
    if (!ui->menuListWidget->currentItem()) {
        ui->orderTextEdit->append("Error: No item selected!");
        return;
    }

    QString rawItem = ui->menuListWidget->currentItem()->text();
    QString item = cleanItemName(rawItem);
    int quantity = ui->quantitySpinBox->value();

    std::vector<std::string> menu = {
        "Burger","Pizza","Noodles","Pasta","Chicken",
        "Fish","Meat","Shawerma","Fries","Salad",
        "Cake","Soda","Water"
    };

    if (std::find(menu.begin(), menu.end(), item.toStdString()) == menu.end()) {
        ui->orderTextEdit->append("Error: Invalid item!");
        return;
    }

    if (quantity <= 0) {
        ui->orderTextEdit->append("Error: Quantity must be greater than 0!");
        return;
    }


    json order;
    order["item"] = item.toStdString();
    order["quantity"] = quantity;

    QString message = QString::fromStdString(order.dump());

    socket->write(message.toUtf8());

    ui->orderTextEdit->append("Order sent to server!");

    QString displayOrder = rawItem + " x " + QString::number(quantity);

    orderPlacedTime[displayOrder] = QDateTime::currentDateTime();

    ui->incomingOrdersList->addItem(displayOrder);

    currentOrder = displayOrder;

    orderStartTime.start();
    statusTimer->start(1000);
}

// ================= STATUS =================
void MainWindow::updateOrderStatus()
{
    int elapsed = orderStartTime.elapsed() / 1000;

    ui->preparingLabel->setStyleSheet("");
    ui->cookingLabel->setStyleSheet("");
    ui->readyLabel->setStyleSheet("");

    if (elapsed < 10) {
        ui->preparingLabel->setStyleSheet("color:#7CFFB2; font-weight:bold;");
    }
    else if (elapsed < 20) {
        ui->cookingLabel->setStyleSheet("color:#7CFFB2; font-weight:bold;");
    }
    else {
        ui->readyLabel->setStyleSheet("color:#7CFFB2; font-weight:bold;");
        statusTimer->stop();
    }
}

// ================= NAVIGATION =================
void MainWindow::on_customerButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->menuPage);
}

void MainWindow::on_staffButton_clicked()
{
    bool ok;

    QString staffID = QInputDialog::getText(
        this,
        "Staff Authentication",
        "Enter Staff ID:",
        QLineEdit::Normal,
        "",
        &ok
        );

    if (!ok || staffID.isEmpty())
        return;

    if (staffID.startsWith("1234") && staffID.length() == 6) {
        QMessageBox::information(this, "Access Granted", "Welcome Staff!");
        ui->stackedWidget->setCurrentWidget(ui->staffPage);
    } else {
        QMessageBox::warning(this, "Access Denied", "Invalid Staff ID!");
    }
}

void MainWindow::on_backButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->welcomePage);
}

void MainWindow::on_checkorderStatus_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->orderStatusPage);
}

void MainWindow::on_viewhistoryButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->OrderHistoryPage);
}

// ================= STAFF =================
void MainWindow::on_completeOrderButton_clicked()
{
    QListWidgetItem *item = ui->incomingOrdersList->currentItem();

    if (!item) {
        ui->orderTextEdit->append("Select an order first!");
        return;
    }

    QString order = item->text();

    orderCompletedTime[order] = QDateTime::currentDateTime();

    QListWidgetItem *historyItem =
        new QListWidgetItem(order + " ✔ Completed");

    historyItem->setForeground(Qt::green);

    ui->historyListWidget->addItem(historyItem);

    delete item;
}

// ================= HISTORY DETAILS =================
void MainWindow::on_historyListWidget_itemClicked(QListWidgetItem *item)
{
    if (!item)
        return;

    QString order = item->text();
    order.remove(" ✔ Completed");

    QStringList parts = order.split(" x ");
    QString itemName = parts[0];
    QString quantity = (parts.size() > 1) ? parts[1] : "1";

    QDateTime placed = orderPlacedTime.value(order);
    QDateTime completed = orderCompletedTime.value(order);

    QString details;
    details += "Item: " + itemName + "\n";
    details += "Quantity: " + quantity + "\n";
    details += "Status: Completed\n";

    if (placed.isValid())
        details += "Placed: " + placed.toString("hh:mm:ss AP") + "\n";

    if (completed.isValid())
        details += "Completed: " + completed.toString("hh:mm:ss AP") + "\n";

    if (placed.isValid() && completed.isValid()) {
        int seconds = placed.secsTo(completed);
        details += "Total Time: " + QString::number(seconds) + " seconds\n";
    }

    ui->historyDetailsBox->setText(details);
}
