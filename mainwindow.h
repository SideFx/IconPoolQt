/////////////////////////////////////////////////////////////////////////////
// Name:        mainwindow.h
// Purpose:     MainWindow header
// Author:      Jan Buchholz
// Created:     2025-11-17
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QMainWindow>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTableWidget* m_tableView;

    void populateTableView();

private slots:
    void onActionQuit();
};

