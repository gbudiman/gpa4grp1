/* 
 * File:   CoordCube.cpp
 * Author: Wan Kuk
 * 
 * Created on December 1, 2010, 12:47 PM
 */

#include "CoordCube.h"

short CoordCube::twistMove[N_TWIST][N_MOVE];
short CoordCube::flipMove[N_FLIP][N_MOVE];
short CoordCube::parityMove[2][18] = {
    { 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1},
    { 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0}
};
short CoordCube::FRtoBR_Move[N_FRtoBR][N_MOVE];
short CoordCube::URFtoDLF_Move[N_URFtoDLF][N_MOVE];
short CoordCube::URtoDF_Move[N_URtoDF][N_MOVE];
short CoordCube::URtoUL_Move[N_URtoUL][N_MOVE];
short CoordCube::UBtoDF_Move[N_UBtoDF][N_MOVE];
short CoordCube::MergeURtoULandUBtoDF[336][336];
short CoordCube::Slice_URFtoDLF_Parity_Prun[N_SLICE2 * N_URFtoDLF * N_PARITY / 2];
short CoordCube::Slice_URtoDF_Parity_Prun[N_SLICE2 * N_URtoDF * N_PARITY / 2];
short CoordCube::Slice_Twist_Prun[N_SLICE1 * N_TWIST / 2 + 1];
short CoordCube::Slice_Flip_Prun[N_SLICE1 * N_FLIP / 2];

CoordCube::CoordCube(CubieCube c) {
    twist = c.getTwist();
    flip = c.getFlip();
    parity = c.cornerParity();
    FRtoBR = c.getFRtoBR();
    URFtoDLF = c.getURFtoDLF();
    URtoUL = c.getURtoUL();
    UBtoDF = c.getUBtoDF();
    URtoDF = c.getURtoDF(); // only needed in phase2
}

void CoordCube::move(int m) {
    twist = twistMove[twist][m];
    flip = flipMove[flip][m];
    parity = parityMove[parity][m];
    FRtoBR = FRtoBR_Move[FRtoBR][m];
    URFtoDLF = URFtoDLF_Move[URFtoDLF][m];
    URtoUL = URtoUL_Move[URtoUL][m];
    UBtoDF = UBtoDF_Move[UBtoDF][m];
    if (URtoUL < 336 && UBtoDF < 336) {
        URtoDF = MergeURtoULandUBtoDF[URtoUL][UBtoDF];
    }
}

void CoordCube::initializeAll() {
    initializeTwistMove();
    initializeFlipMove();
    initializeFRtoBR_Move();
    initializeURFtoDLF_Move();
    initializeURtoDF_Move();
    initializeURtoUL_Move();
    initializeUBtoDF_Move();
    initializeMergeURtoULandUBtoDF();
    initializeSlice_URFtoDLF_Parity_Prun();
    initializeSlice_URtoDF_Parity_Prun();
    initializeSlice_Twist_Prun();
    initializeSlice_Flip_Prun();
}

void CoordCube::initializeTwistMove() {
    CubieCube a;
    for (short i = 0; i < N_TWIST; i++) {
        a.setTwist(i);
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 3; k++) {
                a.cornerMultiply(CubieCube::moveCube[j]);
                twistMove[i][3 * j + k] = a.getTwist();
            }
            a.cornerMultiply(CubieCube::moveCube[j]);
        }
    }
}

void CoordCube::initializeFlipMove() {
    CubieCube a;
    for (short i = 0; i < N_FLIP; i++) {
        a.setFlip(i);
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 3; k++) {
                a.edgeMultiply(CubieCube::moveCube[j]);
                flipMove[i][3 * j + k] = a.getFlip();
            }
            a.edgeMultiply(CubieCube::moveCube[j]);
            // a
        }
    }
}

void CoordCube::initializeFRtoBR_Move() {
    CubieCube a;
    for (short i = 0; i < N_FRtoBR; i++) {
        a.setFRtoBR(i);
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 3; k++) {
                a.edgeMultiply(CubieCube::moveCube[j]);
                FRtoBR_Move[i][3 * j + k] = a.getFRtoBR();
            }
            a.edgeMultiply(CubieCube::moveCube[j]);
        }
    }
}

