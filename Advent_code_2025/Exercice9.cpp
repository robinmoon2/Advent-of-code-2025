#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>


using namespace std;


vector<pair<long long,long long>> read_positions(const string &filepath) {
    vector<pair<long long,long long>> positions;
    ifstream in(filepath);
    if (!in) {
        cerr << "Error: cannot open file '" << filepath << "'\n";
        return positions;
    }

    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        long long col, row;
        char comma;
        if ((ss >> col >> comma >> row) && comma == ',') {
            positions.emplace_back(col, row);
            continue;
        }

        replace(line.begin(), line.end(), ',', ' ');
        stringstream ss2(line);
        if (ss2 >> col >> row) {
            positions.emplace_back(col, row);
        } else {
            cerr << "Warning: could not parse line: '" << line << "'\n";
        }
    }

    return positions;
}

void print_positions(const vector<pair<long long,long long>> &positions) {
    for (const auto &p : positions) {
        cout << p.first << ',' << p.second << '\n';
    }
}



int main(int argc, char **argv){
    string filename = (argc > 1) ? argv[1] : "Exercice9_intput.txt";
    auto positions = read_positions(filename);
    cout << "Read " << positions.size() << " positions:\n";
    //print_positions(positions);

    long long max_surface = 0;
    for(size_t i = 0; i < positions.size(); ++i) {
        auto point1 = positions[i];
        for(size_t j = i + 1; j < positions.size(); ++j) {
            auto point2 = positions[j];
            long long dx = llabs(point1.first - point2.first);
            long long dy = llabs(point1.second - point2.second);
            long long surface = (dx + 1) * (dy + 1);
            if (surface > max_surface) max_surface = surface;
        }
    }
    cout << "MAX SURFACE  : "<< max_surface << endl;
    return 0;

}