#include <iostream>
#include <string>
#include <functional>
#include "Cube.cpp"

void runTest(std::string testName, std::function<bool()> testFunc) {
    if (testFunc()) {
        std::cout << testName << " verified\n";
    }
    else {
        std::cout << testName << " incorrect\n";
    }
}

bool testU(Cube c) {
    // replacing some sample values on the top face to test rotation as well
    std::array<int, NUMFACES> s = c.state;
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
    std::array<int, NUMFACES> s = c.state;
    Cube uCube = Cube(U(s));
    Cube newCube = Cube(U_p(uCube.state));
    return newCube == c;
}

bool testDoubleD(Cube c) {
    std::array<int, NUMFACES> s = c.state;
    Cube uCube = Cube(D(s));
    Cube newCube = Cube(D_p(uCube.state));
    return newCube == c;
}

bool testDoubleR(Cube c) {
    std::array<int, NUMFACES> s = c.state;
    Cube uCube = Cube(R(s));
    Cube newCube = Cube(R_p(uCube.state));
    return newCube == c;
}

bool testDoubleL(Cube c) {
    std::array<int, NUMFACES> s = c.state;
    Cube uCube = Cube(L(s));
    Cube newCube = Cube(L_p(uCube.state));
    return newCube == c;
}

bool testDoubleF(Cube c) {
    std::array<int, NUMFACES> s = c.state;
    Cube uCube = Cube(F(s));
    Cube newCube = Cube(F_p(uCube.state));
    return newCube == c;
}

bool testDoubleB(Cube c) {
    std::array<int, NUMFACES> s = c.state;
    Cube uCube = Cube(B(s));
    Cube newCube = Cube(B_p(uCube.state));
    return newCube == c;
}

// a set of tests to make sure the moves work
int main() {
    // start from goalState
    // init: all 0's front, all 1's right, all 2's left, all 3's back, all 4's top, all 5's down
    Cube goal = Cube(true);

    runTest("U-movement", [&] {return testU(goal);});
    runTest("DoubleU-Movement", [&] {return testDoubleU(goal);});
    runTest("DoubleD-Movement", [&] {return testDoubleD(goal);});
    runTest("DoubleR-Movement", [&] {return testDoubleR(goal);});
    runTest("DoubleL-Movement", [&] {return testDoubleL(goal);});
    runTest("DoubleF-Movement", [&] {return testDoubleF(goal);});
    runTest("DoubleB-Movement", [&] {return testDoubleB(goal);});

    return 0;
}