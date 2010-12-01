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

class GWindow : public QWidget {
    Q_OBJECT
public:
    GWindow();
    void create2Dview();
    virtual ~GWindow();
private:
    void createConnectionMenu();

    QGroupBox* horizontalGroupBox;
    QLabel* serverLabel;
    QLabel* portLabel;
    QTextEdit* serverText;
    QTextEdit* portText;
    QPushButton* connectButton;

    render2D* r2;
};

#endif	/* _GWINDOW_H */

