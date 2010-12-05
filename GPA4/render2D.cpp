/* 
 * File:   render2D.cpp
 * Author: gbudiman
 * 
 * Created on November 30, 2010, 8:31 PM
 */

#include "render2D.h"
#include <string>
#include <iostream>
using namespace std;

render2D::render2D(QWidget* parent) : QWidget(parent) {
}

render2D::~render2D() {
}

void render2D::setState(string state) {
    cubeState = state;
    this->update();
}

void render2D::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    for(int i = 0; i < 9; i++) {
        painter.setBrush(Qt::black);
        painter.drawRect(100 + i%3 * 30, i/3 * 30, 30, 30);
        //painter.setBrush(getColor(cubeState.at(i)));
        painter.fillRect(100 + i%3 * 30 + 1, i/3 * 30 + 1, 30-1, 30-1, getColor(cubeState.at(i)));
    }
    for(int i = 9; i < 18; i++) {
        painter.setBrush(Qt::black);
        painter.drawRect(10 + (i-9)%3 * 30, i/3 * 30, 30, 30);
        //painter.setBrush(getColor(cubeState.at(i)));
        painter.fillRect(10 + (i-9)%3 * 30 + 1, i/3 * 30 + 1, 30-1, 30-1, getColor(cubeState.at(i)));
    }
    for(int i = 18; i < 27; i++) {
        painter.setBrush(Qt::black);
        painter.drawRect(100 + (i-18)%3 * 30, (i-9)/3 * 30, 30, 30);
        //painter.setBrush(getColor(cubeState.at(i)));
        painter.fillRect(100 + (i-18)%3 * 30 + 1, (i-9)/3 * 30 + 1, 30-1, 30-1, getColor(cubeState.at(i)));
    }
    for(int i = 27; i < 36; i++) {
        painter.setBrush(Qt::black);
        painter.drawRect(190 + (i-27)%3 * 30, (i-18)/3 * 30, 30, 30);
        //painter.setBrush(getColor(cubeState.at(i)));
        painter.fillRect(190 + (i-27)%3 * 30 + 1, (i-18)/3 * 30 + 1, 30-1, 30-1, getColor(cubeState.at(i)));
    }
    for(int i = 36; i < 45; i++) {
        painter.setBrush(Qt::black);
        painter.drawRect(280 + (i-36)%3 * 30, (i-27)/3 * 30, 30, 30);
        //painter.setBrush(getColor(cubeState.at(i)));
        painter.fillRect(280 + (i-36)%3 * 30 + 1, (i-27)/3 * 30 + 1, 30-1, 30-1, getColor(cubeState.at(i)));
    }
    for(int i = 45; i < 54; i++) {
        painter.setBrush(Qt::black);
        painter.drawRect(100 + (i-45)%3 * 30, (i-27)/3 * 30, 30, 30);
        //painter.setBrush(getColor(cubeState.at(i)));
        painter.fillRect(100 + (i-45)%3 * 30 + 1, (i-27)/3 * 30 + 1, 30-1, 30-1, getColor(cubeState.at(i)));
    }
    painter.setRenderHint(QPainter::Antialiasing, true);
}

QBrush render2D::getColor(char s) {
    if (s == 'R') {
        return Qt::red;
    }
    else if (s == 'Y') {
        return Qt::yellow;
    }
    else if (s == 'B') {
        return Qt::blue;
    }
    else if (s == 'O') {
        return QBrush(QColor(255, 102, 0));
    }
    else if (s == 'W') {
        return Qt::white;
    }
    else {
        return QBrush(QColor(0, 255, 0));
    }
}
