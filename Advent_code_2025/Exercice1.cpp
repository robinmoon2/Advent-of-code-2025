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

bool inInterval(int a, int b, int number){
    if(a < number  && number < b){
        cout << "A : "<< a << " Number : "<< number << " B :" << b << endl;
        return true;
    }
    return false;
}


int countZeroCrossings(int start, char dir, int d) {
    const int N = 100;
    int start_mod = ((start % N) + N) % N; // 0..99

    int first_k;
    if (dir == 'R') {
        if (start_mod == 0) first_k = 100;
        else                first_k = N - start_mod;
    } else { // 'L'
        if (start_mod == 0) first_k = 100;
        else                first_k = start_mod;
    }

    if (d < first_k) return 0;
    return 1 + (d - first_k) / N;
}



int main(){
    
    int actual_position = 50; 
    bool iszero = false;
    int passzero = 0;
    int password = 0;
    int pass_key = 0;
    
    vector<string> instructions = readInstructions("Ex1_input.txt");
    for(int i=0; i<instructions.size();i++){
        string instruction = instructions[i];
        int value = stoi(instruction.substr(1));
        char dir = instruction[0];
        int new_position;
        if( dir == 'R'){
            new_position = actual_position+value;
        }

        if(dir == 'L'){
            new_position = actual_position - value;
        }

        int hits = countZeroCrossings(actual_position,dir,value);
        password+=hits;

        actual_position = ((new_position % 100) + 100) % 100;
        cout << "actual position " << actual_position<< endl;

    }
    cout << "PASSWORD : "<< password << endl;
    cout << "PASSZEO : "<< passzero << endl;
    cout << "Final result : "<<password+passzero<<endl;

    return 0;
}