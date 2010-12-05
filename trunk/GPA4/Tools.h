/* 
 * File:   Tools.h
 * Author: Wan Kuk
 *
 * Created on December 1, 2010, 3:48 PM
 */

#ifndef TOOLS_H
#define	TOOLS_H
#include <string>
#include "Definition.h"
using namespace std;

class Tools {
public:
    static int ordinal(Color col);
    static int ordinal(Corner c);
    static int ordinal(Edge e);
    static int ordinal(Facelet f);
    static Corner getCorner(int i);
    static Edge getEdge(int i);
    static Color getColor(string c);
    static string colorToString(Color c);
private:

};

#endif	/* TOOLS_H */

