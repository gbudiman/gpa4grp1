/* 
 * File:   render2D.cpp
 * Author: gbudiman
 * 
 * Created on November 30, 2010, 8:31 PM
 */

#include "render2D.h"

render2D::render2D() {
}

render2D::~render2D() {
}

void render2D::setState(string state) {
    cubeState = state;
    update();
}

void render2D::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    for(int i = 0; i < 9; i++) {
        painter.setPen(Qt::SolidLine);
        painter.drawRect(100 + i%3 * 30, i/3 * 30, 30, 30);
    }
    for(int i = 9; i < 18; i++) {
        painter.setPen(Qt::SolidLine);
        painter.drawRect(100 + i%3 * 30, i/3 * 30, 30, 30);
    }
    for(int i = 18; i < 27; i++) {
        painter.setPen(Qt::SolidLine);
        painter.drawRect(100 + i%3 * 30, i/3 * 30, 30, 30);
    }
    for(int i = 27; i < 36; i++) {
        painter.setPen(Qt::SolidLine);
        painter.drawRect(100 + i%3 * 30, i/3 * 30, 30, 30);
    }
    for(int i = 36; i < 45; i++) {
        painter.setPen(Qt::SolidLine);
        painter.drawRect(100 + i%3 * 30, i/3 * 30, 30, 30);
    }
    for(int i = 45; i < 54; i++) {
        painter.setPen(Qt::SolidLine);
        painter.drawRect(100 + i%3 * 30, i/3 * 30, 30, 30);
    }
}