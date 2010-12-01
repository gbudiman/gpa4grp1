/* 
 * File:   render3D.h
 * Author: gbudiman
 *
 * Created on November 30, 2010, 9:55 PM
 */

#ifndef _RENDER3D_H
#define	_RENDER3D_H
#include <string>
#include <QtGui>
#include <iostream>
#include "rubik.h"
using namespace std;

class render3D : public QWidget {
    Q_OBJECT
public:
    render3D(QWidget* parent = 0);
    void setCube(rubik* cube);
    int reMapCell(int request, int face);
    char getFaceCell(string face, int i);
    QBrush getColor(char c);
    virtual ~render3D();
protected:
    void paintEvent(QPaintEvent* event);
private:
    rubik drawCube;
};

#endif	/* _RENDER3D_H */

