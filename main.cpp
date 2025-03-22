#include <iostream>
#include <array>
#include <unordered_set>
#include "moves.cpp"
using namespace std;
// Rubik cube solver with bidirectional search


// bidirectional bfs:
void bidirectional_bfs() {
    ;
}

int main() {
    // unordered_set<array<int, NUMFACES>> seen;
    // keeps track of goal state
    // TODO: before checking if solved, align to the orientation of the fixed goal state
    array<int, NUMFACES> GOALSTATE = {}; 
    for (int i = 0; i < NUMFACES; i++) {
        GOALSTATE[i] = i / 9;
    }

    for (int f : GOALSTATE) {
        cout << f;
    }

    // keeps track of current state
    array<int, NUMFACES> CUBESTATE = {};
    // sample random cube state
    for (int i = 0; i < NUMFACES; i++) {
        CUBESTATE[i] = i % 6;
    }

    cout << "\n";

    for (int f : CUBESTATE) {
        cout << f;
    }
    }