#include "HQCMainWindow.h"

#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    HQCCMainWindow w;
    //w.show();
    w.showFullScreen();
    return a.exec();
}
