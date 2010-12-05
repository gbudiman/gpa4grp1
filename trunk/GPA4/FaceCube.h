/* 
 * File:   FaceCube.h
 * Author: Wan Kuk
 *
 * Created on December 1, 2010, 9:49 PM
 */

#ifndef FACECUBE_H
#define	FACECUBE_H
#include <string>
#include "Definition.h"
#include "Tools.h"
#include "CubieCube.h"
using namespace std;

class FaceCube {
public:
    FaceCube();
    FaceCube(string cubeString);
    string to_String();
    CubieCube toCubieCube();
    static FaceCube toFaceCube(CubieCube &cube);
    Color f[54];
    static Facelet cornerFacelet[8][3];
    static Facelet edgeFacelet[12][2];
    static Color cornerColor[8][3];
    static Color edgeColor[12][2];
private:

};

#endif	/* FACECUBE_H */

