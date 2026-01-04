#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;



bool check_safe(vector<int> list){
    bool ascending = 0;
    bool descending = 0;
    bool safe = 1;
    for(int j=0; j<list.size()-1;j++){
        if(list[j] < list[j+1])
            ascending = 1;
        if(list[j] > list[j+1])
            descending = 1;
        if((abs(list[j] - list[j+1]) > 3) || (list[j] > list[j+1] && ascending) || (list[j] < list[j+1] && descending)|| list[j] == list[j+1]){
            safe = 0;
        }
    }
    return safe;
};



int main(){

    int total_safe_list = 0;
    vector<vector<int>> lists;

    string line;

    while(getline(cin,line)){

        if (line.empty()) break;                
        istringstream iss(line);
        int x;
        vector<int> v;
        while (iss >> x) {                        
            v.push_back(x);
        }
        lists.push_back(v);
    }

    for (size_t i = 0; i < lists.size(); ++i) {
        cout << "list " << i+1 << ":";
        for (int val : lists[i]) cout << ' ' << val;
        cout << '\n';
    }

    for(int i = 0 ; i< lists.size(); i++){
        vector<int> actual_list = lists[i];
        bool safe = check_safe(actual_list);
        if(safe){
            total_safe_list++;
        }
        else{
            for(int j= 0; j< actual_list.size();j++){
                vector<int> modified_list = actual_list;
                modified_list.erase(modified_list.begin() + j);
                safe = check_safe(modified_list);
                if(safe){
                    total_safe_list++;
                    j = actual_list.size();
                }
            }
        }
    }
    cout << "Number of safe lists :" << total_safe_list;
    return 0;
}

