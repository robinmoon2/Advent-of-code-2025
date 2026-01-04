#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility> 
#include <map>
#include <sstream>

using namespace std;

map<int, vector<int>> rules;

map<int,vector<int>> readRules(const std::string& filename,map<int,vector<int>> rules) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return rules;
    }
    
    int left, right;
    char delimiter;
    while (file >> left >> delimiter >> right) {
        rules[left].push_back(right);
        std::cout << "Left: " << left << ", Right: " << right << std::endl;
    }
    
    file.close();
    return rules;
}

vector<vector<int>> readUpdate(const std::string& filename){
    std::ifstream file(filename);
    vector<vector<int>> updates;
    if(!file.is_open()){
        std::cerr <<"Could not open file"<<filename << std::endl;
    }
    else{
        string line;
        while(std::getline(file,line)){
            if (line.empty()) continue;  // Skip empty lines
        
            std::vector<int> update;
            std::stringstream ss(line);
            std::string number;
            
            while (std::getline(ss, number, ',')) {
                update.push_back(std::stoi(number));
                std::cout << number << " ";
            }
            std::cout << " "<<std::endl;
            updates.push_back(update);
        }
    }
    return updates;
}

int main(){
    rules = readRules("rules_ex5.txt",rules);
    vector<vector<int>> updates = readUpdate("update5.txt");
    int total = 0;
    int total_not = 0;
    for(int i=0; i<updates.size();i++){
        vector<int> line = updates[i];
        bool clean = true;
        int middle_page_number = line[line.size()/2];

        for(int j =0; j<line.size();j++){

            int index = line[j];
            auto rule = rules.find(index);
            vector<int> index_rule = rule->second; //rules for the actual position

            for(int k=0; k<j;k++){ // each position before
                for(int g = 0; g<index_rule.size();g++){
                    if(line[k] == index_rule[g]){
                        int a = line[k];
                        line[k] == line[j];
                        line[j] == a;
                        clean = false;
                        cout << "REPLACE " << line[k] << " BY " <<line[j] <<endl;
                    }
                }
            }
        }
        cout << endl;
        if(clean)
            total+=middle_page_number;
        else{
            middle_page_number = line[(line.size()/2) - 1];
            cout << "middle " << middle_page_number<< endl;
            total_not+=middle_page_number;}
    }

    cout << "TOTAL :"<< total <<endl;
    cout << "TOTAL NOT :"<< total_not <<endl;

    return 0;
}