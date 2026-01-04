#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
    vector<string> matrix;
    string line;

    cout << "Enter the input" << endl;

    while(cin >> line){
        matrix.push_back(line);
    }

    cout << "Matrix: " << endl;
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }

    // Analyze the matrix 
    int total_word = 0;
    string word = "XMAS";
    
    // 8 directions: N, NE, E, SE, S, SW, W, NW
    int di[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int dj[8] = {0, 1, 1, 1, 0, -1, -1, -1};

    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            // For each position, try all 8 directions
            for(int dir = 0; dir < 8; dir++){
                bool found = true;
                
                // Check if we can spell "XMAS" in this direction
                for(int k = 0; k < word.length(); k++){
                    int x = i + k * di[dir];
                    int y = j + k * dj[dir];
                    
                    // Check bounds
                    if(x < 0 || x >= matrix.size() || y < 0 || y >= matrix[x].size()){
                        found = false;
                        break;
                    }
                    // Check if character matches
                    if(matrix[x][y] != word[k]){
                        found = false;
                        break;
                    }
                }
                if(found){
                    total_word++;
                }
            }
        }
    }
    
    cout << "Nombre de mots : " << total_word << endl;
    return 0;
}