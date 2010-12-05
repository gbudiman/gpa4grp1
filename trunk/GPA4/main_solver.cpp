/* 
 * File:   main.cpp
 * Author: Wan Kuk
 *
 * Created on December 1, 2010, 1:41 PM
 */

#include <cstdlib>
#include <iostream>
#include "Search.h"
#include "Cube.h"
#include <string>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

/*
 * 
 */


int main(int argc, char** argv) {
    string disable = "FF'RR'UU'B'LL'DD'X'Y'Z'";
    vector<int> solution;
    vector<int> finalSolution;
    try {
	Cube a;
	a.generateRandomState();
	a.generateRandomState();
	a.generateRandomState();
	cout << a.getState() << endl<<endl;

        string sol = Search::solution(a.getState(), 20);
	string finalSol = Search::getFinalSolution(sol, disable);

	Cube b;
	for(int i = 1 ; i < 7; i++){
	    for(int j = 1; j < 10; j++) {
		b.enterState(a.getState(i,j), i, j);
	    }		
	}
	Search::readMoves(sol, solution);
	b.doTurns(solution);
	cout << sol << endl;
	cout << b.getState() << endl<<endl;

	Cube c;
	for(int i = 1 ; i < 7; i++){
	    for(int j = 1; j < 10; j++) {
		c.enterState(a.getState(i,j), i, j);
	    }		
	}
	Search::readMoves(finalSol, finalSolution);
	c.doTurns(finalSolution);
	cout << finalSol << endl;
	cout << c.getState() << endl;

    } catch (string s) {
        cout << s << endl;
    }
    return 0;
}

