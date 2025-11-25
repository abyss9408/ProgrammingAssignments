#include "rubik_cube.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace chrono;

// Helper function to trim leading and trailing whitespace
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (string::npos == first) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

vector<string> splitSolution(const string& solution) {
    vector<string> moves;
    for (size_t i = 0; i < solution.length(); i++) {
        if (i + 1 < solution.length() && solution[i + 1] == '\'') {
            // Handle counter-clockwise moves (e.g., U', R')
            moves.push_back(solution.substr(i, 2));
            i++; // Skip the next character
        } else {
            // Handle clockwise moves (e.g., U, R)
            moves.push_back(string(1, solution[i]));
        }
    }
    return moves;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
      cerr << "Usage: " << argv[0] << " <filename>" << endl;
      return EXIT_FAILURE;
    }

    // Data import
    string filename = argv[1];
    ifstream testFile(filename);
    string line;
    string scrambledState;

    if (!testFile) {
      cerr << "Error: Could not open file " << filename << endl;
      return 0;
    }

    int lineNumber = 0;
    while (getline(testFile, line)) {
        lineNumber++;
        line = trim(line); // Trim whitespace

        // Skip empty lines and comment lines
        if (line.empty() || line[0] == '#') {
            continue;
        }

        if (scrambledState.empty()) {
            scrambledState = line;
        }  
    }

    // Time the cube solver
    auto start_time = high_resolution_clock::now();

    // Call cube solver
    string solution = solveCube(scrambledState);

    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time);
    
    // Output timing information
    cout << "Time taken to solve: " << duration.count() << " milliseconds" << endl;

    // Hint: Uncomment below to debug test case and raw solution.
    // cout << "scrambled state" << scrambledState << endl;
    // cout << solution << endl;

    // Output result
    if (solution == "") {
        cout << "Already solved, no need movement!" << endl; 
    } else if (solution == "No solution found") {
        cout << solution << endl;
    } else {
        cout << "Solution: " << solution << endl; // Solution: move sequences
    }

    // Hint: Uncomment below to verify solution. 
    // Need to add Cube structure declaration here. Trim separaters in move sequence.
    // if ((solution != "") && (solution != "No solution found")) {
    //     Cube cube;
    //     cube.state = scrambledState;
    //     vector<string> moves = splitSolution(solution);

    //     for (const string& move : moves) {
    //         if (move == "U") {
    //             cube.rotateUp();
    //             cout << "Applied Move: U" << endl;
    //         } else if (move == "U'") {
    //             cube.rotateUpCounter();
    //             cout << "Applied Move: U'" << endl;
    //         } else if (move == "D") {
    //             cube.rotateDown();
    //             cout << "Applied Move: D" << endl;
    //         } else if (move == "D'") {
    //             cube.rotateDownCounter();
    //             cout << "Applied Move: D'" << endl;
    //         } else if (move == "R") {
    //             cube.rotateRight();
    //             cout << "Applied Move: R" << endl;
    //         } else if (move == "R'") {
    //             cube.rotateRightCounter();
    //             cout << "Applied Move: R'" << endl;
    //         } else if (move == "L") {
    //             cube.rotateLeft();
    //             cout << "Applied Move: L" << endl;
    //         } else if (move == "L'") {
    //             cube.rotateLeftCounter();
    //             cout << "Applied Move: L'" << endl;
    //         } else if (move == "F") {
    //             cube.rotateFront();
    //             cout << "Applied Move: F" << endl;
    //         } else if (move == "F'") {
    //             cube.rotateFrontCounter();
    //             cout << "Applied Move: F'" << endl;
    //         } else if (move == "B") {
    //             cube.rotateBack();
    //             cout << "Applied Move: B" << endl;
    //         } else if (move == "B'") {
    //             cube.rotateBackCounter();
    //             cout << "Applied Move: B'" << endl;
    //         } else {
    //             cout << "Invalid Move: " << move << endl;
    //             return false;
    //         }
    //     }

    //     cout << "After solution: " << cube.state << endl;

    //     if (cube.isSolved()) {
    //         cout << "Cube solution is verified!" << endl;
    //     } else {
    //         cout << "Cube is not solved." << endl;
    //     }
    // }

    return 0;
}