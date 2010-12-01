/* 
 * File:   render3D.cpp
 * Author: gbudiman
 * 
 * Created on November 30, 2010, 9:55 PM
 */

#include "render3D.h"
#include "rubik.h"
#include <string>
#include <iostream>
using namespace std;

render3D::render3D(QWidget* parent) : QWidget(parent) {
}

render3D::~render3D() {
}

void render3D::setCube(rubik* cube) {
    drawCube.setState(cube->display());
    drawCube.applyOrientation(cube->showOrientation());
    update();
}

void render3D::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.translate(0, 20);
    painter.shear(-1.75, 0);
    for (int i = 0; i < 9; i++) {
        painter.setBrush(Qt::black);
        painter.drawRect(100 + i%3 * 30, i/3 * 12, 30, 12);
        painter.fillRect(100 + i%3 * 30 + 1, i/3 * 12 + 1, 30-1, 12-1, getColor(getFaceCell("top", i)));
    }
    painter.shear(1.75, 0);
    for (int i = 0; i < 9; i++) {
        painter.setBrush(Qt::black);
        painter.drawRect(37 + i%3 * 30, 37 + i/3 * 30, 30, 30);
        painter.fillRect(37 + i%3 * 30 + 1, 37 + i/3 * 30 + 1, 30-1, 30-1, getColor(getFaceCell("front", i)));
    }
    painter.shear(0, -0.58);
    painter.translate(128, 53);
    for (int i = 0; i < 9; i++) {
        painter.setBrush(Qt::black);
        painter.drawRect(i%3 * 21, 58 + i/3 * 30, 21, 30);
        painter.fillRect(i%3 * 21 + 1, 58 + i/3 * 30 + 1, 21-1, 30-1, getColor(getFaceCell("right", i)));
    }
    painter.setRenderHint(QPainter::Antialiasing, true);
}

int render3D::reMapCell(int request, int face) {
    string combination = "";
    char cellState;
    switch(drawCube.top) {
        case 0:
            switch(drawCube.front) {
                case 1: combination = "BAA"; break;
                case 2: combination = "AAA"; break;
                case 3: combination = "DAA"; break;
                case 4: combination = "CAA"; break;
            } break;
        case 1:
            switch(drawCube.front) {
                case 2: combination = "DDD"; break;
                case 0: combination = "CDB"; break;
                case 4: combination = "BBD"; break;
                case 5: combination = "ADD"; break;
            } break;
        case 2:
            switch(drawCube.front) {
                case 0: combination = "CCB"; break;
                case 1: combination = "BBA"; break;
                case 5: combination = "BBD"; break;
                case 3: combination = "ADD"; break;
            } break;
        case 3:
            switch(drawCube.front) {
                case 0: combination = "CBB"; break;
                case 2: combination = "BBB"; break;
                case 5: combination = "ABD"; break;
                case 4: combination = "DDB"; break;
            } break;
        case 4:
            switch(drawCube.front) {
                case 1: combination = "DDA"; break;
                case 0: combination = "CAB"; break;
                case 3: combination = "BBC"; break;
                case 5: combination = "ACD"; break;
            } break;
        case 5:
            switch(drawCube.front) {
                case 1: combination = "BCC"; break;
                case 2: combination = "ACC"; break;
                case 3: combination = "DCC"; break;
                case 4: combination = "CCC"; break;
            } break;
    }

    cellState = combination.at(face);
    if (cellState == 'A') {
        return request;
    }
    else if (cellState == 'B') {
        switch (request) {
            case 0: return 2;
            case 1: return 5;
            case 2: return 8;
            case 3: return 1;
            case 4: return 4;
            case 5: return 7;
            case 6: return 0;
            case 7: return 3;
            case 8: return 6;
        }
    }
    else if (cellState == 'C') {
        switch (request) {
            case 0: return 8;
            case 1: return 7;
            case 2: return 6;
            case 3: return 5;
            case 4: return 4;
            case 5: return 3;
            case 6: return 2;
            case 7: return 1;
            case 8: return 0;
        }
    }
    else {
        switch (request) {
            case 0: return 6;
            case 1: return 3;
            case 2: return 0;
            case 3: return 7;
            case 4: return 4;
            case 5: return 1;
            case 6: return 8;
            case 7: return 5;
            case 8: return 2;
        }
    }
    return -1;
}

char render3D::getFaceCell(string face, int i) {
    /*
     * face can only take value of "front", "top", or "left"
     */

    int remapped;
    if (face.compare("top") == 0) {
        remapped = reMapCell(i, 0);
        return drawCube.cube[drawCube.top][remapped];
    }
    else if (face.compare("front") == 0) {
        remapped = reMapCell(i, 1);
        return drawCube.cube[drawCube.front][remapped];
    }
    else {
        remapped = reMapCell(i, 2);
        return drawCube.cube[drawCube.right][remapped];
    }
}

QBrush render3D::getColor(char c) {
    switch (c) {
        case 'R': return Qt::red;
        case 'Y': return Qt::yellow;
        case 'B': return Qt::blue;
        case 'O': return QBrush(QColor(255, 102, 0));
        case 'W': return Qt::white;
        case 'G': return QBrush(QColor(0, 255, 0));
    }
}