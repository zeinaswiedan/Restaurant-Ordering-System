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

void MainWindow::on_pushButton_3_clicked()
{
    if (!ui->listWidget->currentItem()) return;

    QString item = ui->listWidget->currentItem()->text();
    int quantity = ui->spinBox->value();

    QString order = item + " x" + QString::number(quantity);

    ui->textEdit->append(order);
}


void MainWindow::on_pushButton_4_clicked()
{
    if (ui->textEdit->toPlainText().isEmpty()) {
        ui->textEdit->append("No items in order!");
        return;
    }

    ui->textEdit->append("Order Submitted!");
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->label_received->setStyleSheet("");
    ui->label_preparing->setStyleSheet("");
    ui->label_ready->setStyleSheet("");
    ui->label_completed->setStyleSheet("");

    if (statusIndex == 0)
    {
        ui->label_received->setStyleSheet("QLabel { color: #7CFFB2; font-weight: bold; }");
    }
    else if (statusIndex == 1)
    {
        ui->label_preparing->setStyleSheet("QLabel { color: #7CFFB2; font-weight: bold; }");
    }
    else if (statusIndex == 2)
    {
        ui->label_ready->setStyleSheet("QLabel { color: #7CFFB2; font-weight: bold; }");
    }
    else if (statusIndex == 3)
    {

        ui->label_completed->setStyleSheet("QLabel { color: #7CFFB2; font-weight: bold; }");
    }

    statusIndex++;
}

