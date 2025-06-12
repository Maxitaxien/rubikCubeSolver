#include <array>
#include <algorithm>
#include "consts.cpp"


// helper functions for moves
std::array<int, 3> getRow(std::array<int, NUMFACES>& cubeState, int start) {
    return {cubeState[start], cubeState[start + 1], cubeState[start + 2]};
}

std::array<int, 3> getCol(std::array<int, NUMFACES>& cubeState, int start) {
    return {cubeState[start], cubeState[start + 3], cubeState[start + 6]};
}

void assignRow(std::array<int, NUMFACES>& cubeState, std::array<int, 3> row, int start) {
    cubeState[start] = row[0];
    cubeState[start + 1] = row[1];
    cubeState[start + 2] = row[2];
}

void assignCol(std::array<int, NUMFACES>& cubeState, std::array<int, 3> col, int start) {
    cubeState[start] = col[0];
    cubeState[start + 3] = col[1];
    cubeState[start + 6] = col[2];
}

void clockwiseRot(std::array<int, NUMFACES>& cubeState, int start) {
    // Hard-coded, but efficient
    std::array<int, 9> face = {
        cubeState[start + 6], cubeState[start + 3], cubeState[start],
        cubeState[start + 7], cubeState[start + 4], cubeState[start + 1],
        cubeState[start + 8], cubeState[start + 5], cubeState[start + 2]
    };
    for (int i = 0; i < 9; i++) {
        cubeState[start + i] = face[i];
    }
}

void cclockwiseRot(std::array<int, NUMFACES>& cubeState, int start) {
    // Again, hard-coded but efficient
    std::array<int, 9> face = {
        cubeState[start + 2], cubeState[start + 5], cubeState[start + 8],
        cubeState[start + 1], cubeState[start + 4], cubeState[start + 7],
        cubeState[start],     cubeState[start + 3], cubeState[start + 6]
    };
    for (int i = 0; i < 9; i++) {
        cubeState[start + i] = face[i];
    }
}

// used for F and B moves
void rotateFace(std::array<int, NUMFACES>& cubeState, int f1, int f2, int f3, int f4, bool reverseCols) {
    std::array<int, 3> row1 = getRow(cubeState, f1); 
    std::array<int, 3> col1 = getCol(cubeState, f2); 
    std::array<int, 3> row2 = getRow(cubeState, f3); 
    std::array<int, 3> col2 = getCol(cubeState, f4); 

    // reversing either columns or rows depending on operation
    if (reverseCols) {
        std::reverse(col1.begin(), col1.end());
        std::reverse(col2.begin(), col2.end());
    }

    else {
        std::reverse(row1.begin(), row1.end());
        std::reverse(row2.begin(), row2.end());
    }


    assignRow(cubeState, col1, f1);
    assignCol(cubeState, row1, f2);
    assignRow(cubeState, col2, f3);
    assignCol(cubeState, row2, f4);
}

void moveRow(std::array<int, NUMFACES>& cubeState, int f1, int f2, int f3, int f4, int offset) {
    std::array<int, 3> temp = getRow(cubeState, f1 + offset); // store before writing over
    assignRow(cubeState, getRow(cubeState, f2 + offset), f1 + offset);
    assignRow(cubeState, getRow(cubeState, f3 + offset), f2 + offset);
    assignRow(cubeState, getRow(cubeState, f4 + offset), f3 + offset);
    assignRow(cubeState, temp, f4 + offset);
}

// can't have constant offset for column movement - 
// for instance, r moves the third columns of front, down and top, but first column of back
void moveCol(std::array<int, NUMFACES>& cubeState, int f1, int f2, int f3, int f4) {
    std::array<int, 3> temp = getCol(cubeState, f1);
    assignCol(cubeState, getCol(cubeState, f2), f1);
    assignCol(cubeState, getCol(cubeState, f3), f2);
    assignCol(cubeState, getCol(cubeState, f4), f3);
    assignCol(cubeState, temp, f4);
}

// move functions
// https://jperm.net/3x3/moves
// basic: up, down, right, left, front, back (clockwise)
// and corresponding prime versions for counterclockwise
// total = 12 = branching factor of search
// can be extended to 18 with mid moves, but let's try without first
std::array<int, NUMFACES> U(const std::array<int, NUMFACES>& cubeState) {
    std::array<int, NUMFACES> newCube = cubeState;
    moveRow(newCube, FRONT, RIGHT, BACK, LEFT, 0);
    clockwiseRot(newCube, TOP);
    return newCube;
}

