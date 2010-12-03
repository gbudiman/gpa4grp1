/* 
 * File:   GWindow.h
 * Author: gbudiman
 *
 * Created on November 30, 2010, 8:03 PM
 */

#ifndef _GWINDOW_H
#define	_GWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "render2D.h"
#include "render3D.h"
#include <string>
class GWindow : public QWidget {
    Q_OBJECT
public:
    GWindow();
    void create2Dview();
    void create3Dview();
    virtual ~GWindow();

public slot:
    void update2dState(string s);
    void update3dState(string s);
    void reset2dState();
    void reset3dState();
    void displayOutcome(bool k);
private:
    void createConnectionMenu();
    void createResponseMenu();

    QGroupBox* horizontalGroupBox;
    QLabel* serverLabel;
    QLabel* portLabel;
    QTextEdit* serverText;
    QTextEdit* portText;
    QPushButton* connectButton;

    QGroupBox* gridGroupBox;
    QLabel* sequenceLabel;
    QTextEdit* sequenceText;
    QLabel* stateLabel;
    QTextEdit* stateText;
    QLabel* outcomeLabel;
    
    render2D* r2;
    render3D* r3;
    string state;	
};

#endif	/* _GWINDOW_H */

