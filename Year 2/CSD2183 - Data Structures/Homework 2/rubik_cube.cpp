#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;

// Define the cube state as a string of 24 characters
// Use UFRBLD face notation (U1U2U3U4F1F2F3F4R1R2R3R4B1B2B3B4L1L2L3L4D1D2D3D4) 
struct Cube {
    string state;

    Cube() : state("WWWWRRRRGGGGYYYYOOOOBBBBB") {} // Initialized state

    // Check if the cube is solved (each face has all stickers of the same color)
    bool isSolved() const {
        // Check each face (6 faces, 4 stickers per face)
        for (int face = 0; face < 6; face++) {
            char color = state[face * 4];
            for (int i = 1; i < 4; i++) {
                if (state[face * 4 + i] != color) {
                    return false;
                }
            }
        }
        return true;
    }

    // Print the cube state in an explicit format
    void printExplicit() const {
            cout << "Up (U):    " << state[0] << ", " << state[1] << ", " << state[2] << ", " << state[3] << endl;
            cout << "Front (F): " << state[4] << ", " << state[5] << ", " << state[6] << ", " << state[7] << endl;
            cout << "Right (R): " << state[8] << ", " << state[9] << ", " << state[10] << ", " << state[11] << endl;
            cout << "Back (B):  " << state[12] << ", " << state[13] << ", " << state[14] << ", " << state[15] << endl;
            cout << "Left (L):  " << state[16] << ", " << state[17] << ", " << state[18] << ", " << state[19] << endl;
            cout << "Down (D):  " << state[20] << ", " << state[21] << ", " << state[22] << ", " << state[23] << endl;
        }

    // Rotate the up face clockwise (U)
    void rotateUp() {
        string newState = state;
        // Rotate the face stickers
        newState[0] = state[2]; // U1 <- U3
        newState[1] = state[0]; // U2 <- U1
        newState[2] = state[3]; // U3 <- U4
        newState[3] = state[1]; // U4 <- U2
        
        // Rotate adjacent stickers
        newState[4] = state[8]; // F1 <- R1
        newState[5] = state[9]; // F2 <- R2
        newState[8] = state[12]; // R1 <- B1
        newState[9] = state[13]; // R2 <- B2
        newState[12] = state[16]; // B1 <- L1
        newState[13] = state[17]; // B2 <- L2
        newState[16] = state[4]; // L1 <- F1
        newState[17] = state[5]; // L2 <- F2
        
        state = newState;
    }

    // Rotate the up face counter-clockwise (U')
    void rotateUpCounter() {
        string newState = state;
        // Rotate the face stickers
        newState[0] = state[1]; // U1 <- U2
        newState[1] = state[3]; // U2 <- U4
        newState[2] = state[0]; // U3 <- U1
        newState[3] = state[2]; // U4 <- U3
        
        // Rotate adjacent stickers
        newState[4] = state[16]; // F1 <- L1
        newState[5] = state[17]; // F2 <- L2
        newState[8] = state[4]; // R1 <- F1
        newState[9] = state[5]; // R2 <- F2
        newState[12] = state[8]; // B1 <- R1
        newState[13] = state[9]; // B2 <- R2
        newState[16] = state[12]; // L1 <- B1
        newState[17] = state[13]; // L2 <- B2
        
        state = newState;
    }

    // Rotate the down face clockwise (D)
    void rotateDown() {
        string newState = state;
        // Rotate the face stickers
        newState[20] = state[22]; // D1 <- D3
        newState[21] = state[20]; // D2 <- D1
        newState[22] = state[23]; // D3 <- D4
        newState[23] = state[21]; // D4 <- D2
        
        // Rotate adjacent stickers
        newState[6] = state[18];  // F3 <- L3
        newState[7] = state[19];  // F4 <- L4
        newState[10] = state[6];  // R3 <- F3
        newState[11] = state[7];  // R4 <- F4
        newState[14] = state[10]; // B3 <- R3
        newState[15] = state[11]; // B4 <- R4
        newState[18] = state[14]; // L3 <- B3
        newState[19] = state[15]; // L4 <- B4
        
        state = newState;
    }

