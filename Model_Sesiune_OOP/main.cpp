#include "Main_Window.h"
#include <QtWidgets/QApplication>
#include "repo.h"
#include "service.h"


int main(int argc, char *argv[])
{
    //testeRepo();
    QApplication a(argc, argv);

    FileRepo rep;
    Service srv{ rep };

    
    Main_Window w1(srv);

    w1.setWindowTitle(" Meniu1");
    w1.show();

    return a.exec();
}
