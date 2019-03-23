#include <QApplication>
#include "soap_client_widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SoapClientWidget w;
    w.show();

    return a.exec();
}
