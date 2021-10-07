﻿#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton->setText(tr("Converting"));
    ui->pushButton->showLoading(true);
    ui->pushButton->setIcon(":/duck.png");
    ui->pushButton->setLoadingPng(":/loading.png", 960, 40);

    ui->pushButton_2->setText("Merging");
    ui->pushButton_2->showLoading(true);
    ui->pushButton_2->setIcon(":/duck.png");
    ui->pushButton_2->setLoadingPng(":/loading1.png", 288, 16);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    static bool bLoading = true;
    bLoading = !bLoading;
    ui->pushButton->showLoading(bLoading);
}


void MainWindow::on_pushButton_2_clicked()
{
    static bool bLoading = true;
    bLoading = !bLoading;
    ui->pushButton_2->showLoading(bLoading);
}

