#include "widget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    btnFriendly = new QPushButton("В5: Дружественные числа", this);
    btnFraction = new QPushButton("С5: Десятичная дробь", this);
    btnGreater = new QPushButton("С11: Перестановки больше", this);
    btnDigitsBase = new QPushButton("В11: Кол-во цифр в n-системе", this);
    btnCompute = new QPushButton("Посчитать", this);
    btnCompute->setVisible(false);

    labelInput1 = new QLabel(this);
    labelInput2 = new QLabel(this);
    lineInput1 = new QLineEdit(this);
    lineInput2 = new QLineEdit(this);
    labelInput1->setVisible(false);
    labelInput2->setVisible(false);
    lineInput1->setVisible(false);
    lineInput2->setVisible(false);


    labelResult = new QLabel("Здесь будет результат", this);
    labelResult->setWordWrap(true);


    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(btnFriendly);
    layout->addWidget(btnFraction);
    layout->addWidget(btnGreater);
    layout->addWidget(btnDigitsBase);

    QHBoxLayout *inputRow1 = new QHBoxLayout;
    inputRow1->addWidget(labelInput1);
    inputRow1->addWidget(lineInput1);

    QHBoxLayout *inputRow2 = new QHBoxLayout;
    inputRow2->addWidget(labelInput2);
    inputRow2->addWidget(lineInput2);

    layout->addLayout(inputRow1);
    layout->addLayout(inputRow2);
    layout->addWidget(btnCompute);
    layout->addWidget(labelResult);


    connect(btnFriendly, &QPushButton::clicked, this, &Widget::FriendN);
    connect(btnFraction, &QPushButton::clicked, this, &Widget::countD);
    connect(btnGreater, &QPushButton::clicked, this, &Widget::countG);
    connect(btnDigitsBase, &QPushButton::clicked, this, &Widget::countB);
    connect(btnCompute, &QPushButton::clicked, this, &Widget::compRes);
}

void Widget::setupInputs(int count, const QString &label1Text, const QString &label2Text)
{
    currentTask = None;

    labelInput1->setVisible(count >= 1);
    lineInput1->setVisible(count >= 1);
    labelInput2->setVisible(count == 2);
    lineInput2->setVisible(count == 2);

    labelInput1->setText(label1Text);
    labelInput2->setText(label2Text);

    lineInput1->clear();
    lineInput2->clear();

    btnCompute->setVisible(true);
}

void Widget::FriendN()
{
    setupInputs(2, "Введите первое число:", "Введите второе число:");
    currentTask = Friendly;
}

void Widget::countD()
{
    setupInputs(2, "Введите p (>1):", "Введите k:");
    currentTask = Fraction;
}

void Widget::countG()
{
    setupInputs(1, "Введите число:");
    currentTask = Greater;
}

void Widget::countB()
{
    setupInputs(2, "Введите число x:", "Введите основание n (2-9):");
    currentTask = DigitsBase;
}

int Widget::sumDivisors(int n)
{
    int sum = 0;
    for (int i = 1; i < n; ++i) {
        if (n % i == 0) sum += i;
    }
    return sum;
}

void Widget::compRes()
{
    if (currentTask == Friendly) {
        int a = lineInput1->text().toInt();
        int b = lineInput2->text().toInt();
        int sumA = sumDivisors(a);
        int sumB = sumDivisors(b);
        labelResult->setText((sumA == b && sumB == a)
                                 ? QString("Числа %1 и %2 дружественные.").arg(a).arg(b)
                                 : QString("Числа %1 и %2 не дружественные.").arg(a).arg(b));
    }
    else if (currentTask == Fraction) {
        int p = lineInput1->text().toInt();
        int k = lineInput2->text().toInt();
        if (p <= 1) {
            labelResult->setText("Ошибка: p должно быть больше 1.");
            return;
        }
        QString result = "0.";
        int cel = 0, ost = 1;
        for (int i = 0; i < k; i++) {
            ost *= 10;
            cel = ost / p;
            ost %= p;
            result += QString::number(cel);
            if (ost == 0) break;
        }
        labelResult->setText(result);
    }
    else if (currentTask == Greater) {
        int n = lineInput1->text().toInt();
        int orig = n, k = 0, rev = 0;
        while (n > 0) {
            rev = rev * 10 + n % 10;
            n /= 10;
            k++;
        }
        int x, a = 0;
        while (rev >= 10) {
            x = rev / 10;
            k--;
            int cnt = 0;
            while (x > 0) {
                if (x % 10 > rev % 10) cnt++;
                x /= 10;
            }
            a = k * (a + cnt);
            rev /= 10;
        }
        labelResult->setText(QString("Чисел составленных из цифр числа %1, больше чем оно само: %2")
                                 .arg(orig).arg(a));
    }
    else if (currentTask == DigitsBase) {
        int x = lineInput1->text().toInt();
        int n = lineInput2->text().toInt();
        if (n > 2 && n < 9) {
            labelResult->setText("Ошибка: основание должно быть от 2 до 9.");
            return;
        }
        int count = 0, temp = x;
        do {
            temp /= n;
            count++;
        } while (temp > 0);
        labelResult->setText(QString("Количество цифр в системе с основанием %1: %2").arg(n).arg(count));
    }
}
