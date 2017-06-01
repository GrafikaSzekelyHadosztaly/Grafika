#include <QApplication>
#include "GUI/MainWindow.h"
#include "Core/Matrices.h"
#include <fstream>

using namespace cagd;
using namespace std;

int main(int argc, char **argv)
{
    // creating an application object and setting one of its attributes
    QApplication app(argc, argv);

    // if you have installed a different version of Qt, it may happen that
    // the application attribute Qt::AA_UseDesktopOpenGL is not recognized
    // on Windows its existence is critical for our applications
    // on Linux or Mac you can uncomment this line
    app.setAttribute(Qt::AA_UseDesktopOpenGL, true);

    // creating a main window object
    MainWindow mwnd;
    mwnd.showMaximized();

    // running the application
//beleirtam egy uj kodot
    // en is beirok egyet
    return app.exec();
}
