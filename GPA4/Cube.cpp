/* 
 * File:   Cube.cpp
 * Author: Wan Kuk
 * 
 * Created on November 7, 2010, 5:29 PM
 */

#include "Cube.h"
#include <iostream>
#include <string.h>
using namespace std;

Cube::Cube() {
    for (int i = 1; i < 10; i++) {
        state[YELLOW][i] = 'Y';
        state[RED][i] = 'R';
        state[GREEN][i] = 'G';
        state[ORANGE][i] = 'O';
        state[BLUE][i] = 'B';
        state[WHITE][i] = 'W';
    }
    orientation[TOP] = YELLOW;
    orientation[FRONT] = RED;
    orientation[RIGHT] = GREEN;
    orientation[BACK] = ORANGE;
    orientation[LEFT] = BLUE;
    orientation[BOTTOM] = WHITE;
}

void Cube::generateRandomState() {
    int numberTurns = rand() % 20 + 20;
    int const C = 1;
    int const CC = -1;
    for (int i = 0; i < numberTurns; i++) {
        int move = rand() % 12;
        switch (move) {
            case 0:
                performTurn(TOP, C);
                break;
            case 1:
                performTurn(RIGHT, C);
                break;
            case 2:
                performTurn(FRONT, C);
                break;
            case 3:
                performTurn(BOTTOM, C);
                break;
            case 4:
                performTurn(LEFT, C);
                break;
            case 5:
                performTurn(BACK, C);
                break;
            case 6:
                performTurn(TOP, CC);
                break;
            case 7:
                performTurn(RIGHT, CC);
                break;
            case 8:
                performTurn(FRONT, CC);
                break;
            case 9:
                performTurn(BOTTOM, CC);
                break;
            case 10:
                performTurn(LEFT, CC);
                break;
            case 11:
                performTurn(BACK, CC);
                break;
            case 12:
                rotateXClockwise();
                break;
            case 13:
                rotateXCounterClockwise();
                break;
            case 14:
                rotateYClockwise();
                break;
            case 15:
                rotateYCounterClockwise();
                break;
            case 16:
                rotateZClockwise();
                break;
            case 17:
                rotateZCounterClockwise();
                break;
        }
    }
}

