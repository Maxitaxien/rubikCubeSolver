#include <iostream>
#include "Cube.cpp"
using namespace std;

bool testU(Cube c) {
    // replacing some sample values on the top face to test rotation as well
    array<int, NUMFACES> s = c.state;
    s[TOP] = 0; // top left corner -> top of last col
    s[TOP + 1] = 1; // middle of top row -> middle of last col
    s[TOP + 3] = 2;  // middle of first column -> middle of top row
    s[TOP + 5] = 3; // middle of last column -> middle of last row

    Cube newCube = Cube(U(s));
    Cube target = Cube({1, 1, 1, 0, 0, 0, 0, 0, 0,
                                   3, 3, 3, 1, 1, 1, 1, 1, 1,
                                   0, 0, 0, 2, 2, 2, 2, 2, 2,
                                   2, 2, 2, 3, 3, 3, 3, 3, 3,
                                   4, 2, 0, 4, 4, 1, 4, 3, 4, 
                                   5, 5, 5, 5, 5, 5, 5, 5, 5});
    return (newCube == target);
}

bool testDoubleU(Cube c) {
    // TODO: Test that U into U prime gives same state
}

bool testDoubleD(Cube c) {
    // TODO: Test that D into D prime gives same state
}

bool testDoubleR(Cube c) {
    // TODO: Test that R into R prime gives same state
}

bool testDoubleL(Cube c) {
    // TODO: Test that L into L prime gives same state
}

bool testDoubleF(Cube c) {
    // TODO: Test that F into F prime gives same state
}

bool testDoubleB(Cube c) {
    // TODO: Test that B into B prime gives same state
}

// a set of tests to make sure the moves work
int main() {
    // start from goalState
    // init: all 0's front, all 1's right, all 2's left, all 3's back, all 4's top, all 5's down
    Cube goal = Cube(true);

    if (testU(goal)) {
        cout << "U-movement verified\n";
    }
    else {
        cout << "U-movement incorrect\n";
    }
    return 0;
}