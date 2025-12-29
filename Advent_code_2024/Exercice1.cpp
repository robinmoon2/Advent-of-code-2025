#include <vector>
#include <iostream>
#include <algorithm>

int main(){

    using namespace std;

    int length_list = 1000;
    int global_distance = 0;
    int similarity_score = 0;

    vector<int> left;
    vector<int> right;

    for(int i=0; i<length_list;i++){
        int x,y;
        cin >> x >> y;
        left.push_back(x);
        right.push_back(y);
    }
    sort(left.begin(), left.end());
    sort(right.begin(),right.end());
    
    

    for(int i=0; i<length_list;i++){
        global_distance+=abs(left[i] - right[i]);
    }

    for(int i=0; i<length_list;i++){
        int target = left[i];
        int similarity = 0;
        for(int j=0; j<length_list;j++){
            if(target == right[j]){
                similarity++;
            }
        }
        similarity_score += target*similarity;
    }
    cout << "distance globale : " << global_distance <<endl;
    cout << "similarity score : " << similarity_score <<endl;

    return 0;
}