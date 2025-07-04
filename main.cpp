#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("Задания В5, В11, С5, С11");
    w.resize(400, 300);
    w.show();
    return a.exec();
}
