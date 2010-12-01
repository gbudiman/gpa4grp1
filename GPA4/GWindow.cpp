/* 
 * File:   GWindow.cpp
 * Author: gbudiman
 * 
 * Created on November 30, 2010, 8:03 PM
 */

#include "GWindow.h"
#include "render2D.h"
#include <QtGui>
#include <iostream>
using namespace std;

GWindow::GWindow() {
    createConnectionMenu();
    create2Dview();

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(horizontalGroupBox);
    mainLayout->addWidget(r2);
    setLayout(mainLayout);
    setWindowTitle("GPA 4 Group 1");
}

void GWindow::createConnectionMenu() {
    horizontalGroupBox = new QGroupBox("Connection");
    QHBoxLayout* layout = new QHBoxLayout;

    serverLabel = new QLabel("Server IP: ");
    serverText = new QTextEdit();
    serverText->setMaximumHeight(24);
    serverText->setMaximumWidth(128);
    portLabel = new QLabel("Port: ");
    portText = new QTextEdit();
    portText->setMaximumHeight(24);
    portText->setMaximumWidth(64);
    connectButton = new QPushButton("Connect");

    layout->addWidget(serverLabel);
    layout->addWidget(serverText);
    layout->addWidget(portLabel);
    layout->addWidget(portText);
    layout->addWidget(connectButton);

    horizontalGroupBox->setLayout(layout);
}

void GWindow::create2Dview() {
    r2 = new render2D();
    r2->setState("YYYYYYYYYBBBBBBBBBGGGGGGGGGOOOOOOOOOWWWWWWWWWRRRRRRRRR");
    r2->setMinimumHeight(400);
    r2->setMinimumWidth(400);
    r2->update();
}

GWindow::~GWindow() {
}

