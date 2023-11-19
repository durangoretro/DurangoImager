#include <QApplication>
#include "durangoImagerUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DurangoImager durangoImager;
    durangoImager.show();
    return a.exec();
}
