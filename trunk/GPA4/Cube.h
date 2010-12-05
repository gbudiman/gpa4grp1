/* 
 * File:   Cube.h
 * Author: Wan Kuk
 *
 * Created on November 7, 2010, 5:29 PM
 */


#ifndef CUBE_H
#define	CUBE_H
#include <QtCore>
#include <string>
#include <vector>
using namespace std;

class Cube {
public:
    Cube();
    void generateRandomState();
    bool isEqualTo(Cube &cube);
    void doTurns(vector<int> &sol);
    void enterState(char c, int i, int j);
    void performTurn(int turn, int direction);
    void rotateXClockwise();
    void rotateXCounterClockwise();
    void rotateYClockwise();
    void rotateYCounterClockwise();
    void rotateZClockwise();
    void rotateZCounterClockwise();
    void reset();
    void printState();
    string getState();
    char getState(int i, int j);
private:
    void turnYellowClockwise();
    void turnYellowCounterClockwise();
    void turnRedClockwise();
    void turnRedCounterClockwise();
    void turnGreenClockwise();
    void turnGreenCounterClockwise();
    void turnOrangeClockwise();
    void turnOrangeCounterClockwise();
    void turnBlueClockwise();
    void turnBlueCounterClockwise();
    void turnWhiteClockwise();
    void turnWhiteCounterClockwise();
    void faceTurnClockwise(char* face);
    void faceTurnCounterClockwise(char* face);
    static const int TOP = 1;
    static const int FRONT = 2;
    static const int RIGHT = 3;
    static const int BACK = 4;
    static const int LEFT = 5;
    static const int BOTTOM = 6;
    static const int YELLOW = 1;
    static const int RED = 2;
    static const int GREEN = 3;
    static const int ORANGE = 4;
    static const int BLUE = 5;
    static const int WHITE = 6;
    char state[7][10];
    char state3D[4][10];
    int orientation[7];
    int tempOrientation;
    char tempState;
    char* stateString;
};

#endif	/* CUBE_H */