    // Rotate the down face counter-clockwise (D')
    void rotateDownCounter() {
        string newState = state;
        // Rotate the face stickers
        newState[20] = state[21]; // D1 <- D2
        newState[21] = state[23]; // D2 <- D4
        newState[22] = state[20]; // D3 <- D1
        newState[23] = state[22]; // D4 <- D3
        
        // Rotate adjacent stickers
        newState[6] = state[10];  // F3 <- R3
        newState[7] = state[11];  // F4 <- R4
        newState[10] = state[14]; // R3 <- B3
        newState[11] = state[15]; // R4 <- B4
        newState[14] = state[18]; // B3 <- L3
        newState[15] = state[19]; // B4 <- L4
        newState[18] = state[6];  // L3 <- F3
        newState[19] = state[7];  // L4 <- F4
        
        state = newState;
    }

    // Rotate the left face clockwise (L)
    void rotateLeft() {
        string newState = state;
        // Rotate the face stickers
        newState[16] = state[18]; // L1 <- L3
        newState[17] = state[16]; // L2 <- L1
        newState[18] = state[19]; // L3 <- L4
        newState[19] = state[17]; // L4 <- L2
        
        // Rotate adjacent stickers
        newState[0] = state[15];   // U1 <- B4
        newState[2] = state[13];   // U3 <- B2
        newState[4] = state[0];  // F1 <- U1
        newState[6] = state[2];  // F3 <- U3
        newState[13] = state[22];  // B2 <- D3
        newState[15] = state[20];  // B4 <- D1
        newState[20] = state[4]; // D1 <- F1
        newState[22] = state[6]; // D3 <- F3
        
        state = newState;
    }

    // Rotate the left face counter-clockwise (L')
    void rotateLeftCounter() {
        string newState = state;
        // Rotate the face stickers
        newState[16] = state[17]; // L1 <- L2
        newState[17] = state[19]; // L2 <- L4
        newState[18] = state[16]; // L3 <- L1
        newState[19] = state[18]; // L4 <- L3
        
        // Rotate adjacent stickers
        newState[0] = state[4];   // U1 <- F1
        newState[2] = state[6];   // U3 <- F3
        newState[4] = state[20];  // F1 <- D1
        newState[6] = state[22];  // F3 <- D3
        newState[13] = state[2];  // B2 <- U3
        newState[15] = state[0];  // B4 <- U1
        newState[20] = state[15]; // D1 <- B4
        newState[22] = state[13]; // D3 <- B2
        
        state = newState;
    }

    // Rotate the right face (R)
    void rotateRight() {
        string newState = state;
        // Rotate the face stickers
        newState[8] = state[10]; // R1 <- R3
        newState[9] = state[8]; // R2 <- R1
        newState[10] = state[11]; // R3 <- R4
        newState[11] = state[9]; // R4 <- R2
        
        // Rotate adjacent stickers
        newState[1] = state[5];  // U2 <- F2
        newState[3] = state[7];  // U4 <- F4
        newState[5] = state[21];   // F2 <- D2
        newState[7] = state[23];   // F4 <- D4
        newState[12] = state[3]; // B1 <- U4
        newState[14] = state[1]; // B3 <- U2
        newState[20] = state[14];  // D2 <- B3
        newState[21] = state[12];  // D4 <- B1

        state = newState;
    }

    // Rotate the right face counter-clockwise (R')
    void rotateRightCounter() {
        string newState = state;
        // Rotate the face stickers
        newState[8] = state[9]; // R1 <- R2
        newState[9] = state[11]; // R2 <- R4
        newState[10] = state[8]; // R3 <- R1
        newState[11] = state[10]; // R4 <- R3
        
        // Rotate adjacent stickers
        newState[1] = state[14];  // U2 <- B3
        newState[3] = state[12];  // U4 <- B1
        newState[5] = state[1];   // F2 <- U2
        newState[7] = state[3];   // F4 <- U4
        newState[12] = state[23]; // B1 <- D4
        newState[14] = state[21]; // B3 <- D2
        newState[20] = state[5];  // D2 <- F2
        newState[21] = state[7];  // D4 <- F4
        
        state = newState;
    }

    // Rotate the front face closewise (F)
    void rotateFront() {
        string newState = state;
        // Rotate the face stickers
        newState[4] = state[6]; // F1 <- F3
        newState[5] = state[4]; // F2 <- F1
        newState[6] = state[7]; // F3 <- F4
        newState[7] = state[5]; // F4 <- F2
        
        // Rotate adjacent stickers
        newState[2] = state[19];   // U3 <- L4
        newState[3] = state[17];  // U4 <- L2
        newState[8] = state[2];  // R1 <- U3
        newState[10] = state[3]; // R3 <- U4
        newState[17] = state[20];  // L2 <- D1
        newState[19] = state[21];  // L4 <- D2
        newState[20] = state[10]; // D1 <- R3
        newState[21] = state[8]; // D2 <- R1
        
        state = newState;
    }

