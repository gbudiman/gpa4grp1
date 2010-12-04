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
/*
public slots:
    void update2dState(string s);
    void update3dState(string s);
    void reset2dState();
    void reset3dState();
    void displayOutcome(bool k);
*/

private slots:
    void returnConnectionData();

private:
    void createConnectionMenu();
    void createResponseMenu();

    QGroupBox* horizontalGroupBox;
    QLabel* serverLabel;
    QLabel* portLabel;
    QLineEdit* serverText;
    QLineEdit* portText;
    QPushButton* connectButton;

    QGroupBox* gridGroupBox;
    QLabel* sequenceLabel;
    QTextEdit* sequenceText;
    QLabel* stateLabel;
    QTextEdit* stateText;
    QLabel* outcomeLabel;
    
    GPA4Client * client;
    render2D* r2;
    render3D* r3;
    string state;	

signals:
    void sendConnectionData(string port, string server);
};

#endif	/* _GWINDOW_H */
