#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>


using namespace std;

vector<string> readInstructions(const string& filename) {
    vector<string> instructions;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return instructions;
    }
    
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            instructions.push_back(line);
        }
    }
    file.close();
    return instructions;
}


int main(){
    vector<string> instructions = readInstructions("Exercice3_input.txt");
    int total = 0;
    for(int i=0; i<instructions.size();i++){
        string instruction = instructions[i];
        int max = 0;
        for(int j=0; j<instruction.length();j++){
            for(int k=j+1; k<instruction.length();k++){
                string input = "";
                input += instruction[j];
                input += instruction[k];
                if(stoi(input) > max){
                    max = stoi(input);
                }
            }
        }
        total+=max;
    }

    cout << "TOTAL : "<<total<<endl;
}