    // Rotate the front face counter-closewise (F')
    void rotateFrontCounter() {
        string newState = state;
        // Rotate the face stickers
        newState[4] = state[5]; // F1 <- F2
        newState[5] = state[7]; // F2 <- F4
        newState[6] = state[4]; // F3 <- F1
        newState[7] = state[6]; // F4 <- F3
        
        // Rotate adjacent stickers
        newState[2] = state[8];   // U3 <- R1
        newState[3] = state[10];  // U4 <- R3
        newState[8] = state[21];  // R1 <- D2
        newState[10] = state[20]; // R3 <- D1
        newState[17] = state[3];  // L2 <- U4
        newState[19] = state[2];  // L4 <- U3
        newState[20] = state[17]; // D1 <- L2
        newState[21] = state[19]; // D2 <- L4
        
        state = newState;
    }

    // Rotate the back face clockwise (B)
    void rotateBack() {
        string newState = state;
        // Rotate the face stickers
        newState[12] = state[14]; // B1 <- B3
        newState[13] = state[12]; // B2 <- B1
        newState[14] = state[15]; // B3 <- B4
        newState[15] = state[13]; // B4 <- B2
        
        // Rotate adjacent stickers
        newState[0] = state[9];  // U1 <- R2
        newState[1] = state[11];  // U2 <- R4
        newState[9] = state[23];   // R2 <- D4
        newState[11] = state[22];  // R4 <- D3
        newState[16] = state[1]; // L1 <- U2
        newState[18] = state[0]; // L3 <- U1
        newState[22] = state[16]; // D3 <- L1
        newState[23] = state[18];  // D4 <- L3

        state = newState;
    }

    // Rotate the back face counter-clockwise (B')
    void rotateBackCounter() {
        string newState = state;
        // Rotate the face stickers
        newState[12] = state[13]; // B1 <- B2
        newState[13] = state[15]; // B2 <- B4
        newState[14] = state[12]; // B3 <- B1
        newState[15] = state[14]; // B4 <- B3
        
        // Rotate adjacent stickers
        newState[0] = state[18];  // U1 <- L3
        newState[1] = state[16];  // U2 <- L1
        newState[9] = state[0];   // R2 <- U1
        newState[11] = state[1];  // R4 <- U2
        newState[16] = state[22]; // L1 <- D3
        newState[18] = state[23]; // L3 <- D4
        newState[22] = state[11]; // D3 <- R4
        newState[23] = state[9];  // D4 <- R2
        
        state = newState;
    }

    void print() const {
        cout << "Cube State: " << state << endl;
    }
};

// BFS to solve the cube
string solveCube(const string& scrambledState) {
    // Start state
    Cube start;
    start.state = scrambledState;

    if (start.isSolved())
    {
        return "";
    }
    
    // Define queue for BFS
    queue<pair<Cube, string>> q; // pair(cube state, move path)
    q.push({start, ""});

    unordered_map<string, bool> visited;
    visited[start.state] = true;

    // Define moves and corresponding functions
    vector<pair<string, void (Cube::*)()>> moves = {
        {"U", &Cube::rotateUp},
        {"U'", &Cube::rotateUpCounter},
        {"D", &Cube::rotateDown},
        {"D'", &Cube::rotateDownCounter},
        {"L", &Cube::rotateLeft},
        {"L'", &Cube::rotateLeftCounter},
        {"R", &Cube::rotateRight},
        {"R'", &Cube::rotateRightCounter},
        {"F", &Cube::rotateFront},
        {"F'", &Cube::rotateFrontCounter},
        {"B", &Cube::rotateBack},
        {"B'", &Cube::rotateBackCounter}
    };

    while (!q.empty()) {
        // Pop the front of the queue
        Cube currentCube = q.front().first;
        string currentPath = q.front().second;
        q.pop();
        
        // Debug output
        // cout << "pop state: " << currentCube.state << endl;
        // cout << "pop path: " << currentPath << endl;

        // If the cube is solved, return the path
        if (currentCube.isSolved()) {
            return currentPath;
        }

        // Try all possible moves
        for (const auto& move : moves) {
            Cube nextCube = currentCube;
            (nextCube.*move.second)(); // Apply the move
            
            // If this state hasn't been visited, add it to the queue
            if (visited.find(nextCube.state) == visited.end()) {
                visited[nextCube.state] = true;
                q.push({nextCube, currentPath + move.first});
            }
        }
    }

    return "No solution found";
}