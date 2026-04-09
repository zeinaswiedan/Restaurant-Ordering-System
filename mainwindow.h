private slots:

// MENU
void on_addToOrderButton_clicked();
void on_submitOrderButton_clicked();

// ORDER STATUS
void on_updateStatusButton_clicked();

// NAVIGATION
void on_customerButton_clicked();
void on_staffButton_clicked();
void on_backButton_clicked();

// STAFF DASHBOARD
void on_clearOrdersButton_clicked();
void on_completeOrderButton_clicked();

private:
Ui::MainWindow *ui;
QString currentOrder;
};
#endif // MAINWINDOW_H
