#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QListWidgetItem>
#include <QTimer>
#include <QTime>
#include <QMap>
#include <QDateTime>
#include <QInputDialog>
#include <QMessageBox>

#include <vector>
#include <nlohmann/json.hpp>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // MENU
    void on_addToOrderButton_clicked();
    void on_submitOrderButton_clicked();

    // STATUS (automatic)
    void updateOrderStatus();

    // NAVIGATION
    void on_customerButton_clicked();
    void on_staffButton_clicked();
    void on_backButton_clicked();
    void on_checkorderStatus_clicked();

    // STAFF
    void on_completeOrderButton_clicked();

    // HISTORY
    void on_historyListWidget_itemClicked(QListWidgetItem *item);
    void on_viewhistoryButton_clicked();

private:
    Ui::MainWindow *ui;

    QString currentOrder;

    std::vector<nlohmann::json> orders;

    // TIMER SYSTEM
    QTimer *statusTimer;
    QTime orderStartTime;

    // TIME TRACKING
    QMap<QString, QDateTime> orderPlacedTime;
    QMap<QString, QDateTime> orderCompletedTime;

    // HELPER
    QString cleanItemName(const QString &item);
};

#endif // MAINWINDOW_H
