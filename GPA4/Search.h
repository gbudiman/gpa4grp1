/* 
 * File:   Search.h
 * Author: Wan Kuk
 *
 * Created on December 1, 2010, 11:30 PM
 */

#ifndef SEARCH_H
#define	SEARCH_H
#include "Tools.h"
#include "CoordCube.h"
#include "FaceCube.h"
#include "CubieCube.h"
#include "math.h"
#include <string>
#include <string.h>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <vector>
using namespace std;

class Search {
public:
    static string getFinalSolution(string sol, string disable);
    static string solution(string face, int maxDepth);
    static void readMoves(string s, vector<int> &result); 
private:
    static int ax[31];
    static int bx[50];
    static int po[31];
    static int flip[31];
    static int twist[31];
    static int slice[31];
    static int parity[31];
    static int URFtoDLF[31];
    static int FRtoBR[31];
    static int URtoUL[31];
    static int UBtoDF[31];
    static int URtoDF[31];
    static int minDistPhase1[31];
    static int minDistPhase2[31];
    static int rotationTable[6][12];
    static vector<int> solutionMoves;
    static vector<int> finalSolution;
    static vector<int> disableMoves;
    static vector<int> allowedRotations;
    static vector<int> rotationVector;
    static string moves[18];
    static const int U_C = 0;
    static const int R_C = 1;
    static const int F_C = 2;
    static const int D_C = 3;
    static const int L_C = 4;
    static const int B_C = 5;
    static const int U_CC = 6;
    static const int R_CC = 7;
    static const int F_CC = 8;
    static const int D_CC = 9;
    static const int L_CC = 10;
    static const int B_CC = 11;
    static const int X_C = 0;
    static const int X_CC = 1;
    static const int Y_C = 2;
    static const int Y_CC = 3;
    static const int Z_C = 4;
    static const int Z_CC = 5;
    static string SolutionToString(int length);
    static int totalDepth(int depthPhase1, int maxDepth);
    static string convertColor(string color);
    static bool isMoveDisable(int move);
    static bool isPairMoveDisable(int move);
    static int getPairMove(int move);
    static void updateRotationVector(int *vect, int rot);
    static int updateMove(int move);

};

#endif	/* SEARCH_H */
