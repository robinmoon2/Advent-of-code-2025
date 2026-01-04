#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>


using namespace std;

struct RangePair {
    string left;
    string right;
    
    // Constructor
    RangePair(const string& l, const string& r) : left(l), right(r) {}
    
    void print() const {
        cout << "Left: " << left << ", Right: " << right << endl;
    }
};

vector<RangePair> parseRangeFile(const std::string& filename) {
    vector<RangePair> ranges;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cout << "Error: Cannot open file " << filename << endl;
        return ranges;
    }
    
    string line;
    string content;
    
    // Read entire file content
    while (std::getline(file, line)) {
        content += line;
    }
    file.close();
    
    // Parse the content
    stringstream ss(content);
    string token;
    
    // Split by comma
    while (getline(ss, token, ',')) {
        // Remove whitespace
        token.erase(0, token.find_first_not_of(" \t\n\r"));
        token.erase(token.find_last_not_of(" \t\n\r") + 1);
        
        if (token.empty()) continue;
        
        // Find the dash separator
        size_t dashPos = token.find('-');
        if (dashPos != std::string::npos) {
            string left = token.substr(0, dashPos);
            string right = token.substr(dashPos + 1);
            
            ranges.push_back(RangePair(left, right));
        }
    }
    return ranges;
}

bool isPattern(long long input){
    string str = to_string(input);
    int len = str.length();

    for (size_t patternLen = 1; patternLen <= len / 2; patternLen++) {
        // Check if the length is divisible by pattern length
        if (len % patternLen == 0) {
            std::string pattern = str.substr(0, patternLen);
            bool isValid = true;
            for (int i = patternLen; i < len; i += patternLen) {
                if (str.substr(i, patternLen) != pattern) {
                    isValid = false;
                    break;
                }
            }
            if (isValid) {
                return true; 
            }
        }
    }
    return false; 
}



int main(){
    vector<RangePair> list_instructions = parseRangeFile("Exercice2_input.txt");
    long long total_invalid = 0;
    for(int i=0; i<list_instructions.size();i++){
        RangePair instruction = list_instructions[i];
        instruction.print();
        string left = instruction.left;
        string right = instruction.right;

        for(long long j = stoll(left); j <= stoll(right); j++){
            string input = to_string(j);
            if(isPattern(j)){
                total_invalid+=j;
            }
        }
        
    }
    cout << "TOTAL : "<<total_invalid <<endl;
}