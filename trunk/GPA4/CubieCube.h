/* 
 * File:   CubieCube.h
 * Author: Wan Kuk
 *
 * Created on December 1, 2010, 12:49 PM
 */

#ifndef CUBIECUBE_H
#define	CUBIECUBE_H
#include "Definition.h"
#include "Tools.h"
#include <iostream>
using namespace std;

class CubieCube {
public:
    static void initializeMoveCube();
    CubieCube();
    void setCP(Corner* cp2);
    CubieCube(Corner *cp, short *co, Edge *ep, short *eo);
    static void rotateLeft(Corner *array, int l, int r);
    static void rotateRight(Corner *array, int l, int r);
    static void rotateLeft(Edge *array, int l, int r);
    static void rotateRight(Edge *array, int l, int r);
    //    FaceCube toFaceCube();
    void cornerMultiply(CubieCube &b);
    void edgeMultiply(CubieCube &b);
    void invCubieCube(CubieCube &c);
    short getTwist();
    void setTwist(short twist);
    short getFlip();
    void setFlip(short flip);
    short cornerParity();
    short edgeParity();
    short getFRtoBR();
    void setFRtoBR(short idx);
    short getURFtoDLF();
    void setURFtoDLF(short idx);
    int getURtoDF();
    void setURtoDF(int idx);
    static int getURtoDF(short idx1, short idx2);
    short getURtoUL();
    void setURtoUL(short idx);
    short getUBtoDF();
    void setUBtoDF(short idx);
    int getURFtoDLB();
    void setURFtoDLB(int idx);
    int getURtoBR();
    void setURtoBR(int idx);
    int verify();
    static CubieCube moveCube[6];
    Corner cp[8];
    Edge ep[12];
    short co[8];
    short eo[12];
private:
    static int NChooseK(int n, int k);
};

#endif	/* CUBIECUBE_H */

