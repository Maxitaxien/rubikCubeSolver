#include <iostream>
#include "moves.cpp"
using namespace std;

bool testU(array<int, NUMFACES> cubeState) {
    // replacing some sample values on the top face to test rotation as well
    cubeState[TOP] = 0; // top left corner -> top of last col
    cubeState[TOP + 1] = 1; // middle of top row -> middle of last col
    cubeState[TOP + 3] = 2;  // middle of first column -> middle of top row
    cubeState[TOP + 5] = 3; // middle of last column -> middle of last row

    U(cubeState);
    array<int, NUMFACES> target = {1, 1, 1, 0, 0, 0, 0, 0, 0,
                                   3, 3, 3, 1, 1, 1, 1, 1, 1,
                                   0, 0, 0, 2, 2, 2, 2, 2, 2,
                                   2, 2, 2, 3, 3, 3, 3, 3, 3,
                                   4, 2, 0, 4, 4, 1, 4, 3, 4, 
                                   5, 5, 5, 5, 5, 5, 5, 5, 5};
    return (cubeState == target);
}


// a set of tests to make sure the moves work
int main() {
    // start from goalState
    // init: all 0's front, all 1's right, all 2's left, all 3's back, all 4's top, all 5's down
    array<int, NUMFACES> GOALSTATE = {}; 
    for (int i = 0; i < NUMFACES; i++) {
        GOALSTATE[i] = i / 9;
    }

    if (testU(GOALSTATE)) {
        cout << "U-movement verified\n";
    }
    return 0;
}