/* 
 * File:   Search.cpp
 * Author: Wan Kuk
 * 
 * Created on December 1, 2010, 11:30 PM
 */

#include "Search.h"
#include "CoordCube.h"

int Search::ax[31];
int Search::bx[50];
int Search::po[31];
int Search::flip[31];
int Search::twist[31];
int Search::slice[31];
int Search::parity[31];
int Search::URFtoDLF[31];
int Search::FRtoBR[31];
int Search::URtoUL[31];
int Search::UBtoDF[31];
int Search::URtoDF[31];
int Search::minDistPhase1[31];
int Search::minDistPhase2[31];
int Search::rotationTable[6][12];
vector<int> Search::disableMoves;
vector<int> Search::solutionMoves;
vector<int> Search::allowedRotations;
vector<int> Search::rotationVector;
vector<int> Search::finalSolution;
string Search::moves[18] = {"U", "R", "F", "D", "L", "B", "U'", "R'", "F'", "D'", "L'", "B'", "X", "X'", "Y", "Y'", "Z", "Z'"};

void Search::readMoves(string s, vector<int> &result) {
    for (int i = 0; i < (int) s.length(); i++) {
        string turn = s.substr(i, 1);
        if (turn.compare("'") == 0 || turn.compare(" ") == 0) {
            continue;
        }
        if (s.substr(i + 1, 1).compare("'") == 0) {
            turn += "'";
        }
        for (int j = 0; j < 18; j++) {
            if (turn.compare(moves[j]) == 0) {
                result.push_back(j);
		break;
            }
        }
    }
}

int Search::updateMove(int m) {
    int move = m;

    for (int i = 0; i < (int) rotationVector.size(); i++) {
        move = rotationTable[rotationVector.at(i)][move];
    }
    return move;
}

