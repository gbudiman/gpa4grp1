/*
 * File:   main.cpp
 * Author: gbudiman
 *
 * Created on November 30, 2010, 7:59 PM
 */

#include <QtGui/QApplication>
#include "GWindow.h"
#include "render2D.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);
    GWindow gwindow;
   // connect(&socket, SIGNAL(setGUIstate(string state),&gWindow,create2Dview(state) 
    gwindow.show();
    // create and show your widgets here

    return app.exec();
}
