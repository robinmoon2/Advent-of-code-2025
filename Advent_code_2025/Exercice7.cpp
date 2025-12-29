#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>


using namespace std;

struct MatrixData {
    vector<vector<char>> rows;      // columns becames rows
    vector<char> beams;
};

MatrixData readInstructions(const string& filename) {
    vector<vector<char>> matrix;
    vector<char> beams;
    MatrixData data = {matrix, beams};
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return data;
    }

    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            vector<char> row;
            for (char c : line) {
                row.push_back(c);
            }
            data.rows.push_back(row);
            data.beams.push_back('.');
        }
    }
    
    file.close();
    return data;
}


int main(){
    MatrixData data = readInstructions("Exercice7_input.txt");
    int total = 0;
    for(int i=0; i<data.rows.size(); i++){
        for(int j=0; j< data.rows[i].size();j++){
            char c = data.rows[i][j];
            cout << c << " ";
        }
        cout << endl;
    }

    // First beam
    for(int j=0; j<data.rows[0].size(); j++){
        if(data.rows[0][j] == 'S'){
            data.beams[j] = '|';
            break;
        }
    }

    for(int i=0; i<data.rows.size()-1; i++){
        for(int j=0; j<data.rows[i].size(); j++){
            char component = data.rows[i][j];
            if(data.beams[j] == '|'){
                if(component == '^'){
                    if(j > 0){
                        data.beams[j-1] = '|';
                    }
                    if(j < data.rows[i].size()-1){
                        data.beams[j+1] = '|';
                    }
                    total++;
                    data.beams[j] = '.';
                }
            }
        }
        
        // Afficher les rayons sur la prochaine ligne
        if(i < data.rows.size()-1){
            for(int j=0; j<data.rows[i+1].size(); j++){
                if(data.beams[j] == '|' && data.rows[i+1][j] == '.'){
                    data.rows[i+1][j] = '|';
                }
                else if(data.beams[j] == '|' && data.rows[i+1][j] == '^'){

                    if(j > 0 && data.rows[i+1][j-1] == '.'){
                        data.rows[i+1][j-1] = '|';
                    }
                    if(j < data.rows[i+1].size()-1 && data.rows[i+1][j+1] == '.'){
                        data.rows[i+1][j+1] = '|';
                    }
                }
            }
        }
    }
    
    cout << endl;
    cout << endl;
    
    for(int i=0; i<data.rows.size(); i++){
        for(int j=0; j< data.rows[i].size();j++){
            char c = data.rows[i][j];
            cout << c << " ";
        }
        cout << endl;
    }

    cout << "\n TOTAL DIFRACTION " << total << endl;
    
    return 0;
}
