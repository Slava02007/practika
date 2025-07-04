#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);

private slots:
    void FriendN();
    void countD();
    void countG();
    void countB();
    void compRes();

private:
    void setupInputs(int count, const QString &label1Text, const QString &label2Text = "");
    int sumDivisors(int n);

    QPushButton *btnFriendly;
    QPushButton *btnFraction;
    QPushButton *btnGreater;
    QPushButton *btnDigitsBase;
    QPushButton *btnCompute;

    QLabel *labelInput1;
    QLabel *labelInput2;
    QLineEdit *lineInput1;
    QLineEdit *lineInput2;

    QLabel *labelResult;

    enum TaskType {
        None, Friendly, Fraction, Greater, DigitsBase
    } currentTask = None;
};

#endif // WIDGET_H
