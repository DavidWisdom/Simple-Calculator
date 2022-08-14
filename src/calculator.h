#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_calculator.h"
#include <QPainter>
#include <QBitmap>
#include <QMouseEvent>
#include <QTextEdit>
#include <string>
#include "bigdecimal.h"

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = Q_NULLPTR);

private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
     void on_pushButton_8_clicked();
     void on_pushButton_9_clicked();
     void on_pushButton_10_clicked();
     void on_pushButton_11_clicked();
     void on_pushButton_12_clicked();
     void on_pushButton_13_clicked();
     void on_pushButton_14_clicked();
     void on_pushButton_15_clicked();
     void on_pushButton_16_clicked();
     void on_pushButton_17_clicked();
     void on_pushButton_18_clicked();
     void on_pushButton_19_clicked();
     void on_pushButton_20_clicked();

private:
    void push(const char c);
    QString showQString(const QString& qstr);
    QString val1;
    QString val2;
    int cur = 1;                                        // 当前输入的是第几个数值
    bool isVal1Empty = true; 
    bool isVal2Empty = true;
    bool symbolOfVal1 = true;
    bool symbolOfVal2 = true;
    bool isVal1HasDot = false;
    bool isVal2HasDot = false;
    char ch = '+';
    bool isCh = false;
    Ui::CalculatorClass ui;
    QPoint last_mouse_position;
};
