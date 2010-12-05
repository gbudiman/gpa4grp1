/* 
 * File:   Tools.cpp
 * Author: Wan Kuk
 * 
 * Created on December 1, 2010, 3:48 PM
 */

#include "Tools.h"


int Tools::ordinal(Color c) {
    if (c == U) {
        return 0;
    } else if (c == R) {
        return 1;
    } else if (c == F) {
        return 2;
    } else if (c == D) {
        return 3;
    } else if (c == L) {
        return 4;
    } else if (c == B) {
        return 5;
    }
    throw "color ordinal error";
}

int Tools::ordinal(Corner c) {
    if (c == URF) {
        return 0;
    } else if (c == UFL) {
        return 1;
    } else if (c == ULB) {
        return 2;
    } else if (c == UBR) {
        return 3;
    } else if (c == DFR) {
        return 4;
    } else if (c == DLF) {
        return 5;
    } else if (c == DBL) {
        return 6;
    } else if (c == DRB) {
        return 7;
    }
    throw "corner ordinal error";
}

int Tools::ordinal(Edge e) {
    if (e == UR) {
        return 0;
    } else if (e == UF) {
        return 1;
    } else if (e == UL) {
        return 2;
    } else if (e == UB) {
        return 3;
    } else if (e == DR) {
        return 4;
    } else if (e == DF) {
        return 5;
    } else if (e == DL) {
        return 6;
    } else if (e == DB) {
        return 7;
    } else if (e == FR) {
        return 8;
    } else if (e == FL) {
        return 9;
    } else if (e == BL) {
        return 10;
    } else if (e == BR) {
        return 11;
    }
    throw "edge ordinal error";
}

int Tools::ordinal(Facelet f) {
    if (f == U1) {
        return 0;
    } else if (f == U2) {
        return 1;
    } else if (f == U3) {
        return 2;
    } else if (f == U4) {
        return 3;
    } else if (f == U5) {
        return 4;
    } else if (f == U6) {
        return 5;
    } else if (f == U7) {
        return 6;
    } else if (f == U8) {
        return 7;
    } else if (f == U9) {
        return 8;
    } else if (f == R1) {
        return 9;
    } else if (f == R2) {
        return 10;
    } else if (f == R3) {
        return 11;
    } else if (f == R4) {
        return 12;
    } else if (f == R5) {
        return 13;
    } else if (f == R6) {
        return 14;
    } else if (f == R7) {
        return 15;
    } else if (f == R8) {
        return 16;
    } else if (f == R9) {
        return 17;
    } else if (f == F1) {
        return 18;
    } else if (f == F2) {
        return 19;
    } else if (f == F3) {
        return 20;
    } else if (f == F4) {
        return 21;
    } else if (f == F5) {
        return 22;
    } else if (f == F6) {
        return 23;
    } else if (f == F7) {
        return 24;
    } else if (f == F8) {
        return 25;
    } else if (f == F9) {
        return 26;
    } else if (f == D1) {
        return 27;
    } else if (f == D2) {
        return 28;
    } else if (f == D3) {
        return 29;
    } else if (f == D4) {
        return 30;
    } else if (f == D5) {
        return 31;
    } else if (f == D6) {
        return 32;
    } else if (f == D7) {
        return 33;
    } else if (f == D8) {
        return 34;
    } else if (f == D9) {
        return 35;
    } else if (f == L1) {
        return 36;
    } else if (f == L2) {
        return 37;
    } else if (f == L3) {
        return 38;
    } else if (f == L4) {
        return 39;
    } else if (f == L5) {
        return 40;
    } else if (f == L6) {
        return 41;
    } else if (f == L7) {
        return 42;
    } else if (f == L8) {
        return 43;
    } else if (f == L9) {
        return 44;
    } else if (f == B1) {
        return 45;
    } else if (f == B2) {
        return 46;
    } else if (f == B3) {
        return 47;
    } else if (f == B4) {
        return 48;
    } else if (f == B5) {
        return 49;
    } else if (f == B6) {
        return 50;
    } else if (f == B7) {
        return 51;
    } else if (f == B8) {
        return 52;
    } else if (f == B9) {
        return 53;
    }
    throw "facelet ordinal error";
}

Corner Tools::getCorner(int i) {
    switch (i) {
        case 0:
            return URF;
        case 1:
            return UFL;
        case 2:
            return ULB;
        case 3:
            return UBR;
        case 4:
            return DFR;
        case 5:
            return DLF;
        case 6:
            return DBL;
        case 7:
            return DRB;
    }
   throw "getCorner error";
}

Edge Tools::getEdge(int i) {
    switch (i) {
        case 0:
            return UR;
        case 1:
            return UF;
        case 2:
            return UL;
        case 3:
            return UB;
        case 4:
            return DR;
        case 5:
            return DF;
        case 6:
            return DL;
        case 7:
            return DB;
        case 8:
            return FR;
        case 9:
            return FL;
        case 10:
            return BL;
        case 11:
            return BR;
    }
    throw "getEdge error";
}

Color Tools::getColor(string c) {
    if (c.compare("U") == 0) {
        return U;
    } else if (c.compare("R") == 0) {
        return R;
    } else if (c.compare("F") == 0) {
        return F;
    } else if (c.compare("D") == 0) {
        return D;
    } else if (c.compare("L") == 0) {
        return L;
    } else if (c.compare("B") == 0) {
        return B;
    }
    throw "getColor error";
}

string Tools::colorToString(Color c) {
    if (c == U) {
        return "U";
    } else if (c == R) {
        return "R";
    } else if (c == F) {
        return "F";
    } else if (c == D) {
        return "D";
    } else if (c == L) {
        return "L";
    } else if (c == B) {
        return "B";
    }
    throw "colorToString error";
}

