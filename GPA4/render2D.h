/* 
 * File:   render2D.h
 * Author: gbudiman
 *
 * Created on November 30, 2010, 8:31 PM
 */

#ifndef _RENDER2D_H
#define	_RENDER2D_H
#include <string>
#include <QtGui>
using namespace std;

class render2D : public QWidget {
    Q_OBJECT
public:
    render2D(QWidget* parent = 0);
    virtual ~render2D();
    void setState(string state);
    QBrush getColor(char s);
protected:
    void paintEvent(QPaintEvent* event);
private:
    string cubeState;
};

#endif	/* _RENDER2D_H */

