#include <unordered_set>
#include <queue>
#include "Cube.cpp"
const int AMNTMOVES = 12;
// Rubik cube solver with bidirectional search

// bidirectional bfs:
bool bidirectional_bfs(const Cube& start, const Cube& goal) {
    std::unordered_set<Cube, Cube::Hash> visitedStart, visitedGoal;
    std::queue<Cube> qStart, qGoal;

    visitedStart.insert(start);
    visitedGoal.insert(goal);
    qStart.push(start);
    qGoal.push(goal);

    int C = 0;

    while (!qStart.empty() && !qGoal.empty() && C < 100) {
        Cube s = qStart.front();
        qStart.pop();

        Cube g = qGoal.front();
        qGoal.pop();


        for (auto& move : moveList) {
            Cube newSCube = Cube(move(s.state));

            Cube newGCube = Cube( move(g.state));

            if (newSCube == newGCube) {
                return true;
            }
            if (visitedStart.find(newSCube) == visitedStart.end()) {
                qStart.push(newSCube);
                visitedStart.insert(newSCube);
            }
            if (visitedGoal.find(newGCube) == visitedGoal.end()) {
                qGoal.push(newGCube);
                visitedGoal.insert(newGCube);
            }
        }
        C++;
    }
    std::cout << "\n";

    qStart.front().displayCube();
    std::cout << "\n";

    qGoal.front().displayCube();
    std::cout << "\n";

    return false;
}

int main() {
    // unordered_set<array<int, NUMFACES>> seen;
    // keeps track of goal state
    // TODO: Goal state and start state should have same orientation.

    // cube objects
    Cube start = Cube();
    Cube goal = Cube(true);

    start.displayCube();
    std::cout << "\n";
    goal.displayCube();
    std::cout << "\n";

    if (bidirectional_bfs(start, goal)) {
        std::cout << "Success!";
    }
    else {
        std::cout << ":((";
    }
    }