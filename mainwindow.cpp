/////////////////////////////////////////////////////////////////////////////
// Name:        mainwindow.cpp
// Purpose:     The MainWindow: QListWidget + icon data
// Author:      Jan Buchholz
// Created:     2025-11-17
/////////////////////////////////////////////////////////////////////////////

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "iconpool.h"
#include <QHeaderView>
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::onActionQuit);
    m_tableView = new QTableWidget();
    setCentralWidget(m_tableView);
    populateTableView();
    int totalWidth = 0;
    for (int col = 0; col < m_tableView->columnCount(); col++) {
        totalWidth += m_tableView->columnWidth(col) + 10;
    }
    resize(totalWidth, height());
}

MainWindow::~MainWindow() {
    delete m_tableView;
    delete ui;
}

void MainWindow::onActionQuit() {
    close();
}

void MainWindow::populateTableView() {
    QStringList tableHeaders = {"Icon Name", "Normal", "Hover", "Pressed", "Disabled"};
    m_tableView->clearContents();
    m_tableView->setRowCount(0);
    m_tableView->setColumnCount(tableHeaders.count());
    m_tableView->setHorizontalHeaderLabels(tableHeaders);
    m_tableView->horizontalHeader()->setStretchLastSection(false);
    m_tableView->setIconSize(QSize(24, 24));
    int row = 0;
    QStringList iconNames = IconPool::getIconNamesAll();
    for (auto& icon : iconNames) {
        m_tableView->insertRow(row);
        m_tableView->setItem(row, 0, new QTableWidgetItem(icon));
        QPixmap n_pixmap, h_pixmap, p_pixmap, d_pixmap;
        n_pixmap.loadFromData(IconPool::getSVGIconByNameAndState(icon, IconState::Normal));
        h_pixmap.loadFromData(IconPool::getSVGIconByNameAndState(icon, IconState::Hover));
        p_pixmap.loadFromData(IconPool::getSVGIconByNameAndState(icon, IconState::Pressed));
        d_pixmap.loadFromData(IconPool::getSVGIconByNameAndState(icon, IconState::Disabled));
        QTableWidgetItem* n_item = new QTableWidgetItem();
        n_item->setIcon(n_pixmap);
        QTableWidgetItem* h_item = new QTableWidgetItem();
        h_item->setIcon(h_pixmap);
        QTableWidgetItem* p_item = new QTableWidgetItem();
        p_item->setIcon(p_pixmap);
        QTableWidgetItem* d_item = new QTableWidgetItem();
        d_item->setIcon(d_pixmap);
        m_tableView->setItem(row, 1, n_item);
        m_tableView->setItem(row, 2, h_item);
        m_tableView->setItem(row, 3, p_item);
        m_tableView->setItem(row, 4, d_item);
        row++;
    }
    QHeaderView* header = m_tableView->verticalHeader();
    header->sectionResizeMode(QHeaderView::Fixed);
    m_tableView->resizeColumnsToContents();
}