void CoordCube::initializeURFtoDLF_Move() {
    CubieCube a;
    for (short i = 0; i < N_URFtoDLF; i++) {
        a.setURFtoDLF(i);
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 3; k++) {
                a.cornerMultiply(CubieCube::moveCube[j]);
                URFtoDLF_Move[i][3 * j + k] = a.getURFtoDLF();
            }
            a.cornerMultiply(CubieCube::moveCube[j]);
        }
    }
}

void CoordCube::initializeURtoDF_Move() {
    CubieCube a;
    for (short i = 0; i < N_URtoDF; i++) {
        a.setURtoDF(i);
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 3; k++) {
                a.edgeMultiply(CubieCube::moveCube[j]);
                URtoDF_Move[i][3 * j + k] = (short) a.getURtoDF();
                // Table values are only valid for phase 2 moves!
                // For phase 1 moves, casting to short is not possible.
            }
            a.edgeMultiply(CubieCube::moveCube[j]);
        }
    }
}

void CoordCube::initializeURtoUL_Move() {
    CubieCube a;
    for (short i = 0; i < N_URtoUL; i++) {
        a.setURtoUL(i);
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 3; k++) {
                a.edgeMultiply(CubieCube::moveCube[j]);
                URtoUL_Move[i][3 * j + k] = a.getURtoUL();
            }
            a.edgeMultiply(CubieCube::moveCube[j]);
        }
    }
}

void CoordCube::initializeUBtoDF_Move() {
    CubieCube a;
    for (short i = 0; i < N_UBtoDF; i++) {
        a.setUBtoDF(i);
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 3; k++) {
                a.edgeMultiply(CubieCube::moveCube[j]);
                UBtoDF_Move[i][3 * j + k] = a.getUBtoDF();
            }
            a.edgeMultiply(CubieCube::moveCube[j]);
        }
    }
}

void CoordCube::initializeMergeURtoULandUBtoDF() {
    for (short uRtoUL = 0; uRtoUL < 336; uRtoUL++) {
        for (short uBtoDF = 0; uBtoDF < 336; uBtoDF++) {
            MergeURtoULandUBtoDF[uRtoUL][uBtoDF] = (short) CubieCube::getURtoDF(uRtoUL, uBtoDF);
        }
    }
}

void CoordCube::initializeSlice_URFtoDLF_Parity_Prun() {
    for (int i = 0; i < N_SLICE2 * N_URFtoDLF * N_PARITY / 2; i++)
        Slice_URFtoDLF_Parity_Prun[i] = -1;
    int depth = 0;
    setPruning(Slice_URFtoDLF_Parity_Prun, 0, (short) 0);
    int done = 1;
    while (done != N_SLICE2 * N_URFtoDLF * N_PARITY) {
        for (int i = 0; i < N_SLICE2 * N_URFtoDLF * N_PARITY; i++) {
            int parity = i % 2;
            int URFtoDLF = (i / 2) / N_SLICE2;
            int slice = (i / 2) % N_SLICE2;
            if (getPruning(Slice_URFtoDLF_Parity_Prun, i) == depth) {
                for (int j = 0; j < 18; j++) {
                    switch (j) {
                        case 3:
                        case 5:
                        case 6:
                        case 8:
                        case 12:
                        case 14:
                        case 15:
                        case 17:
                            continue;
                        default:
                            int newSlice = FRtoBR_Move[slice][j];
                            int newURFtoDLF = URFtoDLF_Move[URFtoDLF][j];
                            int newParity = parityMove[parity][j];
                            if (getPruning(Slice_URFtoDLF_Parity_Prun, (N_SLICE2 * newURFtoDLF + newSlice) * 2 + newParity) == 0x0f) {
                                setPruning(Slice_URFtoDLF_Parity_Prun, (N_SLICE2 * newURFtoDLF + newSlice) * 2 + newParity,
                                        (short) (depth + 1));
                                done++;
                            }
                    }
                }
            }
        }
        depth++;
    }
}

