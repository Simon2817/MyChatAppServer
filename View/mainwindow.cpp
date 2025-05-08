#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlTableModel>
#include <QStandardItem>
#include <mydatabase.h>

// 单实例
MainWindow *MainWindow::m_MainWindow = nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    QString title = index.data(Qt::UserRole).toString();
    if (title == "用户账号")
    {
        QSqlTableModel *model = new QSqlTableModel(this, MyDatabase::getInstance()->m_Database);
        model->setTable("user_account");
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();
        // 个各个字段取别名
        model->setHeaderData(0, Qt::Horizontal, tr("id"));
        model->setHeaderData(1, Qt::Horizontal, tr("account"));
        model->setHeaderData(2, Qt::Horizontal, tr("password"));

        ui->tableView->setModel(model);
        ui->stackedWidget->setCurrentWidget(ui->userAccountPage);

        ui->tableView->hideColumn(0); // don't show the ID
    }
    else if (title == "用户信息")
    {
        QSqlTableModel *model = new QSqlTableModel(this, MyDatabase::getInstance()->m_Database);
        model->setTable("user_info");
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();

        ui->tableView_2->setModel(model);
        ui->stackedWidget->setCurrentWidget(ui->userInfoPage);
        ui->tableView_2->hideColumn(0);// don't show the ID
        ui->tableView_2->hideColumn(1);// don't show the uacID
    }
}
