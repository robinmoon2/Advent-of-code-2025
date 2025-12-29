#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>


using namespace std;


struct MatrixData {
    vector<vector<int>> rows;      // columns becames rows
    vector<char> operators;
};

MatrixData parseMatrix(const string& filename) {
    MatrixData data;
    ifstream file(filename);
    string line;
    vector<vector<int>> temp_columns;
    // read all line but not the last one
    while(getline(file, line)) {
        if(line.find_first_of("*+-/") != string::npos) {
            // operators line
            istringstream iss(line);
            char op;
            while(iss >> op) {
                if(op == '*' || op == '+' || op == '-' || op == '/') {
                    data.operators.push_back(op);
                }
            }
            break;
        }
        
        istringstream iss(line);
        int num;
        int col = 0;
        while(iss >> num) {
            if(col >= temp_columns.size()) {
                temp_columns.push_back(vector<int>());
            }
            temp_columns[col].push_back(num);
            col++;
        }
    }
    
    data.rows = temp_columns;
    
    file.close();
    return data;
}

int main() {
    MatrixData data = parseMatrix("Exercice6_input.txt");
    long long grand_total = 0;
    
    for(size_t i = 0; i < data.rows.size(); i++){
        vector<int> row = data.rows[i];
        long long total = row[0];

        
        for(size_t j = 1; j < row.size(); j++){
            cout << "  " << total << " " << data.operators[i] << " " << row[j];
            
            if(data.operators[i] == '*'){total = total * row[j];}
            else if(data.operators[i] == '+'){total = total + row[j];}
            else if(data.operators[i] == '-'){total = total - row[j];}
            else if(data.operators[i] == '/'){total = total / row[j];}
            
            cout << " = " << total << endl;
        }
        grand_total += total;
    }
    cout << "GRAND TOTAL: " << grand_total << endl;
    return 0;
}

