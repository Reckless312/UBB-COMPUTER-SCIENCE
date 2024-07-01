#include "App.h"
#include <QtWidgets/QApplication>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    App b;
    return a.exec();
}
