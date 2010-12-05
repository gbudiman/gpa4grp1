/* 
 * File:   CoordCube.h
 * Author: Wan Kuk
 *
 * Created on December 1, 2010, 12:47 PM
 */

#ifndef COORDCUBE_H
#define	COORDCUBE_H
#include "CubieCube.h"
#include "iostream"
using namespace std;

class CoordCube {
public:
    static void initializeAll();
    CoordCube(CubieCube c);
    void move(int m);
    static void setPruning(short *table, int index, short value);
    static short getPruning(short *table, int index);
    static const short N_TWIST = 2187; // 3^7 possible corner orientations
    static const short N_FLIP = 2048; // 2^11 possible edge flips
    static const short N_SLICE1 = 495; // 12 choose 4 possible positions of FR,FL,BL,BR edges
    static const short N_SLICE2 = 24; // 4! permutations of FR,FL,BL,BR edges in phase2
    static const short N_PARITY = 2; // 2 possible corner parities
    static const short N_URFtoDLF = 20160; // 8!/(8-6)! permutation of URF,UFL,ULB,UBR,DFR,DLF corners
    static const short N_FRtoBR = 11880; // 12!/(12-4)! permutation of FR,FL,BL,BR edges
    static const short N_URtoUL = 1320; // 12!/(12-3)! permutation of UR,UF,UL edges
    static const short N_UBtoDF = 1320; // 12!/(12-3)! permutation of UB,DR,DF edges
    static const short N_URtoDF = 20160; // 8!/(8-6)! permutation of UR,UF,UL,UB,DR,DF edges in phase2
    static const int N_URFtoDLB = 40320; // 8! permutations of the corners
    static const int N_URtoBR = 479001600; // 8! permutations of the corners
    static const short N_MOVE = 18;
    static short twistMove[N_TWIST][N_MOVE];
    static short flipMove[N_FLIP][N_MOVE];
    static short parityMove[2][18];
    static short FRtoBR_Move[N_FRtoBR][N_MOVE];
    static short URFtoDLF_Move[N_URFtoDLF][N_MOVE];
    static short URtoDF_Move[N_URtoDF][N_MOVE];
    static short URtoUL_Move[N_URtoUL][N_MOVE];
    static short UBtoDF_Move[N_UBtoDF][N_MOVE];
    static short MergeURtoULandUBtoDF[336][336];
    static short Slice_URFtoDLF_Parity_Prun[N_SLICE2 * N_URFtoDLF * N_PARITY / 2];
    static short Slice_URtoDF_Parity_Prun[N_SLICE2 * N_URtoDF * N_PARITY / 2];
    static short Slice_Twist_Prun[N_SLICE1 * N_TWIST / 2 + 1];
    static short Slice_Flip_Prun[N_SLICE1 * N_FLIP / 2];
    short twist;
    short flip;
    short parity;
    short FRtoBR;
    short URFtoDLF;
    short URtoUL;
    short UBtoDF;
    int URtoDF;
private:
    static void initializeTwistMove();
    static void initializeFlipMove();
    static void initializeFRtoBR_Move();
    static void initializeURFtoDLF_Move();
    static void initializeURtoDF_Move();
    static void initializeURtoUL_Move();
    static void initializeUBtoDF_Move();
    static void initializeMergeURtoULandUBtoDF();
    static void initializeSlice_URFtoDLF_Parity_Prun();
    static void initializeSlice_URtoDF_Parity_Prun();
    static void initializeSlice_Twist_Prun();
    static void initializeSlice_Flip_Prun();
};

#endif	/* COORDCUBE_H */

