#include "windows.h"
#include "widget.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

    Widget w;
    w.show();

    return a.exec();
}
