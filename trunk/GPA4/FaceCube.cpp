/* 
 * File:   FaceCube.cpp
 * Author: Wan Kuk
 * 
 * Created on December 1, 2010, 9:49 PM
 */

#include "FaceCube.h"


Facelet FaceCube::cornerFacelet[8][3] = {
    {U9, R1, F3},
    {U7, F1, L3},
    {U1, L1, B3},
    {U3, B1, R3},
    {D3, F9, R7},
    {D1, L9, F7},
    {D7, B9, L7},
    {D9, R9, B7}
};
Facelet FaceCube::edgeFacelet[12][2] = {
    {U6, R2},
    {U8, F2},
    {U4, L2},
    {U2, B2},
    {D6, R8},
    {D2, F8},
    {D4, L8},
    {D8, B8},
    {F6, R4},
    {F4, L6},
    {B6, L4},
    {B4, R6}
};
Color FaceCube::cornerColor[8][3] = {
    { U, R, F},
    { U, F, L},
    { U, L, B},
    { U, B, R},
    { D, F, R},
    { D, L, F},
    { D, B, L},
    { D, R, B}
};
Color FaceCube::edgeColor[12][2] = {
    { U, R},
    { U, F},
    { U, L},
    { U, B},
    { D, R},
    { D, F},
    { D, L},
    { D, B},
    { F, R},
    { F, L},
    { B, L},
    { B, R}
};

FaceCube::FaceCube() {
    string s = "UUUUUUUUURRRRRRRRRFFFFFFFFFDDDDDDDDDLLLLLLLLLBBBBBBBBB";
    for (int i = 0; i < 54; i++) {
        f[i] = Tools::getColor(s.substr(i, 1));
    }
}

FaceCube::FaceCube(string cubeString) {
    for (int i = 0; i < (int) cubeString.length(); i++)
        f[i] = Tools::getColor(cubeString.substr(i, 1));
}

string FaceCube::to_String() {
    string s = "";
    for (int i = 0; i < 54; i++)
        s += Tools::colorToString(f[i]);
    return s;
}

CubieCube FaceCube::toCubieCube() {
    short ori;
    CubieCube ccRet;
    for (int i = 0; i < 8; i++)
        ccRet.cp[i] = URF; // invalidate corners
    for (int i = 0; i < 12; i++)
        ccRet.ep[i] = UR; // and edges
    Color col1, col2;
    for (int i = 0; i < 8; i++) {
        // get the colors of the cubie at corner i, starting with U/D
        for (ori = 0; ori < 3; ori++) {
            if (f[Tools::ordinal(cornerFacelet[i][ori])] == U || f[Tools::ordinal(cornerFacelet[i][ori])] == D) {
                break;
            }
        }
        col1 = f[Tools::ordinal(cornerFacelet[i][(ori + 1) % 3])];
        col2 = f[Tools::ordinal(cornerFacelet[i][(ori + 2) % 3])];

        for (int j = 0; j < 8; j++) {
            if (col1 == cornerColor[j][1] && col2 == cornerColor[j][2]) {
                // in cornerposition i we have cornercubie j
                ccRet.cp[i] = Tools::getCorner(j);
                ccRet.co[i] = (short) (ori % 3);
                break;
            }
        }
    }
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            if (f[Tools::ordinal(edgeFacelet[i][0])] == edgeColor[j][0]
                    && f[Tools::ordinal(edgeFacelet[i][1])] == edgeColor[j][1]) {
                ccRet.ep[i] = Tools::getEdge(j);
                ccRet.eo[i] = 0;
                break;
            }
            if (f[Tools::ordinal(edgeFacelet[i][0])] == edgeColor[j][1]
                    && f[Tools::ordinal(edgeFacelet[i][1])] == edgeColor[j][0]) {
                ccRet.ep[i] = Tools::getEdge(j);
                ccRet.eo[i] = 1;
                break;
            }
        }
    }
    return ccRet;
}

FaceCube FaceCube::toFaceCube(CubieCube &cube){
        FaceCube fcRet;
        for (int i = 0; i < 8; i++) {
            int j = Tools::ordinal(cube.cp[i]);// cornercubie with index j is at
            // cornerposition with index i
            short ori = cube.co[i];// Orientation of this cubie
            for (int n = 0; n < 3; n++) {
                fcRet.f[Tools::ordinal(FaceCube::cornerFacelet[i][(n + ori) % 3])] = FaceCube::cornerColor[j][n];
            }
        }
        for (int i = 0; i < 12; i++) {
            int j = Tools::ordinal(cube.ep[i]);// edgecubie with index j is at edgeposition
            // with index i
            short ori = cube.eo[i];// Orientation of this cubie
            for (int n = 0; n < 2; n++) {
                fcRet.f[Tools::ordinal(FaceCube::edgeFacelet[i][(n + ori) % 2])] = FaceCube::edgeColor[j][n];
            }
        }
        return fcRet;
}
