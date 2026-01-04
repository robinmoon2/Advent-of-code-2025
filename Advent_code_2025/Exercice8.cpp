#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <string>
#include <map>

using namespace std;

struct Point {
    int x, y, z;
};

struct Edge {
    int u, v;
    double dist;
    Point pu, pv;
    
    bool operator<(const Edge& other) const {
        return dist < other.dist;
    }
};

class UnionFind {
private:
    vector<int> parent;
    vector<int> size;
    
public:
    UnionFind(int n) : parent(n), size(n, 1) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        
        if (px == py) return false;
        
        if (size[px] < size[py]) {
            parent[px] = py;
            size[py] += size[px];
        } else {
            parent[py] = px;
            size[px] += size[py];
        }
        return true;
    }
    
    vector<int> getComponentSizes() {
        map<int, int> components;
        for (int i = 0; i < parent.size(); i++) {
            components[find(i)]++;
        }
        
        vector<int> sizes;
        for (auto& p : components) {
            sizes.push_back(p.second);
        }
        return sizes;
    }
};

double distance(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    double dz = a.z - b.z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}




int main() {
    ifstream infile("Exercice8_input.txt");
    if (!infile) {
        cerr << "Error: Cannot open input.txt" << endl;
        return 1;
    }
    
    vector<Point> points;
    string line;
    
    while (getline(infile, line)) {
        if (line.empty()) continue;
        Point p;
        sscanf(line.c_str(), "%d,%d,%d", &p.x, &p.y, &p.z);
        points.push_back(p);
    }
    
    infile.close();
    
    int n = points.size();
    cout << "Read " << n << " junction boxes" << endl;
    
    int targetEdges = (n == 20) ? 10 : 1000;
    cout << "Target edges to process: " << targetEdges << endl;
    
    // Generate all edges
    vector<Edge> edges;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            Edge e;
            e.u = i;
            e.v = j;
            e.pu = points[i];
            e.pv = points[j];
            e.dist = distance(points[i], points[j]);
            edges.push_back(e);
        }
    }
    
    cout << "Generated " << edges.size() << " edges" << endl;
    
    // Sort edges by distance
    sort(edges.begin(), edges.end());
    
    // Union-Find
    UnionFind uf(n);
    
    int successfulConnections = 0;
    
    if (n == 20) {
        cout << "\nConnection details:" << endl;
    }
    
    // Process the first targetEdges edges
    for (int i = 0; i < targetEdges && i < edges.size(); i++) {
        const Edge& e = edges[i];
        bool connected = uf.unite(e.u, e.v);
        
        if (n == 20) {
            cout << "Edge " << (i+1) << ": (" << e.pu.x << "," << e.pu.y << "," << e.pu.z << ") - "
                 << "(" << e.pv.x << "," << e.pv.y << "," << e.pv.z << ") "
                 << "(dist=" << e.dist << ") ";
            if (connected) {
                cout << "CONNECTED";
                successfulConnections++;
            } else {
                cout << "SKIPPED";
            }
            cout << endl;
        } else if (connected) {
            successfulConnections++;
        }
    }
    
    cout << "\nProcessed " << targetEdges << " edges" << endl;
    cout << "Made " << successfulConnections << " successful connections" << endl;
    
    // Get component sizes
    vector<int> sizes = uf.getComponentSizes();
    
    cout << "Number of circuits: " << sizes.size() << endl;
    
    sort(sizes.begin(), sizes.end(), greater<int>());
    
    cout << "Circuit sizes: ";
    for (int s : sizes) {
        cout << s << " ";
    }
    cout << endl;
    
    cout << "Three largest circuits: " << sizes[0] << ", " << sizes[1] << ", " << sizes[2] << endl;
    
    long long result = (long long)sizes[0] * sizes[1] * sizes[2];
    
    cout << "Answer: " << result << endl;
    
    return 0;
}
