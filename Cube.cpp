#include <array>
#include <iostream>
#include "moves.cpp"
class Cube {
public:
    std::array<int, NUMFACES> state;

    Cube (bool goal = false) {
        // this cube initiates to goal state
        if (goal) {
            for (int i = 0; i < NUMFACES; i++) {
                state[i] = i / 9;
            }
        }
        else { // creates random face
            for (int i = 0; i < NUMFACES; i++) {
                state[i] = i % 6;
            }
        }
    }

    explicit Cube (const std::array<int, NUMFACES>& s) : state(s) {}

    bool operator==(const Cube& other) const {
        return state == other.state;
    }

    struct Hash {
        std::size_t operator()(const Cube& cube) const {
            std::size_t h = 0;
            for (int face : cube.state)
                h = h * 31 + face;
            return h;
        }
    };

    void displayCube() {
        for (int f: state) {
            std::cout << f;
        }
    }
};