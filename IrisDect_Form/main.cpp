#include "IrisDect_Form.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IrisDect_Form w;
    w.show();
    return a.exec();
}
