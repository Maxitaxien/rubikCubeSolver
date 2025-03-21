#include <array>
#include <algorithm>
#include "consts.cpp"
using namespace std;
// move functions
// https://jperm.net/3x3/moves
// basic: up, down, right, left, front, back (clockwise)
// and corresponding prime versions for counterclockwise
// total = 18 = branching factor of search
array<int, 3> getRow(array<int, NUMFACES>& cubeState, int start) {
    return {cubeState[start], cubeState[start + 1], cubeState[start + 2]};
}

array<int, 3> getCol(array<int, NUMFACES>& cubeState, int start) {
    return {cubeState[start], cubeState[start + 3], cubeState[start + 6]};
}

void assignRow(array<int, NUMFACES>& cubeState, array<int, 3> row, int start) {
    cubeState[start] = row[0];
    cubeState[start + 1] = row[1];
    cubeState[start + 2] = row[2];
}

void assignCol(array<int, NUMFACES>& cubeState, array<int, 3> col, int start) {
    cubeState[start] = col[0];
    cubeState[start + 3] = col[1];
    cubeState[start + 6] = col[2];
}

void clockwiseRot(array<int, NUMFACES>& cubeState, int start) {
    // Hard-coded, but efficient
    array<int, 9> face = {
        cubeState[start + 6], cubeState[start + 3], cubeState[start],
        cubeState[start + 7], cubeState[start + 4], cubeState[start + 1],
        cubeState[start + 8], cubeState[start + 5], cubeState[start + 2]
    };
    for (int i = 0; i < 9; i++) {
        cubeState[start + i] = face[i];
    }
}

void cclockwiseRot(array<int, NUMFACES>& cubeState, int start) {
    // Again, hard-coded but efficient
    array<int, 9> face = {
        cubeState[start + 2], cubeState[start + 5], cubeState[start + 8],
        cubeState[start + 1], cubeState[start + 4], cubeState[start + 7],
        cubeState[start],     cubeState[start + 3], cubeState[start + 6]
    };
    for (int i = 0; i < 9; i++) {
        cubeState[start + i] = face[i];
    }
}

// used for F and B moves
void rotateFace(array<int, NUMFACES>& cubeState, int f1, int f2, int f3, int f4) {
    // TODO: Implement generalisable F-logic here
}

void moveRow(array<int, NUMFACES>& cubeState, int f1, int f2, int f3, int f4, int offset) {
    array<int, 3> temp = getRow(cubeState, f1 + offset); // store before writing over
    assignRow(cubeState, getRow(cubeState, f2 + offset), f1 + offset);
    assignRow(cubeState, getRow(cubeState, f3 + offset), f2 + offset);
    assignRow(cubeState, getRow(cubeState, f4 + offset), f3 + offset);
    assignRow(cubeState, temp, f4 + offset);
}

void moveCol(array<int, NUMFACES>& cubeState, int f1, int f2, int f3, int f4, int offset) {
    array<int, 3> temp = getCol(cubeState, f1 + offset);
    assignCol(cubeState, getCol(cubeState, f2 + offset), f1 + offset);
    assignCol(cubeState, getCol(cubeState, f3 + offset), f2 + offset);
    assignCol(cubeState, getCol(cubeState, f4 + offset), f3 + offset);
    assignCol(cubeState, temp, f4 + offset);
}

void U(array<int, NUMFACES>& cubeState) {
    moveRow(cubeState, FRONT, RIGHT, BACK, LEFT, 0);
    clockwiseRot(cubeState, TOP);
}

void D(array<int, NUMFACES>& cubeState) {
    moveRow(cubeState, FRONT, RIGHT, BACK, LEFT, 6);
    clockwiseRot(cubeState, DOWN);
}

void R(array<int, NUMFACES>& cubeState) {
    moveCol(cubeState, FRONT, DOWN, BACK, TOP, 3);
    clockwiseRot(cubeState, RIGHT);
}

void L(array<int, NUMFACES>& cubeState) {
    moveCol(cubeState, FRONT, TOP, BACK, DOWN, 0);
    clockwiseRot(cubeState, LEFT);
}

// when keeping our orientation constant, F and B would be a mix of
// moving columns and rows, so it's easier to hardcode them.
void F(array<int, NUMFACES>& cubeState) {
    array<int, 3> topRow = getRow(cubeState, TOP + 6);
    array<int, 3> rightCol = getCol(cubeState, RIGHT);
    array<int, 3> downRow = getRow(cubeState, DOWN);
    array<int, 3> leftCol = getCol(cubeState, LEFT + 3);

    // When swapping the columns around to a row,
    // the last element in the column array should be the first in the new row position
    // therefore, we reverse:
    reverse(rightCol.begin(), rightCol.end());
    reverse(leftCol.begin(), leftCol.end());

    assignRow(cubeState, leftCol, TOP + 6);
    assignCol(cubeState, topRow, RIGHT);
    assignRow(cubeState, rightCol, DOWN);
    assignCol(cubeState, downRow, LEFT + 3);
    
    clockwiseRot(cubeState, FRONT);
}

// TODO: implement other moves. should be copy-paste
void B(array<int, NUMFACES>& cubeState) {
    moveRow(cubeState, TOP, RIGHT, DOWN, LEFT, 0);
}

// p = prime, counterclockwise rotation
void U_p(array<int, NUMFACES>& cubeState) {
}

void D_p(array<int, NUMFACES>& cubeState) {
}

void R_p(array<int, NUMFACES>& cubeState) {
}

void L_p(array<int, NUMFACES>& cubeState) {
}

void F_p(array<int, NUMFACES>& cubeState) {
}

void B_p(array<int, NUMFACES>& cubeState) {
}

// slice moves: move middle layer clockwise (and counterclockwise for prime versions)
void M(array<int, NUMFACES>& cubeState) {
}

void E(array<int, NUMFACES>& cubeState) {
}

void S(array<int, NUMFACES>& cubeState) {
}

void M_p(array<int, NUMFACES>& cubeState) {
}

void F_p(array<int, NUMFACES>& cubeState) {
}

void B_p(array<int, NUMFACES>& cubeState) {
}
    