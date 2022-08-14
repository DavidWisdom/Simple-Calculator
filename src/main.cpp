#include "calculator.h"
#include <QtWidgets/QApplication>
#include <QTextEdit>

int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication a(argc, argv);
    Calculator w;
    w.show();
    return a.exec();
}