string Search::getFinalSolution(string sol, string disable) {
    readMoves(disable, disableMoves);
    readMoves(sol, solutionMoves);
    for (int i = 12; i < 18; i++) {
        if (!isMoveDisable(i)) {
            allowedRotations.push_back(i - 12);
        }
    }

    int move;
    int newMove;
    int secondMove;
    int thirdMove;
    int pairMove;
    for (int i = 0; i < (int) solutionMoves.size(); i++) {
        move = updateMove(solutionMoves.at(i));
        if (!isMoveDisable(move)) {
            finalSolution.push_back(move);
        } else {
            for (int r = 0; r < (int) allowedRotations.size(); r++) {
                newMove = rotationTable[allowedRotations.at(r)][move];
                if (!isMoveDisable(newMove)) {
                    //cout << i << " ROTATE_ONCE" << endl;
                    rotationVector.push_back(allowedRotations.at(r));
                    finalSolution.push_back(allowedRotations.at(r) + 12);
                    finalSolution.push_back(newMove);
                    goto end;
                }
            }

            if (!isPairMoveDisable(move)) {
                cout << i << " TURN_THREE" << endl;
                pairMove = getPairMove(move);
		if((i + 1) < (int) solutionMoves.size()) {
		    if(solutionMoves.at(i) == solutionMoves.at(i + 1)){
			finalSolution.push_back(pairMove);
                	finalSolution.push_back(pairMove);
			i++;
			goto end;
		    }
		}
                finalSolution.push_back(pairMove);
                finalSolution.push_back(pairMove);
                finalSolution.push_back(pairMove);
                goto end;
            }
            for (int r = 0; r < (int) allowedRotations.size(); r++) {
                newMove = rotationTable[allowedRotations.at(r)][move];
                for (int r2 = 0; r2 < (int) allowedRotations.size(); r2++) {
                    secondMove = rotationTable[allowedRotations.at(r2)][newMove];
                    if (!isMoveDisable(secondMove)) {
                        //cout << i << " ROTATE_TWICE" << endl;
                        rotationVector.push_back(allowedRotations.at(r));
                        rotationVector.push_back(allowedRotations.at(r2));
                        finalSolution.push_back(allowedRotations.at(r) + 12);
                        finalSolution.push_back(allowedRotations.at(r2) + 12);
                        finalSolution.push_back(secondMove);
                        goto end;
                    }
                }
            }

	    for (int r = 0; r < (int) allowedRotations.size(); r++) {
                newMove = rotationTable[allowedRotations.at(r)][move];
                for (int r2 = 0; r2 < (int) allowedRotations.size(); r2++) {
                    secondMove = rotationTable[allowedRotations.at(r2)][newMove];
                    for (int r3 = 0; r3 < (int) allowedRotations.size(); r3++) {
                        thirdMove = rotationTable[allowedRotations.at(r3)][secondMove];
                        if (!isMoveDisable(thirdMove)) {
                            //cout<< i << " ROTATE_THREE" << endl;
                            rotationVector.push_back(allowedRotations.at(r));
                            rotationVector.push_back(allowedRotations.at(r2));
                            rotationVector.push_back(allowedRotations.at(r3));
                            finalSolution.push_back(allowedRotations.at(r) + 12);
                            finalSolution.push_back(allowedRotations.at(r2) + 12);
                            finalSolution.push_back(allowedRotations.at(r3) + 12);
                            finalSolution.push_back(thirdMove);
                            goto end;
                        }
                    }
                }
            }

            for (int r = 0; r < (int) allowedRotations.size(); r++) {
                newMove = rotationTable[allowedRotations.at(r)][move];
                if (!isPairMoveDisable(newMove)) {
                    //cout<< i << " ROTATE_ONCE_TURN_THREE" << endl;
                    pairMove = getPairMove(newMove);
		    rotationVector.push_back(allowedRotations.at(r));
                    finalSolution.push_back(allowedRotations.at(r) + 12);
		    if((i + 1) < (int) solutionMoves.size()) {
		        if(solutionMoves.at(i) == solutionMoves.at(i + 1)){
			    finalSolution.push_back(pairMove);
                	    finalSolution.push_back(pairMove);
		   	    i++;
			    goto end;
		        }
		    }
                    finalSolution.push_back(pairMove);
                    finalSolution.push_back(pairMove);
                    finalSolution.push_back(pairMove);
                    goto end;
                }
            }

            for (int r = 0; r < (int) allowedRotations.size(); r++) {
                newMove = rotationTable[allowedRotations.at(r)][move];
                for (int r2 = 0; r2 < (int) allowedRotations.size(); r2++) {
                    secondMove = rotationTable[allowedRotations.at(r2)][newMove];
                    if (!isPairMoveDisable(secondMove)) {
                        //cout<< i << " ROTATE_TWICE_TURN_THREE" << endl;
                        pairMove = getPairMove(secondMove);
			rotationVector.push_back(allowedRotations.at(r));
			rotationVector.push_back(allowedRotations.at(r2));
                    	finalSolution.push_back(allowedRotations.at(r) + 12);
			finalSolution.push_back(allowedRotations.at(r2) + 12);
		    	if((i + 1) < (int) solutionMoves.size()) {
		            if(solutionMoves.at(i) == solutionMoves.at(i + 1)){
			    	finalSolution.push_back(pairMove);
                	    	finalSolution.push_back(pairMove);
		   	    	i++;
			    	goto end;
		            }
		    	}	
                        finalSolution.push_back(pairMove);
                        finalSolution.push_back(pairMove);
                        finalSolution.push_back(pairMove);
                        goto end;
                    }
                }
            }

            for (int r = 0; r < (int) allowedRotations.size(); r++) {
                newMove = rotationTable[allowedRotations.at(r)][move];
                for (int r2 = 0; r2 < (int) allowedRotations.size(); r2++) {
                    secondMove = rotationTable[allowedRotations.at(r2)][newMove];
                    for (int r3 = 0; r3 < (int) allowedRotations.size(); r3++) {
                        thirdMove = rotationTable[allowedRotations.at(r3)][secondMove];
                        if (!isPairMoveDisable(thirdMove)) {
                            //cout << i << " ROTATE_THREE_TURN_THREE" << endl;
                            pairMove = getPairMove(thirdMove);
			    rotationVector.push_back(allowedRotations.at(r));
			    rotationVector.push_back(allowedRotations.at(r2));
			    rotationVector.push_back(allowedRotations.at(r3));
                    	    finalSolution.push_back(allowedRotations.at(r) + 12);
			    finalSolution.push_back(allowedRotations.at(r2) + 12);
			    finalSolution.push_back(allowedRotations.at(r3) + 12);
		    	    if((i + 1) < (int) solutionMoves.size()) {
		            	if(solutionMoves.at(i) == solutionMoves.at(i + 1)){
			    	    finalSolution.push_back(pairMove);
                	    	    finalSolution.push_back(pairMove);
		   	    	    i++;
			    	    goto end;
		            	}
		    	    }
                            finalSolution.push_back(pairMove);
                            finalSolution.push_back(pairMove);
                            finalSolution.push_back(pairMove);
                            goto end;
                        }

                    }
                }
            }
end:
            for (int i = 0; i < 1; i++) {
            }
        }

    }

    string solution = "";
    for (int i = 0; i < (int) finalSolution.size(); i++) {
        solution += moves[finalSolution.at(i)];
        solution += " ";
    }
    return solution;
}

