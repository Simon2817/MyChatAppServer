#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMutex>
#include <QStandardItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    static MainWindow *m_MainWindow;

    static MainWindow *getInstance()
    {
        QMutex mutex;
        if (MainWindow::m_MainWindow == nullptr)
        {
            QMutexLocker locker(&mutex);
            return new MainWindow();
        }
        return MainWindow::m_MainWindow;
    }

private slots:
    void on_treeView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QStandardItemModel model;
};

#endif // MAINWINDOW_H
