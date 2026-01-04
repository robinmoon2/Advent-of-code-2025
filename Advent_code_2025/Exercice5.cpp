#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
using namespace std;

struct DocumentData {
    vector<pair<long long, long long>> ranges; 
    vector<long long> ids;
};

DocumentData readDocument(const string& filename) {
    DocumentData data;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return data;
    }

    string line;
    bool readingRanges = true;

    while (getline(file, line)) {
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        if (line.empty()) {
            readingRanges = false;
            continue;
        }

        if (readingRanges) {
            size_t dashPos = line.find('-');
            if (dashPos != string::npos) {
                try {
                    long long start = stoll(line.substr(0, dashPos));
                    long long end = stoll(line.substr(dashPos + 1));
                    data.ranges.push_back({start, end});
                } catch (const exception& e) {
                    cerr << "Error parsing range: " << line << endl;
                }
            }
        } else {
            try {
                data.ids.push_back(stoll(line));
            } catch (const exception& e) {
                cerr << "Error parsing ID: " << line << endl;
            }
        }
    }

    file.close();
    return data;
}

int main() {
    DocumentData data = readDocument("Exercice5_input.txt");
    int total = 0;

    for(size_t i=0; i<data.ids.size();i++){
        long long ID = data.ids[i];
        bool inrange = false;

        for(size_t j=0; j<data.ranges.size();j++){

            long long left = data.ranges[j].first;
            long long right = data.ranges[j].second;
            
            if(left <= ID && ID <=right){
                inrange=true;
                break;
            }
        }
        if(inrange){total++;}

    }
     vector<pair<long long, long long>> sorted_ranges = data.ranges;
    sort(sorted_ranges.begin(), sorted_ranges.end());

    long long total_unique = 0;
    long long left = sorted_ranges[0].first;
    long long right = sorted_ranges[0].second;

    for(size_t i=1; i<sorted_ranges.size(); i++){
        if(sorted_ranges[i].first <= right + 1){
            right = max(right, sorted_ranges[i].second);
        } else {
            total_unique += (right - left + 1);
            left = sorted_ranges[i].first;
            right = sorted_ranges[i].second;
        }
    }
    total_unique += (right - left + 1);
    
    cout << "TOTAL : "<<total <<endl;
    cout << "TOTAL PART 2 : "<< total_unique << endl;
    return 0;
}