bool Search::isMoveDisable(int move) {
    for (int i = 0; i < (int) disableMoves.size(); i++) {
        if (move == disableMoves.at(i)) {
            return false;
        }
    }
    return true; 
}

bool Search::isPairMoveDisable(int move) {
    if (move < 6) {
        if (isMoveDisable(move + 6)) {
            return true;
        }
        return false;
    } else if (move < 12) {
        if (isMoveDisable(move - 6)) {
            return true;
        }
        return false;
    }
    throw "isPairMoveDisable Error";
}

int Search::getPairMove(int move) {
    if (move < 6) {
        return (move + 6);
    } else if (move < 12) {
        return (move - 6);
    }
    throw "getPairMove Error";
}

string Search::SolutionToString(int length) {
    rotationTable[X_CC][U_C] = F_C;
    rotationTable[X_CC][F_C] = D_C;
    rotationTable[X_CC][D_C] = B_C;
    rotationTable[X_CC][B_C] = U_C;
    rotationTable[X_CC][L_C] = L_C;
    rotationTable[X_CC][R_C] = R_C;
    rotationTable[X_CC][U_CC] = F_CC;
    rotationTable[X_CC][F_CC] = D_CC;
    rotationTable[X_CC][D_CC] = B_CC;
    rotationTable[X_CC][B_CC] = U_CC;
    rotationTable[X_CC][L_CC] = L_CC;
    rotationTable[X_CC][R_CC] = R_CC;
    rotationTable[Y_CC][F_C] = R_C;
    rotationTable[Y_CC][R_C] = B_C;
    rotationTable[Y_CC][B_C] = L_C;
    rotationTable[Y_CC][L_C] = F_C;
    rotationTable[Y_CC][U_C] = U_C;
    rotationTable[Y_CC][D_C] = D_C;
    rotationTable[Y_CC][F_CC] = R_CC;
    rotationTable[Y_CC][R_CC] = B_CC;
    rotationTable[Y_CC][B_CC] = L_CC;
    rotationTable[Y_CC][L_CC] = F_CC;
    rotationTable[Y_CC][U_CC] = U_CC;
    rotationTable[Y_CC][D_CC] = D_CC;
    rotationTable[Z_CC][U_C] = L_C;
    rotationTable[Z_CC][L_C] = D_C;
    rotationTable[Z_CC][D_C] = R_C;
    rotationTable[Z_CC][R_C] = U_C;
    rotationTable[Z_CC][F_C] = F_C;
    rotationTable[Z_CC][B_C] = B_C;
    rotationTable[Z_CC][U_CC] = L_CC;
    rotationTable[Z_CC][L_CC] = D_CC;
    rotationTable[Z_CC][D_CC] = R_CC;
    rotationTable[Z_CC][R_CC] = U_CC;
    rotationTable[Z_CC][F_CC] = F_CC;
    rotationTable[Z_CC][B_CC] = B_CC;

    rotationTable[X_C][U_C] = B_C;
    rotationTable[X_C][B_C] = D_C;
    rotationTable[X_C][D_C] = F_C;
    rotationTable[X_C][F_C] = U_C;
    rotationTable[X_C][L_C] = L_C;
    rotationTable[X_C][R_C] = R_C;
    rotationTable[X_C][U_CC] = B_CC;
    rotationTable[X_C][B_CC] = D_CC;
    rotationTable[X_C][D_CC] = F_CC;
    rotationTable[X_C][F_CC] = U_CC;
    rotationTable[X_C][L_CC] = L_CC;
    rotationTable[X_C][R_CC] = R_CC;
    rotationTable[Y_C][F_C] = L_C;
    rotationTable[Y_C][L_C] = B_C;
    rotationTable[Y_C][B_C] = R_C;
    rotationTable[Y_C][R_C] = F_C;
    rotationTable[Y_C][U_C] = U_C;
    rotationTable[Y_C][D_C] = D_C;
    rotationTable[Y_C][F_CC] = L_CC;
    rotationTable[Y_C][L_CC] = B_CC;
    rotationTable[Y_C][B_CC] = R_CC;
    rotationTable[Y_C][R_CC] = F_CC;
    rotationTable[Y_C][U_CC] = U_CC;
    rotationTable[Y_C][D_CC] = D_CC;
    rotationTable[Z_C][U_C] = R_C;
    rotationTable[Z_C][R_C] = D_C;
    rotationTable[Z_C][D_C] = L_C;
    rotationTable[Z_C][L_C] = U_C;
    rotationTable[Z_C][F_C] = F_C;
    rotationTable[Z_C][B_C] = B_C;
    rotationTable[Z_C][U_CC] = R_CC;
    rotationTable[Z_C][R_CC] = D_CC;
    rotationTable[Z_C][D_CC] = L_CC;
    rotationTable[Z_C][L_CC] = U_CC;
    rotationTable[Z_C][F_CC] = F_CC;
    rotationTable[Z_C][B_CC] = B_CC;

    string s = "";
    string m;
    for (int i = 0; i < length; i++) {
        switch (rotationTable[Y_CC][ax[i]]) {
            case 0:
                m = " U ";
                s += "U";
                break;
            case 1:
                m = " R ";
                s += "R";
                break;
            case 2:
                m = " F ";
                s += "F";
                break;
            case 3:
                m = " D ";
                s += "D";
                break;
            case 4:
                m = " L ";
                s += "L";
                break;
            case 5:
                m = " B ";
                s += "B";
                break;
        }
        switch (po[i]) {
            case 1:
                s += " ";
                break;
            case 2:
                s += m;
                break;
            case 3:
                s += "' ";
                break;

        }
    }
    return s;
}