bool Cube::isEqualTo(Cube &cube) {
    for (int i = 1; i < 7; i++) {
        for (int j = 1; j < 10; j++) {
            if (state[i][j] != cube.state[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void Cube::doTurns(vector<int> &sol) {
    int const C = 1;
    int const CC = -1;
    for (int i = 0; i < (int) sol.size(); i++) {
        switch (sol.at(i)) {
            case 0:
                performTurn(TOP, C);
                break;
            case 1:
                performTurn(RIGHT, C);
                break;
            case 2:
                performTurn(FRONT, C);
                break;
            case 3:
                performTurn(BOTTOM, C);
                break;
            case 4:
                performTurn(LEFT, C);
                break;
            case 5:
                performTurn(BACK, C);
                break;
            case 6:
                performTurn(TOP, CC);
                break;
            case 7:
                performTurn(RIGHT, CC);
                break;
            case 8:
                performTurn(FRONT, CC);
                break;
            case 9:
                performTurn(BOTTOM, CC);
                break;
            case 10:
                performTurn(LEFT, CC);
                break;
            case 11:
                performTurn(BACK, CC);
                break;
            case 12:
                rotateXClockwise();
                break;
            case 13:
                rotateXCounterClockwise();
                break;
            case 14:
                rotateYClockwise();
                break;
            case 15:
                rotateYCounterClockwise();
                break;
            case 16:
                rotateZClockwise();
                break;
            case 17:
                rotateZCounterClockwise();
                break;
        }
    }
}

void Cube::enterState(char c, int i ,int j) {
    state[i][j] = c;
}

void Cube::performTurn(int turn, int direction) {
    int color = orientation[turn];

    if (direction == -1) {
        switch (color) {
            case YELLOW:
                turnYellowCounterClockwise();
                break;
            case RED:
                turnRedCounterClockwise();
                break;
            case GREEN:
                turnGreenCounterClockwise();
                break;
            case ORANGE:
                turnOrangeCounterClockwise();
                break;
            case BLUE:
                turnBlueCounterClockwise();
                break;
            case WHITE:
                turnWhiteCounterClockwise();
                break;
        }
    } else if (direction == 1) {
        switch (color) {
            case YELLOW:
                turnYellowClockwise();
                break;
            case RED:
                turnRedClockwise();
                break;
            case GREEN:
                turnGreenClockwise();
                break;
            case ORANGE:
                turnOrangeClockwise();
                break;
            case BLUE:
                turnBlueClockwise();
                break;
            case WHITE:
                turnWhiteClockwise();
                break;
        }
    }
}

void Cube::rotateXClockwise() {
    tempOrientation = orientation[FRONT];
    orientation[FRONT] = orientation[BOTTOM];
    orientation[BOTTOM] = orientation[BACK];
    orientation[BACK] = orientation[TOP];
    orientation[TOP] = tempOrientation;
}

void Cube::rotateXCounterClockwise() {
    tempOrientation = orientation[BACK];
    orientation[BACK] = orientation[BOTTOM];
    orientation[BOTTOM] = orientation[FRONT];
    orientation[FRONT] = orientation[TOP];
    orientation[TOP] = tempOrientation;
}

void Cube::rotateYClockwise() {
    tempOrientation = orientation[FRONT];
    orientation[FRONT] = orientation[RIGHT];
    orientation[RIGHT] = orientation[BACK];
    orientation[BACK] = orientation[LEFT];
    orientation[LEFT] = tempOrientation;
}

void Cube::rotateYCounterClockwise() {
    tempOrientation = orientation[BACK];
    orientation[BACK] = orientation[RIGHT];
    orientation[RIGHT] = orientation[FRONT];
    orientation[FRONT] = orientation[LEFT];
    orientation[LEFT] = tempOrientation;
}

void Cube::rotateZClockwise() {
    tempOrientation = orientation[LEFT];
    orientation[LEFT] = orientation[BOTTOM];
    orientation[BOTTOM] = orientation[RIGHT];
    orientation[RIGHT] = orientation[TOP];
    orientation[TOP] = tempOrientation;
}

void Cube::rotateZCounterClockwise() {
    tempOrientation = orientation[RIGHT];
    orientation[RIGHT] = orientation[BOTTOM];
    orientation[BOTTOM] = orientation[LEFT];
    orientation[LEFT] = orientation[TOP];
    orientation[TOP] = tempOrientation;
}

void Cube::turnYellowClockwise() {
    faceTurnClockwise(state[TOP]);
    for (int i = 1; i <= 3; i++) {
        tempState = state[FRONT][i];
        state[FRONT][i] = state[RIGHT][i];
        state[RIGHT][i] = state[BACK][i];
        state[BACK][i] = state[LEFT][i];
        state[LEFT][i] = tempState;
    }
}

void Cube::turnYellowCounterClockwise() {
    faceTurnCounterClockwise(state[TOP]);
    for (int i = 1; i <= 3; i++) {
        tempState = state[FRONT][i];
        state[FRONT][i] = state[LEFT][i];
        state[LEFT][i] = state[BACK][i];
        state[BACK][i] = state[RIGHT][i];
        state[RIGHT][i] = tempState;
    }
}

void Cube::turnRedClockwise() {
    faceTurnClockwise(state[FRONT]);
    tempState = state[LEFT][9];
    state[LEFT][9] = state[BOTTOM][1];
    state[BOTTOM][1] = state[RIGHT][1];
    state[RIGHT][1] = state[TOP][1];
    state[TOP][1] = tempState;
    tempState = state[LEFT][6];
    state[LEFT][6] = state[BOTTOM][4];
    state[BOTTOM][4] = state[RIGHT][4];
    state[RIGHT][4] = state[TOP][4];
    state[TOP][4] = tempState;
    tempState = state[LEFT][3];
    state[LEFT][3] = state[BOTTOM][7];
    state[BOTTOM][7] = state[RIGHT][7];
    state[RIGHT][7] = state[TOP][7];
    state[TOP][7] = tempState;
}

void Cube::turnRedCounterClockwise() {
    faceTurnCounterClockwise(state[FRONT]);
    tempState = state[RIGHT][1];
    state[RIGHT][1] = state[BOTTOM][1];
    state[BOTTOM][1] = state[LEFT][9];
    state[LEFT][9] = state[TOP][1];
    state[TOP][1] = tempState;
    tempState = state[RIGHT][4];
    state[RIGHT][4] = state[BOTTOM][4];
    state[BOTTOM][4] = state[LEFT][6];
    state[LEFT][6] = state[TOP][4];
    state[TOP][4] = tempState;
    tempState = state[RIGHT][7];
    state[RIGHT][7] = state[BOTTOM][7];
    state[BOTTOM][7] = state[LEFT][3];
    state[LEFT][3] = state[TOP][7];
    state[TOP][7] = tempState;
}

void Cube::turnGreenClockwise() {
    faceTurnClockwise(state[RIGHT]);
    tempState = state[FRONT][3];
    state[FRONT][3] = state[BOTTOM][1];
    state[BOTTOM][1] = state[BACK][7];
    state[BACK][7] = state[TOP][9];
    state[TOP][9] = tempState;
    tempState = state[FRONT][6];
    state[FRONT][6] = state[BOTTOM][2];
    state[BOTTOM][2] = state[BACK][4];
    state[BACK][4] = state[TOP][8];
    state[TOP][8] = tempState;
    tempState = state[FRONT][9];
    state[FRONT][9] = state[BOTTOM][3];
    state[BOTTOM][3] = state[BACK][1];
    state[BACK][1] = state[TOP][7];
    state[TOP][7] = tempState;
}

void Cube::turnGreenCounterClockwise() {
    faceTurnCounterClockwise(state[RIGHT]);
    tempState = state[FRONT][3];
    state[FRONT][3] = state[TOP][9];
    state[TOP][9] = state[BACK][7];
    state[BACK][7] = state[BOTTOM][1];
    state[BOTTOM][1] = tempState;
    tempState = state[FRONT][6];
    state[FRONT][6] = state[TOP][8];
    state[TOP][8] = state[BACK][4];
    state[BACK][4] = state[BOTTOM][2];
    state[BOTTOM][2] = tempState;
    tempState = state[FRONT][9];
    state[FRONT][9] = state[TOP][7];
    state[TOP][7] = state[BACK][1];
    state[BACK][1] = state[BOTTOM][3];
    state[BOTTOM][3] = tempState;
}

void Cube::turnOrangeClockwise() {
    faceTurnClockwise(state[BACK]);
    tempState = state[RIGHT][3];
    state[RIGHT][3] = state[BOTTOM][3];
    state[BOTTOM][3] = state[LEFT][7];
    state[LEFT][7] = state[TOP][3];
    state[TOP][3] = tempState;
    tempState = state[RIGHT][6];
    state[RIGHT][6] = state[BOTTOM][6];
    state[BOTTOM][6] = state[LEFT][4];
    state[LEFT][4] = state[TOP][6];
    state[TOP][6] = tempState;
    tempState = state[RIGHT][9];
    state[RIGHT][9] = state[BOTTOM][9];
    state[BOTTOM][9] = state[LEFT][1];
    state[LEFT][1] = state[TOP][9];
    state[TOP][9] = tempState;
}

void Cube::turnOrangeCounterClockwise() {
    faceTurnCounterClockwise(state[BACK]);
    tempState = state[LEFT][7];
    state[LEFT][7] = state[BOTTOM][3];
    state[BOTTOM][3] = state[RIGHT][3];
    state[RIGHT][3] = state[TOP][3];
    state[TOP][3] = tempState;
    tempState = state[LEFT][4];
    state[LEFT][4] = state[BOTTOM][6];
    state[BOTTOM][6] = state[RIGHT][6];
    state[RIGHT][6] = state[TOP][6];
    state[TOP][6] = tempState;
    tempState = state[LEFT][1];
    state[LEFT][1] = state[BOTTOM][9];
    state[BOTTOM][9] = state[RIGHT][9];
    state[RIGHT][9] = state[TOP][9];
    state[TOP][9] = tempState;
}

void Cube::turnBlueClockwise() {
    faceTurnClockwise(state[LEFT]);
    tempState = state[FRONT][1];
    state[FRONT][1] = state[TOP][3];
    state[TOP][3] = state[BACK][9];
    state[BACK][9] = state[BOTTOM][7];
    state[BOTTOM][7] = tempState;
    tempState = state[FRONT][4];
    state[FRONT][4] = state[TOP][2];
    state[TOP][2] = state[BACK][6];
    state[BACK][6] = state[BOTTOM][8];
    state[BOTTOM][8] = tempState;
    tempState = state[FRONT][7];
    state[FRONT][7] = state[TOP][1];
    state[TOP][1] = state[BACK][3];
    state[BACK][3] = state[BOTTOM][9];
    state[BOTTOM][9] = tempState;
}

void Cube::turnBlueCounterClockwise() {
    faceTurnCounterClockwise(state[LEFT]);
    tempState = state[FRONT][1];
    state[FRONT][1] = state[BOTTOM][7];
    state[BOTTOM][7] = state[BACK][9];
    state[BACK][9] = state[TOP][3];
    state[TOP][3] = tempState;
    tempState = state[FRONT][4];
    state[FRONT][4] = state[BOTTOM][8];
    state[BOTTOM][8] = state[BACK][6];
    state[BACK][6] = state[TOP][2];
    state[TOP][2] = tempState;
    tempState = state[FRONT][7];
    state[FRONT][7] = state[BOTTOM][9];
    state[BOTTOM][9] = state[BACK][3];
    state[BACK][3] = state[TOP][1];
    state[TOP][1] = tempState;
}

void Cube::turnWhiteClockwise() {
    faceTurnClockwise(state[BOTTOM]);
    for (int i = 7; i <= 9; i++) {
        tempState = state[FRONT][i];
        state[FRONT][i] = state[LEFT][i];
        state[LEFT][i] = state[BACK][i];
        state[BACK][i] = state[RIGHT][i];
        state[RIGHT][i] = tempState;
    }
}

void Cube::turnWhiteCounterClockwise() {
    faceTurnCounterClockwise(state[BOTTOM]);
    for (int i = 7; i <= 9; i++) {
        tempState = state[FRONT][i];
        state[FRONT][i] = state[RIGHT][i];
        state[RIGHT][i] = state[BACK][i];
        state[BACK][i] = state[LEFT][i];
        state[LEFT][i] = tempState;
    }
}

void Cube::faceTurnClockwise(char* face) {
    tempState = face[7];
    face[7] = face[9];
    face[9] = face[3];
    face[3] = face[1];
    face[1] = tempState;
    tempState = face[4];
    face[4] = face[8];
    face[8] = face[6];
    face[6] = face[2];
    face[2] = tempState;
}

void Cube::faceTurnCounterClockwise(char* face) {
    tempState = face[3];
    face[3] = face[9];
    face[9] = face[7];
    face[7] = face[1];
    face[1] = tempState;
    tempState = face[6];
    face[6] = face[8];
    face[8] = face[4];
    face[4] = face[2];
    face[2] = tempState;
}

void Cube::reset() {
    for (int i = 1; i < 10; i++) {
        state[YELLOW][i] = 'Y';
        state[RED][i] = 'R';
        state[GREEN][i] = 'G';
        state[ORANGE][i] = 'O';
        state[BLUE][i] = 'B';
        state[WHITE][i] = 'W';
    }
    orientation[TOP] = YELLOW;
    orientation[FRONT] = RED;
    orientation[RIGHT] = GREEN;
    orientation[BACK] = ORANGE;
    orientation[LEFT] = BLUE;
    orientation[BOTTOM] = WHITE;
}

void Cube::printState() {
    for (int i = 1; i < 7; i++) {
        for (int j = 1; j < 10; j++) {
            cout << state[i][j];
        }
    }
    cout << endl;
}

string Cube::getState() {
    string s = "";
    for (int i = 1; i < 7; i++) {
        for (int j = 1; j < 10; j++) {
            s += state[i][j];
        }
    }
    return s;
}

char Cube::getState(int i, int j) {
    return state[i][j];
}
