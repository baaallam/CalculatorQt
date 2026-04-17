#include "calculator.h"
#include <QGridLayout>
#include <QPushButton>
#include <QFont>

Calculator::Calculator(QWidget *parent) : QWidget(parent) {
    storedValue = 0;
    pendingOp = "";
    createUI();
}

void Calculator::createUI() {
    setWindowTitle("Khadija Calculator");
    resize(350, 500);
    setStyleSheet("background:black; color:white;");

    QGridLayout *layout = new QGridLayout(this);

    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setStyleSheet("font-size:40px; background:black; color:white; border:none;");
    layout->addWidget(display, 0, 0, 1, 4);

    QString buttons[4][4] = {
        {"AC","+/-","%","÷"},
        {"7","8","9","×"},
        {"4","5","6","-"},
        {"1","2","3","+"}
    };

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            QString text = buttons[i][j];
            QPushButton *btn = new QPushButton(text);
            btn->setStyleSheet(
                "background:#333; color:white; font-size:22px; border-radius:25px;"
            );
            layout->addWidget(btn, i+1, j);

            connect(btn, &QPushButton::clicked, [=]() {
                if(text == "AC") {
                    display->setText("0");
                    storedValue = 0;
                    pendingOp = "";
                }
                else if(text == "+/-") {
                    display->setText(QString::number(-display->text().toDouble()));
                }
                else if(text == "%") {
                    display->setText(QString::number(display->text().toDouble()/100));
                }
                else if(text == "+" || text == "-" || text == "×" || text == "÷") {
                    storedValue = display->text().toDouble();
                    pendingOp = text;
                    display->setText("0");
                }
                else {
                    QString cur = display->text();
                    display->setText(cur == "0" ? text : cur + text);
                }
            });
        }
    }

    QPushButton *zero = new QPushButton("0");
    QPushButton *dot  = new QPushButton(".");
    QPushButton *eq   = new QPushButton("=");

    zero->setStyleSheet("background:#333; color:white; font-size:22px;");
    dot->setStyleSheet("background:#333; color:white;");
    eq->setStyleSheet("background:orange; color:white;");

    layout->addWidget(zero, 5, 0, 1, 2);
    layout->addWidget(dot, 5, 2);
    layout->addWidget(eq, 5, 3);

    connect(zero, &QPushButton::clicked, [=]() {
        display->setText(display->text() == "0" ? "0" : display->text() + "0");
    });

    connect(dot, &QPushButton::clicked, [=]() {
        if(!display->text().contains('.'))
            display->setText(display->text() + ".");
    });

    connect(eq, &QPushButton::clicked, [=]() {
        double b = display->text().toDouble();
        double result = 0;

        if(pendingOp == "+") result = storedValue + b;
        if(pendingOp == "-") result = storedValue - b;
        if(pendingOp == "×") result = storedValue * b;
        if(pendingOp == "÷") result = (b == 0 ? 0 : storedValue / b);

        display->setText(QString::number(result));
        pendingOp = "";
    });
}