string Search::convertColor(string color) {
    if (color.compare("Y") == 0) {
        return "U";
    } else if (color.compare("R") == 0) {
        return "L";
    } else if (color.compare("G") == 0) {
        return "F";
    } else if (color.compare("O") == 0) {
        return "R";
    } else if (color.compare("B") == 0) {
        return "B";
    } else if (color.compare("W") == 0) {
        return "D";
    }
    throw "convertColor error";
}

string Search::solution(string face, int maxDepth) {
    CubieCube::initializeMoveCube();
    CoordCube::initializeAll();
    string facelets = "";
    for (int j = 0; j < 9; j++) {
        facelets += convertColor(face.substr(j, 1));
    }
    for (int j = 27; j < 36; j++) {
        facelets += convertColor(face.substr(j, 1));
    }
    for (int j = 18; j < 27; j++) {
        facelets += convertColor(face.substr(j, 1));
    }
    for (int j = 45; j < 54; j++) {
        facelets += convertColor(face.substr(j, 1));
    }
    for (int j = 9; j < 18; j++) {
        facelets += convertColor(face.substr(j, 1));
    }
    for (int j = 36; j < 45; j++) {
        facelets += convertColor(face.substr(j, 1));
    }
    int s;
    int count[6] = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 54; i++) {
        count[Tools::ordinal(Tools::getColor(facelets.substr(i, 1)))]++;
    }
    for (int i = 0; i < 6; i++)
        if (count[i] != 9) {
            return "Error 1";
        }
    FaceCube fc(facelets);
    CubieCube cc = fc.toCubieCube();
    if ((s = cc.verify()) != 0) {
        std::ostringstream stm;
        stm << s;
        return "Error " + stm.str();
    }

    CoordCube c(cc);
    po[0] = 0;
    ax[0] = 0;
    flip[0] = c.flip;
    twist[0] = c.twist;
    parity[0] = c.parity;
    slice[0] = c.FRtoBR / 24;
    URFtoDLF[0] = c.URFtoDLF;
    FRtoBR[0] = c.FRtoBR;
    URtoUL[0] = c.URtoUL;
    UBtoDF[0] = c.UBtoDF;
    minDistPhase1[1] = 1;
    int mv = 0, n = 0;
    bool busy = false;
    int depthPhase1 = 1;

    do {
        do {
            if ((depthPhase1 - n > minDistPhase1[n + 1]) && !busy) {

                if (ax[n] == 0 || ax[n] == 3)// Initialize next move
                    ax[++n] = 1;
                else
                    ax[++n] = 0;
                po[n] = 1;
            } else if (++po[n] > 3) {
                do {// increment axis
                    if (++ax[n] > 5) {
                        if (n == 0) {
                            if (depthPhase1 >= maxDepth)
                                return "Error 7";
                            else {
                                depthPhase1++;
                                ax[n] = 0;
                                po[n] = 1;
                                busy = false;
                                break;
                            }
                        } else {
                            n--;
                            busy = true;
                            break;
                        }

                    } else {
                        po[n] = 1;
                        busy = false;
                    }
                } while (n != 0 && (ax[n - 1] == ax[n] || ax[n - 1] - 3 == ax[n]));
            } else
                busy = false;
        } while (busy);

        mv = 3 * ax[n] + po[n] - 1;
        flip[n + 1] = CoordCube::flipMove[flip[n]][mv];
        twist[n + 1] = CoordCube::twistMove[twist[n]][mv];
        slice[n + 1] = CoordCube::FRtoBR_Move[slice[n] * 24][mv] / 24;
        minDistPhase1[n + 1] = max(CoordCube::getPruning(CoordCube::Slice_Flip_Prun, CoordCube::N_SLICE1 * flip[n + 1]
                + slice[n + 1]), CoordCube::getPruning(CoordCube::Slice_Twist_Prun, CoordCube::N_SLICE1 * twist[n + 1]
                + slice[n + 1]));
        // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        if (minDistPhase1[n + 1] == 0 && n >= depthPhase1 - 5) {
            minDistPhase1[n + 1] = 10;
            if (n == depthPhase1 - 1 && (s = totalDepth(depthPhase1, maxDepth)) >= 0) {
                if (s == depthPhase1
                        || (ax[depthPhase1 - 1] != ax[depthPhase1] && ax[depthPhase1 - 1] != ax[depthPhase1] + 3))
                    return SolutionToString(s);
            }

        }
    } while (true);
}

