/* 
 * File:   CubieCube.cpp
 * Author: Wan Kuk
 * 
 * Created on December 1, 2010, 12:49 PM
 */

#include "CubieCube.h"

CubieCube CubieCube::moveCube[6];

CubieCube::CubieCube() {
    cp[0] = URF;
    cp[1] = UFL;
    cp[2] = ULB;
    cp[3] = UBR;
    cp[4] = DFR;
    cp[5] = DLF;
    cp[6] = DBL;
    cp[7] = DRB;

    ep[0] = UR;
    ep[1] = UF;
    ep[2] = UL;
    ep[3] = UB;
    ep[4] = DR;
    ep[5] = DF;
    ep[6] = DL;
    ep[7] = DB;
    ep[8] = FR;
    ep[9] = FL;
    ep[10] = BL;
    ep[11] = BR;
    for (int i = 0; i < 8; i++) {
        co[i] = 0;
    }
    for (int i = 0; i < 12; i++) {
        eo[i] = 0;
    }
}

void CubieCube::setCP(Corner* cp2) {
    for (int i = 0; i < 8; i++) {
        cp[i] = cp2[i];
    }
}

CubieCube::CubieCube(Corner* cp2, short* co2, Edge* ep2, short* eo2) {
    for (int i = 0; i < 8; i++) {
        cp[i] = cp2[i];
        co[i] = co2[i];
    }
    for (int i = 0; i < 12; i++) {
        ep[i] = ep2[i];
        eo[i] = eo2[i];
    }
}

