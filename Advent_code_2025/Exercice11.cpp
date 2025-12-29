#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

struct Node {
    string name;
    vector<int> next;
};

vector<Node> nodes;

/* find node index by name, create if not exists */
int get_index(const string &name) {
    for (size_t i = 0; i < nodes.size(); ++i) {
        if (nodes[i].name == name)
            return i;
    }
    Node n;
    n.name = name;
    nodes.push_back(n);
    return nodes.size() - 1;
}

/* DFS path counting */
long long count_paths(int u) {
    if (nodes[u].name == "out")
        return 1;

    long long total = 0;
    for (int v : nodes[u].next) {
        total += count_paths(v);
    }
    return total;
}

/* Read graph from file */
void read_graph(const string &filepath) {
    ifstream in(filepath);
    if (!in) {
        cerr << "Error: cannot open file '" << filepath << "'\n";
        return;
    }

    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;

        int colon = line.find(':');
        if (colon == string::npos) continue;

        string from = line.substr(0, colon);
        string rest = line.substr(colon + 1);

        stringstream ss(rest);
        string to;

        int from_idx = get_index(from);
        while (ss >> to) {
            int to_idx = get_index(to);
            nodes[from_idx].next.push_back(to_idx);
        }
    }
}

int main(int argc, char **argv) {
    string filename = "Exercice11_input.txt";
    read_graph(filename);

    int start = -1;
    for (size_t i = 0; i < nodes.size(); ++i) {
        if (nodes[i].name == "you") {
            start = i;
            break;
        }
    }

    if (start == -1) {
        cerr << "Error: 'you' not found\n";
        return 1;
    }

    long long result = count_paths(start);
    cout << "NUMBER OF PATHS : " << result << endl;

    return 0;
}
