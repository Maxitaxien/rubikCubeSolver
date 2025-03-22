#include <array>
#include <algorithm>
#include "consts.cpp"
using namespace std;


// helper functions for moves
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
void rotateFace(array<int, NUMFACES>& cubeState, int f1, int f2, int f3, int f4, bool reverseCols) {
    array<int, 3> row1 = getRow(cubeState, f1); 
    array<int, 3> col1 = getCol(cubeState, f2); 
    array<int, 3> row2 = getRow(cubeState, f3); 
    array<int, 3> col2 = getCol(cubeState, f4); 

    // reversing either columns or rows depending on operation
    if (reverseCols) {
        reverse(col1.begin(), col1.end());
        reverse(col2.begin(), col2.end());
    }

    else {
        reverse(row1.begin(), row1.end());
        reverse(row2.begin(), row2.end());
    }


    assignRow(cubeState, col1, f1);
    assignCol(cubeState, row1, f2);
    assignRow(cubeState, col2, f3);
    assignCol(cubeState, row2, f4);
}

void moveRow(array<int, NUMFACES>& cubeState, int f1, int f2, int f3, int f4, int offset) {
    array<int, 3> temp = getRow(cubeState, f1 + offset); // store before writing over
    assignRow(cubeState, getRow(cubeState, f2 + offset), f1 + offset);
    assignRow(cubeState, getRow(cubeState, f3 + offset), f2 + offset);
    assignRow(cubeState, getRow(cubeState, f4 + offset), f3 + offset);
    assignRow(cubeState, temp, f4 + offset);
}

// can't have constant offset for column movement - 
// for instance, r moves the third columns of front, down and top, but first column of back
void moveCol(array<int, NUMFACES>& cubeState, int f1, int f2, int f3, int f4) {
    array<int, 3> temp = getCol(cubeState, f1);
    assignCol(cubeState, getCol(cubeState, f2), f1);
    assignCol(cubeState, getCol(cubeState, f3), f2);
    assignCol(cubeState, getCol(cubeState, f4), f3);
    assignCol(cubeState, temp, f4);
}

// move functions
// https://jperm.net/3x3/moves
// basic: up, down, right, left, front, back (clockwise)
// and corresponding prime versions for counterclockwise
// total = 18 = branching factor of search
void U(array<int, NUMFACES>& cubeState) {
    moveRow(cubeState, FRONT, RIGHT, BACK, LEFT, 0);
    clockwiseRot(cubeState, TOP);
}

void D(array<int, NUMFACES>& cubeState) {
    moveRow(cubeState, FRONT, RIGHT, BACK, LEFT, 6);
    clockwiseRot(cubeState, DOWN);
}

void R(array<int, NUMFACES>& cubeState) {
    moveCol(cubeState, FRONT + 3, DOWN + 3, BACK, TOP + 3);
    clockwiseRot(cubeState, RIGHT);
}

void L(array<int, NUMFACES>& cubeState) {
    moveCol(cubeState, FRONT, TOP, BACK + 3, DOWN);
    clockwiseRot(cubeState, LEFT);
}

// when keeping our orientation constant,
// F and B operations apply to both some rows and columns
void F(array<int, NUMFACES>& cubeState) {
    rotateFace(cubeState, TOP + 6, LEFT + 2, DOWN, RIGHT, true);
    clockwiseRot(cubeState, FRONT);
}

void B(array<int, NUMFACES>& cubeState) {
    rotateFace(cubeState, TOP, RIGHT + 2, DOWN + 6, LEFT, false);
    cclockwiseRot(cubeState, BACK);
}

// p = prime, counterclockwise rotation
void U_p(array<int, NUMFACES>& cubeState) {
    moveRow(cubeState, FRONT, LEFT, BACK, RIGHT, 0);
    cclockwiseRot(cubeState, TOP);
}

void D_p(array<int, NUMFACES>& cubeState) {
    moveRow(cubeState, FRONT, LEFT, BACK, RIGHT, 6);
    cclockwiseRot(cubeState, DOWN);
}

void R_p(array<int, NUMFACES>& cubeState) {
    moveCol(cubeState, FRONT + 3, TOP + 3, BACK, DOWN + 3);
    cclockwiseRot(cubeState, RIGHT);
}

void L_p(array<int, NUMFACES>& cubeState) {
    moveCol(cubeState, FRONT, DOWN, BACK + 3, TOP);
    cclockwiseRot(cubeState, LEFT);
}

void F_p(array<int, NUMFACES>& cubeState) {
    rotateFace(cubeState, TOP + 6, RIGHT, DOWN, LEFT + 2, false);
    cclockwiseRot(cubeState, FRONT);
}

void B_p(array<int, NUMFACES>& cubeState) {
    rotateFace(cubeState, TOP, LEFT, DOWN + 6, RIGHT + 2, true);
    clockwiseRot(cubeState, BACK);
}

// TODO: slice moves: move middle layer clockwise (and counterclockwise for prime versions)
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
    