void CubieCube::initializeMoveCube() {
    static const Corner cpU[] = {UBR, URF, UFL, ULB, DFR, DLF, DBL, DRB};
    static const short coU[] = {0, 0, 0, 0, 0, 0, 0, 0};
    static const Edge epU[] = {UB, UR, UF, UL, DR, DF, DL, DB, FR, FL, BL, BR};
    static const short eoU[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    static const Corner cpR[] = {DFR, UFL, ULB, URF, DRB, DLF, DBL, UBR};
    static const short coR[] = {2, 0, 0, 1, 1, 0, 0, 2};
    static const Edge epR[] = {FR, UF, UL, UB, BR, DF, DL, DB, DR, FL, BL, UR};
    static const short eoR[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    static const Corner cpF[] = {UFL, DLF, ULB, UBR, URF, DFR, DBL, DRB};
    static const short coF[] = {1, 2, 0, 0, 2, 1, 0, 0};
    static const Edge epF[] = {UR, FL, UL, UB, DR, FR, DL, DB, UF, DF, BL, BR};
    static const short eoF[] = {0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0};

    static const Corner cpD[] = {URF, UFL, ULB, UBR, DLF, DBL, DRB, DFR};
    static const short coD[] = {0, 0, 0, 0, 0, 0, 0, 0};
    static const Edge epD[] = {UR, UF, UL, UB, DF, DL, DB, DR, FR, FL, BL, BR};
    static const short eoD[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    static const Corner cpL[] = {URF, ULB, DBL, UBR, DFR, UFL, DLF, DRB};
    static const short coL[] = {0, 1, 2, 0, 0, 2, 1, 0};
    static const Edge epL[] = {UR, UF, BL, UB, DR, DF, FL, DB, FR, UL, DL, BR};
    static const short eoL[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    static const Corner cpB[] = {URF, UFL, UBR, DRB, DFR, DLF, ULB, DBL};
    static const short coB[] = {0, 0, 1, 2, 0, 0, 2, 1};
    static const Edge epB[] = {UR, UF, UL, BR, DR, DF, DL, BL, FR, FL, UB, DB};
    static const short eoB[] = {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1};

    for (int i = 0; i < 8; i++) {
        moveCube[0].cp[i] = cpU[i];
        moveCube[0].co[i] = coU[i];
        moveCube[1].cp[i] = cpR[i];
        moveCube[1].co[i] = coR[i];
        moveCube[2].cp[i] = cpF[i];
        moveCube[2].co[i] = coF[i];
        moveCube[3].cp[i] = cpD[i];
        moveCube[3].co[i] = coD[i];
        moveCube[4].cp[i] = cpL[i];
        moveCube[4].co[i] = coL[i];
        moveCube[5].cp[i] = cpB[i];
        moveCube[5].co[i] = coB[i];
    }
    for (int i = 0; i < 12; i++) {
        moveCube[0].ep[i] = epU[i];
        moveCube[0].eo[i] = eoU[i];
        moveCube[1].ep[i] = epR[i];
        moveCube[1].eo[i] = eoR[i];
        moveCube[2].ep[i] = epF[i];
        moveCube[2].eo[i] = eoF[i];
        moveCube[3].ep[i] = epD[i];
        moveCube[3].eo[i] = eoD[i];
        moveCube[4].ep[i] = epL[i];
        moveCube[4].eo[i] = eoL[i];
        moveCube[5].ep[i] = epB[i];
        moveCube[5].eo[i] = eoB[i];
    }

}

int CubieCube::NChooseK(int n, int k) {
    int i, j, s;
    if (n < k)
        return 0;
    if (k > n / 2)
        k = n - k;
    for (s = 1, i = n, j = 1; i != n - k; i--, j++) {
        s *= i;
        s /= j;
    }
    return s;
}

void CubieCube::rotateLeft(Corner *array, int l, int r) {
    Corner temp = array[l];
    for (int i = l; i < r; i++) {
        array[i] = array[i + 1];
    }
    array[r] = temp;
}

void CubieCube::rotateRight(Corner* array, int l, int r) {
    Corner temp = array[r];
    for (int i = r; i > l; i--) {
        array[i] = array[i - 1];
    }
    array[l] = temp;
}

void CubieCube::rotateLeft(Edge* array, int l, int r) {
    Edge temp = array[l];
    for (int i = l; i < r; i++) {
        array[i] = array[i + 1];
    }
    array[r] = temp;
}

void CubieCube::rotateRight(Edge* array, int l, int r) {
    Edge temp = array[r];
    for (int i = r; i > l; i--) {
        array[i] = array[i - 1];
    }
    array[l] = temp;
}

//FaceCube CubieCube::toFaceCube() {
//    FaceCube fcRet;
//        for (int i = 0; i < 8; i++) {
//            int j = Tools::ordinal(cp[i]);// cornercubie with index j is at
//            // cornerposition with index i
//            short ori = co[i];// Orientation of this cubie
//            for (int n = 0; n < 3; n++) {
//                fcRet.f[Tools::ordinal(FaceCube::cornerFacelet[i][(n + ori) % 3])] = FaceCube::cornerColor[j][n];
//            }
//        }
//        for (int i = 0; i < 12; i++) {
//            int j = Tools::ordinal(ep[i]);// edgecubie with index j is at edgeposition
//            // with index i
//            short ori = eo[i];// Orientation of this cubie
//            for (int n = 0; n < 2; n++) {
//                fcRet.f[Tools::ordinal(FaceCube::edgeFacelet[i][(n + ori) % 2])] = FaceCube::edgeColor[j][n];
//            }
//        }
//        return fcRet;
//}

void CubieCube::cornerMultiply(CubieCube &b) {
    Corner cPerm[8];
    short cOri[8];
    for (int i = 0; i < 8; i++) {
        cPerm[i] = cp[Tools::ordinal(b.cp[i])];

        short oriA = co[Tools::ordinal(b.cp[i])];
        short oriB = b.co[i];
        short ori = 0;
        if (oriA < 3 && oriB < 3) {
            ori = (short) (oriA + oriB);
            if (ori >= 3) {
                ori -= 3;
            }
        } else if (oriA < 3 && oriB >= 3) {
            ori = (short) (oriA + oriB);
            if (ori >= 6) {
                ori -= 3;
            }
        } else if (oriA >= 3 && oriB < 3) {
            ori = (short) (oriA - oriB);
            if (ori < 3) {
                ori += 3;
            }
        } else if (oriA >= 3 && oriB >= 3) {
            ori = (short) (oriA - oriB);
            if (ori < 0) {
                ori += 3;
            }
        }
        cOri[i] = ori;
    }
    for (int i = 0; i < 8; i++) {
        cp[i] = cPerm[i];
        co[i] = cOri[i];
    }
}

void CubieCube::edgeMultiply(CubieCube &b) {
    Edge ePerm[12];
    short eOri[12];
    for (int i = 0; i < 12; i++) {
        ePerm[i] = ep[Tools::ordinal(b.ep[i])];
        eOri[i] = (short) ((b.eo[i] + eo[Tools::ordinal(b.ep[i])]) % 2);
    }
    for (int i = 0; i < 12; i++) {
        ep[i] = ePerm[i];
        eo[i] = eOri[i];
    }
}

void CubieCube::invCubieCube(CubieCube& c) {
    for (int i = 0; i < 12; i++) {
        c.ep[Tools::ordinal(ep[i])] = Tools::getEdge(i);
    }
    for (int i = 0; i < 12; i++) {
        c.eo[i] = eo[Tools::ordinal(c.ep[i])];
    }
    for (int i = 0; i < 8; i++) {
        c.cp[Tools::ordinal(cp[i])] = Tools::getCorner(i);
    }
    for (int i = 0; i < 8; i++) {
        short ori = co[Tools::ordinal(c.cp[i])];
        if (ori >= 3) {
            c.co[i] = ori;
        } else {
            c.co[i] = (short) -ori;
            if (c.co[i] < 0) {
                c.co[i] += 3;
            }
        }
    }
}

short CubieCube::getTwist() {
    short ret = 0;
    for (int i = Tools::ordinal(URF); i < Tools::ordinal(DRB); i++) {
        ret = (short) (3 * ret + co[i]);
    }
    return ret;
}

void CubieCube::setTwist(short twist) {
    int twistParity = 0;
    for (int i = Tools::ordinal(DRB) - 1; i >= Tools::ordinal(URF); i--) {
        twistParity += co[i] = (short) (twist % 3);
        twist /= 3;
    }
    co[Tools::ordinal(DRB)] = (short) ((3 - twistParity % 3) % 3);
}

short CubieCube::getFlip() {
    short ret = 0;
    for (int i = Tools::ordinal(UR); i < Tools::ordinal(BR); i++) {
        ret = (short) (2 * ret + eo[i]);
    }
    return ret;
}

void CubieCube::setFlip(short flip) {
    int flipParity = 0;
    for (int i = Tools::ordinal(BR) - 1; i >= Tools::ordinal(UR); i--) {
        flipParity += eo[i] = (short) (flip % 2);
        flip /= 2;
    }
    eo[Tools::ordinal(BR)] = (short) ((2 - flipParity % 2) % 2);
}

short CubieCube::cornerParity() {
    int s = 0;
    for (int i = Tools::ordinal(DRB); i >= Tools::ordinal(URF) + 1; i--) {
        for (int j = i - 1; j >= Tools::ordinal(URF); j--) {
            if (Tools::ordinal(cp[j]) > Tools::ordinal(cp[i])) {
                s++;
            }
        }
    }
    return (short) (s % 2);
}

short CubieCube::edgeParity() {
    int s = 0;
    for (int i = Tools::ordinal(BR); i >= Tools::ordinal(UR) + 1; i--) {
        for (int j = i - 1; j >= Tools::ordinal(UR); j--) {
            if (Tools::ordinal(ep[j]) > Tools::ordinal(ep[i])) {
                s++;
            }
        }
    }
    return (short) (s % 2);
}

short CubieCube::getFRtoBR() {
    int a = 0, x = 0;
    Edge edge4[4];
    for (int j = Tools::ordinal(BR); j >= Tools::ordinal(UR); j--) {
        if (Tools::ordinal(FR) <= Tools::ordinal(ep[j]) && Tools::ordinal(ep[j]) <= Tools::ordinal(BR)) {
            a += NChooseK(11 - j, x + 1);
            edge4[3 - x++] = ep[j];
        }
    }

    int b = 0;
    for (int j = 3; j > 0; j--) {
        int k = 0;
        while (Tools::ordinal(edge4[j]) != j + 8) {
            rotateLeft(edge4, 0, j);
            k++;
        }
        b = (j + 1) * b + k;
    }
    return (short) (24 * a + b);
}

void CubieCube::setFRtoBR(short idx) {
    int x;
    Edge sliceEdge[] = {FR, FL, BL, BR};
    Edge otherEdge[] = {UR, UF, UL, UB, DR, DF, DL, DB};
    int b = idx % 24;
    int a = idx / 24;
    for (int i = 0; i < 12; i++) {
        ep[i] = DB;
    }
    for (int j = 1, k; j < 4; j++) {
        k = b % (j + 1);
        b /= j + 1;
        while (k-- > 0) {
            rotateRight(sliceEdge, 0, j);
        }
    }

    x = 3;
    for (int j = Tools::ordinal(UR); j <= Tools::ordinal(BR); j++) {
        if (a - NChooseK(11 - j, x + 1) >= 0) {
            ep[j] = sliceEdge[3 - x];
            a -= NChooseK(11 - j, x-- +1);
        }
    }
    x = 0;
    for (int j = Tools::ordinal(UR); j <= Tools::ordinal(BR); j++) {
        if (ep[j] == DB) {
            ep[j] = otherEdge[x++];
        }
    }
}

short CubieCube::getURFtoDLF() {
    int a = 0, x = 0;
    Corner corner6[6];
    for (int j = Tools::ordinal(URF); j <= Tools::ordinal(DRB); j++) {
        if (Tools::ordinal(cp[j]) <= Tools::ordinal(DLF)) {
            a += NChooseK(j, x + 1);
            corner6[x++] = cp[j];
        }
    }
    int b = 0;
    for (int j = 5; j > 0; j--) {
        int k = 0;
        while (Tools::ordinal(corner6[j]) != j) {
            rotateLeft(corner6, 0, j);
            k++;
        }
        b = (j + 1) * b + k;
    }
    return (short) (720 * a + b);
}

void CubieCube::setURFtoDLF(short idx) {
    int x;
    Corner corner6[6] = {URF, UFL, ULB, UBR, DFR, DLF};
    Corner otherCorner[2] = {DBL, DRB};
    int b = idx % 720; // Permutation
    int a = idx / 720; // Combination
    for (int i = 0; i < 8; i++) {
        cp[i] = DRB; // Use DRB to invalidate all corners
    }
    for (int j = 1; j < 6; j++)// generate permutation from index b
    {
        int k = b % (j + 1);
        b /= j + 1;
        while (k-- > 0) {
            rotateRight(corner6, 0, j);
        }
    }
    x = 5; // generate combination and set corners
    for (int j = Tools::ordinal(DRB); j >= 0; j--) {
        if (a - NChooseK(j, x + 1) >= 0) {
            cp[j] = corner6[x];
            a -= NChooseK(j, x-- + 1);
        }
    }
    x = 0;
    for (int j = Tools::ordinal(URF); j <= Tools::ordinal(DRB); j++) {
        if (cp[j] == DRB) {
            cp[j] = otherCorner[x++];
        }
    }
}

int CubieCube::getURtoDF() {
    int a = 0, x = 0;
    Edge edge6[6];
    // compute the index a < (12 choose 6) and the edge permutation.
    for (int j = Tools::ordinal(UR); j <= Tools::ordinal(BR); j++) {
        if (Tools::ordinal(ep[j]) <= Tools::ordinal(DF)) {
            a += NChooseK(j, x + 1);
            edge6[x++] = ep[j];
        }
    }

    int b = 0;
    for (int j = 5; j > 0; j--)// compute the index b < 6! for the
        // permutation in edge6
    {
        int k = 0;
        while (Tools::ordinal(edge6[j]) != j) {
            rotateLeft(edge6, 0, j);
            k++;
        }
        b = (j + 1) * b + k;
    }
    return 720 * a + b;
}

void CubieCube::setURtoDF(int idx) {
    int x;
    Edge edge6[] = {UR, UF, UL, UB, DR, DF};
    Edge otherEdge[] = {DL, DB, FR, FL, BL, BR};
    int b = idx % 720;
    int a = idx / 720;
    for (int i = 0; i < 12; i++) {
        ep[i] = BR;
    }
    for (int j = 1, k; j < 6; j++) {
        k = b % (j + 1);
        b /= j + 1;
        while (k-- > 0) {
            rotateRight(edge6, 0, j);
        }
    }
    x = 5; // generate combination and set edges
    for (int j = Tools::ordinal(BR); j >= 0; j--) {
        if (a - NChooseK(j, x + 1) >= 0) {
            ep[j] = edge6[x];
            a -= NChooseK(j, x-- +1);
        }
    }
    x = 0; // set the remaining edges DL..BR
    for (int j = Tools::ordinal(UR); j <= Tools::ordinal(BR); j++) {
        if (ep[j] == BR) {
            ep[j] = otherEdge[x++];
        }
    }
}

int CubieCube::getURtoDF(short idx1, short idx2) {
    CubieCube a;
    CubieCube b;
    a.setURtoUL(idx1);
    b.setUBtoDF(idx2);
    for (int i = 0; i < 8; i++) {
        if (a.ep[i] != BR) {
            if (b.ep[i] != BR)// collision
            {
                return -1;
            } else {
                b.ep[i] = a.ep[i];
            }
        }
    }
    return b.getURtoDF();
}

short CubieCube::getURtoUL() {
    int a = 0, x = 0;
    Edge edge3[3];
    for (int j = Tools::ordinal(UR); j <= Tools::ordinal(BR); j++) {
        if (Tools::ordinal(ep[j]) <= Tools::ordinal(UL)) {
            a += NChooseK(j, x + 1);
            edge3[x++] = ep[j];
        }
    }

    int b = 0;
    for (int j = 2; j > 0; j--) {
        int k = 0;
        while (Tools::ordinal(edge3[j]) != j) {
            rotateLeft(edge3, 0, j);
            k++;
        }
        b = (j + 1) * b + k;
    }
    return (short) (6 * a + b);
}

void CubieCube::setURtoUL(short idx) {
    int x;
    Edge edge3[] = {UR, UF, UL};
    int b = idx % 6;
    int a = idx / 6;
    for (int i = 0; i < 12; i++) {
        ep[i] = BR;
    }
    for (int j = 1, k; j < 3; j++) {
        k = b % (j + 1);
        b /= j + 1;
        while (k-- > 0) {
            rotateRight(edge3, 0, j);
        }
    }
    x = 2;
    for (int j = Tools::ordinal(BR); j >= 0; j--) {
        if (a - NChooseK(j, x + 1) >= 0) {
            ep[j] = edge3[x];
            a -= NChooseK(j, x-- +1);
        }
    }
}

short CubieCube::getUBtoDF() {
    int a = 0, x = 0;
    Edge edge3[3];
    for (int j = Tools::ordinal(UR); j <= Tools::ordinal(BR); j++) {
        if (Tools::ordinal(UB) <= Tools::ordinal(ep[j]) && Tools::ordinal(ep[j]) <= Tools::ordinal(DF)) {
            a += NChooseK(j, x + 1);
            edge3[x++] = ep[j];
        }
    }

    int b = 0;
    for (int j = 2; j > 0; j--) {
        int k = 0;
        while (Tools::ordinal(edge3[j]) != Tools::ordinal(UB) + j) {
            rotateLeft(edge3, 0, j);
            k++;
        }
        b = (j + 1) * b + k;
    }
    return (short) (6 * a + b);
}

void CubieCube::setUBtoDF(short idx) {
    int x;
    Edge edge3[] = {UB, DR, DF};
    int b = idx % 6;
    int a = idx / 6;
    for (int i = 0; i < 12; i++) {
        ep[i] = BR;
    }
    for (int j = 1, k; j < 3; j++) {
        k = b % (j + 1);
        b /= j + 1;
        while (k-- > 0) {
            rotateRight(edge3, 0, j);
        }
    }
    x = 2;
    for (int j = Tools::ordinal(BR); j >= 0; j--) {
        if (a - NChooseK(j, x + 1) >= 0) {
            ep[j] = edge3[x];
            a -= NChooseK(j, x-- +1);
        }
    }
}

int CubieCube::getURFtoDLB() {
    Corner perm[8];
    int b = 0;
    for (int i = 0; i < 8; i++) {
        perm[i] = cp[i];
    }
    for (int j = 7; j > 0; j--) {
        int k = 0;
        while (Tools::ordinal(perm[j]) != j) {
            rotateLeft(perm, 0, j);
            k++;
        }
        b = (j + 1) * b + k;
    }
    return b;
}

void CubieCube::setURFtoDLB(int idx) {
    Corner perm[] = {URF, UFL, ULB, UBR, DFR, DLF, DBL, DRB};
    int k;
    for (int j = 1; j < 8; j++) {
        k = idx % (j + 1);
        idx /= j + 1;
        while (k-- > 0) {
            rotateRight(perm, 0, j);
        }
    }
    int x = 7; // set corners
    for (int j = 7; j >= 0; j--) {
        cp[j] = perm[x--];
    }
}

int CubieCube::getURtoBR() {
    Edge perm[12];
    int b = 0;
    for (int i = 0; i < 12; i++) {
        perm[i] = ep[i];
    }
    for (int j = 11; j > 0; j--)// compute the index b < 12! for the permutation in perm
    {
        int k = 0;
        while (Tools::ordinal(perm[j]) != j) {
            rotateLeft(perm, 0, j);
            k++;
        }
        b = (j + 1) * b + k;
    }
    return b;
}

void CubieCube::setURtoBR(int idx) {
    Edge perm[] = {UR, UF, UL, UB, DR, DF, DL, DB, FR, FL, BL, BR};
    int k;
    for (int j = 1; j < 12; j++) {
        k = idx % (j + 1);
        idx /= j + 1;
        while (k-- > 0) {
            rotateRight(perm, 0, j);
        }
    }
    int x = 11; // set edges
    for (int j = 11; j >= 0; j--) {
        ep[j] = perm[x--];
    }
}

int CubieCube::verify() {
    int sum = 0;
    int edgeCount[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 12; i++) {
        edgeCount[Tools::ordinal(ep[i])]++;
    }
    for (int i = 0; i < 12; i++) {
        if (edgeCount[i] != 1) {
            return -2;
        }
    }

    for (int i = 0; i < 12; i++) {
        sum += eo[i];
    }
    if (sum % 2 != 0) {
        return -3;
    }

    int cornerCount[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 8; i++) {
        cornerCount[Tools::ordinal(cp[i])]++;
    }
    for (int i = 0; i < 8; i++) {
        if (cornerCount[i] != 1) {
            return -4;
        }
    }
    sum = 0;
    for (int i = 0; i < 8; i++) {
        sum += co[i];
    }
    if (sum % 3 != 0) {
        return -5;
    }
    if ((edgeParity() ^ cornerParity()) != 0) {
        return -6;
    }
    return 0;
}
