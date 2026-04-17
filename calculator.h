#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>

class Calculator : public QWidget {
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);

private:
    QLineEdit *display;

    double storedValue;
    QString pendingOp;

    void createUI();
    void onNumberClicked(QString text);
    void onOperationClicked(QString op);
    void calculate();
};

#endif
