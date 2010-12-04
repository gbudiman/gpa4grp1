/* 
 * File:   GWindow.cpp
 * Author: gbudiman
 * 
 * Created on November 30, 2010, 8:03 PM
 */

#include "GWindow.h"
#include "GPA4Client.h"
#include "render2D.h"
#include "render3D.h"
#include <QtGui>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

GWindow::GWindow() {
    createConnectionMenu();
    create2Dview();
    create3Dview();
    createResponseMenu();

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(horizontalGroupBox);
    mainLayout->addWidget(r3);
    mainLayout->addWidget(r2);
    mainLayout->addWidget(gridGroupBox);
    setLayout(mainLayout);
    setWindowTitle("GPA 4 Group 1");
    
    client = new GPA4Client(this);

    connect(this,SIGNAL(sendConnectionData(string,string)),client,SLOT(updateConnectionData(string,string)));
    connect(client,SIGNAL(getConnectionData()),this,SLOT(returnConnectionData()));
    connect(client,SIGNAL(errorConnecting(int)),this,SLOT(connectionError(int)));
    connect(client, SIGNAL(weWon(bool)),this,SLOT(displayOutcome(bool)));
    connect(client, SIGNAL(setGUIState(string)),this,SLOT(updateGuiState(string)));
}

void GWindow::connectionError(int type){
  switch(type) {


   case 1:
     QMessageBox::information(this, tr("GPA4 Group 1 Client"),
 			     tr("The host was not found. Please check the "
 				"host name and port settings."));
     break;
   case 2:
     QMessageBox::information(this,tr("GPA4 Group 1 Client"),
 			     tr("The connection was refused by the peer. "
 				"Make sure the peer server is running, and"
 				"check that the host name and port settings"
 				"are correct."));
     break;
   default:
     break;
  }
   connectButton->setEnabled(true);

}

void GWindow::createConnectionMenu() {
    horizontalGroupBox = new QGroupBox("Connection");
    QHBoxLayout* layout = new QHBoxLayout;

    serverLabel = new QLabel("Server IP: ");
    serverText = new QLineEdit();
    serverText->setMaximumHeight(24);
    serverText->setMaximumWidth(128);
    portLabel = new QLabel("Port: ");
    portText = new QLineEdit();
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

void GWindow::updateGuiState(string s){
  //update the 2d viewer
  r2->setState(s);
  //update the 3d viewer
  temp_cube.setState(s);
  r3->setCube(&temp_cube);
}

/*
void GWindow::update3dState(string s){
  precube->setState(s);
}
void GWindow::reset2dState() {
  r2->setState("YYYYYYYYYRRRRRRRRRGGGGGGGGGOOOOOOOOOBBBBBBBBBWWWWWWWWW");
}
void GWindow::reset3dState(){
  precube->setState("YYYYYYYYYRRRRRRRRRGGGGGGGGGOOOOOOOOOBBBBBBBBBWWWWWWWWW");	
}*/

void GWindow::create2Dview() {
    r2 = new render2D();
    r2->setState("OYYBYYBYYBRRBRRBRRYGGYGGYRROOOOOOGGGBBWBBWOOWGWWGWWRWW");
   // connect(client, SIGNAL(client::resetGUIState(string)),this,SLOT(reset2dState(string)));
    r2->setMinimumHeight(300);
    r2->setMinimumWidth(400);
    r2->update();
}

void GWindow::returnConnectionData(){
  emit sendConnectionData(portText->text().toStdString(),serverText->text().toStdString());
}

void GWindow::create3Dview() {
    r3 = new render3D();
    rubik* precube = new rubik();
    precube->setState("OYYBYYBYYBRRBRRBRRYGGYGGYRROOOOOOGGGBBWBBWOOWGWWGWWRWW");
   // connect(client, SIGNAL(client::setGUIState(string)),this,SLOT(update3dState(string)));
   // connect(client, SIGNAL(client::resetGUIState(string)),this,SLOT(reset2dState(string)));
    vector<int> aori;
    aori.push_back(0);
    aori.push_back(1);
    aori.push_back(2);
    aori.push_back(3);
    aori.push_back(4);
    aori.push_back(5);
    precube->applyOrientation(aori);
    
    r3->setCube(precube);
    r3->setMinimumHeight(180);
    r3->setMinimumWidth(400);
    r3->update();
}

void GWindow::displayOutcome(bool k){
    if(k) {
       outcomeLabel->setText("We won!");}
    else {
       outcomeLabel->setText("We lost");}
}

void GWindow::createResponseMenu() {
    gridGroupBox = new QGroupBox();
    QGridLayout* layout = new QGridLayout;
    sequenceLabel = new QLabel("Sequence");
    sequenceText = new QTextEdit();
    sequenceText->setReadOnly(true);
    sequenceText->setMaximumSize(400, 80);
    stateLabel = new QLabel("State");
    stateText = new QTextEdit();
    stateText->setReadOnly(true);
    stateText->setMaximumSize(400, 80);
    outcomeLabel = new QLabel("<Outcome>");
    layout->addWidget(sequenceLabel, 0, 0);
    layout->addWidget(sequenceText, 0, 1);
    layout->addWidget(stateLabel, 1, 0);
    layout->addWidget(stateText, 1, 1);
    layout->addWidget(outcomeLabel, 2, 0, 1, 2, Qt::AlignCenter);

    gridGroupBox->setLayout(layout);
}
GWindow::~GWindow() {
}