void CoordCube::initializeSlice_URtoDF_Parity_Prun() {
    for (int i = 0; i < N_SLICE2 * N_URtoDF * N_PARITY / 2; i++)
        Slice_URtoDF_Parity_Prun[i] = -1;
    int depth = 0;
    setPruning(Slice_URtoDF_Parity_Prun, 0, (short) 0);
    int done = 1;
    while (done != N_SLICE2 * N_URtoDF * N_PARITY) {
        for (int i = 0; i < N_SLICE2 * N_URtoDF * N_PARITY; i++) {
            int parity = i % 2;
            int URtoDF = (i / 2) / N_SLICE2;
            int slice = (i / 2) % N_SLICE2;
            if (getPruning(Slice_URtoDF_Parity_Prun, i) == depth) {
                for (int j = 0; j < 18; j++) {
                    switch (j) {
                        case 3:
                        case 5:
                        case 6:
                        case 8:
                        case 12:
                        case 14:
                        case 15:
                        case 17:
                            continue;
                        default:
                            int newSlice = FRtoBR_Move[slice][j];
                            int newURtoDF = URtoDF_Move[URtoDF][j];
                            int newParity = parityMove[parity][j];
                            if (getPruning(Slice_URtoDF_Parity_Prun, (N_SLICE2 * newURtoDF + newSlice) * 2 + newParity) == 0x0f) {
                                setPruning(Slice_URtoDF_Parity_Prun, (N_SLICE2 * newURtoDF + newSlice) * 2 + newParity,
                                        (short) (depth + 1));
                                done++;
                            }
                    }
                }
            }
        }
        depth++;
    }
}

void CoordCube::initializeSlice_Twist_Prun() {
    for (int i = 0; i < N_SLICE1 * N_TWIST / 2 + 1; i++)
        Slice_Twist_Prun[i] = -1;
    int depth = 0;
    setPruning(Slice_Twist_Prun, 0, (short) 0);
    int done = 1;
    while (done != N_SLICE1 * N_TWIST) {
        for (int i = 0; i < N_SLICE1 * N_TWIST; i++) {
            int twist = i / N_SLICE1, slice = i % N_SLICE1;
            if (getPruning(Slice_Twist_Prun, i) == depth) {
                for (int j = 0; j < 18; j++) {
                    int newSlice = FRtoBR_Move[slice * 24][j] / 24;
                    int newTwist = twistMove[twist][j];
                    if (getPruning(Slice_Twist_Prun, N_SLICE1 * newTwist + newSlice) == 0x0f) {
                        setPruning(Slice_Twist_Prun, N_SLICE1 * newTwist + newSlice, (short) (depth + 1));
                        done++;
                    }
                }
            }
        }
        depth++;
    }
}

void CoordCube::initializeSlice_Flip_Prun() {
    for (int i = 0; i < N_SLICE1 * N_FLIP / 2; i++)
        Slice_Flip_Prun[i] = -1;
    int depth = 0;
    setPruning(Slice_Flip_Prun, 0, (short) 0);
    int done = 1;
    while (done != N_SLICE1 * N_FLIP) {
        for (int i = 0; i < N_SLICE1 * N_FLIP; i++) {
            int flip = i / N_SLICE1, slice = i % N_SLICE1;
            if (getPruning(Slice_Flip_Prun, i) == depth) {
                for (int j = 0; j < 18; j++) {
                    int newSlice = FRtoBR_Move[slice * 24][j] / 24;
                    int newFlip = flipMove[flip][j];
                    if (getPruning(Slice_Flip_Prun, N_SLICE1 * newFlip + newSlice) == 0x0f) {
                        setPruning(Slice_Flip_Prun, N_SLICE1 * newFlip + newSlice, (short) (depth + 1));
                        done++;
                    }
                }
            }
        }
        depth++;
    }
}

void CoordCube::setPruning(short *table, int index, short value) {
    if ((index & 1) == 0) {
        table[index / 2] &= 0xf0 | value;
    } else {
        table[index / 2] &= 0x0f | (value << 4);
    }
}

short CoordCube::getPruning(short *table, int index) {
    if ((index & 1) == 0) {
        return (short) (table[index / 2] & 0x0f);
    } else {
        return (short) ((table[index / 2] & 0xf0) >> 4);
    }
}
