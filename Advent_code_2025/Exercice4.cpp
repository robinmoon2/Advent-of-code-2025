#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>


using namespace std;

vector<vector<char>> readInstructions(const string& filename) {
    vector<vector<char>> matrix;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return matrix;
    }

    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            vector<char> row;
            for (char c : line) {
                row.push_back(c);
            }
            matrix.push_back(row);
        }
    }
    
    file.close();
    return matrix;
}

int countAroundPosition(int x, int y, const vector<vector<char>>& matrix) {
    int count = 0;
    
    // check valid position
    if (y < 0 || y >= (int)matrix.size() || x < 0 || x >= (int)matrix[y].size()) {
        return 0;  
    }
    int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
    int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};

    for (int i = 0; i < 8; i++) {
        int newX = x + dx[i];
        int newY = y + dy[i];
        if (newY >= 0 && newY < (int)matrix.size() && 
            newX >= 0 && newX < (int)matrix[newY].size()) {
            
            if (matrix[newX][newY] == '@') {
                count++;
            }
        }
    }
    return count;
}



int main(){
    vector<vector<char>> matrix = readInstructions("Exercice4_input.txt");
    int total = 0;
    int removed = 1;
    while(removed!=0){
        removed = 0;
        for (size_t i = 0; i < matrix.size(); i++) {
            for (size_t j = 0; j < matrix[i].size(); j++) {
                char component = matrix[i][j];
                if(component =='@'){
                    int count = countAroundPosition(i,j,matrix);
                    if(count < 4){
                        removed++;
                        matrix[i][j] = 'X';
                    }
                }
            }
        }
        for (size_t i = 0; i < matrix.size(); i++) {
            for (size_t j = 0; j < matrix[i].size(); j++) {
                if(matrix[i][j] == 'X'){
                    matrix[i][j] = '.';
                }
            }
        }
        cout << "REMOVE :" <<removed <<endl;
        total+=removed;
    }
    cout << "TOTAL : "<<total << endl;
    cout << "REMOVE :" <<removed <<endl;
    return 0;
}