std::array<int, NUMFACES> D(const std::array<int, NUMFACES>& cubeState) {
    std::array<int, NUMFACES> newCube = cubeState;
    moveRow(newCube, FRONT, RIGHT, BACK, LEFT, 6);
    clockwiseRot(newCube, DOWN);
    return newCube;
}

std::array<int, NUMFACES> R(const std::array<int, NUMFACES>& cubeState) {
    std::array<int, NUMFACES> newCube = cubeState;
    moveCol(newCube, FRONT + 3, DOWN + 3, BACK + 6, TOP + 3);
    clockwiseRot(newCube, RIGHT);
    return newCube;
}

std::array<int, NUMFACES> L(const std::array<int, NUMFACES>& cubeState) {
    std::array<int, NUMFACES> newCube = cubeState;
    moveCol(newCube, FRONT, TOP, BACK + 3, DOWN);
    clockwiseRot(newCube, LEFT);
    return newCube;
}

// when keeping our orientation constant,
// F and B operations apply to both some rows and columns
std::array<int, NUMFACES> F(const std::array<int, NUMFACES>& cubeState) {
    std::array<int, NUMFACES> newCube = cubeState;
    rotateFace(newCube, TOP + 6, LEFT + 2, DOWN, RIGHT, true);
    clockwiseRot(newCube, FRONT);
    return newCube;
}

std::array<int, NUMFACES> B(const std::array<int, NUMFACES>& cubeState) {
    std::array<int, NUMFACES> newCube = cubeState;
    rotateFace(newCube, TOP, RIGHT + 2, DOWN + 6, LEFT, false);
    cclockwiseRot(newCube, BACK);
    return newCube;
}

// p = prime, counterclockwise rotation
std::array<int, NUMFACES> U_p(const std::array<int, NUMFACES>& cubeState) {
    std::array<int, NUMFACES> newCube = cubeState;
    moveRow(newCube, FRONT, LEFT, BACK, RIGHT, 0);
    cclockwiseRot(newCube, TOP);
    return newCube;
}

std::array<int, NUMFACES> D_p(const std::array<int, NUMFACES>& cubeState) {
    std::array<int, NUMFACES> newCube = cubeState;
    moveRow(newCube, FRONT, LEFT, BACK, RIGHT, 6);
    cclockwiseRot(newCube, DOWN);
    return newCube;
}

std::array<int, NUMFACES> R_p(const std::array<int, NUMFACES>& cubeState) {
    std::array<int, NUMFACES> newCube = cubeState;
    moveCol(newCube, FRONT + 3, TOP + 3, BACK + 6, DOWN + 3);
    cclockwiseRot(newCube, RIGHT);
    return newCube;
}

std::array<int, NUMFACES> L_p(const std::array<int, NUMFACES>& cubeState) {
    std::array<int, NUMFACES> newCube = cubeState;
    moveCol(newCube, FRONT, DOWN, BACK + 3, TOP);
    cclockwiseRot(newCube, LEFT);
    return newCube;
}

std::array<int, NUMFACES> F_p(const std::array<int, NUMFACES>& cubeState) {
    std::array<int, NUMFACES> newCube = cubeState;
    rotateFace(newCube, TOP + 6, RIGHT, DOWN, LEFT + 2, false);
    cclockwiseRot(newCube, FRONT);
    return newCube;
}

std::array<int, NUMFACES> B_p(const std::array<int, NUMFACES>& cubeState) {
    std::array<int, NUMFACES> newCube = cubeState;
    rotateFace(newCube, TOP, LEFT, DOWN + 6, RIGHT + 2, true);
    clockwiseRot(newCube, BACK);
    return newCube;
}

/* slice moves: move middle layer clockwise (and counterclockwise for prime versions)
currently not implemented, as they are not necessary to solve a cube, but can be added for full functionality
void M(array<int, NUMFACES>& cubeState) {
}

void E(array<int, NUMFACES>& cubeState) {
}

void S(array<int, NUMFACES>& cubeState) {
}

void M_p(array<int, NUMFACES>& cubeState) {
}

void E_p(array<int, NUMFACES>& cubeState) {
}

void S_p(array<int, NUMFACES>& cubeState) {
}
*/

using MoveFunc = std::array<int, NUMFACES> (*)(const std::array<int, NUMFACES>&);
std::vector<MoveFunc> moveList = {U, R, F, D, L, B, U_p, R_p, F_p, D_p, L_p, B_p};