int Search::totalDepth(int depthPhase1, int maxDepth) {
    int mv = 0, d1 = 0, d2 = 0;
    int maxDepthPhase2 = min(10, maxDepth - depthPhase1);
    for (int i = 0; i < depthPhase1; i++) {
        mv = 3 * ax[i] + po[i] - 1;
        URFtoDLF[i + 1] = CoordCube::URFtoDLF_Move[URFtoDLF[i]][mv];
        FRtoBR[i + 1] = CoordCube::FRtoBR_Move[FRtoBR[i]][mv];
        parity[i + 1] = CoordCube::parityMove[parity[i]][mv];
    }

    if ((d1 = CoordCube::getPruning(CoordCube::Slice_URFtoDLF_Parity_Prun,
            (CoordCube::N_SLICE2 * URFtoDLF[depthPhase1] + FRtoBR[depthPhase1]) * 2 + parity[depthPhase1])) > maxDepthPhase2)
        return -1;

    for (int i = 0; i < depthPhase1; i++) {
        mv = 3 * ax[i] + po[i] - 1;
        URtoUL[i + 1] = CoordCube::URtoUL_Move[URtoUL[i]][mv];
        UBtoDF[i + 1] = CoordCube::UBtoDF_Move[UBtoDF[i]][mv];
    }
    URtoDF[depthPhase1] = CoordCube::MergeURtoULandUBtoDF[URtoUL[depthPhase1]][UBtoDF[depthPhase1]];

    if ((d2 = CoordCube::getPruning(CoordCube::Slice_URtoDF_Parity_Prun,
            (CoordCube::N_SLICE2 * URtoDF[depthPhase1] + FRtoBR[depthPhase1]) * 2 + parity[depthPhase1])) > maxDepthPhase2)
        return -1;

    if ((minDistPhase2[depthPhase1] = max(d1, d2)) == 0)// already solved
        return depthPhase1;

    int depthPhase2 = 1;
    int n = depthPhase1;
    bool busy = false;
    po[depthPhase1] = 0;
    ax[depthPhase1] = 0;
    minDistPhase2[n + 1] = 1;
    do {
        do {
            if ((depthPhase1 + depthPhase2 - n > minDistPhase2[n + 1]) && !busy) {

                if (ax[n] == 0 || ax[n] == 3)// Initialize next move
                {
                    ax[++n] = 1;
                    po[n] = 2;
                } else {
                    ax[++n] = 0;
                    po[n] = 1;
                }
            } else if ((ax[n] == 0 || ax[n] == 3) ? (++po[n] > 3) : ((po[n] = po[n] + 2) > 3)) {
                do {
                    if (++ax[n] > 5) {
                        if (n == depthPhase1) {
                            if (depthPhase2 >= maxDepthPhase2)
                                return -1;
                            else {
                                depthPhase2++;
                                ax[n] = 0;
                                po[n] = 1;
                                busy = false;
                                break;
                            }
                        } else {
                            n--;
                            busy = true;
                            break;
                        }

                    } else {
                        if (ax[n] == 0 || ax[n] == 3)
                            po[n] = 1;
                        else
                            po[n] = 2;
                        busy = false;
                    }
                } while (n != depthPhase1 && (ax[n - 1] == ax[n] || ax[n - 1] - 3 == ax[n]));
            } else
                busy = false;
        } while (busy);

        mv = 3 * ax[n] + po[n] - 1;

        URFtoDLF[n + 1] = CoordCube::URFtoDLF_Move[URFtoDLF[n]][mv];
        FRtoBR[n + 1] = CoordCube::FRtoBR_Move[FRtoBR[n]][mv];
        parity[n + 1] = CoordCube::parityMove[parity[n]][mv];
        URtoDF[n + 1] = CoordCube::URtoDF_Move[URtoDF[n]][mv];

        minDistPhase2[n + 1] = max(CoordCube::getPruning(CoordCube::Slice_URtoDF_Parity_Prun, (CoordCube::N_SLICE2
                * URtoDF[n + 1] + FRtoBR[n + 1])
                * 2 + parity[n + 1]), CoordCube::getPruning(CoordCube::Slice_URFtoDLF_Parity_Prun, (CoordCube::N_SLICE2
                * URFtoDLF[n + 1] + FRtoBR[n + 1])
                * 2 + parity[n + 1]));
    } while (minDistPhase2[n + 1] != 0);
    return depthPhase1 + depthPhase2;
}
