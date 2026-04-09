#include "mainwindow.h"
#include "./ui_mainwindow.h"

int statusIndex = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


// ================= MENU =================

void MainWindow::on_addToOrderButton_clicked()
{
    if (!ui->menuListWidget->currentItem())
        return;

    QString item = ui->menuListWidget->currentItem()->text();
    int quantity = ui->quantitySpinBox->value();

    QString order = item + " x " + QString::number(quantity);

    ui->orderTextEdit->append(order);
}


void MainWindow::on_submitOrderButton_clicked()
{
    if (ui->orderTextEdit->toPlainText().isEmpty()) {
        ui->orderTextEdit->append("No items in order!");
        return;
    }

    ui->orderTextEdit->append("Order Submitted!");

    ui->incomingOrdersList->addItem(ui->orderTextEdit->toPlainText());

    currentOrder = ui->orderTextEdit->toPlainText();
}


// ================= ORDER STATUS =================

void MainWindow::on_updateStatusButton_clicked()
{
    ui->receivedLabel->setStyleSheet("");
    ui->preparingLabel->setStyleSheet("");
    ui->readyLabel->setStyleSheet("");
    ui->completedLabel->setStyleSheet("");

    if (statusIndex == 0)
        ui->receivedLabel->setStyleSheet("QLabel { color: #7CFFB2; font-weight: bold; }");

    else if (statusIndex == 1)
        ui->preparingLabel->setStyleSheet("QLabel { color: #7CFFB2; font-weight: bold; }");

    else if (statusIndex == 2)
        ui->readyLabel->setStyleSheet("QLabel { color: #7CFFB2; font-weight: bold; }");

    else if (statusIndex == 3)
        ui->completedLabel->setStyleSheet("QLabel { color: #7CFFB2; font-weight: bold; }");

    statusIndex++;
}


// ================= NAVIGATION =================

void MainWindow::on_customerButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_staffButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_backButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->welcomePage);
}


// ================= STAFF DASHBOARD =================

void MainWindow::on_clearOrdersButton_clicked()
{
    ui->incomingOrdersList->clear();
}


void MainWindow::on_completeOrderButton_clicked()
{
    QListWidgetItem *item = ui->incomingOrdersList->currentItem();

    if (!item)
        return;

    QString order = item->text();

    // Add to history
    ui->historyListWidget->addItem(order + " - Completed");

    // Remove from current orders
    delete item;

    // Go to history page
    ui->stackedWidget->setCurrentWidget(ui->OrderHistoryPage);
}
