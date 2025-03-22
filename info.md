# Rubik Cube Solver Project

## Cube representation

- I have chosen to represent the cube in a 54-sized array, where each set of 9 entries
correspond to a face.
- If we imagine looking right at the cube, the following are the entries.

They go row by row - first three entries is row 1, next three is row 2 and final are last row. This is chosen

1. First 9 entries are the ones we look at.
2. Second 9 entries are the ones to the right.
3. Third 9 entries are the ones to the left.
4. Fourth 9 entries are the ones on the back.
5. Fifth 9 entries are the ones on the top.
6. Sixth 9 entries are the ones on the bottom.